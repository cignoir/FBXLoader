#include "Skeleton.h"

/**

*	@brief	ボーンを追加する

*/
void C_Skeleton::AddBone(BonePtr ptr) {
	ptr->SetBoneIndex(this->GetBoneCount());
	ptr->SetSkeleton(this);

	this->m_p_bone_list.push_back(ptr);
}

/**

*	@brief	ボーン名からボーンインデックスを検索、なければ-1を返す

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

*	@brief	ボーン名からボーンを取得する

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

*	@brief	スケルトン情報をコピーする

*	@param[in]	copy_invert_matrices	trueでベースポーズの逆行列配列をコピーする

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

