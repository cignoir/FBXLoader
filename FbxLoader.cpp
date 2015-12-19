#include "FbxLoader.h"
#include "Skeleton.h"

//RAII
class C_FbxManager {
	struct S_Deleter {
		void operator()(FbxObject* ptr) {
			if (ptr) {
				ptr->Destroy();
			}
		}
		void operator()(FbxManager* ptr) {
			if (ptr) {
				ptr->Destroy();
			}
		}
	};

	std::unique_ptr<FbxManager, S_Deleter>	m_p_manager;

public:
	using FbxScenePtr = std::unique_ptr<FbxScene, S_Deleter>;
	using FbxImporterPtr = std::unique_ptr<FbxImporter, S_Deleter>;
	C_FbxManager() : 
		m_p_manager(FbxManager::Create())
	{};

	FbxScenePtr CreateScene(const char* name) {
		return FbxScenePtr(FbxScene::Create(this->m_p_manager.get(), name));
	}
	FbxImporterPtr CreateImporter(const char * name) {
		return FbxImporterPtr(FbxImporter::Create(this->m_p_manager.get(),name));
	}

	FbxManager* operator->() { return this->m_p_manager.get(); }
	FbxManager* get() { return this->m_p_manager.get(); }
};

//プロトタイプ宣言
using Vertices = std::vector<S_VertexPUNTBW>;
using AnimeSceneNodeDictionary = std::unordered_map<std::string, int>;
void AddInverseBasePoseMatricesToSkeleton(SkeletonPtr p_skeleton, FbxMesh* p_fbx_mesh);
SkeletonPtr GetSkeleton(FbxScene* p_scene);
MeshesPtr GetMeshes(FbxScene* p_scene, SkeletonPtr p_skeleton);
MeshPtr CreateMesh(FbxMesh* p_fbx_mesh, SkeletonPtr p_skeleton);
MaterialPtr GetMeshMaterial(FbxMesh* p_fbx_mesh);
void GetSkeleton(SkeletonPtr p_skeleton, BonePtr p_parent_bone, FbxNode* root_node);
void AddAnimationMatricesToSkeleton(FbxScene* p_scene, AnimeSceneNodeDictionary& dic, SkeletonPtr p_skeleton, int end_frame);
void AddBlendShapeMeshes(FbxMesh* p_fbx_mesh,MeshPtr p_mesh, SkeletonPtr p_skeleton);
/**

*	@brief	頂点が保持する要素のインデックスを保持する構造体

*/
struct S_VertexElementIndex {
	unsigned short m_position_index = 0;
	unsigned short m_uv_index = 0;
	unsigned short m_normal_index = 0;
	unsigned short m_tangent_index = 0;
	unsigned short m_binormal_index = 0;

	bool operator==(S_VertexElementIndex face) {
		if (this->m_position_index == face.m_position_index &&
			this->m_uv_index == face.m_uv_index &&
			this->m_normal_index == face.m_normal_index &&
			this->m_tangent_index == face.m_tangent_index &&
			this->m_binormal_index == face.m_binormal_index
			) {
			return true;
		}
		return false;
	}
};

using VertexElementIndices = std::vector<S_VertexElementIndex>;
/**

*	@brief	FBXを読み込み、メッシュ情報とスケルトン情報を取得する

*	@param[in]	file_path	ファイルパス

*	@return	メッシュの集まりとスケルトン情報

*/
Fbx::MeshesAndSkeleton Fbx::LoadMeshesAndSkeleton(const char* file_path) {
	C_FbxManager p_fbx_manager;
	auto p_fbx_importer = p_fbx_manager.CreateImporter("");

	if (!p_fbx_importer->Initialize(file_path, -1, p_fbx_manager->GetIOSettings())) {
		assert(false);
	}

	//シーンにfbx情報を展開
	auto p_fbx_scene = p_fbx_manager.CreateScene("scene");

	p_fbx_importer->Import(p_fbx_scene.get());

	//三角形ジオメトリ化
	auto geometry_converter = FbxGeometryConverter(p_fbx_manager.get());
	geometry_converter.Triangulate(p_fbx_scene.get(), true);


	//スケルトン情報を取得する
	auto p_skeleton = GetSkeleton(p_fbx_scene.get());
	auto p_meshes = GetMeshes(p_fbx_scene.get(), p_skeleton);
	//ベースポーズ用のマトリックス配列のreserve
	auto count = p_skeleton->GetBoneCount();
	p_skeleton->ResizeInverseBasePoseMatrices<GALib::Math::Matrix4x4>(count);

	auto mesh_count = p_fbx_scene->GetMemberCount<FbxMesh>();
	for (int i = 0; i < mesh_count; ++i) {
		auto p_fbx_mesh = p_fbx_scene->GetMember<FbxMesh>(i);

		//ベースポーズの逆行列をスケルトンに追加
		AddInverseBasePoseMatricesToSkeleton(p_skeleton, p_fbx_mesh);
	}


	return MeshesAndSkeleton(p_meshes, p_skeleton);
}

