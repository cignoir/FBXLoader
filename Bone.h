#pragma once
#include "common.h"

class C_Bone;
class C_Skeleton;
using BonePtr = std::shared_ptr<C_Bone>;

/**

*	@brief	FBX上でスケルトンノードだったかメッシュノードだったか

*/
enum class eBoneType {
	TYPE_NULL = -1,
	TYPE_BONE = 1,
	TYPE_MESH
};

/**

*	@brief	保持するアニメーション行列のタイプ

*/
enum class eMathType {
	TYPE_NONE = -1,
	TYPE_WORLD = 1,		//計算済みのワールド行列
	TYPE_LOCAL		//ローカル行列
};

/**

*	@brief	保持するアニメーション行列のタイプ

*/
enum class eMatrixType {
	TYPE_NONE = -1,
	TYPE_MAT4x4 = 1,			//4x4行列
	TYPE_MAT4x3,			//4x3行列
	TYPE_QUATERNION		//クォータニオン
};

struct S_MatrixTypeSize {
	static int s_GetMatrixTypeSize(eMatrixType type) {
		switch (type)
		{
		case eMatrixType::TYPE_NONE:
			break;
		case eMatrixType::TYPE_MAT4x4:
			return sizeof(GALib::Math::Matrix4x4);
			break;
		case eMatrixType::TYPE_MAT4x3:
			break;
		case eMatrixType::TYPE_QUATERNION:
			break;
		default:
			break;
		}

		return 0;
	}
};
/**

*	@brief	ボーン情報を表す
			１つのアニメーションのボーン行列の配列も保持する
			ボーンが参照すべき配列はSkeletonが持つ
*/
class C_Bone {
public:

	void SetSkeleton(C_Skeleton* ptr) { this->m_p_skeleton = ptr; }

	void SetBoneName(const char* name) {
		this->m_bone_name = std::string(name);
	}
	const char* GetBoneName() { return this->m_bone_name.c_str(); }
	void SetBoneIndex(int index) { this->m_bone_index = index; }
	int GetBoneIndex() { return this->m_bone_index; }
	void SetParentIndex(int index) { this->m_parent_index = index; }
	int GetParentIndex() { return this->m_parent_index; }
	int GetParentNum(int count = 0);

	//子ボーンインデックスを追加し、子ボーンに親ボーンインデックスを追加する
	void AddChildIndex(BonePtr ptr) {
		ptr->SetParentIndex(this->m_bone_index);
		this->m_child_index_array.push_back(ptr->GetBoneIndex());
	}
	void CopyBufferToChildIndexArray(void* buffer, int size) {
		this->m_child_index_array.resize(size / 2);
		memcpy(this->m_child_index_array.data(), buffer, size);
	}
	int GetChildIndexCount() { return this->m_child_index_array.size(); }
	int GetChildIndex(int index) { return this->m_child_index_array[index]; }
	void* GetChildIndexArrayPtr() { return this->m_child_index_array.data(); }


	void SetBoneType(eBoneType type) { this->m_bone_type = type; }
	eBoneType GetBoneType() { return this->m_bone_type; }
	void SetMathType(eMathType type) { this->m_math_type = type; }
	eMathType GetMathType() { return this->m_math_type; }
	void SetMatrixType(eMatrixType type) { this->m_mat_type = type; }
	eMatrixType GetMatrixType() { return this->m_mat_type; }

	template<class _MatrixType>
	void SetAnimationMatrix(_MatrixType mat, int frame) {
		auto data = (_MatrixType*)this->m_animation_matrices_buffer.data();
		data += frame;
		*data = mat;
	}
	template<class _MatrixType>
	_MatrixType GetAnimationMatrix(int frame) {
		auto data = (_MatrixType*)this->m_animation_matrices_buffer.data();
		return *(data + frame);
	}

	void* GetAnimationMatricesPtr() { return this->m_animation_matrices_buffer.data(); }

	template<class _MatrixType>
	void ResizeAnimationMatrices(int count) {
		this->m_animation_matrices_buffer.resize(sizeof(_MatrixType) * count);
	}


	//バイト配列をアニメーションポーズのバイト配列にコピーする
	void CopyBufferToAnimationMatrices(void* buffer, int size) {
		this->m_animation_matrices_buffer.resize(size);
		std::memcpy(this->m_animation_matrices_buffer.data(), buffer, size);
	}

	BonePtr Clone();
private:
	std::string	m_bone_name;
	std::vector<unsigned short>	m_child_index_array;
	C_Skeleton*	m_p_skeleton = nullptr;
	eBoneType m_bone_type = eBoneType::TYPE_NULL;
	eMathType m_math_type = eMathType::TYPE_NONE;
	eMatrixType m_mat_type = eMatrixType::TYPE_NONE;
	int	m_parent_index = -1;
	int m_bone_index = -1;
	ByteArray m_animation_matrices_buffer;
};

