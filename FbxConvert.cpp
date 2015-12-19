#include "FbxConvert.h"

using WriteFunc = std::function<void(void*, int)>;
using ReadFunc = std::function<void(void*, int)>;

void WriteVertexBuffer(WriteFunc write_func, void* v_buffer, int v_count, eVertexType v_type);
void WriteConvertMesh(WriteFunc write_func,MeshPtr p_mesh, bool write_name, eVertexType write_vertex_type);
void WriteConvertShapeMesh(WriteFunc write_func, ShapeMeshPtr p_shape_mesh,int v_count, bool write_name);
void WriteConvertMaterial(WriteFunc write_func,  MaterialPtr p_mat, bool write_name);
void WriteConvertSkeleton(WriteFunc write_func,SkeletonPtr p_skeleton, bool write_name, eMatrixType write_mat_type);
void WriteConvertBone(WriteFunc write_func, BonePtr p_bone, bool write_name, eMatrixType write_mat_type);
void ReadConvertMesh(ReadFunc read_func, MeshesPtr p_meshes,bool read_name,eVertexType v_type);
void ReadConvertShapeMesh(ReadFunc read_func, MeshPtr p_mesh, bool read_name);
void ReadConvertMaterial(ReadFunc read_func, MeshesPtr p_meshes, bool read_name);
void ReadConvertSkeleton(ReadFunc read_func, SkeletonPtr p_skeleton, bool read_name);
void ReadConvertBone(ReadFunc read_func, SkeletonPtr p_skeleton, bool read_name);


/**

*	@brief	FBX��Ǝ��`���ɕϊ�����
�s������̂͂��̂������

*	@param[in]	file_path	FBX�ւ̃t�@�C���p�X
*	@param[in]	write_name	���b�V�����A�{�[�����A�}�e���A�������o�͂��邩�ǂ���
*	@param[in]	write_vertex_type	�o�͂��郁�b�V���̒��_���

*	@return	�Ȃ�

*/
void Fbx::ConvertFbxMesh(const char* file_path, bool write_name, eVertexType write_vertex_type, eMatrixType write_mat_type){
	auto pair = LoadMeshesAndSkeleton(file_path);


	FILE* fp = nullptr;
	auto str = std::string(file_path);
	auto pos = str.find_last_of(".");
	str.replace(pos, 5, ".smdl");
	fopen_s(&fp, str.c_str(), "wb");
	auto write_func = [fp](void* buffer, int size) {
		fwrite(buffer, size, 1, fp);
	};

	auto p_meshes = pair.first;

	char mesh_count = p_meshes->GetMeshCount();
	char mat_count = p_meshes->GetMaterialCount();
	char v_type = (char)write_vertex_type;
	bool skeleton = pair.second->GetBoneCount();

	write_func(&mesh_count, 1);
	write_func(&mat_count, 1);
	write_func(&v_type, 1);
	write_func(&write_name, 1);

	//�{�[��������΃X�P���g���\�����o�͂���

	//�X�P���g���\�������݂��邩�ǂ���
	if (skeleton) {
		char v = 1;
		write_func(&v, 1);
	}
	else {
		char v = 0;
		write_func(&v, 1);
	}

	//���b�V����񏑂�����
	for (int i = 0; i < mesh_count; ++i) {
		auto p_mesh = p_meshes->GetMesh(i);
		WriteConvertMesh(write_func, p_mesh, write_name ,write_vertex_type);
	}
	//�}�e���A����������
	for (int i = 0; i < mat_count; ++i) {
		auto p_mat = p_meshes->GetMaterial(i);
		WriteConvertMaterial(write_func, p_mat, write_name);
	}

	//�X�P���g���o��
	WriteConvertSkeleton(write_func, pair.second, write_name,write_mat_type);

	fclose(fp);
}

