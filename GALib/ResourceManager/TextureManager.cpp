///>プロジェクトのヘッダのインクルード
#include "TextureManager.h"
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
		
		*	@brief	テクスチャ関連の名前空間
		
		*/
		namespace TextureManager{
			/**
			
			*	@brief	テクスチャハンドルの実装クラス
			
			*/
			class C_TextureHandle final : public IC_TextureHandle{
			public:
				/**
				
				*	@brief	コンストラクタ

				*	@param	なし
				
				*/
				C_TextureHandle(){}

				/**
				
				*	@brief	デストラクタ

				*	@param	なし
				
				*/
				~C_TextureHandle(){}

				/**
				
				*	@brief	指定されたインデックスにUVを設定する

				*	@param[in]	index	頂点インデックス
				*	@param[in]	u		u
				*	@param[in]	v		v

				*	@return	なし
				
				*/
				void SetUV(int index, float u, float v){ 
					this->m_uv[index].m_u = u; 
					this->m_uv[index].m_v = v;
				}

				/**
				
				*	@brief	指定された頂点インデックスのUVを取得

				*	@param[in]	index	頂点インデックス

				*	@return	UV構造体
				
				*/
				Math::Vector2 GetTextureUV(int index)const override{ return this->m_uv[index]; }

				/**
				
				*	@brief	SRVのアドレスの取得

				*	@param	なし

				*	@return	ID3D11ShaderResourceView**

				*/
				ID3D11ShaderResourceView**	GetAddressOf(){ return &this->m_p_srv; }

				/**
				
				*	@brief	テクスチャAPIの取得
				
				*	@param	なし

				*	@return	テクスチャAPIのポインタ

				*/
				void*	GetTextureAPIPtr()const override{
					if (this->m_p_parent_texture) return this->m_p_parent_texture->GetTextureAPIPtr();
					return this->m_p_srv.Get();
				}
				
				/**
				
				*	@brief	テクスチャ幅の設定

				*	@param[in]	width,height	テクスチャの幅、高さ

				*	@return	なし
				
				*/
				void SetTextureSize(int width, int height){
					this->m_width = width;
					this->m_height = height;
				}

				/**
				
				*	@brief	テクスチャ横幅の取得

				*	@param	なし

				*	@return	横幅
				
				*/
				int GetTextureWidth()const  override{ return this->m_width; }

				/**
				
				*	@brief	テクスチャ縦幅の取得

				*	@param	なし

				*	@return	縦幅
				
				*/
				int GetTextureHeight() const override{ return this->m_height; }


				/**
				
				*	@brief	親テクスチャハンドルの設定

				*	@param[in]	ptr	親テクスチャハンドルへのぽいんた

				*	@return	なし
				
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
			
			*	@brief	SRVからテクスチャサイズを取得する

			*	@param[in]	texture	SRVのポインタ
			*	@param[out]	width,height	テクスチャサイズ格納用変数の参照

			*	@return	なし

			*/
			void GetTextureSize(ID3D11ShaderResourceView *texture,int& out_width,int &out_height){
				//リソースを取得
				if (!texture){
					out_width = 0;
					out_height = 0;
				}
				Microsoft::WRL::ComPtr<ID3D11Resource> resource;
				texture->GetResource(&resource);

				//何やってるのかわからんけどこうする
				Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
				resource.As(&texture2D);

				//テクスチャ情報取得
				D3D11_TEXTURE2D_DESC desc;
				texture2D->GetDesc(&desc);

				out_width = desc.Width;
				out_height = desc.Height;

			}
		}
	}

}



/**

*	@brief	指定されたファイルのテクスチャを読み込む

*	@param[in]	file_path	ファイルパス

*	@return	テクスチャハンドル

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

*	@brief	指定された親テクスチャからテクスチャを切り出す

*	@param[in]	tx,ty	左上座標
*	@param[in]	tw,th	左上座標からの幅、高さ
*	@param[in]	base_handle	親ハンドル

*	@return	テクスチャハンドル

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

*	@brief	テクスチャの分割読み込み

*	@param[in]	base_graph	元となるテクスチャ
*	@param[in]	tx,ty	開始左上座標
*	@param[in]	tw,th	分割テクスチャサイズ
*	@param[in]	x_num,y_num	縦横分割数
*	@param[in]	div_num	読み込み数
						4*4で14を指定した場合、縦三列分と四列目の二つ目のテクスチャまで読み込む
*	@param[out]	out	出力配列

*	@return	なし

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