/**

*	@brief	FBXを読み込み、アニメーション情報を構築する

*	@param[in]	file_path	ファイルパス

*	@return

*/
Fbx::AnimationSkeltonList Fbx::LoadAnimation(const char* file_path, SkeletonPtr p_base_skeleton) {
	//アニメーション読み込み
	C_FbxManager p_fbx_manager;
	auto p_fbx_importer = p_fbx_manager.CreateImporter("");
	if (!p_fbx_importer->Initialize(file_path, -1, p_fbx_manager->GetIOSettings())) {
		assert(false);
	}
	auto p_anime_scene = p_fbx_manager.CreateScene("animation_scene");
	p_fbx_importer->Import(p_anime_scene.get());


	//アニメーションファイルに登録されたノードをリスト化する
	auto node_count = p_anime_scene->GetNodeCount();

	AnimeSceneNodeDictionary animation_scene_node_dic;
	animation_scene_node_dic.reserve(node_count);
	for (int i = 0; i < node_count; ++i) {
		animation_scene_node_dic.emplace(p_anime_scene->GetNode(i)->GetName(), i);
	}


	//アニメスタックカウント取得
	auto anime_stack_count = p_anime_scene->GetSrcObjectCount<FbxAnimStack>();
	AnimationSkeltonList list;
	for (int i = 0; i < anime_stack_count; ++i) {
		auto p_anime_stack = p_anime_scene->GetSrcObject<FbxAnimStack>(i);
		p_anime_scene->SetCurrentAnimationStack(p_anime_stack);
		OSReport("ANIME NAME : %s", p_anime_stack->GetName());
		auto take_info = p_fbx_importer->GetTakeInfo(i);
		auto import_offset = take_info->mImportOffset;
		auto start_time = take_info->mLocalTimeSpan.GetStart();
		auto end_time = take_info->mLocalTimeSpan.GetStop();
		auto start_frame = (import_offset.Get() + start_time.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
		auto end_frame = (import_offset.Get() + end_time.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);

		auto clone_skeleton = p_base_skeleton->Clone();
		list.emplace_back(p_anime_stack->GetName(), clone_skeleton);
		AddAnimationMatricesToSkeleton(p_anime_scene.get(), animation_scene_node_dic, clone_skeleton, end_frame);
	}

	return list;
}

/**

*	@brief	FBXを読み込み、スケルトン情報を構築する

*	@param[in]	file_path	ファイルパス

*	@return	スケルトｎ

*/
SkeletonPtr Fbx::LoadSkeleton(const char* file_path) {
	C_FbxManager p_fbx_manager;
	auto p_fbx_importer = p_fbx_manager.CreateImporter("");

	if (!p_fbx_importer->Initialize(file_path, -1, p_fbx_manager->GetIOSettings())) {
		assert(false);
	}

	//シーンにfbx情報を展開
	auto p_fbx_scene = p_fbx_manager.CreateScene("scene");

	p_fbx_importer->Import(p_fbx_scene.get());



	//スケルトン情報を取得する
	auto p_skeleton = GetSkeleton(p_fbx_scene.get());

	//ベースポーズ用のマトリックス配列のreserve
	auto count = p_skeleton->GetBoneCount();
	p_skeleton->ResizeInverseBasePoseMatrices<GALib::Math::Matrix4x4>(count);

	auto mesh_count = p_fbx_scene->GetMemberCount<FbxMesh>();
	for (int i = 0; i < mesh_count; ++i) {
		auto p_fbx_mesh = p_fbx_scene->GetMember<FbxMesh>(i);

		//ベースポーズの逆行列をスケルトンに追加
		AddInverseBasePoseMatricesToSkeleton(p_skeleton, p_fbx_mesh);
	}

	return p_skeleton;
}
/**

*	@brief	FbxSceneからメッシュを取り出す

*	@param[in]	p_scene	fbxscene
*	@param[in]	p_skeleton	構築済みのスケルトン情報

*	@return	メッシュ

*/
MeshesPtr GetMeshes(FbxScene* p_scene,SkeletonPtr p_skeleton) {
	auto p_meshes = std::make_shared<C_Meshes>();

	//メッシュを構築する
	auto mesh_count = p_scene->GetMemberCount<FbxMesh>();
	p_meshes->ReserveMeshArray(mesh_count);
	for (int i = 0; i < mesh_count; ++i) {
		auto p_fbx_mesh = p_scene->GetMember<FbxMesh>(i);
		auto p_mesh = CreateMesh(p_fbx_mesh, p_skeleton);
		p_meshes->AddMesh(p_mesh);
		AddBlendShapeMeshes(p_fbx_mesh, p_mesh, p_skeleton);

		//メッシュからマテリアル取得
		auto p_mat = GetMeshMaterial(p_fbx_mesh);
		auto mat_index = p_meshes->FindMaterialIndex(p_mat->GetMaterialName());

		//同一名マテリアルが見つからなければ追加する
		if (mat_index == -1) {
			p_meshes->AddMaterialPtr(p_mat);
			p_mesh->SetMaterialIndex(p_mat->GetMaterialIndex());
		}
		else {
			p_mesh->SetMaterialIndex(mat_index);
		}


	}

	return p_meshes;
}

/**

*	@brief	骨格情報の取得

*	@param[in]	p_scene	シーン情報

*	@return	C_Skeleton

*/
SkeletonPtr GetSkeleton(FbxScene* p_scene){
	auto ptr = std::make_shared<C_Skeleton>();
	

	GetSkeleton(ptr, nullptr, p_scene->GetRootNode());


	//ボーン情報を出力
	auto count = ptr->GetBoneCount();
	ptr->SetMatrixType(eMatrixType::TYPE_MAT4x4);
	for (int i = 0; i < count; ++i) {

		auto bone = ptr->GetBone(i);
		int space = bone->GetParentNum(0);
		char buffer[64] = {};
		for (int j = 0; j < space; ++j) {
			buffer[j] = '-';
		}

		if (bone->GetBoneType() == eBoneType::TYPE_BONE) {
			OSReport("%sBone : %s\n", buffer, bone->GetBoneName());
		}
		else {
			OSReport("%sMesh : %s\n", buffer, bone->GetBoneName());

		}
	}

	return ptr;
};

/**

*	@brief	再帰を使いノードからボーンの親子構造を取得しスケルトンに構築

*	@param[out]	p_skeleton	構築先スケルトン
*	@param[in]	p_parent_bone	親ボーン
*	@param[in]	root_node	情報を取得するノード

*	@return	なし

*/
void GetSkeleton(SkeletonPtr p_skeleton, BonePtr p_parent_bone, FbxNode* root_node) {
	auto count = root_node->GetChildCount();

	BonePtr next_parent = p_parent_bone;
	for (int i = 0; i < count; ++i) {
		auto node = root_node->GetChild(i);
		auto type = node->GetNodeAttribute()->GetAttributeType();

		auto node_attribute = node->GetNodeAttribute();


		//ノードの親子関係で動いているメッシュが存在するので、メッシュの親子関係も構築する
		if (type == FbxNodeAttribute::eMesh) {
			//親ノードが存在しないのならメッシュ情報は追加しない
			if (next_parent) {
				auto bone_ptr = std::make_shared<C_Bone>();
				bone_ptr->SetBoneName(node_attribute->GetNode()->GetName());
				bone_ptr->SetBoneType(eBoneType::TYPE_MESH);

				p_skeleton->AddBone(bone_ptr);

				if (p_parent_bone) {
					p_parent_bone->AddChildIndex(bone_ptr);
				}
				next_parent = bone_ptr;
			}
		}

		//ボーン情報は全て構築する
		if (type == FbxNodeAttribute::eSkeleton) {
			auto bone_ptr = std::make_shared<C_Bone>();
			bone_ptr->SetBoneName(node_attribute->GetNode()->GetName());
			bone_ptr->SetBoneType(eBoneType::TYPE_BONE);
			p_skeleton->AddBone(bone_ptr);

			if (p_parent_bone) {
				p_parent_bone->AddChildIndex(bone_ptr);
			}
			next_parent = bone_ptr;
		}

		GetSkeleton(p_skeleton, next_parent, node);

		//再帰から戻ってきたら親ボーンを戻す
		next_parent = p_parent_bone;
	}
}


/**

*	@brief	メッシュからコントロールポイントのインデックス配列を取得する

*	@param[in]	p_mesh	FbxMesh*

*	@return	インデックス配列

*/
auto GetMeshControlPointIndices(FbxMesh* p_mesh) {
	auto poly_count = p_mesh->GetPolygonCount();
	std::vector<unsigned short> vec;
	vec.reserve(poly_count * 3);
	for (int i = 0; i < poly_count; ++i) {
		vec.push_back(p_mesh->GetPolygonVertex(i, 0));
		vec.push_back(p_mesh->GetPolygonVertex(i, 1));
		vec.push_back(p_mesh->GetPolygonVertex(i, 2));
	}

	return vec;
}



/**

*	@brief	メッシュからエレメントのインデックス配列を取得する

*	@param[in]	p_mesh	FbxMesh*
*	@param[in]	p_element	メッシュのエレメント
*	@param[in]	control_point_indices	メッシュのコントロールポイントのインデックス配列

*	@return	エレメントのインデックス配列

*/
template<class _Element>
auto GetMeshElementIndices(FbxMesh* p_mesh, _Element* p_element, Indices& control_point_indices) {
	if (!p_element) return Indices();
	Indices vec;

	auto mapping_mode = p_element->GetMappingMode();
	auto reference_mode = p_element->GetReferenceMode();
	auto&& index_array = p_element->GetIndexArray();
	vec.reserve(control_point_indices.size());

	//コントロールポイント（頂点情報）でマッピングする
	if (mapping_mode == fbxsdk::FbxLayerElement::eByControlPoint) {
		for (auto &it : control_point_indices) {
			//参照情報を確認し、eDirectならばコントロールポイントのインデックスリストをインデックスに
			//INDEX_TO_DIRECTならば、コントロールポイントのインデックスリストからインデックスリストを参照し、インデックスを取得する
			auto index = (reference_mode == fbxsdk::FbxLayerElement::eDirect) ?
				it : index_array.GetAt(it);
			vec.emplace_back(index);
		}
	}
	else if (mapping_mode == fbxsdk::FbxLayerElement::eByPolygonVertex) {
		auto polygon_count = p_mesh->GetPolygonCount();
		int polygon_index = 0;
		//ポリゴン数分ぶん回す
		for (int i = 0; i < polygon_count; ++i) {
			auto polygon_size = p_mesh->GetPolygonSize(i);
			//ポリゴンの頂点サイズ分回す
			for (int j = 0; j < polygon_size; ++j) {
				//参照情報を確認し、eDirectならばポリゴンインデックスを法線インデックスに
				//INDEX_TO_DIRECTならば、ポリゴンインデックスからインデックスリストを参照し、インデックスを取得する
				auto index = (reference_mode == fbxsdk::FbxLayerElement::eDirect) ?
					polygon_index : index_array.GetAt(polygon_index);
				vec.emplace_back(index);

				polygon_index++;
			}
		}
	}
	else {
		assert(false);
	}

	return vec;
}



auto GetVectorData(FbxVector4 vec) {
	GALib::Math::Vector4 vec4;
	vec4.m_x = vec[0];
	vec4.m_y = vec[1];
	vec4.m_z = vec[2];
	vec4.m_w = vec[3];

	return vec4;
}

auto GetVectorData(FbxVector2 vec) {
	GALib::Math::Vector2 vec2;
	vec2.m_x = vec[0];
	vec2.m_y = vec[1];
	
	return vec2;
}

/**

*	@brief	メッシュからインデックスを使いエレメントのデータを取得する

*	@param[in]	p_element	メッシュのエレメント
*	@param[in]	index	エレメントのインデックス

*	@return	エレメントの要素

*/
template<class _Element>
auto GetMeshElementData(_Element* p_element,unsigned short index) {
	if (!p_element) {
		return decltype(GetVectorData(p_element->GetDirectArray().GetAt(0)))();
	}

	auto&& direct_array = p_element->GetDirectArray();

	return GetVectorData(direct_array.GetAt(index));
}

/**

*	@brief	メッシュから頂点の座標を取得する

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	index		インデックス

*	@return	座標情報

*/
auto GetMeshPositionData(FbxGeometryBase* p_fbx_mesh, unsigned short index) {
	auto cp = p_fbx_mesh->GetControlPointAt(index);
	return GALib::Math::Vector3(cp[0], cp[1], cp[2]);
}

/**

*	@brief	複数のインデックスリストから共通インデックスリストを作成する

*/
auto GetCompIndices(Indices& control_point_indices,Indices& uv_indices, Indices& normal_indices, Indices& binormal_indices, Indices& tangent_indices) {
	//インデックスリストの作成
	{
		VertexElementIndices v_list;
		v_list.resize(control_point_indices.size());

		for (int i = 0; i < v_list.size(); ++i) {
			v_list[i].m_position_index = control_point_indices[i];

			//インデックスがなければコピーしない
			if (uv_indices.size() > i) {
				v_list[i].m_uv_index = uv_indices[i];
			}
			if (normal_indices[i] > i) {
				v_list[i].m_normal_index = normal_indices[i];
			}
			if (binormal_indices.size() > i) {
				v_list[i].m_binormal_index = binormal_indices[i];
			}
			if (tangent_indices.size() > i) {
				v_list[i].m_tangent_index = tangent_indices[i];
			}

		}

		//頂点インデックスを登録していき、同一の頂点を参照する場合インデックス化する
		Indices indices;
		std::vector<S_VertexElementIndex> entry_vertex;

		indices.reserve(control_point_indices.size());

		//登録した頂点と同一の頂点があればインデックスを登録する
		auto SerceVertex = [](S_VertexElementIndex v, VertexElementIndices& entry_vertex) {
			int i = 0;
			for (auto &it : entry_vertex) {
				if (it == v) {
					return i;
				}
				++i;
			}
			return -1;
		};

		//同一頂点が見つからなかった場合、頂点を登録し新しいインデックスを登録しインデックスを加算する
		//頂点が見つかった場合はインデックスのみを登録する
		int i = 0;
		for (auto &it : v_list) {
			int index = SerceVertex(it, entry_vertex);
			if (index < 0) {
				indices.push_back(i);
				entry_vertex.push_back(it);
				++i;
			}
			else {
				indices.push_back((unsigned short)index);
			}
		}
		return std::pair<VertexElementIndices, Indices>(entry_vertex, indices);
	}
}


/**

*	@brief	メッシュから１頂点のデータを取得する

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@parma[in]	index		頂点要素のインデックス構造体

*	@return	頂点データ

*/
auto GetMeshVertexData(FbxGeometryBase* p_fbx_mesh, S_VertexElementIndex index) {
	S_VertexPUNTBW v;
	v.m_pos = GetMeshPositionData(p_fbx_mesh, index.m_position_index);
	v.m_uv = GetMeshElementData(p_fbx_mesh->GetElementUV(), index.m_uv_index);
	v.m_normal = GetMeshElementData(p_fbx_mesh->GetElementNormal(), index.m_normal_index);
	v.m_binormal = GetMeshElementData(p_fbx_mesh->GetElementBinormal(), index.m_binormal_index);
	v.m_tangent = GetMeshElementData(p_fbx_mesh->GetElementTangent(), index.m_tangent_index);

	return v;
}
/**

*	@brief	メッシュを構築する頂点配列を取得する

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	v_element_indices	頂点要素のインデックス配列

*	@return	頂点配列

*/
auto GetMeshVertices(FbxGeometryBase* p_fbx_mesh, VertexElementIndices& v_element_indices) {
	std::vector<S_VertexPUNTBW> vec;
	vec.resize(v_element_indices.size());

	for (int i = 0; i < v_element_indices.size(); ++i) {
		auto it = v_element_indices[i];
		vec[i] = GetMeshVertexData(p_fbx_mesh,it);
	}
	
	return vec;
}

/**

*	@brief	メッシュを構築する頂点のボーンウェイトを取得する

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	p_skeleton	構築済みスケルトン情報
*	@param[in]	v_element_indices	頂点要素のインデックス配列

*	@return	ウェイト配列

*/
auto GetMeshVertexBoneWeightArray(FbxMesh* p_fbx_mesh, SkeletonPtr p_skeleton,VertexElementIndices& v_element_indices) {
	using IndexAndWeight = std::pair<int, float>;
	using TempBoneWeightList = std::vector<std::vector<IndexAndWeight>>;
	using BoneWeightList = std::vector<S_BoneWeight>;
	//スキンのデフォーマーの数を取得する
	auto skin_count = p_fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);

	//スキンは一戸まで
	assert(skin_count <= 1);


	//メッシュのコントロールポイントの数を取得
	auto control_points_count = p_fbx_mesh->GetControlPointsCount();

	//メッシュ頂点とそれに対応するボーンのウェイトリスト情報
	TempBoneWeightList temp_bone_weight_list(control_points_count);

	auto mesh_name = p_fbx_mesh->GetNode()->GetName();
	//スキンがあればボーンからウェイトをとる
	if (skin_count){
		//スキン情報を持ったデフォーマーの取得
		auto p_skin = static_cast<FbxSkin*>(p_fbx_mesh->GetDeformer(0, FbxDeformer::eSkin));

		//ボーンの数を取得
		auto cluster_count = p_skin->GetClusterCount();

		for (int i = 0; i < cluster_count; ++i) {
			auto p_cluster = p_skin->GetCluster(i);

			//クラスタ名からスケルトンのボーン位置を取得し、ボーンインデックスにする
			auto bone_index = p_skeleton->FindBoneIndex(p_cluster->GetLink()->GetName());

			//enomalize(ボーンのウェイトの合計値が1.0fでノーマライズされているもの）しか対応しない
			assert(p_cluster->GetLinkMode() == FbxCluster::eNormalize);

			//クラスタが影響を与えるメッシュの頂点配列へのインデックス配列の数とそのインデックス配列の取得
			auto index_count = p_cluster->GetControlPointIndicesCount();
			auto indices = p_cluster->GetControlPointIndices();

			//ウェイトの配列を取得
			auto weights = p_cluster->GetControlPointWeights();

			//クラスタインデックスとウェイトを対象頂点インデックスにあわせて突っ込む
			for (int j = 0; j < index_count; ++j) {
				auto control_point_index = indices[j];
				temp_bone_weight_list[control_point_index].push_back({ bone_index,weights[j] });
			}
		}
	}



	//重みを除外、正規化する

	BoneWeightList bone_weight_list;
	bone_weight_list.reserve(control_points_count);
	for (auto &tmp_bone_weight : temp_bone_weight_list) {
		//ソート
		std::sort(tmp_bone_weight.begin(), tmp_bone_weight.end(),
			[](const IndexAndWeight& weightA, const IndexAndWeight& weightB) { return weightA.second > weightB.second; }
		);

		//そもそもウェイト数が0ならばボーンが存在しないので、メッシュ計算用ダミーを投入する
		if (tmp_bone_weight.size() == 0 && skin_count == 0) {
			auto bone_index = p_skeleton->FindBoneIndex(mesh_name);
			tmp_bone_weight.push_back({ bone_index, 1.0f });
			tmp_bone_weight.push_back({ 0, 0.0f });
			tmp_bone_weight.push_back({ 0, 0.0f });
			tmp_bone_weight.push_back({ 0, 0.0f });
		}

		// 1頂点に4つより多くウェイトが割り振られているなら影響が少ないものは無視する
		while (tmp_bone_weight.size() > 4)
		{
			tmp_bone_weight.pop_back();
		}

		// 4つに満たない場合はダミーを挿入
		while (tmp_bone_weight.size() < 4)
		{
			tmp_bone_weight.push_back({ 0, 0.0f });
		}

		S_BoneWeight weight;
		float total = 0.0f;
		for (int i = 0; i < 4; ++i)
		{
			weight.m_bone_index[i] = tmp_bone_weight[i].first;
			weight.m_bone_weight.m_elements[i] = tmp_bone_weight[i].second;

			total += tmp_bone_weight[i].second;
		}

		// ウェイトの正規化
		for (int i = 0; i < 4; ++i)
		{
			weight.m_bone_weight.m_elements[i] /= total;
		}

		bone_weight_list.push_back(weight);
	}

	//ウェイト配列をメッシュのインデックス配列にあわせて展開する
	//インデックスによる同一頂点の処理を行う場合は必要なし
	BoneWeightList list;
	list.reserve(v_element_indices.size());
	for (auto index : v_element_indices) {
		list.push_back(bone_weight_list[index.m_position_index]);
	}

	return list;
}


