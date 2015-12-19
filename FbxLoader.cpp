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

//�v���g�^�C�v�錾
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

*	@brief	���_���ێ�����v�f�̃C���f�b�N�X��ێ�����\����

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

*	@brief	FBX��ǂݍ��݁A���b�V�����ƃX�P���g�������擾����

*	@param[in]	file_path	�t�@�C���p�X

*	@return	���b�V���̏W�܂�ƃX�P���g�����

*/
Fbx::MeshesAndSkeleton Fbx::LoadMeshesAndSkeleton(const char* file_path) {
	C_FbxManager p_fbx_manager;
	auto p_fbx_importer = p_fbx_manager.CreateImporter("");

	if (!p_fbx_importer->Initialize(file_path, -1, p_fbx_manager->GetIOSettings())) {
		assert(false);
	}

	//�V�[����fbx����W�J
	auto p_fbx_scene = p_fbx_manager.CreateScene("scene");

	p_fbx_importer->Import(p_fbx_scene.get());

	//�O�p�`�W�I���g����
	auto geometry_converter = FbxGeometryConverter(p_fbx_manager.get());
	geometry_converter.Triangulate(p_fbx_scene.get(), true);


	//�X�P���g�������擾����
	auto p_skeleton = GetSkeleton(p_fbx_scene.get());
	auto p_meshes = GetMeshes(p_fbx_scene.get(), p_skeleton);
	//�x�[�X�|�[�Y�p�̃}�g���b�N�X�z���reserve
	auto count = p_skeleton->GetBoneCount();
	p_skeleton->ResizeInverseBasePoseMatrices<GALib::Math::Matrix4x4>(count);

	auto mesh_count = p_fbx_scene->GetMemberCount<FbxMesh>();
	for (int i = 0; i < mesh_count; ++i) {
		auto p_fbx_mesh = p_fbx_scene->GetMember<FbxMesh>(i);

		//�x�[�X�|�[�Y�̋t�s����X�P���g���ɒǉ�
		AddInverseBasePoseMatricesToSkeleton(p_skeleton, p_fbx_mesh);
	}


	return MeshesAndSkeleton(p_meshes, p_skeleton);
}

