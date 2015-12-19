#pragma once
#include "common.h"
#include "FbxLoader.h"

namespace Fbx {
	//fbx -> 独自形式
	//行列対応はそのうち
	void ConvertFbxMesh(const char* file_path, bool write_name, eVertexType write_vertex_type = eVertexType::TYPE_PUNTBW, eMatrixType write_mat_type = eMatrixType::TYPE_MAT4x4);
	void ConvertFbxAnimation(const char* file_path, const char* base_skeleton_file = nullptr, eMatrixType write_mat_type = eMatrixType::TYPE_MAT4x4);

	//独自形式 -> ゲーム用データ
	MeshesAndSkeleton LoadSMDL(const char* file_path);
	SkeletonPtr LoadSKIN(const char* file_path, SkeletonPtr p_base_skeleton);
}