/**

*	@brief	FbxMeshからメッシュデータを構築する

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	p_skeleton	構築済みスケルトン情報

*	@return	メッシュ

*/
MeshPtr CreateMesh(FbxMesh* p_fbx_mesh, SkeletonPtr p_skeleton) {
	auto p_mesh = std::make_shared<C_Mesh>();
	p_mesh->SetMeshName(p_fbx_mesh->GetNode()->GetName());
	OSReport("Mesh : %s\n",p_mesh->GetMeshName());

	//メッシュのコントロールポイントのインデックス配列を取得
	auto control_point_indices = GetMeshControlPointIndices(p_fbx_mesh);
	auto uv_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementUV(), control_point_indices);
	auto normal_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementNormal(), control_point_indices);
	auto binormal_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementBinormal(), control_point_indices);
	auto tangent_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementTangent(), control_point_indices);


	auto pair = GetCompIndices(control_point_indices, uv_indices,normal_indices,binormal_indices,tangent_indices);
	auto vertices = GetMeshVertices(p_fbx_mesh,pair.first);
	auto bone_weight_list = GetMeshVertexBoneWeightArray(p_fbx_mesh, p_skeleton, pair.first);

	//ボーンウェイトのコピー
	for (int i = 0; i < bone_weight_list.size(); ++i) {
		vertices[i].m_bone.m_bone_weight = bone_weight_list[i].m_bone_weight;
		for (int j = 0; j < 4; ++j) {
			vertices[i].m_bone.m_bone_index[j] = bone_weight_list[i].m_bone_index[j];
		}
	}
	p_mesh->CopyVertices(vertices);
	p_mesh->CopyIndices(pair.second);
	p_mesh->SetVertexType(eVertexType::TYPE_PUNTBW);
	return p_mesh;
}


