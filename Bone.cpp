#include "Skeleton.h"
#include "Bone.h"

/**

*	@brief	ボーンが持つ親の数を取得

*/
 int C_Bone::GetParentNum(int count) {
	 auto ptr = this->m_p_skeleton->GetBone(this->m_parent_index);
	 if (ptr) {
		 return ptr->GetParentNum(count + 1);
	 }
	 return count;
}


 /**

 *	@brief	アニメーション行列意外の情報をすべてコピーする

 */
 BonePtr C_Bone::Clone() {
	 auto ptr = std::make_shared<C_Bone>();
	 ptr->m_bone_name = this->m_bone_name;
	 ptr->m_bone_type = this->m_bone_type;
	 ptr->m_math_type = this->m_math_type;
	 ptr->m_mat_type = this->m_mat_type;
	 ptr->m_parent_index = this->m_parent_index;
	 ptr->m_bone_index = this->m_bone_index;
	 ptr->m_child_index_array = this->m_child_index_array;

	 return ptr;
 }