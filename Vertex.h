#pragma once
#include "common.h"
/**

*	@brief	�{�[���E�F�C�g�ƃC���f�b�N�X�ێ��p

*/
struct S_BoneWeight {
	unsigned int m_bone_index[4] = {};
	GALib::Math::Vector4 m_bone_weight;
};

/**

*	@brief	���W�AUV�A�@���A�ڐ��A�]�@���A�{�[���C���f�b�N�X�A�E�F�C�g������

*/
struct S_VertexPUNTBW {
	GALib::Math::Vector3 m_pos;
	GALib::Math::Vector2 m_uv;
	GALib::Math::Vector3 m_normal;
	GALib::Math::Vector3 m_tangent;
	GALib::Math::Vector3 m_binormal;
	S_BoneWeight m_bone;
};


/**

*	@brief	���W�AUV�A�@���A�ڐ��A�]�@��������

*/
struct S_VertexPUNTB {
	GALib::Math::Vector3 m_pos;
	GALib::Math::Vector2 m_uv;
	GALib::Math::Vector3 m_normal;
	GALib::Math::Vector3 m_tangent;
	GALib::Math::Vector3 m_binormal;

	void operator=(S_VertexPUNTBW v) {
		this->m_pos = v.m_pos;
		this->m_uv = v.m_uv;
		this->m_normal = v.m_normal;
		this->m_tangent = v.m_tangent;
		this->m_binormal = v.m_binormal;
	}
};


/**

*	@brief	���W�AUV�A�@���A�{�[���C���f�b�N�X�A�E�F�C�g������

*/
struct S_VertexPUNW {
	GALib::Math::Vector3 m_pos;
	GALib::Math::Vector2 m_uv;
	GALib::Math::Vector3 m_normal;
	S_BoneWeight m_bone;

	void operator=(S_VertexPUNTBW v) {
		this->m_pos = v.m_pos;
		this->m_uv = v.m_uv;
		this->m_normal = v.m_normal;
		this->m_bone = v.m_bone;
	}
};


/**

*	@brief	���W�AUV�A�@��������

*/
struct S_VertexPUN {
	GALib::Math::Vector3 m_pos;
	GALib::Math::Vector2 m_uv;
	GALib::Math::Vector3 m_normal;

	void operator=(S_VertexPUNTBW v) {
		this->m_pos = v.m_pos;
		this->m_uv = v.m_uv;
		this->m_normal = v.m_normal;
	}
};

/**

*	@brief	���W�A�@���A�ڐ��A�]�@��������
			��{�I�ɃV�F�C�v�p

*/
struct S_VertexPNTB {
	GALib::Math::Vector3 m_pos;
	GALib::Math::Vector3 m_normal;
	GALib::Math::Vector3 m_tangent;
	GALib::Math::Vector3 m_binormal;
	void operator=(S_VertexPUNTBW v) {
		this->m_pos = v.m_pos;
		this->m_normal = v.m_normal;
		this->m_tangent = v.m_tangent;
		this->m_binormal = v.m_binormal;
	}
};

/**

*	@brief	���W�A�@��������
			��{�I�ɃV�F�C�v�p

*/
struct S_VertexPN {
	GALib::Math::Vector3 m_pos;
	GALib::Math::Vector3 m_normal;
	void operator=(S_VertexPUNTBW v) {
		this->m_pos = v.m_pos;
		this->m_normal = v.m_normal;
	}
};

/**

*	@brief	���_�^�C�v

*/
enum class eVertexType {
	TYPE_NONE = -1,		
	TYPE_PUNTBW = 1,		//���W�AUV�A�@���A�ڐ��A�]�@���A�{�[���C���f�b�N�X�A�E�F�C�g������
	TYPE_PUNTB,			//���W�AUV�A�@���A�ڐ��A�]�@��������
	TYPE_PUNW,			//���W�AUV�A�@���A�{�[���C���f�b�N�X�A�E�F�C�g������
	TYPE_PUN,			//���W�AUV�A�@��������
	TYPE_PNTB,			//���W�A�@���A�ڐ��A�]�@��������
	TYPE_PN,			//���W�A�@��������
};

struct S_VertexTypeSize {
	static int s_GetSize(eVertexType type) {
		switch (type)
		{
		case eVertexType::TYPE_NONE:
			return 0;
			break;
		case eVertexType::TYPE_PUNTBW:
			return sizeof(S_VertexPUNTBW);
			break;
		case eVertexType::TYPE_PUNTB:
			return sizeof(S_VertexPUNTB);
			break;
		case eVertexType::TYPE_PUNW:
			return sizeof(S_VertexPUNW);
			break;
		case eVertexType::TYPE_PUN:
			return sizeof(S_VertexPUN);
			break;
		case eVertexType::TYPE_PNTB:
			return sizeof(S_VertexPNTB);
			break;
		case eVertexType::TYPE_PN:
			return sizeof(S_VertexPN);
			break;
		default:
			break;
		}

		return 0;
	}
};