/**

*	@brief	スケルトンにベースポーズの逆行列配列を構築する

*	@param[in]	p_skeleton	構築済みスケルトン情報
*	@param[in]	p_fbx_mesh	FbxMesh*

*	@return	なし

*/
void AddInverseBasePoseMatricesToSkeleton(SkeletonPtr p_skeleton,FbxMesh* p_fbx_mesh){
	//スケルトンに一切ボーンが存在しなければアニメーションはなし
	if (p_skeleton->GetBoneCount() == 0) return;


	//スキンのデフォーマーの数を取得する
	auto skin_count = p_fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);

	//スキンは一戸まで
	assert(skin_count <= 1);

	
	//スキンがなければメッシュの逆行列を生成
	if (skin_count == 0) {
		GALib::Math::Matrix4x4 mat;
		auto base_pose_matrix = p_fbx_mesh->GetNode()->EvaluateGlobalTransform().Inverse();
		auto ptr = (double*)base_pose_matrix;
		for (int i = 0; i < 16; ++i) {
			mat.m_elements[i] = (float)ptr[i];
		}
		auto trans = p_fbx_mesh->GetNode()->EvaluateLocalTransform();
		auto bone_index = p_skeleton->FindBoneIndex(p_fbx_mesh->GetNode()->GetName());
		p_skeleton->SetInversePoseMatrix(mat, bone_index);

	}else {
		//スキン情報を持ったデフォーマーの取得
		auto p_skin = static_cast<FbxSkin*>(p_fbx_mesh->GetDeformer(0, FbxDeformer::eSkin));

		//ボーンの数を取得
		auto cluster_count = p_skin->GetClusterCount();

		for (int i = 0; i < cluster_count; ++i) {
			auto p_cluster = p_skin->GetCluster(i);

			//クラスタ名からスケルトンのボーンインデックスを取得
			auto bone_index = p_skeleton->FindBoneIndex(p_cluster->GetLink()->GetName());
			assert(bone_index >= 0);
			GALib::Math::Matrix4x4 mat;
			auto base_pose_matrix = p_cluster->GetLink()->EvaluateGlobalTransform().Inverse();
			auto ptr = (double*)base_pose_matrix;
			for (int j = 0; j < 16; ++j) {
				mat.m_elements[j] = (float)ptr[j];
			}

			p_skeleton->SetInversePoseMatrix(mat, bone_index);


		}
	}
}

