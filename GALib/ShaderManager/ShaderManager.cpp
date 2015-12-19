#include "ShaderManager.h"
#include "../D3D11/D3DUser.h"
#include "../FileSystem/FileReader.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	リソース関連の名前空間
	
	*/
	namespace Resource{
		/**
		
		*	@brief	シェーダ関連の名前空間

		*/
		namespace ShaderManager{
			/**
			
			*	@brief	シェーダ管理オブジェクト実装
			
			*/
			template<class _Shader>
			class C_ShaderObject final : public IC_ShaderObject{
			public:

				/**
				
				*	@brief	デストラクタ

				*	@param	なし
				
				*/
				~C_ShaderObject(){
					this->m_resource.Destroy();
				}

				/**
				
				*	@brief	シェーダAPIポインタの取得

				*	@param	なし

				*	@return	ポインタ
				
				*/
				void* GetShader() const override final{ return this->m_p_shader.Get(); }

				/**
				
				*	@brief	COMオブジェクトのアドレスの取得

				*	@param	なし

				*	@return	_Shader**
				
				*/
				_Shader**	GetAddressOf(){ return &this->m_p_shader; }

				
				/**
				
				*	@brief	シェーダのバイトコードを保持するためFileReaderから読みこんだリソースを保持する

				*	@param[in] resource	FileReaderから読み込んだS_ResourceData

				*	@return	なし
				
				*/
				void SetResource(FileSystem::S_ResourceData resource){
					this->m_resource = resource;
				}

				/**
				
				*	@brief	リソースバッファのポインタを取得

				*	@param	なし

				*	@return	ポインタ
				
				*/
				void* GetResourceBuffer(){ return this->m_resource.m_p_buffer; }

				/**
				
				*	@brief	リソースのサイズの取得

				*	@param	なし

				*	@return	サイズ
				
				*/
				std::size_t GetResourceSize(){ return this->m_resource.m_length; }

			private:
				ComPtr<_Shader>	m_p_shader;
				FileSystem::S_ResourceData	m_resource;
			};

			using VSHANDLE = C_ShaderObject < ID3D11VertexShader > ;
			using PSHANDLE = C_ShaderObject < ID3D11PixelShader > ;

			/**
			
			*	@brief	入力レイアウト管理クラス
			
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
				
				*	@brief	コンストラクタ

				*	@param[in]	ptr	入力レイアウト作成元の頂点シェーダハンドル
				
				*/
				C_ShaderObject(VSHANDLE* ptr) : m_p_vertex_shader_handle(ptr){}

				/**

				*	@brief	リストにエレメントの追加

				*	@parma[in]	semantics	セマンティクス名
				*	@parma[in]	buffer_index	頂点バッファ配列のインデックス
				*	@parma[in]	element_size	要素のバイト数
				*	@parma[in]	format			要素のフォーマット

				*	@return	なし

				*/
				void AddElementDesc(const char* semantics, std::size_t buffer_index, std::size_t element_size, int format){
					std::size_t size = 0;
					//バッファの先頭からのバイト数を計算
					for (auto &it : this->m_input_element_list){
						//同一インデックスだけ加算する
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
				
				*	@brief	追加された入力レイアウト要素を元に作成する

				*	@param	なし

				*	@return	なし
				
				*/
				void CreateInputLayout(){
					if (this->GetShader()) return;

					std::size_t element_num = this->m_input_element_list.size();
					D3D11_INPUT_ELEMENT_DESC*	desc = new D3D11_INPUT_ELEMENT_DESC[element_num];

					//descのコピー
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
				
				*	@brief	シェーダ生APIの取得

				*	@param	なし

				*	@return	生ポインタ
				
				*/
				void* GetShader()const override final { return this->m_p_input_layout.Get(); }


				/**
				
				*	@brief	インプットレイアウトの元の頂点シェーダの設定

				*	@param[in]	ptr	頂点シェーダ

				*	@return	なし
				
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
			
			*	@brief	頂点シェーダの読み込み

			*	@param[in]	file_path	拡張子を除いたファイルパス

			*	@return	シェーダハンドル
			
			*/
			SHADERHANDLE	LoadVertexShader(const char* file_path){
				//拡張子の追加
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
			
			*	@brief	メモリから頂点シェーダを読み込む

			*	@param[in]	byte	バイト配列への先頭ポインタ
			*	@param[in]	size	バイト数

			*	@return	シェーダハンドル
			
			*/
			SHADERHANDLE LoadVertexShaderFromMem(void* byte, std::size_t size){
				//メモリを確保し、コピーする
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

			*	@brief	ピクセルシェーダの読み込み

			*	@param[in]	file_path	拡張子を除いたファイルパス

			*	@return	シェーダハンドル

			*/
			SHADERHANDLE	LoadPixelShader(const char* file_path){
				//拡張子の追加
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

			*	@brief	メモリからピクセルシェーダを読み込む

			*	@param[in]	byte	バイト配列への先頭ポインタ
			*	@param[in]	size	バイト数

			*	@return	シェーダハンドル

			*/
			SHADERHANDLE LoadPixelShaderFromMem(void* byte, std::size_t size){
				//メモリを確保し、コピーする
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
			
			*	@brief	入力レイアウトハンドルの作成

			*	@param[in]	vertex_shader	入力レイアウト作成元の頂点シェーダ

			*	@return	なし
			
			*/
			SHADERHANDLE	CreateInputLayoutHandle(SHADERHANDLE& vertex_shader){
				return Utility::MakeShared<INPUT_LAYOUT_HANDLE>(static_cast<VSHANDLE*>(vertex_shader.Get()));
			}

			/**
			
			*	@brief	入力レイアウトの要素の追加
			
			*	@param[in]	input_layout_handle	作成された入力レイアウトハンドル
			*	@param[in]	semantics	セマンティクス名
			*	@param[in]	buffer_index	バインドされる頂点バッファ配列のインデックス
			*	@param[in]	format			要素のフォーマット

			*	@return	なし

			*/
			void AddInputLayoutElement(SHADERHANDLE& input_layout_handle, const char* semantics, std::size_t buffer_index, int format){
				auto handle = static_cast<INPUT_LAYOUT_HANDLE*>(input_layout_handle.Get());
				handle->AddElementDesc(semantics, buffer_index, GetFormatByteSize(format), format);
			}

			/**
			
			*	@brief	追加された入力レイアウト要素から入力レイアウトを作成

			*	@param[in]	input_layout_handle	入力レイアウトハンドル

			*	@return	なし
			
			*/
			void CreateInputLayout(SHADERHANDLE& input_layout_handle){
				auto handle = static_cast<INPUT_LAYOUT_HANDLE*>(input_layout_handle.Get());
				handle->CreateInputLayout();
			}
		}
	}
}