/**

*	@brief	FBX����ǂݍ��񂾒��_�o�b�t�@����������

*	@param[in]	write_func	�������݊֐�
*	@param[in]	v_buffer	���_�o�b�t�@�̐擪�|�C���^
*	@param[in]	v_count		���_�J�E���g
*	@param[in]	v_type		�������ݒ��_�^�C�v

*	@return	�Ȃ�

*/
void WriteVertexBuffer(WriteFunc write_func,void* v_buffer,int v_count, eVertexType write_vertex_type) {
	auto GetVertex = [](void* v_buffer, int count) {
		auto v = (S_VertexPUNTBW*)v_buffer + count;
		return *v;
	};

	//�o�͂ɍ��킹�ď������
	for (int v = 0; v < v_count; ++v) {
		bool end = false;
		auto vertex = GetVertex(v_buffer,v);

		switch (write_vertex_type)
		{
		case eVertexType::TYPE_PUNTBW:
		{//�������K�v���Ȃ��̂ł��̂܂܃o�C�g�z����o�͂���
			write_func(v_buffer, sizeof(S_VertexPUNTBW) * v_count);
			end = true;
		}
		break;
		case eVertexType::TYPE_PUNTB:
		{
			S_VertexPUNTB write_v;
			write_v = vertex;
			write_func(&write_v, sizeof(write_v));
		}
		break;
		case eVertexType::TYPE_PUNW:
		{
			S_VertexPUNW write_v;
			write_v = vertex;
			write_func(&write_v, sizeof(write_v));
		}
		break;
		case eVertexType::TYPE_PUN:
		{
			S_VertexPUN write_v;
			write_v = vertex;
			write_func(&write_v, sizeof(write_v));
		}
		break;

		//�V�F�C�v���b�V��
		case eVertexType::TYPE_PNTB:
		{
			S_VertexPNTB write_v;
			write_v = vertex;
			write_func(&write_v, sizeof(write_v));
		}
		break;
		case eVertexType::TYPE_PN:
		{
			S_VertexPN write_v;
			write_v = vertex;
			write_func(&write_v, sizeof(write_v));
		}
		default:
			break;
		}

		if (end) break;
	}
}

/**

*	@brief	���b�V�������R���o�[�g����

*/
void WriteConvertMesh(WriteFunc write_func, MeshPtr p_mesh, bool write_name, eVertexType write_vertex_type) {
	char name_buffer[128] = {};
	strcpy_s(name_buffer, 128, p_mesh->GetMeshName());

	char mat_index = p_mesh->GetMaterialIndex();
	auto v_count = p_mesh->GetVertexCount();
	auto i_count = p_mesh->GetIndexCount();
	char shape_count = p_mesh->GetBlendShapeMeshCount();

	if(write_name) write_func(name_buffer, 128);

	write_func(&mat_index, 1);
	write_func(&v_count, 4);
	write_func(&i_count, 4);
	write_func(&shape_count, 1);

	//�o�͂ɍ��킹�ď������
	WriteVertexBuffer(write_func, p_mesh->GetVertexBufferPtr(), v_count, write_vertex_type);

	//�C���f�b�N�X�͈�C�ɏ�������
	write_func(p_mesh->GetIndexBufferPtr(), i_count * sizeof(unsigned short));


	//��������V�F�C�v�p���b�V����������
	for (int i = 0; i < shape_count; ++i) {
		auto p_shape_mesh = p_mesh->GetBlendShapeMesh(i);
		WriteConvertShapeMesh(write_func, p_shape_mesh, v_count, write_name);
	}
}

/**

*	@brief	�u�����h�V�F�C�v������������

*/
void WriteConvertShapeMesh(WriteFunc write_func, ShapeMeshPtr p_shape_mesh, int v_count, bool write_name) {
	char buffer[128] = {};
	strcpy_s(buffer, 128, p_shape_mesh->GetMeshName());

	char v_type = (char)p_shape_mesh->GetWriteVertexType();

	if (write_name) write_func(buffer, 128);
	write_func(&v_type, 1);

	WriteVertexBuffer(write_func, p_shape_mesh->GetVertexBufferPtr(), v_count, (eVertexType)v_type);
}
/**

*	@brief	�}�e���A�������R���o�[�g����

*/
void WriteConvertMaterial(WriteFunc write_func,MaterialPtr p_mat, bool write_name) {
	char buffer[128] = {};
	strcpy_s(buffer, 128, p_mat->GetMaterialName());
	
	char tex_num = p_mat->GetTextureInfoCount();
	char vec_num = p_mat->GetVectorInfoCount();

	if (write_name) write_func(buffer, 128);
	write_func(&tex_num, 1);
	write_func(&vec_num, 1);

	for (int i = 0; i < tex_num; ++i) {
		auto p_tex_info = p_mat->GetTextureInfo(i);
		strcpy_s(buffer, 128, p_tex_info->GetTextureName());
		auto tex_type = (char)p_tex_info->GetTextureType();

		write_func(buffer, 128);
		write_func(&tex_type, 1);
	}

	for (int i = 0; i < vec_num; ++i) {
		auto p_vec_info = p_mat->GetVectorInfo(i);
		char vec_dim = (char)p_vec_info->GetVectorDimention();
		char vec_type = (char)p_vec_info->GetVectorType();
		auto vec = p_vec_info->GetVector();

		write_func(&vec_dim, 1);
		write_func(&vec_type, 1);
		write_func(&vec, vec_dim * 4);
	}
}