/**

*	@brief	FbxMeshからマテリアル情報を取得し、構築する

*	@param[in]	p_fbx_mesh	FbxMesh*

*	@return	マテリアル

*/
MaterialPtr GetMeshMaterial(FbxMesh* p_fbx_mesh) {
	using TextureInfo = C_Material::C_TextureInfo;
	using VectorInfo = C_Material::C_VectorInfo;
	auto p_mat = std::make_shared<C_Material>();

	auto material_count = p_fbx_mesh->GetElementMaterialCount();
	if (material_count == 0) {
		OSReport("マテリアルがないっぽい\n");
		return p_mat;
	}

	//恐らくマテリアルの適用箇所
	//マッピングが全体でなければ無効ポインタを返す
	auto p_fbx_layer_material = p_fbx_mesh->GetElementMaterial();

	if (p_fbx_layer_material->GetMappingMode() != FbxLayerElement::eAllSame) return p_mat;


	//0番目のマテリアルのみ使用
	int index = p_fbx_layer_material->GetIndexArray()[0];
	auto p_fbx_material = p_fbx_mesh->GetNode()->GetMaterial(index);
	OSReport("Material : %s\n", p_fbx_material->GetName());
	p_mat->SetMaterialName(p_fbx_material->GetName());

	//インプリメントの取得
	auto impl = GetImplementation(p_fbx_material, FBXSDK_IMPLEMENTATION_CGFX);
	if (!impl) {
		impl = GetImplementation(p_fbx_material, FBXSDK_IMPLEMENTATION_HLSL);
	}

	//インプリが取得できなかったのでマテリアルカラーの取得
	if (!impl) {
		if (p_fbx_material->GetClassId().Is(FbxSurfacePhong::ClassId)) {
			auto p_phong = (FbxSurfacePhong*)p_fbx_material;
			//ディフーズ
			{
				auto v = p_phong->Diffuse.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_DIFFUSE,
					(float)v[0],(float)v[1],(float)v[2]
				});
				
			}

			//アンビエント
			{
				auto v = p_phong->Ambient.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_AMBIENT,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//スペキュ
			{
				auto v = p_phong->Specular.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_SPECULAR,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//シャイネス
			{
				auto v = p_phong->Shininess.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_SHININESS,
					(float)v
				});
			}

			//スペキュラファクタ
			{
				auto v = p_phong->SpecularFactor.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_SPECULAR_FACTOR,
					(float)v
				});
			}

			//エミッシブ
			{
				auto v = p_phong->Emissive.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_EMISSIVE,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//オパシティ
			{
				auto v = p_phong->TransparencyFactor.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_TRANSPARENCY_FACTOR,
					(float)v
				});
			}

			//リフレクティビティ
			{
				auto v = p_phong->ReflectionFactor.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_REFLECTION_FACTOR,
					(float)v
				});
			}
			
		}
		else if (p_fbx_material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
			auto p_lam = (FbxSurfaceLambert*)p_fbx_material;
			//ディフーズ
			{
				auto v = p_lam->Diffuse.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_DIFFUSE,
					(float)v[0],(float)v[1],(float)v[2]
				});

			}

			//アンビエント
			{
				auto v = p_lam->Ambient.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_AMBIENT,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}


			//エミッシブ
			{
				auto v = p_lam->Emissive.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_EMISSIVE,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//オパシティ
			{
				auto v = p_lam->TransparencyFactor.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_TRANSPARENCY_FACTOR,
					(float)v
				});
			}
		}
		else
			OSReport("マテリアル不明\n");
		
		return p_mat;
	}
	
	//implが取得できたのでテクスチャ名とかの取得
	auto p_root_table = impl->GetRootTable();
	auto entry_count = p_root_table->GetEntryCount();
	for (int table = 0; table < entry_count; ++table) {
		auto entry_table = p_root_table->GetEntry(table);
		auto entry_type = entry_table.GetEntryType(true);

		FbxProperty prop;

		//プロパティを取得する
		if (strcmp(FbxPropertyEntryView::sEntryType, entry_type) == 0)
		{
			prop = p_fbx_material->FindPropertyHierarchical(entry_table.GetSource());
			if (!prop.IsValid())
			{
				prop = p_fbx_material->RootProperty.FindHierarchical(entry_table.GetSource());
			}
		}
		else if (strcmp(FbxConstantEntryView::sEntryType, entry_type) == 0)
		{
			prop = impl->GetConstants().FindHierarchical(entry_table.GetSource());
		}

		//プロパティが取得できなければ処理をキャンセル
		if (!prop.IsValid()) {
			continue;
		}

		auto str = entry_table.GetSource();

		//とりあえずソースの名前取得
		auto source_type_name = std::string(str);
		OSReport("SourceType : %s\n", source_type_name.c_str());

		//名前からなんか検索する
		auto Find = [&](const char* a) {
			if (source_type_name.find(a) == std::string::npos) return false;
			return true;
		};

		//ファイルテクスチャを取得
		if (prop.GetSrcObjectCount<FbxTexture>() > 0)
		{

			auto p_file_tex = prop.GetSrcObject<FbxFileTexture>(0);
			auto texture_full_path = std::string(p_file_tex->GetFileName());


			auto last_pos = texture_full_path.find_last_of("/");
			auto tex_name = std::string(texture_full_path.c_str() + last_pos+1);

			

			auto EntryTextureInfo = [&]( const char* tex_name, TextureInfo::eTextureType tex_type) {
				p_mat->AddTextureInfo({
					tex_name,
					tex_type
				});
			};

			//見つかれば登録
			if (Find("DiffuseTexture")) {
				EntryTextureInfo(tex_name.c_str(), TextureInfo::eTextureType::TYPE_DIFFUSE);
			}
			else if (Find("ReflectionMapTexture")) {
				EntryTextureInfo(tex_name.c_str(), TextureInfo::eTextureType::TYPE_REFLECTION);
			}
			else if (Find("NormalTexture")) {
				EntryTextureInfo(tex_name.c_str(), TextureInfo::eTextureType::TYPE_NORMAL);

			}
			else if (Find("FalloffTexture")) {
				EntryTextureInfo(tex_name.c_str(), TextureInfo::eTextureType::TYPE_FALLOFF);

			}
			else if (Find("SpecularTexture")) {
				EntryTextureInfo(tex_name.c_str(), TextureInfo::eTextureType::TYPE_SPECULAR);

			}

		}
		//テクスチャじゃなければなんかなのでなんか必要なものを登録する
		else {


			//おそらくmaya上でのエミッシブ値
			if (Find("LitColor")) {
				auto val = prop.Get<FbxDouble3>();
				p_mat->AddVectorInfo({
				VectorInfo::eVectorDimention::DIM_V3,
				VectorInfo::eVectorType::TYPE_EMISSIVE,
					(float)val[0],(float)val[1],(float)val[2]
				});
			}
			else if(Find("FalloffPower")){
				auto val = prop.Get<FbxDouble>();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_FALLOFF_POWER,
					(float)val
				});
			}
			else if (Find("SpecularPower")) {
				auto val = prop.Get<FbxDouble>();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_SHININESS,
					(float)val
				});

			}

			//他は気が向いたら追加する

		
		}


	}

	return p_mat;
}

