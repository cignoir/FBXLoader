#include "Game.h"
#include "Settings.h"
#include "../GALib/D3D11/D3DUser.h"
#include <fbxsdk.h>
#include <unordered_map>
#include "../Skeleton.h"
#include "../FbxLoader.h"
#include "../FbxConvert.h"
/**

*	@brief	初期化関数
			GAライブラリの初期化後、ウィンドウ生成後に呼び出される

			ゲームの初期化処理はここに記述

*/
fbxsdk::FbxManager* g_p_fbx_manager = nullptr;
fbxsdk::FbxScene*	g_p_animation_scene = nullptr;
fbxsdk::FbxAnimLayer*	g_p_anime_layer = nullptr;
GALib::D3D11::GeneralBuffer* g_p_buffer;
GALib::Resource::SHADERHANDLE g_vs;
GALib::Resource::SHADERHANDLE g_shape_vs;

GALib::Resource::SHADERHANDLE g_ps;
GALib::Resource::SHADERHANDLE g_il;
GALib::Resource::SHADERHANDLE g_shape_il;

GALib::Draw::SAMPLERHANDLE g_sam;


struct S_DrawMesh {
	GALib::D3D11::GeneralBuffer m_vertex_buffer;
	GALib::D3D11::GeneralBuffer m_index_buffer;
	std::vector<GALib::D3D11::GeneralBuffer> m_shape_buffer;
	int m_vertex_count;
	int m_index_count;
	int m_material_index;
};

struct S_DrawMeshes {
	std::list<S_DrawMesh> m_draw_mesh_list;
	std::vector<GALib::Resource::GHANDLE> m_textures;
	std::vector<GALib::Resource::GHANDLE> m_fall_off_texture;
	GALib::D3D11::GeneralBuffer m_inverse_pose_buffer;
	GALib::D3D11::GeneralBuffer m_pose_buffer;
	GALib::D3D11::GeneralBuffer	m_shape_time;
};

struct S_ShapeTime {
	float time1 = 1;
	float dummy[3];
};


S_DrawMeshes* g_p_meshes;
SkeletonPtr	g_p_anime_skeleton;
S_ShapeTime g_shape_time;
void GALib::Game::Initialize(){
	g_p_meshes = new S_DrawMeshes;
	const char* file_name = "unitychan.fbx";
	const char* anime_name = "unitychan_WAIT04.fbx";
	Fbx::ConvertFbxMesh(file_name,true,eVertexType::TYPE_PUNW);
	Fbx::ConvertFbxAnimation(anime_name, file_name);
	auto pair = Fbx::LoadSMDL("unitychan.smdl");
	//auto pair = Fbx::LoadMeshesAndSkeleton(file_name);
	//const char* file_name = "humanoid.fbx";
	//const char* anime_name = "humanoid.fbx";
	
	g_p_anime_skeleton = Fbx::LoadSKIN("Take 001.smdlskin", pair.second);

	//メッシュを作る
	int mesh_count = pair.first->GetMeshCount();
	for (int i = 0; i < mesh_count; ++i) {
		auto p_mesh = pair.first->GetMesh(i);
		S_DrawMesh mesh;
		mesh.m_index_count = p_mesh->GetIndexCount();
		mesh.m_vertex_count = p_mesh->GetVertexCount();
		mesh.m_index_buffer.Initialize(sizeof(unsigned short) * mesh.m_index_count, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, p_mesh->GetIndexBufferPtr());
		mesh.m_vertex_buffer.Initialize(sizeof(S_VertexPUNW) * mesh.m_vertex_count, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, p_mesh->GetVertexBufferPtr());
		mesh.m_material_index = p_mesh->GetMaterialIndex();

		auto shape_count = p_mesh->GetBlendShapeMeshCount();
		mesh.m_shape_buffer.resize(shape_count);
		for (int s = 0; s < shape_count; ++s) {
			mesh.m_shape_buffer[s].Initialize(sizeof(S_VertexPN) * mesh.m_vertex_count, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, p_mesh->GetBlendShapeMesh(s)->GetVertexBufferPtr());
		}
		g_p_meshes->m_draw_mesh_list.push_back(mesh);
	}

	int mat_count = pair.first->GetMaterialCount();
	for (int i = 0; i < mat_count; ++i) {
		auto p_mat = pair.first->GetMaterial(i);
		int info_count =  p_mat->GetTextureInfoCount();
		for (int j = 0; j < info_count; ++j) {
			auto p_info = p_mat->GetTextureInfo(j);
			if (p_info->GetTextureType() == C_Material::C_TextureInfo::eTextureType::TYPE_DIFFUSE) {
				auto g = GALib::Resource::TextureManager::LoadGraph(p_info->GetTextureName());
				g_p_meshes->m_textures.push_back(g);
			}
			if (p_info->GetTextureType() == C_Material::C_TextureInfo::eTextureType::TYPE_FALLOFF) {
				auto g = GALib::Resource::TextureManager::LoadGraph(p_info->GetTextureName());
				g_p_meshes->m_fall_off_texture.push_back(g);
			}
		}
	}

	//アニメーションメッシュをいったん作る
	g_p_meshes->m_inverse_pose_buffer.Initialize(sizeof(GALib::Math::Matrix4x4) * g_p_anime_skeleton->GetBoneCount(), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, pair.second->GetInversePoseMatrixArray());
	g_p_meshes->m_pose_buffer.Initialize(sizeof(GALib::Math::Matrix4x4) * g_p_anime_skeleton->GetBoneCount(), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0);


	g_p_meshes->m_shape_time.Initialize(sizeof(S_ShapeTime), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0,&g_shape_time);
	//シェーダ読み込み
	g_vs = GALib::Resource::ShaderManager::LoadVertexShader("VertexShader");
	g_shape_vs = GALib::Resource::ShaderManager::LoadVertexShader("VertexShaderShape");

	g_ps = GALib::Resource::ShaderManager::LoadPixelShader("PixelShader");
	{
		g_il = GALib::Resource::ShaderManager::CreateInputLayoutHandle(g_vs);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "POSITION", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "TEXCOORD", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RG32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "NORMAL", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		//GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "BINORMAL", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		//GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "TANGENT", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "BONE_INDEX", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGBA32_UINT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "BONE_WEIGHT", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGBA32_FLOAT);

		GALib::Resource::ShaderManager::CreateInputLayout(g_il);
	}

	{
		g_shape_il = GALib::Resource::ShaderManager::CreateInputLayoutHandle(g_shape_vs);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "POSITION", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "TEXCOORD", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RG32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "NORMAL", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		//GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "BINORMAL", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		//GALib::Resource::ShaderManager::AddInputLayoutElement(g_il, "TANGENT", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "BONE_INDEX", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGBA32_UINT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "BONE_WEIGHT", 0, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGBA32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "S_POS", 1, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);
		GALib::Resource::ShaderManager::AddInputLayoutElement(g_shape_il, "S_NORM", 1, GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT);

		GALib::Resource::ShaderManager::CreateInputLayout(g_shape_il);

	}
	g_sam = GALib::Draw::SamplerManager::CreateSampler(GALib::Draw::SamplerManager::C_FilterTypes::FILTER_BILINEAR, GALib::Draw::SamplerManager::C_ClampTypes::CLAMP_WRAP);
}

