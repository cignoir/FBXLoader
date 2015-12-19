///>�v���W�F�N�g�̃w�b�_�̃C���N���[�h
#include "TextureManager.h"
#include "../D3D11/D3DUser.h"
#include "../FileSystem/FileReader.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	���\�[�X�֘A�̖��O���
	
	*/
	namespace Resource{
		/**
		
		*	@brief	�e�N�X�`���֘A�̖��O���
		
		*/
		namespace TextureManager{
			/**
			
			*	@brief	�e�N�X�`���n���h���̎����N���X
			
			*/
			class C_TextureHandle final : public IC_TextureHandle{
			public:
				/**
				
				*	@brief	�R���X�g���N�^

				*	@param	�Ȃ�
				
				*/
				C_TextureHandle(){}

				/**
				
				*	@brief	�f�X�g���N�^

				*	@param	�Ȃ�
				
				*/
				~C_TextureHandle(){}

				/**
				
				*	@brief	�w�肳�ꂽ�C���f�b�N�X��UV��ݒ肷��

				*	@param[in]	index	���_�C���f�b�N�X
				*	@param[in]	u		u
				*	@param[in]	v		v

				*	@return	�Ȃ�
				
				*/
				void SetUV(int index, float u, float v){ 
					this->m_uv[index].m_u = u; 
					this->m_uv[index].m_v = v;
				}

				/**
				
				*	@brief	�w�肳�ꂽ���_�C���f�b�N�X��UV���擾

				*	@param[in]	index	���_�C���f�b�N�X

				*	@return	UV�\����
				
				*/
				Math::Vector2 GetTextureUV(int index)const override{ return this->m_uv[index]; }

				/**
				
				*	@brief	SRV�̃A�h���X�̎擾

				*	@param	�Ȃ�

				*	@return	ID3D11ShaderResourceView**

				*/
				ID3D11ShaderResourceView**	GetAddressOf(){ return &this->m_p_srv; }

				/**
				
				*	@brief	�e�N�X�`��API�̎擾
				
				*	@param	�Ȃ�

				*	@return	�e�N�X�`��API�̃|�C���^

				*/
				void*	GetTextureAPIPtr()const override{
					if (this->m_p_parent_texture) return this->m_p_parent_texture->GetTextureAPIPtr();
					return this->m_p_srv.Get();
				}
				
				/**
				
				*	@brief	�e�N�X�`�����̐ݒ�

				*	@param[in]	width,height	�e�N�X�`���̕��A����

				*	@return	�Ȃ�
				
				*/
				void SetTextureSize(int width, int height){
					this->m_width = width;
					this->m_height = height;
				}

				/**
				
				*	@brief	�e�N�X�`�������̎擾

				*	@param	�Ȃ�

				*	@return	����
				
				*/
				int GetTextureWidth()const  override{ return this->m_width; }

				/**
				
				*	@brief	�e�N�X�`���c���̎擾

				*	@param	�Ȃ�

				*	@return	�c��
				
				*/
				int GetTextureHeight() const override{ return this->m_height; }


				/**
				
				*	@brief	�e�e�N�X�`���n���h���̐ݒ�

				*	@param[in]	ptr	�e�e�N�X�`���n���h���ւ̂ۂ���

				*	@return	�Ȃ�
				
				*/
				void SetParentTextureHandle(IC_TextureHandle* ptr){
					this->m_p_parent_texture = ptr;
				}
			private:
				ComPtr<ID3D11ShaderResourceView>	m_p_srv;
				IC_TextureHandle*	m_p_parent_texture = nullptr;
				Math::Vector2	m_uv[4];
				int m_width = 0;
				int m_height = 0;
			};

			/**
			
			*	@brief	SRV����e�N�X�`���T�C�Y���擾����

			*	@param[in]	texture	SRV�̃|�C���^
			*	@param[out]	width,height	�e�N�X�`���T�C�Y�i�[�p�ϐ��̎Q��

			*	@return	�Ȃ�

			*/
			void GetTextureSize(ID3D11ShaderResourceView *texture,int& out_width,int &out_height){
				//���\�[�X���擾
				if (!texture){
					out_width = 0;
					out_height = 0;
				}
				Microsoft::WRL::ComPtr<ID3D11Resource> resource;
				texture->GetResource(&resource);

				//������Ă�̂��킩��񂯂ǂ�������
				Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
				resource.As(&texture2D);

				//�e�N�X�`�����擾
				D3D11_TEXTURE2D_DESC desc;
				texture2D->GetDesc(&desc);

				out_width = desc.Width;
				out_height = desc.Height;

			}
		}
	}

}