/**

*	@brief	FbxSceneのアニメーション情報を解読し、スケルトンにアニメーション行列を突っ込む

*	@param[in]	p_scene	FbxScene*
*	@param[in]	dic	シーンのノードとインデックス辞書
*	@param[in]	p_skeleton	スケルトン
*	@param[in]	end_frame	アニメーションの終了フレーム

*	@return	なし

*/
void AddAnimationMatricesToSkeleton(FbxScene* p_scene,AnimeSceneNodeDictionary& dic, SkeletonPtr p_skeleton,int end_frame) {
	p_skeleton->SetAnimationEndFrame(end_frame);
	//スケルトン内のアニメーション行列配列をリサイズする
	int bone_count = p_skeleton->GetBoneCount();
	for (int i = 0; i < bone_count; ++i) {
		p_skeleton->GetBone(i)->ResizeAnimationMatrices<GALib::Math::Matrix4x4>(end_frame);
	}

	for (int frame = 0; frame < end_frame; ++frame) {
		FbxTime time;
		time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

		for (int bone = 0; bone < bone_count; ++bone) {
			auto bone_name = p_skeleton->GetBone(bone)->GetBoneName();
			auto node_id = dic.find(bone_name)->second;
			auto node = p_scene->GetNode(node_id);

			//ローカル行列はそのうち対応する
			auto bone_mat = node->EvaluateGlobalTransform(time);
			auto ptr = (double*)bone_mat;
			GALib::Math::Matrix4x4 mat;
			for (int i = 0; i < 16; ++i) {
				mat.m_elements[i] = (float)ptr[i];
			}

			auto p_bone = p_skeleton->GetBone(bone);
			p_bone->SetAnimationMatrix(mat, frame);
			p_bone->SetMathType(eMathType::TYPE_WORLD);
			p_bone->SetMatrixType(eMatrixType::TYPE_MAT4x4);
		}
	}
}