/**

*	@brief	FBX��ǂݍ��݁A�A�j���[�V���������\�z����

*	@param[in]	file_path	�t�@�C���p�X

*	@return

*/
Fbx::AnimationSkeltonList Fbx::LoadAnimation(const char* file_path, SkeletonPtr p_base_skeleton) {
	//�A�j���[�V�����ǂݍ���
	C_FbxManager p_fbx_manager;
	auto p_fbx_importer = p_fbx_manager.CreateImporter("");
	if (!p_fbx_importer->Initialize(file_path, -1, p_fbx_manager->GetIOSettings())) {
		assert(false);
	}
	auto p_anime_scene = p_fbx_manager.CreateScene("animation_scene");
	p_fbx_importer->Import(p_anime_scene.get());


	//�A�j���[�V�����t�@�C���ɓo�^���ꂽ�m�[�h�����X�g������
	auto node_count = p_anime_scene->GetNodeCount();

	AnimeSceneNodeDictionary animation_scene_node_dic;
	animation_scene_node_dic.reserve(node_count);
	for (int i = 0; i < node_count; ++i) {
		animation_scene_node_dic.emplace(p_anime_scene->GetNode(i)->GetName(), i);
	}


	//�A�j���X�^�b�N�J�E���g�擾
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

*	@brief	FBX��ǂݍ��݁A�X�P���g�������\�z����

*	@param[in]	file_path	�t�@�C���p�X

*	@return	�X�P���g��

*/
SkeletonPtr Fbx::LoadSkeleton(const char* file_path) {
	C_FbxManager p_fbx_manager;
	auto p_fbx_importer = p_fbx_manager.CreateImporter("");

	if (!p_fbx_importer->Initialize(file_path, -1, p_fbx_manager->GetIOSettings())) {
		assert(false);
	}

	//�V�[����fbx����W�J
	auto p_fbx_scene = p_fbx_manager.CreateScene("scene");

	p_fbx_importer->Import(p_fbx_scene.get());



	//�X�P���g�������擾����
	auto p_skeleton = GetSkeleton(p_fbx_scene.get());

	//�x�[�X�|�[�Y�p�̃}�g���b�N�X�z���reserve
	auto count = p_skeleton->GetBoneCount();
	p_skeleton->ResizeInverseBasePoseMatrices<GALib::Math::Matrix4x4>(count);

	auto mesh_count = p_fbx_scene->GetMemberCount<FbxMesh>();
	for (int i = 0; i < mesh_count; ++i) {
		auto p_fbx_mesh = p_fbx_scene->GetMember<FbxMesh>(i);

		//�x�[�X�|�[�Y�̋t�s����X�P���g���ɒǉ�
		AddInverseBasePoseMatricesToSkeleton(p_skeleton, p_fbx_mesh);
	}

	return p_skeleton;
}
/**

*	@brief	FbxScene���烁�b�V�������o��

*	@param[in]	p_scene	fbxscene
*	@param[in]	p_skeleton	�\�z�ς݂̃X�P���g�����

*	@return	���b�V��

*/
MeshesPtr GetMeshes(FbxScene* p_scene,SkeletonPtr p_skeleton) {
	auto p_meshes = std::make_shared<C_Meshes>();

	//���b�V�����\�z����
	auto mesh_count = p_scene->GetMemberCount<FbxMesh>();
	p_meshes->ReserveMeshArray(mesh_count);
	for (int i = 0; i < mesh_count; ++i) {
		auto p_fbx_mesh = p_scene->GetMember<FbxMesh>(i);
		auto p_mesh = CreateMesh(p_fbx_mesh, p_skeleton);
		p_meshes->AddMesh(p_mesh);
		AddBlendShapeMeshes(p_fbx_mesh, p_mesh, p_skeleton);

		//���b�V������}�e���A���擾
		auto p_mat = GetMeshMaterial(p_fbx_mesh);
		auto mat_index = p_meshes->FindMaterialIndex(p_mat->GetMaterialName());

		//���ꖼ�}�e���A����������Ȃ���Βǉ�����
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

*	@brief	���i���̎擾

*	@param[in]	p_scene	�V�[�����

*	@return	C_Skeleton

*/
SkeletonPtr GetSkeleton(FbxScene* p_scene){
	auto ptr = std::make_shared<C_Skeleton>();
	

	GetSkeleton(ptr, nullptr, p_scene->GetRootNode());


	//�{�[�������o��
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

*	@brief	�ċA���g���m�[�h����{�[���̐e�q�\�����擾���X�P���g���ɍ\�z

*	@param[out]	p_skeleton	�\�z��X�P���g��
*	@param[in]	p_parent_bone	�e�{�[��
*	@param[in]	root_node	�����擾����m�[�h

*	@return	�Ȃ�

*/
void GetSkeleton(SkeletonPtr p_skeleton, BonePtr p_parent_bone, FbxNode* root_node) {
	auto count = root_node->GetChildCount();

	BonePtr next_parent = p_parent_bone;
	for (int i = 0; i < count; ++i) {
		auto node = root_node->GetChild(i);
		auto type = node->GetNodeAttribute()->GetAttributeType();

		auto node_attribute = node->GetNodeAttribute();


		//�m�[�h�̐e�q�֌W�œ����Ă��郁�b�V�������݂���̂ŁA���b�V���̐e�q�֌W���\�z����
		if (type == FbxNodeAttribute::eMesh) {
			//�e�m�[�h�����݂��Ȃ��̂Ȃ烁�b�V�����͒ǉ����Ȃ�
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

		//�{�[�����͑S�č\�z����
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

		//�ċA����߂��Ă�����e�{�[����߂�
		next_parent = p_parent_bone;
	}
}


/**

*	@brief	���b�V������R���g���[���|�C���g�̃C���f�b�N�X�z����擾����

*	@param[in]	p_mesh	FbxMesh*

*	@return	�C���f�b�N�X�z��

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

*	@brief	���b�V������G�������g�̃C���f�b�N�X�z����擾����

*	@param[in]	p_mesh	FbxMesh*
*	@param[in]	p_element	���b�V���̃G�������g
*	@param[in]	control_point_indices	���b�V���̃R���g���[���|�C���g�̃C���f�b�N�X�z��

*	@return	�G�������g�̃C���f�b�N�X�z��

*/
template<class _Element>
auto GetMeshElementIndices(FbxMesh* p_mesh, _Element* p_element, Indices& control_point_indices) {
	if (!p_element) return Indices();
	Indices vec;

	auto mapping_mode = p_element->GetMappingMode();
	auto reference_mode = p_element->GetReferenceMode();
	auto&& index_array = p_element->GetIndexArray();
	vec.reserve(control_point_indices.size());

	//�R���g���[���|�C���g�i���_���j�Ń}�b�s���O����
	if (mapping_mode == fbxsdk::FbxLayerElement::eByControlPoint) {
		for (auto &it : control_point_indices) {
			//�Q�Ə����m�F���AeDirect�Ȃ�΃R���g���[���|�C���g�̃C���f�b�N�X���X�g���C���f�b�N�X��
			//INDEX_TO_DIRECT�Ȃ�΁A�R���g���[���|�C���g�̃C���f�b�N�X���X�g����C���f�b�N�X���X�g���Q�Ƃ��A�C���f�b�N�X���擾����
			auto index = (reference_mode == fbxsdk::FbxLayerElement::eDirect) ?
				it : index_array.GetAt(it);
			vec.emplace_back(index);
		}
	}
	else if (mapping_mode == fbxsdk::FbxLayerElement::eByPolygonVertex) {
		auto polygon_count = p_mesh->GetPolygonCount();
		int polygon_index = 0;
		//�|���S�������Ԃ��
		for (int i = 0; i < polygon_count; ++i) {
			auto polygon_size = p_mesh->GetPolygonSize(i);
			//�|���S���̒��_�T�C�Y����
			for (int j = 0; j < polygon_size; ++j) {
				//�Q�Ə����m�F���AeDirect�Ȃ�΃|���S���C���f�b�N�X��@���C���f�b�N�X��
				//INDEX_TO_DIRECT�Ȃ�΁A�|���S���C���f�b�N�X����C���f�b�N�X���X�g���Q�Ƃ��A�C���f�b�N�X���擾����
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

*	@brief	���b�V������C���f�b�N�X���g���G�������g�̃f�[�^���擾����

*	@param[in]	p_element	���b�V���̃G�������g
*	@param[in]	index	�G�������g�̃C���f�b�N�X

*	@return	�G�������g�̗v�f

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

*	@brief	���b�V�����璸�_�̍��W���擾����

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	index		�C���f�b�N�X

*	@return	���W���

*/
auto GetMeshPositionData(FbxGeometryBase* p_fbx_mesh, unsigned short index) {
	auto cp = p_fbx_mesh->GetControlPointAt(index);
	return GALib::Math::Vector3(cp[0], cp[1], cp[2]);
}

/**

*	@brief	�����̃C���f�b�N�X���X�g���狤�ʃC���f�b�N�X���X�g���쐬����

*/
auto GetCompIndices(Indices& control_point_indices,Indices& uv_indices, Indices& normal_indices, Indices& binormal_indices, Indices& tangent_indices) {
	//�C���f�b�N�X���X�g�̍쐬
	{
		VertexElementIndices v_list;
		v_list.resize(control_point_indices.size());

		for (int i = 0; i < v_list.size(); ++i) {
			v_list[i].m_position_index = control_point_indices[i];

			//�C���f�b�N�X���Ȃ���΃R�s�[���Ȃ�
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

		//���_�C���f�b�N�X��o�^���Ă����A����̒��_���Q�Ƃ���ꍇ�C���f�b�N�X������
		Indices indices;
		std::vector<S_VertexElementIndex> entry_vertex;

		indices.reserve(control_point_indices.size());

		//�o�^�������_�Ɠ���̒��_������΃C���f�b�N�X��o�^����
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

		//���꒸�_��������Ȃ������ꍇ�A���_��o�^���V�����C���f�b�N�X��o�^���C���f�b�N�X�����Z����
		//���_�����������ꍇ�̓C���f�b�N�X�݂̂�o�^����
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

*	@brief	���b�V������P���_�̃f�[�^���擾����

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@parma[in]	index		���_�v�f�̃C���f�b�N�X�\����

*	@return	���_�f�[�^

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

*	@brief	���b�V�����\�z���钸�_�z����擾����

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	v_element_indices	���_�v�f�̃C���f�b�N�X�z��

*	@return	���_�z��

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

*	@brief	���b�V�����\�z���钸�_�̃{�[���E�F�C�g���擾����

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	p_skeleton	�\�z�ς݃X�P���g�����
*	@param[in]	v_element_indices	���_�v�f�̃C���f�b�N�X�z��

*	@return	�E�F�C�g�z��

*/
auto GetMeshVertexBoneWeightArray(FbxMesh* p_fbx_mesh, SkeletonPtr p_skeleton,VertexElementIndices& v_element_indices) {
	using IndexAndWeight = std::pair<int, float>;
	using TempBoneWeightList = std::vector<std::vector<IndexAndWeight>>;
	using BoneWeightList = std::vector<S_BoneWeight>;
	//�X�L���̃f�t�H�[�}�[�̐����擾����
	auto skin_count = p_fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);

	//�X�L���͈�˂܂�
	assert(skin_count <= 1);


	//���b�V���̃R���g���[���|�C���g�̐����擾
	auto control_points_count = p_fbx_mesh->GetControlPointsCount();

	//���b�V�����_�Ƃ���ɑΉ�����{�[���̃E�F�C�g���X�g���
	TempBoneWeightList temp_bone_weight_list(control_points_count);

	auto mesh_name = p_fbx_mesh->GetNode()->GetName();
	//�X�L��������΃{�[������E�F�C�g���Ƃ�
	if (skin_count){
		//�X�L�������������f�t�H�[�}�[�̎擾
		auto p_skin = static_cast<FbxSkin*>(p_fbx_mesh->GetDeformer(0, FbxDeformer::eSkin));

		//�{�[���̐����擾
		auto cluster_count = p_skin->GetClusterCount();

		for (int i = 0; i < cluster_count; ++i) {
			auto p_cluster = p_skin->GetCluster(i);

			//�N���X�^������X�P���g���̃{�[���ʒu���擾���A�{�[���C���f�b�N�X�ɂ���
			auto bone_index = p_skeleton->FindBoneIndex(p_cluster->GetLink()->GetName());

			//enomalize(�{�[���̃E�F�C�g�̍��v�l��1.0f�Ńm�[�}���C�Y����Ă�����́j�����Ή����Ȃ�
			assert(p_cluster->GetLinkMode() == FbxCluster::eNormalize);

			//�N���X�^���e����^���郁�b�V���̒��_�z��ւ̃C���f�b�N�X�z��̐��Ƃ��̃C���f�b�N�X�z��̎擾
			auto index_count = p_cluster->GetControlPointIndicesCount();
			auto indices = p_cluster->GetControlPointIndices();

			//�E�F�C�g�̔z����擾
			auto weights = p_cluster->GetControlPointWeights();

			//�N���X�^�C���f�b�N�X�ƃE�F�C�g��Ώے��_�C���f�b�N�X�ɂ��킹�ē˂�����
			for (int j = 0; j < index_count; ++j) {
				auto control_point_index = indices[j];
				temp_bone_weight_list[control_point_index].push_back({ bone_index,weights[j] });
			}
		}
	}



	//�d�݂����O�A���K������

	BoneWeightList bone_weight_list;
	bone_weight_list.reserve(control_points_count);
	for (auto &tmp_bone_weight : temp_bone_weight_list) {
		//�\�[�g
		std::sort(tmp_bone_weight.begin(), tmp_bone_weight.end(),
			[](const IndexAndWeight& weightA, const IndexAndWeight& weightB) { return weightA.second > weightB.second; }
		);

		//���������E�F�C�g����0�Ȃ�΃{�[�������݂��Ȃ��̂ŁA���b�V���v�Z�p�_�~�[�𓊓�����
		if (tmp_bone_weight.size() == 0 && skin_count == 0) {
			auto bone_index = p_skeleton->FindBoneIndex(mesh_name);
			tmp_bone_weight.push_back({ bone_index, 1.0f });
			tmp_bone_weight.push_back({ 0, 0.0f });
			tmp_bone_weight.push_back({ 0, 0.0f });
			tmp_bone_weight.push_back({ 0, 0.0f });
		}

		// 1���_��4��葽���E�F�C�g������U���Ă���Ȃ�e�������Ȃ����͖̂�������
		while (tmp_bone_weight.size() > 4)
		{
			tmp_bone_weight.pop_back();
		}

		// 4�ɖ����Ȃ��ꍇ�̓_�~�[��}��
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

		// �E�F�C�g�̐��K��
		for (int i = 0; i < 4; ++i)
		{
			weight.m_bone_weight.m_elements[i] /= total;
		}

		bone_weight_list.push_back(weight);
	}

	//�E�F�C�g�z������b�V���̃C���f�b�N�X�z��ɂ��킹�ēW�J����
	//�C���f�b�N�X�ɂ�铯�꒸�_�̏������s���ꍇ�͕K�v�Ȃ�
	BoneWeightList list;
	list.reserve(v_element_indices.size());
	for (auto index : v_element_indices) {
		list.push_back(bone_weight_list[index.m_position_index]);
	}

	return list;
}


/**

*	@brief	FbxMesh���烁�b�V���f�[�^���\�z����

*	@param[in]	p_fbx_mesh	FbxMesh*
*	@param[in]	p_skeleton	�\�z�ς݃X�P���g�����

*	@return	���b�V��

*/
MeshPtr CreateMesh(FbxMesh* p_fbx_mesh, SkeletonPtr p_skeleton) {
	auto p_mesh = std::make_shared<C_Mesh>();
	p_mesh->SetMeshName(p_fbx_mesh->GetNode()->GetName());
	OSReport("Mesh : %s\n",p_mesh->GetMeshName());

	//���b�V���̃R���g���[���|�C���g�̃C���f�b�N�X�z����擾
	auto control_point_indices = GetMeshControlPointIndices(p_fbx_mesh);
	auto uv_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementUV(), control_point_indices);
	auto normal_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementNormal(), control_point_indices);
	auto binormal_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementBinormal(), control_point_indices);
	auto tangent_indices = GetMeshElementIndices(p_fbx_mesh, p_fbx_mesh->GetElementTangent(), control_point_indices);


	auto pair = GetCompIndices(control_point_indices, uv_indices,normal_indices,binormal_indices,tangent_indices);
	auto vertices = GetMeshVertices(p_fbx_mesh,pair.first);
	auto bone_weight_list = GetMeshVertexBoneWeightArray(p_fbx_mesh, p_skeleton, pair.first);

	//�{�[���E�F�C�g�̃R�s�[
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

*	@brief	�X�P���g���Ƀx�[�X�|�[�Y�̋t�s��z����\�z����

*	@param[in]	p_skeleton	�\�z�ς݃X�P���g�����
*	@param[in]	p_fbx_mesh	FbxMesh*

*	@return	�Ȃ�

*/
void AddInverseBasePoseMatricesToSkeleton(SkeletonPtr p_skeleton,FbxMesh* p_fbx_mesh){
	//�X�P���g���Ɉ�؃{�[�������݂��Ȃ���΃A�j���[�V�����͂Ȃ�
	if (p_skeleton->GetBoneCount() == 0) return;


	//�X�L���̃f�t�H�[�}�[�̐����擾����
	auto skin_count = p_fbx_mesh->GetDeformerCount(FbxDeformer::eSkin);

	//�X�L���͈�˂܂�
	assert(skin_count <= 1);

	
	//�X�L�����Ȃ���΃��b�V���̋t�s��𐶐�
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
		//�X�L�������������f�t�H�[�}�[�̎擾
		auto p_skin = static_cast<FbxSkin*>(p_fbx_mesh->GetDeformer(0, FbxDeformer::eSkin));

		//�{�[���̐����擾
		auto cluster_count = p_skin->GetClusterCount();

		for (int i = 0; i < cluster_count; ++i) {
			auto p_cluster = p_skin->GetCluster(i);

			//�N���X�^������X�P���g���̃{�[���C���f�b�N�X���擾
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

*	@brief	FbxMesh����}�e���A�������擾���A�\�z����

*	@param[in]	p_fbx_mesh	FbxMesh*

*	@return	�}�e���A��

*/
MaterialPtr GetMeshMaterial(FbxMesh* p_fbx_mesh) {
	using TextureInfo = C_Material::C_TextureInfo;
	using VectorInfo = C_Material::C_VectorInfo;
	auto p_mat = std::make_shared<C_Material>();

	auto material_count = p_fbx_mesh->GetElementMaterialCount();
	if (material_count == 0) {
		OSReport("�}�e���A�����Ȃ����ۂ�\n");
		return p_mat;
	}

	//���炭�}�e���A���̓K�p�ӏ�
	//�}�b�s���O���S�̂łȂ���Ζ����|�C���^��Ԃ�
	auto p_fbx_layer_material = p_fbx_mesh->GetElementMaterial();

	if (p_fbx_layer_material->GetMappingMode() != FbxLayerElement::eAllSame) return p_mat;


	//0�Ԗڂ̃}�e���A���̂ݎg�p
	int index = p_fbx_layer_material->GetIndexArray()[0];
	auto p_fbx_material = p_fbx_mesh->GetNode()->GetMaterial(index);
	OSReport("Material : %s\n", p_fbx_material->GetName());
	p_mat->SetMaterialName(p_fbx_material->GetName());

	//�C���v�������g�̎擾
	auto impl = GetImplementation(p_fbx_material, FBXSDK_IMPLEMENTATION_CGFX);
	if (!impl) {
		impl = GetImplementation(p_fbx_material, FBXSDK_IMPLEMENTATION_HLSL);
	}

	//�C���v�����擾�ł��Ȃ������̂Ń}�e���A���J���[�̎擾
	if (!impl) {
		if (p_fbx_material->GetClassId().Is(FbxSurfacePhong::ClassId)) {
			auto p_phong = (FbxSurfacePhong*)p_fbx_material;
			//�f�B�t�[�Y
			{
				auto v = p_phong->Diffuse.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_DIFFUSE,
					(float)v[0],(float)v[1],(float)v[2]
				});
				
			}

			//�A���r�G���g
			{
				auto v = p_phong->Ambient.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_AMBIENT,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//�X�y�L��
			{
				auto v = p_phong->Specular.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_SPECULAR,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//�V���C�l�X
			{
				auto v = p_phong->Shininess.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_SHININESS,
					(float)v
				});
			}

			//�X�y�L�����t�@�N�^
			{
				auto v = p_phong->SpecularFactor.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_SPECULAR_FACTOR,
					(float)v
				});
			}

			//�G�~�b�V�u
			{
				auto v = p_phong->Emissive.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_EMISSIVE,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//�I�p�V�e�B
			{
				auto v = p_phong->TransparencyFactor.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V1,
					VectorInfo::eVectorType::TYPE_TRANSPARENCY_FACTOR,
					(float)v
				});
			}

			//���t���N�e�B�r�e�B
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
			//�f�B�t�[�Y
			{
				auto v = p_lam->Diffuse.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_DIFFUSE,
					(float)v[0],(float)v[1],(float)v[2]
				});

			}

			//�A���r�G���g
			{
				auto v = p_lam->Ambient.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_AMBIENT,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}


			//�G�~�b�V�u
			{
				auto v = p_lam->Emissive.Get();
				p_mat->AddVectorInfo({
					VectorInfo::eVectorDimention::DIM_V3,
					VectorInfo::eVectorType::TYPE_EMISSIVE,
					(float)v[0],(float)v[1],(float)v[2]
				});
			}

			//�I�p�V�e�B
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
			OSReport("�}�e���A���s��\n");
		
		return p_mat;
	}
	
	//impl���擾�ł����̂Ńe�N�X�`�����Ƃ��̎擾
	auto p_root_table = impl->GetRootTable();
	auto entry_count = p_root_table->GetEntryCount();
	for (int table = 0; table < entry_count; ++table) {
		auto entry_table = p_root_table->GetEntry(table);
		auto entry_type = entry_table.GetEntryType(true);

		FbxProperty prop;

		//�v���p�e�B���擾����
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

		//�v���p�e�B���擾�ł��Ȃ���Ώ������L�����Z��
		if (!prop.IsValid()) {
			continue;
		}

		auto str = entry_table.GetSource();

		//�Ƃ肠�����\�[�X�̖��O�擾
		auto source_type_name = std::string(str);
		OSReport("SourceType : %s\n", source_type_name.c_str());

		//���O����Ȃ񂩌�������
		auto Find = [&](const char* a) {
			if (source_type_name.find(a) == std::string::npos) return false;
			return true;
		};

		//�t�@�C���e�N�X�`�����擾
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

			//������Γo�^
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
		//�e�N�X�`������Ȃ���΂Ȃ񂩂Ȃ̂łȂ񂩕K�v�Ȃ��̂�o�^����
		else {


			//�����炭maya��ł̃G�~�b�V�u�l
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

			//���͋C����������ǉ�����

		
		}


	}

	return p_mat;
}

/**

*	@brief	FbxScene�̃A�j���[�V����������ǂ��A�X�P���g���ɃA�j���[�V�����s���˂�����

*	@param[in]	p_scene	FbxScene*
*	@param[in]	dic	�V�[���̃m�[�h�ƃC���f�b�N�X����
*	@param[in]	p_skeleton	�X�P���g��
*	@param[in]	end_frame	�A�j���[�V�����̏I���t���[��

*	@return	�Ȃ�

*/
void AddAnimationMatricesToSkeleton(FbxScene* p_scene,AnimeSceneNodeDictionary& dic, SkeletonPtr p_skeleton,int end_frame) {
	p_skeleton->SetAnimationEndFrame(end_frame);
	//�X�P���g�����̃A�j���[�V�����s��z������T�C�Y����
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

			//���[�J���s��͂��̂����Ή�����
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
//ShapeMesh�֘A
//----------------------------------------------------------
/**

*	@brief	�u�����h�V�F�v���b�V���̍쐬

*/
ShapeMeshPtr CreateBlendShapeMesh(FbxMesh* p_parent_fbx_mesh, FbxShape* p_shape, SkeletonPtr p_skeleton) {
	//���b�V���̃R���g���[���|�C���g�̃C���f�b�N�X�z����擾
	auto control_point_indices = GetMeshControlPointIndices(p_parent_fbx_mesh);

	//���b�V������uv���Ƃ��Ă��Ȃ��ƃC���f�b�N�X���ʉ��ŃY����\�������ɍ����̂Ń_�~�[�ňꉞ�Ƃ��Ă���A�Ǝ��`�����ɂ͊�{�Ȃ����
	auto uv_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_parent_fbx_mesh->GetElementUV(), control_point_indices);
	auto normal_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_shape->GetElementNormal(), control_point_indices);
	auto binormal_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_shape->GetElementBinormal(), control_point_indices);
	auto tangent_indices = GetMeshElementIndices(p_parent_fbx_mesh, p_shape->GetElementTangent(), control_point_indices);



	auto pair = GetCompIndices(control_point_indices, uv_indices, normal_indices, binormal_indices, tangent_indices);
	auto vertices = GetMeshVertices(p_shape, pair.first);

	auto p_mesh = std::make_shared<C_ShapeMesh>();
	p_mesh->CopyVertices(vertices);
	p_mesh->SetVertexType(eVertexType::TYPE_PUNTBW);

	//�ڐ��A�]�@�����Ȃ���΁A�������ݒ��_��PN�ƂȂ�
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

		//�`�����l���̃Z�b�g
		int target_shape_count = p_channel->GetTargetShapeCount();

		auto p_shape = p_channel->GetTargetShape(0);
		auto p_shape_mesh = CreateBlendShapeMesh(p_fbx_mesh, p_shape, p_skeleton);

		//�V�F�C�v���b�V���ƃ��b�V���̃o�b�t�@�T�C�Y��������烁�����j����N�����Ď���
		assert(p_mesh->GetVertexBufferSize() == p_mesh->GetVertexBufferSize());
		p_shape_mesh->SetMeshName(p_shape->GetName());
		OSReport("ShapeName : %s\n", p_shape->GetName());

		p_mesh->AddBlendShapeMesh(p_shape_mesh);
		
	}
}

