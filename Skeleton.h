#pragma once
#include "common.h"
#include "Bone.h"
class C_Skeleton;
using SkeletonPtr = std::shared_ptr<C_Skeleton>;
/**

*	@brief	���i��\��
			�x�[�X�|�[�Y�̋t�s��z���ێ�����

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
	
	*	@brief	�֐��Ōv�Z����

	*	@param[in]	calc_func	�v�Z�֐���n���A�v�Z�֐��͈�����C_Skeleton���󂯎��A�Ԃ�l�͂Ȃ�
	
	�d�l�͌ł܂��ĂȂ��̂ł��̂����ɒ���
	
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

	//�o�b�t�@���R�s�[�����̂܂܃x�[�X�|�[�Y�̋t�s��o�C�g�z��ɃR�s�[����
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

