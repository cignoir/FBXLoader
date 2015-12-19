#include "Skeleton.h"

/**

*	@brief	�{�[����ǉ�����

*/
void C_Skeleton::AddBone(BonePtr ptr) {
	ptr->SetBoneIndex(this->GetBoneCount());
	ptr->SetSkeleton(this);

	this->m_p_bone_list.push_back(ptr);
}

/**

*	@brief	�{�[��������{�[���C���f�b�N�X�������A�Ȃ����-1��Ԃ�

*/
int C_Skeleton::FindBoneIndex(const char* bone_name) {
	int i = 0;
	for (auto& it : this->m_p_bone_list) {
		if (!std::strcmp(it->GetBoneName(), bone_name)) {
			return i;
		}
		++i;
	}
	return -1;
}

/**

*	@brief	�{�[��������{�[�����擾����

*/
BonePtr C_Skeleton::GetBone(const char* bone_name) {
	int i = 0;
	for (auto& it : this->m_p_bone_list) {
		if (!std::strcmp(it->GetBoneName(), bone_name)) {
			return it;
		}
		++i;
	}
	return nullptr;
}

/*

*	@brief	�X�P���g�������R�s�[����

*	@param[in]	copy_invert_matrices	true�Ńx�[�X�|�[�Y�̋t�s��z����R�s�[����

*/
SkeletonPtr C_Skeleton::Clone(bool copy_invert_matrices) {
	auto ptr = std::make_shared<C_Skeleton>();

	ptr->m_p_bone_list.reserve(this->m_p_bone_list.size());
	for (auto &it : this->m_p_bone_list) {
		auto clone = it->Clone();
		clone->SetSkeleton(ptr.get());
		ptr->m_p_bone_list.emplace_back(clone);
	}

	if(copy_invert_matrices) ptr->m_inverse_pose_matrices = this->m_inverse_pose_matrices;

	return ptr;
}

