#pragma once
#include "common.h"
class C_Material;
using MaterialPtr = std::shared_ptr < C_Material>;
using MaterialPtrArray = std::vector<MaterialPtr>;

/**

*	@brief	マテリアル情報を表す

*/
class C_Material {
public:
	/**
	
	*	@brief	テクスチャ情報を表す

	*/
	struct C_TextureInfo {
	public:
		/**
		
		*	@brief	保持しているテクスチャ名の情報
		
		*/
		enum class eTextureType {
			TYPE_NONE = -1,		//初期値
			TYPE_DIFFUSE=1,	//ディフューズ
			TYPE_NORMAL,	//法線
			TYPE_SPECULAR,	//スペキュラ
			TYPE_REFLECTION,//リフレクション
			TYPE_FALLOFF,	//フォールオブテクスチャ、α値っぽい？
		};
		C_TextureInfo(const char* name, eTextureType type) :
			m_texture_name(name),
			m_texture_type(type)
		{}

		void SetTextureName(const char* name) { }
		const char* GetTextureName() { return this->m_texture_name.c_str(); }
		eTextureType GetTextureType() { return this->m_texture_type; }
	private:
		std::string m_texture_name;
		eTextureType m_texture_type = eTextureType::TYPE_NONE;
	};

	/**
	
	*	@brief	ベクトル情報を表す
	
	*/
	struct C_VectorInfo {
	public:
		/**
		
		*	@brief	保持しているベクトルが使用する次元
		
		*/
		enum class eVectorDimention {
			DIM_V1=1,
			DIM_V2,
			DIM_V3,
			DIM_V4
		};

		/**
		
		*	@brief	ベクトルが表す情報
		
		*/
		enum class eVectorType {
			TYPE_NONE = -1,
			TYPE_DIFFUSE = 1,		//ディフューズ
			TYPE_AMBIENT,		//アンビエント
			TYPE_SPECULAR,		//スペキュラ
			TYPE_SHININESS,		//鏡面反射角だったかなんか、スペキュラパワーでも一緒かな
			TYPE_SPECULAR_FACTOR,//スペキュラカラー増減値？
			TYPE_EMISSIVE,		//エミッシブ
			TYPE_TRANSPARENCY_FACTOR,		//不透明度
			TYPE_REFLECTION_FACTOR,	//環境マップ関係？
			TYPE_FALLOFF_POWER,	//フォールオフテクスチャの適用度かと

		};
		C_VectorInfo(eVectorDimention dim, eVectorType type, float v1 = 0, float v2 = 0, float v3 = 0, float v4 = 0) :
			m_vector_dimention(dim),
			m_vector_type(type),
			m_vector(v1, v2, v3, v4)
		{}

		eVectorDimention GetVectorDimention() { return this->m_vector_dimention; }
		eVectorType GetVectorType() { return this->m_vector_type; }
		GALib::Math::Vector4 GetVector() { return this->m_vector; }
	private:
		eVectorDimention m_vector_dimention = eVectorDimention::DIM_V4;
		eVectorType m_vector_type = eVectorType::TYPE_NONE;
		GALib::Math::Vector4 m_vector;

	};


	void SetMaterialName(const char* name) { this->m_material_name = name; }
	const char* GetMaterialName() { return this->m_material_name.c_str(); }
	int GetMaterialIndex() { return this->m_material_index; }
	void SetMaterialIndex(int index) { this->m_material_index = index; }


	void AddTextureInfo(C_TextureInfo tex) { this->m_textures.push_back(tex); }
	int GetTextureInfoCount() { return this->m_textures.size(); }
	C_TextureInfo* GetTextureInfoArray() { return this->m_textures.data(); }
	C_TextureInfo* GetTextureInfo(int index) { return &this->m_textures[index]; }
	void AddVectorInfo(C_VectorInfo vec) { this->m_vectors.push_back(vec); }
	int GetVectorInfoCount() { return this->m_vectors.size(); }
	C_VectorInfo* GetVectorInfoArray() { return this->m_vectors.data(); }
	C_VectorInfo* GetVectorInfo(int index) { return &this->m_vectors[index]; }

	void ReserveTextureInfoArray(int count) { this->m_textures.reserve(count); }
	void ReserveVectorInfoArray(int count) { this->m_vectors.reserve(count); }
private:
	int m_material_index = -1;
	std::string m_material_name;
	std::vector<C_TextureInfo>	m_textures;
	std::vector<C_VectorInfo>	m_vectors;
};

