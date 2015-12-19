#pragma once
#include "common.h"
/**

*	@brief	ボーンウェイトとインデックス保持用

*/
struct S_BoneWeight {
	unsigned int m_bone_index[4] = {};
	GALib::Math::Vector4 m_bone_weight;
};

/**

*	@brief	座標、UV、法線、接線、従法線、ボーンインデックス、ウェイトを持つ

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

*	@brief	座標、UV、法線、接線、従法線を持つ

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

*	@brief	座標、UV、法線、ボーンインデックス、ウェイトを持つ

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

*	@brief	座標、UV、法線を持つ

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

*	@brief	座標、法線、接線、従法線を持つ
			基本的にシェイプ用

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

*	@brief	座標、法線を持つ
			基本的にシェイプ用

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

*	@brief	頂点タイプ

*/
enum class eVertexType {
	TYPE_NONE = -1,		
	TYPE_PUNTBW = 1,		//座標、UV、法線、接線、従法線、ボーンインデックス、ウェイトを持つ
	TYPE_PUNTB,			//座標、UV、法線、接線、従法線を持つ
	TYPE_PUNW,			//座標、UV、法線、ボーンインデックス、ウェイトを持つ
	TYPE_PUN,			//座標、UV、法線を持つ
	TYPE_PNTB,			//座標、法線、接線、従法線を持つ
	TYPE_PN,			//座標、法線を持つ
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