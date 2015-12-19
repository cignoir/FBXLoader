#pragma once
#include "common.h"
class C_Material;
using MaterialPtr = std::shared_ptr < C_Material>;
using MaterialPtrArray = std::vector<MaterialPtr>;

/**

*	@brief	�}�e���A������\��

*/
class C_Material {
public:
	/**
	
	*	@brief	�e�N�X�`������\��

	*/
	struct C_TextureInfo {
	public:
		/**
		
		*	@brief	�ێ����Ă���e�N�X�`�����̏��
		
		*/
		enum class eTextureType {
			TYPE_NONE = -1,		//�����l
			TYPE_DIFFUSE=1,	//�f�B�t���[�Y
			TYPE_NORMAL,	//�@��
			TYPE_SPECULAR,	//�X�y�L����
			TYPE_REFLECTION,//���t���N�V����
			TYPE_FALLOFF,	//�t�H�[���I�u�e�N�X�`���A���l���ۂ��H
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
	
	*	@brief	�x�N�g������\��
	
	*/
	struct C_VectorInfo {
	public:
		/**
		
		*	@brief	�ێ����Ă���x�N�g�����g�p���鎟��
		
		*/
		enum class eVectorDimention {
			DIM_V1=1,
			DIM_V2,
			DIM_V3,
			DIM_V4
		};

		/**
		
		*	@brief	�x�N�g�����\�����
		
		*/
		enum class eVectorType {
			TYPE_NONE = -1,
			TYPE_DIFFUSE = 1,		//�f�B�t���[�Y
			TYPE_AMBIENT,		//�A���r�G���g
			TYPE_SPECULAR,		//�X�y�L����
			TYPE_SHININESS,		//���ʔ��ˊp���������Ȃ񂩁A�X�y�L�����p���[�ł��ꏏ����
			TYPE_SPECULAR_FACTOR,//�X�y�L�����J���[�����l�H
			TYPE_EMISSIVE,		//�G�~�b�V�u
			TYPE_TRANSPARENCY_FACTOR,		//�s�����x
			TYPE_REFLECTION_FACTOR,	//���}�b�v�֌W�H
			TYPE_FALLOFF_POWER,	//�t�H�[���I�t�e�N�X�`���̓K�p�x����

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

