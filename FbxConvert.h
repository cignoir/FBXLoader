#pragma once
#include "common.h"
#include "FbxLoader.h"

namespace Fbx {
	//fbx -> �Ǝ��`��
	//�s��Ή��͂��̂���
	void ConvertFbxMesh(const char* file_path, bool write_name, eVertexType write_vertex_type = eVertexType::TYPE_PUNTBW, eMatrixType write_mat_type = eMatrixType::TYPE_MAT4x4);
	void ConvertFbxAnimation(const char* file_path, const char* base_skeleton_file = nullptr, eMatrixType write_mat_type = eMatrixType::TYPE_MAT4x4);

	//�Ǝ��`�� -> �Q�[���p�f�[�^
	MeshesAndSkeleton LoadSMDL(const char* file_path);
	SkeletonPtr LoadSKIN(const char* file_path, SkeletonPtr p_base_skeleton);
}