/**

*	@brief	更新関数
			更新関数が呼び出される前に深度などの初期化が入り
			更新関数が呼び出された後でフリップ処理が入る

			ゲームの更新描画処理はここに記述

*/
bool GALib::Game::Update(){

	static GALib::Math::Matrix4x4 rot;
	rot *= GALib::Math::Matrix4x4::s_CreateRotationX(0.01);
	static float x = 0;
	static float y =100;
	static float z =150;
	static int count = 0;
	static float anime_count = 0;
	static int index = 0;
	auto projection = GALib::Math::Matrix4x4::s_CreatePerspectiveProjection(GALib::Math::GetPiDivision4<float>(), (float)s_GAME_SCREEN_WIDTH / (float)s_GAME_SCREEN_HEIGHT, 0.1f, 1000.0f);
	projection.Transpose();
	auto view = GALib::Math::Matrix4x4::s_CreateLookAt(Math::Vector3(x, y, z), Math::Vector3(0, 100, 0), Math::Vector3::m_s_UP_DIRECTION);

	if (count == 0) {
		if (GetKeyState(VK_UP) < 0) {
			g_shape_time.time1 += 0.1f;
			count = 2;
		}

		if (GetKeyState(VK_DOWN) < 0) {
			g_shape_time.time1 -= 0.1f;
			count = 2;
		}

		if (g_shape_time.time1 < 0) g_shape_time.time1 = 0;
		if (g_shape_time.time1 > 1) g_shape_time.time1 = 1;


		if (GetKeyState(VK_RIGHT) < 0) {
			index++;
			count = 10;

		}

		if (GetKeyState(VK_LEFT) < 0) {
			index--;
			count = 10;

		}
		if (index < 0) index = 0;
	}
	view.Transpose();
	GALib::Draw::SetMatricesInVertexShader(g_vs, Math::Matrix4x4::m_s_IDENTITY, view, projection);
	GALib::Draw::SetCulling(GALib::Draw::CULLING_NONE);
	GALib::Draw::SetDepth(true, true);
	GALib::Draw::SetSampler(GALib::Draw::SamplerManager::CreateSampler(GALib::Draw::SamplerManager::C_FilterTypes::FILTER_BILINEAR, GALib::Draw::SamplerManager::C_ClampTypes::CLAMP_WRAP),0);
	
	GALib::D3D11::GetImmediateContext()->PSSetShader((ID3D11PixelShader*)g_ps->GetShader(), nullptr, 0);
	GALib::D3D11::GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (anime_count >= g_p_anime_skeleton->GetAnimationEndFrame()) {
		anime_count = 0;
	}
	g_p_anime_skeleton->SetAnimationFrame(anime_count);

	auto matrices = g_p_anime_skeleton->Calc([](C_Skeleton* p_this)
	{
		std::vector<GALib::Math::Matrix4x4> matrices;
		auto bone_count = p_this->GetBoneCount();

		matrices.resize(bone_count);
		for (int i = 0; i < bone_count; ++i) {
			auto bone = p_this->GetBone(i);
			auto mat = bone->GetAnimationMatrix<GALib::Math::Matrix4x4>(p_this->GetAnimationFrame());
			matrices[i] = mat;
		}

		return matrices;
	});


	GALib::D3D11::UpdateConstantBuffer(D3D11::GetImmediateContext(), (ID3D11Buffer*)g_p_meshes->m_pose_buffer.GetBuffer(), matrices.data());
	GALib::D3D11::UpdateConstantBuffer(D3D11::GetImmediateContext(), (ID3D11Buffer*)g_p_meshes->m_shape_time.GetBuffer(),&g_shape_time);

	GALib::D3D11::VSSetConstantBuffers(D3D11::GetImmediateContext(), 1,
		(ID3D11Buffer*)g_p_meshes->m_inverse_pose_buffer.GetBuffer(),
		(ID3D11Buffer*)g_p_meshes->m_pose_buffer.GetBuffer(),
		(ID3D11Buffer*)g_p_meshes->m_shape_time.GetBuffer()
		);
	GALib::D3D11::PSSetSampler(D3D11::GetImmediateContext(), 0, (ID3D11SamplerState*)g_sam->GetSampler());
	for (auto &it : g_p_meshes->m_draw_mesh_list) {
		if (it.m_shape_buffer.size()) {
			UINT stride[] = { sizeof(S_VertexPUNW),sizeof(S_VertexPN) };
			UINT offset[] = { 0 ,0 };
			auto size = it.m_shape_buffer.size();
			auto shape_index = index;
			if (shape_index >= size) shape_index = size - 1;
			if (shape_index < 0) shape_index = 0;
			GALib::D3D11::GetImmediateContext()->IASetInputLayout((ID3D11InputLayout*)g_shape_il->GetShader());
			GALib::D3D11::GetImmediateContext()->VSSetShader((ID3D11VertexShader*)g_shape_vs->GetShader(), nullptr, 0);
			GALib::D3D11::IASetVertexBuffers(D3D11::GetImmediateContext(), 0, stride, offset, (ID3D11Buffer*)it.m_vertex_buffer.GetBuffer(), (ID3D11Buffer*)it.m_shape_buffer[shape_index].GetBuffer());
			GALib::D3D11::IASetIndexBuffer(D3D11::GetImmediateContext(), (ID3D11Buffer*)it.m_index_buffer.GetBuffer());
			auto ptr = g_p_meshes->m_textures[it.m_material_index]->GetTextureAPIPtr();
			D3D11::PSSetShaderResource(D3D11::GetImmediateContext(), 0, (ID3D11ShaderResourceView*)ptr);
			D3D11::GetImmediateContext()->DrawIndexed(it.m_index_count, 0, 0);
		}
		else {
			UINT stride[] = { sizeof(S_VertexPUNW) };
			UINT offset[] = { 0 };
			GALib::D3D11::GetImmediateContext()->IASetInputLayout((ID3D11InputLayout*)g_il->GetShader());
			GALib::D3D11::GetImmediateContext()->VSSetShader((ID3D11VertexShader*)g_vs->GetShader(), nullptr, 0);
			GALib::D3D11::IASetVertexBuffers(D3D11::GetImmediateContext(), 0, stride, offset, (ID3D11Buffer*)it.m_vertex_buffer.GetBuffer());
			GALib::D3D11::IASetIndexBuffer(D3D11::GetImmediateContext(), (ID3D11Buffer*)it.m_index_buffer.GetBuffer());
			auto ptr = g_p_meshes->m_textures[it.m_material_index]->GetTextureAPIPtr();
			D3D11::PSSetShaderResource(D3D11::GetImmediateContext(), 0, (ID3D11ShaderResourceView*)ptr);
			D3D11::GetImmediateContext()->DrawIndexed(it.m_index_count, 0, 0);
		}
	}
	if(GetKeyState(VK_SPACE) < 0) anime_count++;
	if (count > 0) --count;

	return true;

}


/**

*	@brief	終了処理関数
			この関数が呼び出されたあとにウィンドウが破棄され、GAライブラリが終了する
			GAライブラリが生成するリソースはこの関数が終了した時点で全て破棄されていなければならない

			ゲームの終了処理はここに記述

*/
void GALib::Game::Finalize(){

	g_vs.Reset();
	g_ps.Reset();
	g_il.Reset();
	g_sam.Reset();
	g_shape_il.Reset();
	g_shape_vs.Reset();
}