//----------------------------------------------------------
//ShapeMesh関連
//----------------------------------------------------------
/**

*	@brief	ブレンドシェプメッシュの作成

*/
ShapeMeshPtr CreateBlendShapeMesh(FbxMesh* p_parent_fbx_mesh, FbxShape* p_shape, SkeletonPtr p_skeleton) {
	//メッシュのコントロールポイントのインデックス配列を取得
	auto control_point_indices = GetMeshControlPointIndices(p_parent_fbx_mesh);

	//メッシュからuvをとってこないとインデックス共通化でズレる可能性が非常に高いのでダミーで一応とってくる、独自形式時には基本省かれる
	auto uv_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_parent_fbx_mesh->GetElementUV(), control_point_indices);
	auto normal_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_shape->GetElementNormal(), control_point_indices);
	auto binormal_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_shape->GetElementBinormal(), control_point_indices);
	auto tangent_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_shape->GetElementTangent(), control_point_indices);



	auto pair = GetCompIndices(control_point_indices, uv_indices, normal_indices, binormal_indices, tangent_indices);
	auto vertices = GetMeshVertices(p_shape, pair.first);

	auto p_mesh = std::make_shared<C_ShapeMesh>();
	p_mesh->CopyVertices(vertices);
	p_mesh->SetVertexType(eVertexType::TYPE_PUNTBW);

	//接線、従法線がなければ、書き込み頂点はPNとなる
	if (binormal_indices.size() && tangent_indices.size()) {
		p_mesh->SetWriteVertexType(eVertexType::TYPE_PNTB);
	}
	else {
		p_mesh->SetWriteVertexType(eVertexType::TYPE_PN);
	}

	return p_mesh;
}