/**

*	@brief	�X�P���g�������R���o�[�g����

*/
void WriteConvertSkeleton(WriteFunc write_func, SkeletonPtr p_skeleton, bool write_name, eMatrixType write_mat_type) {
	//�{�[�����Ƌt�s��̃o�C�g�T�C�Y���L�^
	unsigned short bone_count = p_skeleton->GetBoneCount();
	char mat_type_char = (char)write_mat_type;

	write_func(&bone_count, 2);
	write_func(&mat_type_char, 1);

	//����4x4�̂ݑΉ�
	if (write_mat_type == eMatrixType::TYPE_MAT4x4) {
		write_func(p_skeleton->GetInversePoseMatrixArray(), sizeof(GALib::Math::Matrix4x4) * bone_count);
	}
	else {
		assert(false);
	}

	//�{�[����������
	for (int i = 0; i < bone_count; ++i) {
		auto p_bone = p_skeleton->GetBone(i);
		WriteConvertBone(write_func, p_bone, write_name, write_mat_type);
	}
}

/**

*	@brief	�{�[�������R���o�[�g����

*/
void WriteConvertBone(WriteFunc write_func, BonePtr p_bone, bool write_name, eMatrixType write_mat_type) {
	char buffer[128] = {};
	strcpy_s(buffer, 128, p_bone->GetBoneName());

	short parent_index = p_bone->GetParentIndex();
	char bone_type = (char)p_bone->GetBoneType();
	char child_bone_index_count = p_bone->GetChildIndexCount();
	char mat_type = (char)write_mat_type;
	char math_type = (char)p_bone->GetMathType();

	if (write_name) write_func(buffer, 128);
	write_func(&parent_index, 2);
	write_func(&bone_type, 1);
	write_func(&child_bone_index_count, 1);
	write_func(&mat_type, 1);
	write_func(&math_type, 1);
	write_func(p_bone->GetChildIndexArrayPtr(), 2 * child_bone_index_count);
}



/**

*	@brief	�Ǝ��`���̃��f����ǂݍ���

*/
Fbx::MeshesAndSkeleton Fbx::LoadSMDL(const char* file_path){
	FILE* fp = nullptr;
	if (fopen_s(&fp, file_path, "rb")) assert(false);
	auto read_func = [fp](void* buffer, int size) {
		fread_s(buffer, size, size, 1, fp);
	};

	//���b�V���ǂݍ���
	auto p_meshes = std::make_shared<C_Meshes>();
	auto p_skeleton = std::make_shared<C_Skeleton>();
	char mesh_count;
	char mat_count;
	char v_type;
	char read_name;
	char skeleton;
	read_func(&mesh_count,1);
	read_func(&mat_count, 1);
	read_func(&v_type, 1);
	read_func(&read_name, 1);

	read_func(&skeleton, 1);
	p_meshes->ReserveMeshArray(mesh_count);
	p_meshes->ReserveMaterialArray(mesh_count);

	for (int i = 0; i < mesh_count; ++i) {
		ReadConvertMesh(read_func, p_meshes, read_name,(eVertexType)v_type);
	}

	for (int i = 0; i < mat_count; ++i) {
		ReadConvertMaterial(read_func, p_meshes, read_name);
	}

	if (skeleton) {
		ReadConvertSkeleton(read_func, p_skeleton, read_name);
	}

	return MeshesAndSkeleton(p_meshes,p_skeleton);
}

/**

*	@brief	�Ǝ��`���̃��b�V����ǂݍ���

*/
void ReadConvertMesh(ReadFunc read_func, MeshesPtr p_meshes, bool read_name, eVertexType v_type) {
	auto p_mesh = std::make_shared<C_Mesh>();
	char buffer[128] = {};
	char mat_index;
	int v_count;
	int i_count;
	char shape_count;

	if(read_name) read_func(buffer, 128);
	read_func(&mat_index, 1);
	read_func(&v_count, 4);
	read_func(&i_count, 4);
	read_func(&shape_count, 1);

	auto vb_size = S_VertexTypeSize::s_GetSize(v_type) *v_count;
	auto ib_size = 2 * i_count;
	auto v_buffer = std::malloc(vb_size);
	auto i_buffer = std::malloc(ib_size);

	read_func(v_buffer, vb_size);
	read_func(i_buffer, ib_size);

	p_mesh->CopyBufferToVertices(v_buffer, vb_size);
	p_mesh->CopyBufferToIndices(i_buffer, ib_size);
	p_mesh->SetMaterialIndex(mat_index);
	p_mesh->SetMeshName(buffer);
	p_mesh->SetVertexCount(v_count);
	p_mesh->SetVertexType(v_type);

	p_meshes->AddMesh(p_mesh);
	p_mesh->ReserveBlendShapeMeshArray(shape_count);
	for (int i = 0; i < shape_count; ++i) {
		ReadConvertShapeMesh(read_func, p_mesh, read_name);
	}

	std::free(v_buffer);
	std::free(i_buffer);
}

