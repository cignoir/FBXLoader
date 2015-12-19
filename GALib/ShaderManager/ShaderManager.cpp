#include "ShaderManager.h"
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
		
		*	@brief	�V�F�[�_�֘A�̖��O���

		*/
		namespace ShaderManager{
			/**
			
			*	@brief	�V�F�[�_�Ǘ��I�u�W�F�N�g����
			
			*/
			template<class _Shader>
			class C_ShaderObject final : public IC_ShaderObject{
			public:

				/**
				
				*	@brief	�f�X�g���N�^

				*	@param	�Ȃ�
				
				*/
				~C_ShaderObject(){
					this->m_resource.Destroy();
				}

				/**
				
				*	@brief	�V�F�[�_API�|�C���^�̎擾

				*	@param	�Ȃ�

				*	@return	�|�C���^
				
				*/
				void* GetShader() const override final{ return this->m_p_shader.Get(); }

				/**
				
				*	@brief	COM�I�u�W�F�N�g�̃A�h���X�̎擾

				*	@param	�Ȃ�

				*	@return	_Shader**
				
				*/
				_Shader**	GetAddressOf(){ return &this->m_p_shader; }

				
				/**
				
				*	@brief	�V�F�[�_�̃o�C�g�R�[�h��ێ����邽��FileReader����ǂ݂��񂾃��\�[�X��ێ�����

				*	@param[in] resource	FileReader����ǂݍ���S_ResourceData

				*	@return	�Ȃ�
				
				*/
				void SetResource(FileSystem::S_ResourceData resource){
					this->m_resource = resource;
				}

				/**
				
				*	@brief	���\�[�X�o�b�t�@�̃|�C���^���擾

				*	@param	�Ȃ�

				*	@return	�|�C���^
				
				*/
				void* GetResourceBuffer(){ return this->m_resource.m_p_buffer; }

				/**
				
				*	@brief	���\�[�X�̃T�C�Y�̎擾

				*	@param	�Ȃ�

				*	@return	�T�C�Y
				
				*/
				std::size_t GetResourceSize(){ return this->m_resource.m_length; }

			private:
				ComPtr<_Shader>	m_p_shader;
				FileSystem::S_ResourceData	m_resource;
			};

			using VSHANDLE = C_ShaderObject < ID3D11VertexShader > ;
			using PSHANDLE = C_ShaderObject < ID3D11PixelShader > ;

			/**
			
			*	@brief	���̓��C�A�E�g�Ǘ��N���X
			
			*/
			template<>
			class C_ShaderObject<ID3D11InputLayout>	final : public IC_ShaderObject{
				struct S_InputLayout{
					S_InputLayout(std::size_t size,std::size_t index, D3D11_INPUT_ELEMENT_DESC desc) :
						m_element_size(size),
						m_buffer_index(index),
						m_element_desc(desc)
					{}
					std::size_t m_element_size = 0;
					std::size_t	m_buffer_index = 0;
					D3D11_INPUT_ELEMENT_DESC m_element_desc;
				};

				using C_InputElementList = std::list < S_InputLayout >;
			public:
				/**
				
				*	@brief	�R���X�g���N�^

				*	@param[in]	ptr	���̓��C�A�E�g�쐬���̒��_�V�F�[�_�n���h��
				
				*/
				C_ShaderObject(VSHANDLE* ptr) : m_p_vertex_shader_handle(ptr){}

				/**

				*	@brief	���X�g�ɃG�������g�̒ǉ�

				*	@parma[in]	semantics	�Z�}���e�B�N�X��
				*	@parma[in]	buffer_index	���_�o�b�t�@�z��̃C���f�b�N�X
				*	@parma[in]	element_size	�v�f�̃o�C�g��
				*	@parma[in]	format			�v�f�̃t�H�[�}�b�g

				*	@return	�Ȃ�

				*/
				void AddElementDesc(const char* semantics, std::size_t buffer_index, std::size_t element_size, int format){
					std::size_t size = 0;
					//�o�b�t�@�̐擪����̃o�C�g�����v�Z
					for (auto &it : this->m_input_element_list){
						//����C���f�b�N�X�������Z����
						if(it.m_buffer_index == buffer_index )size += it.m_element_size;
					}

					D3D11_INPUT_ELEMENT_DESC	desc =
					{
						semantics,
						0,
						static_cast<DXGI_FORMAT>(format),
						buffer_index,
						size,
						D3D11_INPUT_PER_VERTEX_DATA,
						0
					};

					this->m_input_element_list.emplace_back(element_size,buffer_index,desc);
				}

				/**
				
				*	@brief	�ǉ����ꂽ���̓��C�A�E�g�v�f�����ɍ쐬����

				*	@param	�Ȃ�

				*	@return	�Ȃ�
				
				*/
				void CreateInputLayout(){
					if (this->GetShader()) return;

					std::size_t element_num = this->m_input_element_list.size();
					D3D11_INPUT_ELEMENT_DESC*	desc = new D3D11_INPUT_ELEMENT_DESC[element_num];

					//desc�̃R�s�[
					int i = 0;
					for (auto &it : this->m_input_element_list){
						desc[i] = it.m_element_desc;
						++i;
					}
					
					bool result = D3D11::CreateInputLayout(&this->m_p_input_layout, desc, element_num,this->m_p_vertex_shader_handle->GetResourceBuffer(),this->m_p_vertex_shader_handle->GetResourceSize());					
					assert(result);

					this->m_input_element_list.clear();
				}

				/**
				
				*	@brief	�V�F�[�_��API�̎擾

				*	@param	�Ȃ�

				*	@return	���|�C���^
				
				*/
				void* GetShader()const override final { return this->m_p_input_layout.Get(); }


				/**
				
				*	@brief	�C���v�b�g���C�A�E�g�̌��̒��_�V�F�[�_�̐ݒ�

				*	@param[in]	ptr	���_�V�F�[�_

				*	@return	�Ȃ�
				
				*/
				void SetVertexShader(VSHANDLE* ptr){ this->m_p_vertex_shader_handle = ptr; }
			private:
				ComPtr<ID3D11InputLayout>	m_p_input_layout;
				C_InputElementList	m_input_element_list;
				VSHANDLE*	m_p_vertex_shader_handle = nullptr;
			};

			using INPUT_LAYOUT_HANDLE = C_ShaderObject < ID3D11InputLayout > ;


			void* ShaderAlloc(std::size_t size, std::size_t align){
				return std::malloc(size);
			}

			void ShaderFree(void *ptr){
				std::free(ptr);
			}
			/**
			
			*	@brief	���_�V�F�[�_�̓ǂݍ���

			*	@param[in]	file_path	�g���q���������t�@�C���p�X

			*	@return	�V�F�[�_�n���h��
			
			*/
			SHADERHANDLE	LoadVertexShader(const char* file_path){
				//�g���q�̒ǉ�
				char path[256];
				strcpy_s(path, 256, file_path);
				strcat_s(path, 256, ".cso");

				FileSystem::C_FileReader	reader(path);
				auto handle = Utility::MakeShared<VSHANDLE>();
				handle->SetResource(reader.Read(ShaderAlloc, ShaderFree));

				D3D11::CreateVertexShader(handle->GetAddressOf(), handle->GetResourceBuffer(), handle->GetResourceSize());

				return handle;
			}

			/**
			
			*	@brief	���������璸�_�V�F�[�_��ǂݍ���

			*	@param[in]	byte	�o�C�g�z��ւ̐擪�|�C���^
			*	@param[in]	size	�o�C�g��

			*	@return	�V�F�[�_�n���h��
			
			*/
			SHADERHANDLE LoadVertexShaderFromMem(void* byte, std::size_t size){
				//���������m�ۂ��A�R�s�[����
				void* copy_mem = ShaderAlloc(size, 1);
				std::memcpy(copy_mem, byte, size);

				auto handle = Utility::MakeShared<VSHANDLE>();
				FileSystem::S_ResourceData resource;
				resource.m_p_free_function = ShaderFree;
				resource.m_p_buffer = copy_mem;
				resource.m_length = size;

				handle->SetResource(resource);
				D3D11::CreateVertexShader(handle->GetAddressOf(), handle->GetResourceBuffer(), handle->GetResourceSize());

				return handle;
			}
			


			/**

			*	@brief	�s�N�Z���V�F�[�_�̓ǂݍ���

			*	@param[in]	file_path	�g���q���������t�@�C���p�X

			*	@return	�V�F�[�_�n���h��

			*/
			SHADERHANDLE	LoadPixelShader(const char* file_path){
				//�g���q�̒ǉ�
				char path[256];
				strcpy_s(path, 256, file_path);
				strcat_s(path, 256, ".cso");

				FileSystem::C_FileReader	reader(path);
				auto handle = Utility::MakeShared<PSHANDLE>();
				handle->SetResource(reader.Read(ShaderAlloc, ShaderFree));

				D3D11::CreatePixelShader(handle->GetAddressOf(), handle->GetResourceBuffer(), handle->GetResourceSize());

				return handle;
			}

			/**

			*	@brief	����������s�N�Z���V�F�[�_��ǂݍ���

			*	@param[in]	byte	�o�C�g�z��ւ̐擪�|�C���^
			*	@param[in]	size	�o�C�g��

			*	@return	�V�F�[�_�n���h��

			*/
			SHADERHANDLE LoadPixelShaderFromMem(void* byte, std::size_t size){
				//���������m�ۂ��A�R�s�[����
				void* copy_mem = ShaderAlloc(size, 1);
				std::memcpy(copy_mem, byte, size);

				auto handle = Utility::MakeShared<PSHANDLE>();
				FileSystem::S_ResourceData resource;
				resource.m_p_free_function = ShaderFree;
				resource.m_p_buffer = copy_mem;
				resource.m_length = size;
				handle->SetResource(resource);
				
				D3D11::CreatePixelShader(handle->GetAddressOf(), handle->GetResourceBuffer(), handle->GetResourceSize());

				return handle;
			}
	
			/**
			
			*	@brief	���̓��C�A�E�g�n���h���̍쐬

			*	@param[in]	vertex_shader	���̓��C�A�E�g�쐬���̒��_�V�F�[�_

			*	@return	�Ȃ�
			
			*/
			SHADERHANDLE	CreateInputLayoutHandle(SHADERHANDLE& vertex_shader){
				return Utility::MakeShared<INPUT_LAYOUT_HANDLE>(static_cast<VSHANDLE*>(vertex_shader.Get()));
			}

			/**
			
			*	@brief	���̓��C�A�E�g�̗v�f�̒ǉ�
			
			*	@param[in]	input_layout_handle	�쐬���ꂽ���̓��C�A�E�g�n���h��
			*	@param[in]	semantics	�Z�}���e�B�N�X��
			*	@param[in]	buffer_index	�o�C���h����钸�_�o�b�t�@�z��̃C���f�b�N�X
			*	@param[in]	format			�v�f�̃t�H�[�}�b�g

			*	@return	�Ȃ�

			*/
			void AddInputLayoutElement(SHADERHANDLE& input_layout_handle, const char* semantics, std::size_t buffer_index, int format){
				auto handle = static_cast<INPUT_LAYOUT_HANDLE*>(input_layout_handle.Get());
				handle->AddElementDesc(semantics, buffer_index, GetFormatByteSize(format), format);
			}

			/**
			
			*	@brief	�ǉ����ꂽ���̓��C�A�E�g�v�f������̓��C�A�E�g���쐬

			*	@param[in]	input_layout_handle	���̓��C�A�E�g�n���h��

			*	@return	�Ȃ�
			
			*/
			void CreateInputLayout(SHADERHANDLE& input_layout_handle){
				auto handle = static_cast<INPUT_LAYOUT_HANDLE*>(input_layout_handle.Get());
				handle->CreateInputLayout();
			}
		}
	}
}