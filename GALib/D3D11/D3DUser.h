#pragma once
#include "../common.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	D3D11関連の名前空間

	*/
	namespace D3D11{

		/**
		
		*	@brief	バッファを作成する
		
		*	@param[out]	buf			ID3D11Buffer*へのアドレス
		*	@param[in]	byte_width	バッファサイズ
		*	@param[in]	usag		バッファへのアクセス指定
		*	@param[in]	bind_flags	バッファのバインド指定
		*	@param[in]	cpu_access	CPUアクセス指定
		*	@param[in]	misc_flag	その他のフラグ
		*	@param[in]	structure_byte_stride		構造化バッファの構造体サイズ
		*	@param[in]	initial_data	初期化データ

		*	@return true	成功
		*	@return	false	失敗

		*/
		bool CreateBuffer(ID3D11Buffer **buf, UINT byte_width, D3D11_USAGE usage, UINT BindFlag, UINT cpu_access_flags, UINT misc_flags = 0, UINT StructureByteStride = 0, void* initdata = nullptr);				//バッファの作成

		/**
		
		*	@brief	Texture2Dを作成する

		*	@param[out]	pp_tex			ID3D11Texture2D*へのポインタ
		*	@param[in]	bind_flag		テクスチャのバインド指定
		*	@param[in]	width,height	幅、高さ
		*	@param[in]	format			テクスチャフォーマット
		*	@param[in]	usage			RW指定
		*	@param[in]	cpu_access		CPUからのアクセス指定
		*	@param[in]	mip_level		テクスチャのミップマップレベル
		*	@param[in]	array_size		テクスチャ配列のテクスチャ数
		*	@param[in]	misc_flag		一般性の低いリソースオプション
		*	@param[in]	multi_sample	設定されたMSAAレベルを適用する、適用しない場合MSAAは無し

		*	@return	true	成功
		*	@return	false	失敗

		*/
		bool CreateTexture2D(ID3D11Texture2D** pp_tex, UINT bind_flag, UINT width, UINT height, DXGI_FORMAT format, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, UINT cpu_access_flags = DXGI_CPU_ACCESS_NONE, UINT mip_level = 1, UINT array_size = 1, UINT misc_flag = 0, bool use_multi_sample = false);

		/**
		
		*	@brief	Texture2Dをリソースから作成する

		*	@param[out]	pp_tex			ID3D11Texture2D*へのポインタ
		*	@param[in]	def_buffer		リソース元
		*	@param[in]	sys_mem_pitch	横幅の１ラインのバイト数(width * px_byte)
		*	@param[in]	bind_flag		テクスチャのバインド指定
		*	@param[in]	width,height	幅、高さ
		*	@param[in]	format			テクスチャフォーマット
		*	@param[in]	usage			RW指定
		*	@param[in]	cpu_access		CPUからのアクセス指定
		*	@param[in]	mip_level		テクスチャのミップマップレベル
		*	@param[in]	array_size		テクスチャ配列のテクスチャ数
		*	@param[in]	misc_flag		一般性の低いリソースオプション

		*	@return	true	成功
		*	@return	false	失敗

		*/
		bool CreateTexture2D(ID3D11Texture2D** pp_tex, void* def_buffer, UINT sys_mem_pitch, UINT bind_flag, UINT width, UINT height, DXGI_FORMAT format, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, UINT cpu_access_flags = DXGI_CPU_ACCESS_NONE, UINT mip_level = 1, UINT array_size = 1, UINT misc_flag = 0);

		/**
		
		*	@brief	Texture1Dをリソースから作成する

		*	@param[out]	pp_tex			ID3D11Texture1D*へのポインタ
		*	@param[in]	def_buffer		リソース元
		*	@param[in]	bind_flag		テクスチャのバインド指定
		*	@param[in]	width			幅
		*	@param[in]	format			テクスチャフォーマット
		*	@param[in]	usage			RW指定
		*	@param[in]	cpu_access		CPUからのアクセス指定
		*	@param[in]	mip_level		テクスチャのミップマップレベル
		*	@param[in]	array_size		テクスチャ配列のテクスチャ数
		*	@param[in]	misc_flag		一般性の低いリソースオプション

		*	@return true	成功
		*	@return	false	失敗
		*/
		bool CreateTexture1D(ID3D11Texture1D** pp_tex, void* def_buffer, UINT width, UINT bind_flags, DXGI_FORMAT format, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, UINT cpu_access_flags = DXGI_CPU_ACCESS_NONE, UINT mip_level = 1, UINT array_size = 1, UINT misc_flags = 0);

		/**
		
		*	@brief	SRVをリソースから作成する

		*	@param[out]	pp_srv				ID3D11ShaderResourceView*へのポインタ
		*	@param[in]	tesptr				SRVにバインドするリソース
		*	@param[in]	format				テクスチャフォーマット
		*	@param[in]	view_dimension		次元
		*	@param[in]	miplevel			ミップマップレベル

		*	@return true	成功
		*	@return	false	失敗

		*/
		bool CreateShaderResourceView(ID3D11ShaderResourceView** pp_srv, ID3D11Resource* pp_tex, DXGI_FORMAT format, D3D11_SRV_DIMENSION view_dimension, UINT mip_levels = 1);

		/**

		*	@brief	RTVをTexture2Dから作成する

		*	@param[out]	pp_rtv		:	ID3D11RenderTargetView*ヘのポインタ
		*	@param[in]	pp_tex		:	バインドするテクスチャ2D

		*	@return true	成功
		*	@return	false	失敗
		*/
		bool CreateRenderTargetView(ID3D11RenderTargetView** pp_rtv, ID3D11Texture2D* pp_tex);

		/**

		*	@brief	ラスタライザステートを作成する
		
		*	@param[out]	rssptr			RRS*へのポインタ
		*	@param[in]	fill			レンダリング時の描画モード
		*	@param[in]	cull			カリング指定
		*	@param[in]	front			ポリゴンの時計周り指定
		*	@param[in]	depthbias		指定のピクセルに加算する深度値
		*	@param[in]	depthclamp		最大深度バイアス
		*	@param[in]	slope_ccale_depth_bias		指定のピクセルのスロープに対するスカラ
		*	@param[in]	depthclip			距離にも℉づいたクリッピング
		*	@param[in]	scissor_enable		シザー矩形カリングを有効にするか
		*	@param[in]	multi_sample		MSAAを有効にするか
		*	@param[in]	aalineenable		線のアンチエイリアシングの可否

		*	@return	true	成功
		*	@return	false	失敗

		*/
		bool CreateRasterizerState(ID3D11RasterizerState** pp_rrs, D3D11_FILL_MODE fill, D3D11_CULL_MODE cull, bool front = false, int depth_bias = 0, float depth_clamp = 1.0f, float slope_ccale_depth_bias = 0, bool depth_clip_enable = true, bool scissor_enable = false, bool multi_sample_enable = false, bool antialiased_line_enable = false);

		/**

		*	@brief	深度ステンシルステートを作成する

		*	@param[out]	pp_dst					dst*へのポイインタ
		*	@param[in]	depth_enable			深度テストの可否
		*	@param[in]	mask					深度データの変更可能な部分の識別
		*	@param[in]	compartision_func		比較関数
		*	@param[in]	stencil_enable			ステンシルテストの可否
		*	@param[in]	stencil_read_mask		ステンシルデータの読み取り識別
		*	@param[in]	stencil_write_mask		ステンシルデータの書き込み識別
		*	@param[in]	front_desc				法線がカメラの方向を向いているサーフェスを持つピクセルの深度テストとステンシル テストの結果を使用する方法を識別します 
		*	@param[in]	back_desc				法線がカメラと逆方向を向いているサーフェスを持つピクセルの深度テストとステンシル テストの結果を使用する方法を識別します

		*	@return true	成功
		*	@return false	失敗

		*/
		bool CreateDepthStencilState(ID3D11DepthStencilState** pp_dst, bool depth_enable = true, D3D11_DEPTH_WRITE_MASK mask = D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_FUNC compartision_func = D3D11_COMPARISON_LESS_EQUAL, bool stencil_enable = false, UINT8 stencil_read_mask = D3D11_DEFAULT_STENCIL_READ_MASK, UINT8 stencil_write_mask = D3D11_DEFAULT_STENCIL_WRITE_MASK, D3D11_DEPTH_STENCILOP_DESC* front_desc = nullptr, D3D11_DEPTH_STENCILOP_DESC* back_desc = nullptr);

		/**
		
		*	@brief	ステンシルビューの作成

		*	@param[out]	pp_dst				ステンシルビュー
		*	@param[in]	tesptr				ステンシルテクスチャ
		*	@param[in]	format				テクスチャフォーマット
		*	@param[in]	view_dimension		次元

		*	@return true	成功
		*	@return false	失敗
		*/
		bool CreateDepthStencilView(ID3D11DepthStencilView** pp_dst, ID3D11Texture2D* pp_tex, DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_DSV_DIMENSION view_dimension = D3D11_DSV_DIMENSION_TEXTURE2D);

		/**

		*	@brief	サンプラステートの作成

		*	@param[out]	ptr				サンプラへのポインタ
		*	@param[in]	filster			フィルタ
		*	@param[in]	address_uvw		0~1範囲外の座標解決
		*	@param[in]	anisotropy		異方性フィルタサンプル数(1~16)
		*	@param[in]	comparison		既存のデータとの比較

		*	@return	true	成功
		*	@return false	失敗

		*/
		bool CreateSampleState(ID3D11SamplerState** ptr, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_uvw, UINT anisotropy = 16, D3D11_COMPARISON_FUNC comparison = D3D11_COMPARISON_NEVER);

		/**
		
		*	@brief	ブレンドステートの作成

		*	@param[out]	ptr				ブレンドステートへのポインタ
		*	@param[in]	blend_enable	ブレンドを行うかどうかのフラグ
		*	@param[in]	src_blend		ブレンドを行うデータのRGBソースを設定する
		*	@param[in]	dest_blend		ブレンド先のRGBソースを設定する
		*	@param[in]	blend_op		データソースの組み合わせの設定をする
		*	@param[in]	src_alpha		ブレンドを行うデータのαを設定する
		*	@param[in]	dest_alpha		ブレンド先のデータのαを設定する
		*	@param[in]	blend_alpha_op	αソースの組み合わせを設定する
		*	@param[in]	mask			書き込みマスク
			
		*	@return	true	成功
		*	@return	false	失敗
		
		*/
		bool CreateBlendState(ID3D11BlendState** ptr,bool blend_enable,D3D11_BLEND src_blend,D3D11_BLEND dest_blend,D3D11_BLEND_OP blend_op,D3D11_BLEND src_alpha,D3D11_BLEND dest_alpha,D3D11_BLEND_OP blend_alpha_op,D3D11_COLOR_WRITE_ENABLE mask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL);

		/**
		
		*	@brief	ディファードコンテキストの作成

		*	@param[out]	context	ID3D11DeviceContext*へのアドレス

		*	@return true	成功
		*	@return false	失敗

		*/
		bool CreateDeferredContext(ID3D11DeviceContext** context);

		/**

		*	@brief	コマンドリストを作成しそこにグラフィックコマンドを記録
					コマンドを記録したコマンドリストを返却する

		*	@param[in]	context		ディファードコンテキスト
		*	@param[in]	restore_defferd_context_state	コマンドリストの記録後にディファードコンテキストの状態を復元するかのフラグ

		*	@return	コマンドリストのComPtr

		*/
		ComPtr<ID3D11CommandList> FinishCommandList(ID3D11DeviceContext* context, bool restore_defferd_context_state = false);

		/**
		
		*	@brief	コマンドリストの再生
		
		*	@param[in]	context		コマンドを積むコンテキスト
		*	@param[in]	command		再生するコマンドリスト
		*	@param[in]	restore_context_state		再生後にステートを戻すか

		*	@return	なし

		*/
		void ExecuteCommandList(ID3D11DeviceContext* context, ID3D11CommandList* command, bool restore_context_state = false);

		/**
		
		*	@brief	ビューポートの作成

		*	@param[out]	out	ビューポートへの参照
		*	@param[in]	x1,y1	左上座標
		*	@param[in]	width,height	左上座標からの幅と高さ
		*	@param[in]	min_depth,max_depth		深度情報

		*	@return なし

		*/
		void CreateViewPort(D3D11_VIEWPORT &out, int x1, int y1, int width, int height, float min_depth = 0.0f, float max_depth = 1.0f);

		/**

		*	@brief	ピクセルシェーダの作成

		*	@parma[out]	pp_px	ID3D11PixelShaderへのポインタ
		*	@param[in]	byte_code	コンパイル済みシェーダへのポインタ
		*	@param[in]	size		コンパイル済みシェーダのバイトサイズ
		*	@param[in]	linkage		クラスリンケージのポインタ

		*	@return true	成功
		*	@return	false	失敗

		*/
		bool CreatePixelShader(ID3D11PixelShader** pp_px, void* byte_code,std::size_t size,ID3D11ClassLinkage* linkage = nullptr);

		/**

		*	@brief	頂点シェーダの作成

		*	@parma[out]	pp_vs	ID3D11VertexShaderへのポインタ
		*	@param[in]	byte_code	コンパイル済みシェーダへのポインタ
		*	@param[in]	size		コンパイル済みシェーダのバイトサイズ
		*	@param[in]	linkage		クラスリンケージのポインタ

		*	@return true	成功
		*	@return	false	失敗

		*/
		bool CreateVertexShader(ID3D11VertexShader** pp_vs, void* byte_code, std::size_t size, ID3D11ClassLinkage* linkage = nullptr);

		/**

		*	@brief	ジオメトリシェーダの作成

		*	@parma[out]	pp_gs	ID3D11GeometryShaderへのポインタ
		*	@param[in]	byte_code	コンパイル済みシェーダへのポインタ
		*	@param[in]	size		コンパイル済みシェーダのバイトサイズ
		*	@param[in]	linkage		クラスリンケージのポインタ

		*	@return true	成功
		*	@return	false	失敗

		*/
		bool CreateGeometryShader(ID3D11GeometryShader** pp_gs, void* byte_code, std::size_t size, ID3D11ClassLinkage* linkage = nullptr);

		/**
		
		*	@brief	テクスチャを読み込みSRVを作成する

		*	@param[in]	file_path	テクスチャへのファイルパス
		*	@param[out]	pp_srv		SRVへのダブルポインタ

		*	@return true	成功
		*	@return false	失敗
		
		*/
		bool CreateWICTexture(const char* file_path, ID3D11ShaderResourceView** pp_srv);

		/**

		*	@brief	入力レイアウトの作成
		
		*	@param[out]	pp_input_layout	入力レイアウトへのダブルポインタ
		*	@param[in]	desc			入力レイアウト構造体配列へのポインタ
		*	@param[in]	array_size		構造体配列のサイズ
		*	@param[in]	byte_code		頂点シェーダのバイト構造へのポインタ
		*	@param[in]	size			頂点シェーダのバイトサイズ

		*	@return true	成功
		*	@return false	失敗

		*/
		bool CreateInputLayout(ID3D11InputLayout** pp_input_layout, D3D11_INPUT_ELEMENT_DESC* desc, UINT array_size,void* byte_code,std::size_t size);

		/**
		
		*	@brief	ビューポートの設定

		*	@param[in]	context	コンテキストへのポインタ
		*	@param[in]	view	ビューポート配列へのポインタ
		*	@param[in]	num		ビューポート数

		*	@return		なし

		*/
		void SetViewPort(ID3D11DeviceContext* context, D3D11_VIEWPORT* view, UINT num = 1);

		/**
		
		*	@brief	ビューポートの設定
		
		*	@param[in]	context	コンテキストへのポインタ
		*	@param[in]	x1,y1	左上座標
		*	@param[in]	width,height	左上座標からの幅と高さ

		*	@return		なし
		
		*/
		void SetViewPort(ID3D11DeviceContext* context, int x1, int y1, int w, int h);

		/**
		
		*	@brief	入力アセンブラに頂点バッファをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	stride		頂点バッファの１頂点のストライド値の配列
		*	@param[in]	offset		頂点バッファ開始オフセットの配列
		*	@param[in]	elements	頂点バッファのポインタ

		*	@return		なし
		
		*/
		template<class... Elements>
		void IASetVertexBuffers(ID3D11DeviceContext* context, UINT start_slot, UINT* stride, UINT* offset, Elements...elements){
			ID3D11Buffer* buf[sizeof...(Elements)] = { elements... };
			context->IASetVertexBuffers(start_slot, sizeof...(Elements), buf, stride, offset);
		}

		/**
		
		*	@brief	入力アセンブラにインデックスバッファをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	buffer	インデックスバッファ

		*	@return		なし

		*/
		void IASetIndexBuffer(ID3D11DeviceContext* context, ID3D11Buffer* buffer);

		
		/**
		
		*	@brief	頂点シェーダにコンスタントバッファをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするコンスタントバッファ

		*	@return	なし

		*/
		template<class... Elements>
		void VSSetConstantBuffers(ID3D11DeviceContext* context, UINT start_slot,Elements... elements){
			ID3D11Buffer* buf[sizeof...(Elements)] = { elements... };
			context->VSSetConstantBuffers(start_slot, sizeof...(Elements), buf);
		}

		/**

		*	@brief	頂点シェーダにシェーダリソースをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするシェーダリソース

		*	@return	なし

		*/
		template<class... Elements>
		void VSSetShaderResource(ID3D11DeviceContext* context, UINT start_slot,  Elements... elements){
			ID3D11ShaderResourceView* srv[sizeof...(Elements)] = { elements... };
			context->VSSetShaderResources(start_slot, sizeof...(Elements), srv);
		}

		/**

		*	@brief	ピクセルシェーダにコンスタントバッファをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするコンスタントバッファ

		*	@return	なし

		*/
		template<class... Elements>
		void PSSetConstantBuffers(ID3D11DeviceContext* context, UINT start_slot,  Elements... elements){
			ID3D11Buffer* buf[sizeof...(Elements)] = { elements... };
			context->PSSetConstantBuffers(start_slot, sizeof...(Elements), buf);
		}

		/**

		*	@brief	ピクセルシェーダにシェーダリソースをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするシェーダリソース

		*	@return	なし

		*/
		template<class... Elements>
		void PSSetShaderResource(ID3D11DeviceContext* context, UINT start_slot,  Elements... elements){
			ID3D11ShaderResourceView* srv[sizeof...(Elements)] = { elements... };
			context->PSSetShaderResources(start_slot, sizeof...(Elements), srv);

		}

		/**

		*	@brief	ピクセルシェーダにサンプラをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするサンプラ

		*	@return	なし

		*/
		template<class... Elements>
		void PSSetSampler(ID3D11DeviceContext* context, UINT start_slot, Elements... elements){
			ID3D11SamplerState* sampler[sizeof...(Elements)] = { elements... };
			context->PSSetSamplers(start_slot, sizeof...(Elements), sampler);
		}

		/**

		*	@brief	ジオメトリシェーダにコンスタントバッファをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするコンスタントバッファ

		*	@return	なし

		*/
		template<class... Elements>
		void GSSetConstantBuffers(ID3D11DeviceContext* context, UINT start_slot,  Elements... elements){
			ID3D11Buffer* buf[sizeof...(Elements)] = { elements... };
			context->GSSetConstantBuffers(start_slot, sizeof...(Elements), buf);
		}

		/**

		*	@brief	ジオメトリシェーダにシェーダリソースをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	start_slot	開始レジスタ番号
		*	@param[in]	elements	バインドするシェーダリソース

		*	@return	なし

		*/
		template<class... Elements>
		void GSSetShaderResource(ID3D11DeviceContext* context,UINT start_slot,  Elements... elements){
			ID3D11ShaderResourceView* srv[sizeof...(Elements)] = { elements... };
			context->GSSetConstantBuffers(start_slot, sizeof...(Elements), srv);
		}

		/**

		*	@brief	レンダーターゲットをバインドする

		*	@param[in]	context	コンテキスト
		*	@param[in]	depth	深度ビュー
		*	@param[in]	elements	バインドするレンダーターゲット

		*	@return	なし

		*/
		template<class... Elements>
		void OMSetRenderTargets(ID3D11DeviceContext* context, ID3D11DepthStencilView* depth, Elements... elements){
			ID3D11RenderTargetView* rtv[sizeof...(Elements)] = { elements... };
			context->OMSetRenderTargets(sizeof...(Elements), rtv, depth);
		}

		/**
		
		*	@brief	指定されたコンテキストにラスタライザステートを設定する

		*	@param[in]	context	デバイスコンテキスト
		*	@param[in]	raster	ラスタライザステート

		*	@return	なし
		
		*/
		static void RSSetState(ID3D11DeviceContext* context, ID3D11RasterizerState* raster){
			context->RSSetState(raster);
		}

		/**
		
		*	@brief	指定されたコンテキストに深度ステートを設定する

		*	@param[in]	context	デバイスコンテキスト
		*	@param[in]	depth	ステート
		*	@param[in]	stencil_ref	ステンシルテストの実行時に参照される値

		*	@return	なし
		
		*/
		static void OMSetDepthStencilState(ID3D11DeviceContext* context, ID3D11DepthStencilState* depth, UINT stencil_ref = 0){
			context->OMSetDepthStencilState(depth, stencil_ref);
		}

		/**
		
		*	@brief	指定されたレンダーターゲットをクリアする

		*	@param[in]	context	コンテキスト
		*	@param[in]	view	レンダーターゲット
		*	@param[in]	r,g,b,a	クリアカラー(0.0f~1.0f)

		*	@return	なし
		
		*/
		void ClearRenderTargetView(ID3D11DeviceContext* context, ID3D11RenderTargetView* view, float r = 0, float g = 0, float b =0, float a = 0);

		/**
		
		*	@brief	深度バッファのクリア
		
		*	@param[in]	context		コンテキスト
		*	@param[in]	view		深度ビュー
		*	@param[in]	clear_flag	クリアフラグ
		*	@param[in]	depth		初期化する深度値
		*	@param[in]	stencil		初期化するステンシル値

		*	@return		なし

		*/
		void ClearDepthStencilView(ID3D11DeviceContext* context, ID3D11DepthStencilView* view, UINT clear_flag = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, float depth = 1.0f, UINT8 stencil = 0);

		/**
		
		*	@brief	コンスタンドバッファの更新

		*	@param[in]	context	コンテキスト
		*	@param[in]	resource	更新元のコンスタンドバッファ
		*	@param[in]	src_data	更新する情報

		*	@return		なし
		
		*/
		void UpdateConstantBuffer(ID3D11DeviceContext* context, ID3D11Resource* resource, void* src_data);
		
	}
}