/**

*	@brief	�w�肳�ꂽ�t�@�C���̃e�N�X�`����ǂݍ���

*	@param[in]	file_path	�t�@�C���p�X

*	@return	�e�N�X�`���n���h��

*/
GALib::Resource::GHANDLE	GALib::Resource::TextureManager::LoadGraph(const char* file_path){
	auto str = std::string(file_path);
	auto pos = str.find_first_of(".");
	auto p = std::string(file_path, pos);
	p.append(".png");
	auto handle = Utility::MakeShared<C_TextureHandle>();

	D3D11::CreateWICTexture(p.c_str() , handle->GetAddressOf());

	int width, height;
	GetTextureSize(static_cast<ID3D11ShaderResourceView*>(handle->GetTextureAPIPtr()), width, height);

	handle->SetTextureSize(width, height);
	handle->SetUV(0, 0, 0);
	handle->SetUV(1, 1, 0);
	handle->SetUV(2, 0, 1);
	handle->SetUV(3, 1, 1);

	return handle;
}

/**

*	@brief	�w�肳�ꂽ�e�e�N�X�`������e�N�X�`����؂�o��

*	@param[in]	tx,ty	������W
*	@param[in]	tw,th	������W����̕��A����
*	@param[in]	base_handle	�e�n���h��

*	@return	�e�N�X�`���n���h��

*/
GALib::Resource::GHANDLE GALib::Resource::TextureManager::DerivationGraph(int tx, int ty, int tw, int th, GHANDLE& base_handle){
	auto handle = Utility::MakeShared<C_TextureHandle>();
	auto parent = static_cast<C_TextureHandle*>(base_handle.Get());
	int w = parent->GetTextureWidth();
	int h = parent->GetTextureHeight();
	float l_x = static_cast<float>(tx) / static_cast<float>(w);
	float t_y = static_cast<float>(ty) / static_cast<float>(h);
	float r_x = static_cast<float>(tx + tw) / static_cast<float>(w);
	float b_y = static_cast<float>(ty + th) / static_cast<float>(h);

	handle->SetUV(0, l_x, t_y);
	handle->SetUV(1, r_x, t_y);
	handle->SetUV(2, l_x, b_y);
	handle->SetUV(3, r_x, b_y);
	handle->SetParentTextureHandle(parent);
	handle->SetTextureSize(tw, th);

	return handle;
}


/**

*	@brief	�e�N�X�`���̕����ǂݍ���

*	@param[in]	base_graph	���ƂȂ�e�N�X�`��
*	@param[in]	tx,ty	�J�n������W
*	@param[in]	tw,th	�����e�N�X�`���T�C�Y
*	@param[in]	x_num,y_num	�c��������
*	@param[in]	div_num	�ǂݍ��ݐ�
						4*4��14���w�肵���ꍇ�A�c�O�񕪂Ǝl��ڂ̓�ڂ̃e�N�X�`���܂œǂݍ���
*	@param[out]	out	�o�͔z��

*	@return	�Ȃ�

*/
void GALib::Resource::TextureManager::LoadDivGraph(GHANDLE& base_graph, int tx, int ty, int tw, int th, int x_num, int y_num, int div_num, GHANDLE* out){
	int i = 0;
	for (int y = 0; y < y_num; ++y){
		for (int x = 0; x < x_num; ++x){
			out[i] = DerivationGraph(tx + x*tw, ty + y*th, tw, th, base_graph);

			++i;
			if (div_num == i) return;
		}
	}
}