/**

*	@brief	

*/
void AddBlendShapeMeshes(FbxMesh* p_fbx_mesh,MeshPtr p_mesh,SkeletonPtr p_skeleton) {
	auto count = p_fbx_mesh->GetDeformerCount(FbxDeformer::eBlendShape);
	if (!count) return;
	auto control_point_indices = GetMeshControlPointIndices(p_fbx_mesh);

	auto p_blend_shape = (FbxBlendShape*)p_fbx_mesh->GetDeformer(0);

	auto channel_count = p_blend_shape->GetBlendShapeChannelCount();
	OSReport("BlendShapeChannel : %d\n", channel_count);

	p_mesh->ReserveBlendShapeMeshArray(channel_count);
	for (int i = 0; i < channel_count; ++i) {
		auto p_channel = p_blend_shape->GetBlendShapeChannel(i);

		//チャンネルのセット
		int target_shape_count = p_channel->GetTargetShapeCount();

		auto p_shape = p_channel->GetTargetShape(0);
		auto p_shape_mesh = CreateBlendShapeMesh(p_fbx_mesh, p_shape, p_skeleton);

		//シェイプメッシュとメッシュのバッファサイズが違ったらメモリ破壊を起こして死ぬ
		assert(p_mesh->GetVertexBufferSize() == p_mesh->GetVertexBufferSize());
		p_shape_mesh->SetMeshName(p_shape->GetName());
		OSReport("ShapeName : %s\n", p_shape->GetName());

		p_mesh->AddBlendShapeMesh(p_shape_mesh);
		
	}
}