/**

*	@brief	�Ǝ��`���̃u�����h�V�F�C�v���b�V����ǂݍ���

*/
void ReadConvertShapeMesh(ReadFunc read_func, MeshPtr p_mesh, bool read_name) {
	auto p_shape = std::make_shared<C_ShapeMesh>();

	char buffer[128];
	char v_type;

	if (read_name) read_func(buffer, 128);
	read_func(&v_type, 1);

	int v_count = p_mesh->GetVertexCount();
	int size = S_VertexTypeSize::s_GetSize((eVertexType)v_type) * v_count;

	void* p_buffer = std::malloc(size);
	read_func(p_buffer, size);
	p_shape->CopyBufferToVertices(p_buffer, size);

	std::free(p_buffer);

	p_mesh->AddBlendShapeMesh(p_shape);
	p_shape->SetMeshName(buffer);
	p_shape->SetVertexType((eVertexType)v_type);
}

/**

*	@brief	�Ǝ��`���̃}�e���A����ǂݍ���

*/
void ReadConvertMaterial(ReadFunc read_func, MeshesPtr p_meshes, bool read_name) {
	auto p_mat = std::make_shared<C_Material>();
	p_meshes->AddMaterialPtr(p_mat);
	char buffer[128] = {};
	char tex_count;
	char vec_count;

	if(read_name) read_func(buffer, 128);
	read_func(&tex_count, 1);
	read_func(&vec_count, 1);

	p_mat->SetMaterialName(buffer);
	p_mat->ReserveTextureInfoArray(tex_count);
	p_mat->ReserveVectorInfoArray(vec_count);

	for (int i = 0; i < tex_count; ++i) {
		char tex_type;
		read_func(buffer, 128);
		read_func(&tex_type, 1);

		p_mat->AddTextureInfo(
		{
			buffer,(C_Material::C_TextureInfo::eTextureType)tex_type
		});
	}

	for (int i = 0; i < vec_count; ++i) {
		char vec_type;
		char vec_dim;
		float vec[4] = {};

		read_func(&vec_dim, 1);
		read_func(&vec_type, 1);
		read_func(vec, 4 * vec_dim);

		p_mat->AddVectorInfo(
		{
			(C_Material::C_VectorInfo::eVectorDimention)vec_dim,
			(C_Material::C_VectorInfo::eVectorType)vec_type,
			vec[0],vec[1],vec[2],vec[3]
		});
	}
}


/**

*	@brief	�Ǝ��`���̃X�P���g�����̓ǂݍ���

*/
void ReadConvertSkeleton(ReadFunc read_func, SkeletonPtr p_skeleton, bool read_name) {
	short bone_count;
	char mat_type;
	read_func(&bone_count, 2);
	read_func(&mat_type, 1);

	int read_size = -1;
	if ((eMatrixType)mat_type == eMatrixType::TYPE_MAT4x4) {
		read_size = S_MatrixTypeSize::s_GetMatrixTypeSize((eMatrixType)mat_type) * bone_count;
	}
	else {
		assert(false);
	}

	auto buffer = std::malloc(read_size);
	read_func(buffer, read_size);

	p_skeleton->CopyBufferToInversePoseMatrices(buffer, read_size);
	p_skeleton->ReserveBoneArray(bone_count);

	for (int i = 0; i < bone_count; ++i) {
		ReadConvertBone(read_func, p_skeleton, read_name);
	}
}

