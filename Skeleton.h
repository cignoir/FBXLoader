#pragma once
#include "common.h"
#include "Bone.h"
class C_Skeleton;
using SkeletonPtr = std::shared_ptr<C_Skeleton>;
/**

*	@brief	骨格を表す
			ベースポーズの逆行列配列を保持する

*/
class C_Skeleton {
public:
	void SetAnimationEndFrame(int frame) { this->m_animation_frame_max = frame; }
	int GetAnimationEndFrame() { return this->m_animation_frame_max; }

	void SetAnimationFrame(int frame) { this->m_now_animation_frame = frame; }
	int GetAnimationFrame() { return this->m_now_animation_frame; }
	SkeletonPtr Clone(bool copy_invert_matrices = false);

	void SetMatrixType(eMatrixType type) { this->m_matrix_type = type; }
	eMatrixType GetMatrixType() { return this->m_matrix_type; }

	BonePtr	GetBone(int index) {
		if (index < 0) return nullptr;
		return this->m_p_bone_list[index]; 
	}
	BonePtr GetBone(const char* bone_name);
	void AddBone(BonePtr ptr);
	int GetBoneCount() { return this->m_p_bone_list.size(); }
	int FindBoneIndex(const char* bone_name);

	void ReserveBoneArray(int count) {
		this->m_p_bone_list.reserve(count);
	}


	/**
	
	*	@brief	関数で計算する

	*	@param[in]	calc_func	計算関数を渡す、計算関数は引数にC_Skeletonを受け取る、返り値はなし
	
	仕様は固まってないのでそのうちに直す
	
	*/
	template<class _CalcFunc>
	auto Calc(_CalcFunc calc_func) {
		return calc_func(this);
	};


	template<class _MatrixType = void>
	auto GetInversePoseMatrixArray() { return (_MatrixType*)this->m_inverse_pose_matrices.data(); }

	template<class _MatrixType>
	void SetInversePoseMatrix(_MatrixType mat, int index) {
		auto data = (_MatrixType*)this->m_inverse_pose_matrices.data();
		data += index;
		*data = mat;
	}

	template<class _MatrixType>
	void ResizeInverseBasePoseMatrices(int count) {
		this->m_inverse_pose_matrices.resize(count * sizeof(_MatrixType));
	}

	//バッファをコピーしそのままベースポーズの逆行列バイト配列にコピーする
	void CopyBufferToInversePoseMatrices(void* buffer, int size) {
		this->m_inverse_pose_matrices.resize(size);
		std::memcpy(this->m_inverse_pose_matrices.data(), buffer, size);
	}
private:
	std::vector<BonePtr>	m_p_bone_list;
	ByteArray m_inverse_pose_matrices;
	int m_animation_frame_max = 0;
	int m_now_animation_frame = 0;
	eMatrixType	m_matrix_type = eMatrixType::TYPE_NONE;
};