/**

*	@brief	�Ǝ��`���̃{�[���̓ǂݍ���

*/
void ReadConvertBone(ReadFunc read_func, SkeletonPtr p_skeleton, bool read_name) {
	auto p_bone = std::make_shared<C_Bone>();
	p_skeleton->AddBone(p_bone);
	char buffer[128] = {};
	short parent_bone_index;
	char bone_type;
	char child_bone_index_count;
	char mat_type;
	char math_type;

	if (read_name) read_func(buffer, 128);
	read_func(&parent_bone_index, 2);
	read_func(&bone_type, 1);
	read_func(&child_bone_index_count, 1);
	read_func(&mat_type, 1);
	read_func(&math_type, 1);

	p_bone->SetBoneName(buffer);
	p_bone->SetParentIndex(parent_bone_index);
	p_bone->SetBoneType((eBoneType)bone_type);
	p_bone->SetMatrixType((eMatrixType)mat_type);
	p_bone->SetMathType((eMathType)math_type);

	auto size = child_bone_index_count * 2;
	auto child_buffer = std::malloc(size);
	read_func(child_buffer, size);
	p_bone->CopyBufferToChildIndexArray(child_buffer, size);

	std::free(child_buffer);
}


/**

*	@brief	FBX�̃A�j���[�V������Ǝ��`���ɏo�͂���

*	@param[in]	file_path	�A�j���[�V����fbx�̃t�@�C���p�X
*	@param[in]	base_skeleton_file	���b�V���ƃA�j���[�V������������Ă���ꍇ�A�{�[���̃C���f�b�N�X���Y����̂ŁA�x�[�X�̃X�P���g���ƂȂ�t�@�C�����w�肷��

*	@return	�Ȃ�
*/
void Fbx::ConvertFbxAnimation(const char* file_path, const char* base_skeleton_file, eMatrixType write_mat_type) {
	SkeletonPtr p_skeleton;
	if (base_skeleton_file) {
		p_skeleton = Fbx::LoadSkeleton(base_skeleton_file);
	}
	else {
		p_skeleton = Fbx::LoadSkeleton(file_path);
	}

	auto animation_list = LoadAnimation(file_path, p_skeleton);

	for (auto &it : animation_list) {
		FILE* fp;
		it.first.append(".smdlskin");
		fopen_s(&fp, it.first.c_str(), "wb");
		auto write_func = [fp](void* buffer, int size) {
			fwrite(buffer, size, 1, fp);
		};

		short bone_count = it.second->GetBoneCount();
		short end_frame = it.second->GetAnimationEndFrame();

		write_func(&bone_count, 2);
		write_func(&end_frame, 2);

		for (int i = 0; i < bone_count; ++i) {
			auto bone = it.second->GetBone(i);

			char mat_type = (char)bone->GetMatrixType();
			char math_type = (char)bone->GetMathType();

			write_func(&mat_type, 1);
			write_func(&math_type, 1);


			if (bone->GetMatrixType() == eMatrixType::TYPE_MAT4x4) {
				write_func(bone->GetAnimationMatricesPtr(), end_frame * S_MatrixTypeSize::s_GetMatrixTypeSize(eMatrixType::TYPE_MAT4x4));
			}
			else {
				assert(false);
			}
		}
		
		fclose(fp);
	}
}


/**

*	@brief	�Ǝ��`���̃A�j���[�V�����t�@�C����ǂݍ���

*	@param[in]	file_path	�t�@�C���p�X
*	@param[in]	p_base_skeleton 

*	@return	�Ȃ�
*/
SkeletonPtr Fbx::LoadSKIN(const char* file_path, SkeletonPtr p_base_skeleton){
	SkeletonPtr p_skeleton = p_base_skeleton->Clone();

	FILE* fp;
	if (fopen_s(&fp, file_path, "rb")) {
		assert(false);
	}

	auto read_func = [fp](void* buffer, int size) {
		fread_s(buffer, size, size, 1, fp);
	};

	short bone_count;
	short end_frame;

	read_func(&bone_count, 2);
	read_func(&end_frame, 2);
	p_skeleton->SetAnimationEndFrame(end_frame);
	for (int i = 0; i < bone_count; ++i) {
		auto p_bone = p_skeleton->GetBone(i);

		char mat_type;
		char math_type;

		read_func(&mat_type, 1);
		read_func(&math_type, 1);

		p_bone->SetMatrixType((eMatrixType)mat_type);
		p_bone->SetMathType((eMathType)math_type);
		if (mat_type == (char)eMatrixType::TYPE_MAT4x4) {
			p_bone->ResizeAnimationMatrices<GALib::Math::Matrix4x4>(end_frame);
			int size = S_MatrixTypeSize::s_GetMatrixTypeSize(eMatrixType::TYPE_MAT4x4);
			size *= end_frame;
			void* buffer = std::malloc(size);

			read_func(buffer, size);
			p_bone->CopyBufferToAnimationMatrices(buffer, size);

			std::free(buffer);
		}
		else {
			assert(false);
		}
	}

	return p_skeleton;
}



