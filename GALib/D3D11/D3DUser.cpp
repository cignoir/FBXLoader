#include "../FileSystem/FileReader.h"
#include "D3DUser.h"
#include "D3D11Manager.h"

#include <WICTextureLoader.h>
// ---------------------------------------------------------
//バッファの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateBuffer(ID3D11Buffer **buf, UINT byte_width, D3D11_USAGE usage, UINT BindFlag, UINT cpu_access_flags, UINT misc_flags, UINT StructureByteStride, void* initdata){
	if (!buf){
		return false;
	}


	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = byte_width;
	BufferDesc.Usage = usage;
	BufferDesc.BindFlags = BindFlag;
	BufferDesc.CPUAccessFlags = cpu_access_flags;
	BufferDesc.MiscFlags = misc_flags;
	BufferDesc.StructureByteStride = StructureByteStride;

	if (initdata){
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = initdata;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		if (FAILED(D3D11::GetDevice()->CreateBuffer(&BufferDesc, &data, buf))){
#ifdef GA_LIB_DEBUG_MODE
			DebugPrint("FAILED CreateBuffer\n");
#endif
				return false;
		}
	}
	else {
		if (FAILED(D3D11::GetDevice()->CreateBuffer(&BufferDesc, nullptr, buf))){
#ifdef GA_LIB_DEBUG_MODE
			DebugPrint("FAILED CreateBuffer\n");
#endif
			return false;
		}
	}

	return true;
}

// ---------------------------------------------------------
//テクスチャ2Dの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateTexture2D(ID3D11Texture2D** pp_tex, UINT bind_flag, UINT width, UINT height, DXGI_FORMAT format, D3D11_USAGE usage, UINT cpu_access_flags, UINT mip_level, UINT array_size, UINT misc_flag, bool use_multi_sample){
	if (!pp_tex) return false;

	D3D11_TEXTURE2D_DESC tex_desc;
	ZeroMemory(&tex_desc, sizeof(tex_desc));

	tex_desc.BindFlags = bind_flag;
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.MipLevels = mip_level;
	tex_desc.ArraySize = array_size;
	tex_desc.Format = format;

	//リゾルブフラグが立っていないなら最低クオリティーを設定する
	if (!use_multi_sample){
		tex_desc.SampleDesc = D3D11::GetSampleDesc();
	}
	else {
		tex_desc.SampleDesc.Quality = 0;
		tex_desc.SampleDesc.Count = 1;
	}
	tex_desc.Usage = usage;
	tex_desc.CPUAccessFlags = cpu_access_flags;
	tex_desc.MiscFlags = misc_flag;

	//テクスチャの作成
	if (FAILED(D3D11::GetDevice()->CreateTexture2D(&tex_desc, nullptr, pp_tex))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateTexture2D\n");
#endif
		return false;
	}
	return true;
}

// ---------------------------------------------------------
//初期化データ有のテクスチャ2D作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateTexture2D(ID3D11Texture2D** pp_tex, void* def_buffer, UINT sys_mem_pitch, UINT bind_flag, UINT width, UINT height, DXGI_FORMAT format, D3D11_USAGE usage, UINT cpu_access_flags, UINT mip_level, UINT array_size, UINT misc_flag){
	if (!pp_tex) return false;

	D3D11_TEXTURE2D_DESC tex_desc;
	ZeroMemory(&tex_desc, sizeof(tex_desc));

	tex_desc.BindFlags = bind_flag;
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.MipLevels = mip_level;
	tex_desc.ArraySize = array_size;
	tex_desc.Format = format;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.Usage = usage;
	tex_desc.CPUAccessFlags = cpu_access_flags;
	tex_desc.MiscFlags = misc_flag;

	D3D11_SUBRESOURCE_DATA sub;
	sub.pSysMem = def_buffer;
	sub.SysMemPitch = sys_mem_pitch;
	sub.SysMemSlicePitch = 0;


	//テクスチャの作成
	if (FAILED(D3D11::GetDevice()->CreateTexture2D(&tex_desc, &sub, pp_tex))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateBuffer\n");
#endif
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//初期化データ有のテクスチャ1Dの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateTexture1D(ID3D11Texture1D** pp_tex, void* def_buffer, UINT width, UINT bind_flags, DXGI_FORMAT format, D3D11_USAGE usage, UINT cpu_access_flags, UINT mip_level, UINT array_size, UINT misc_flags){
	D3D11_TEXTURE1D_DESC desc = {};
	desc.ArraySize = array_size;
	desc.BindFlags = bind_flags;
	desc.CPUAccessFlags = cpu_access_flags;
	desc.Format = format;
	desc.MipLevels = mip_level;
	desc.MiscFlags = misc_flags;
	desc.Width = width;
	desc.Usage = usage;

	D3D11_SUBRESOURCE_DATA sub = {};
	sub.pSysMem = def_buffer;


	if (FAILED(D3D11::GetDevice()->CreateTexture1D(&desc, &sub, pp_tex))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateTexture1D\n");
#endif
		return false;
	}
	
	return true;
}



// ---------------------------------------------------------
//Texture2DからSRVを作成する
// ---------------------------------------------------------
bool GALib::D3D11::CreateShaderResourceView(ID3D11ShaderResourceView** pp_srv, ID3D11Resource* pp_tex, DXGI_FORMAT format, D3D11_SRV_DIMENSION view_dimension, UINT mip_levels){
	if (!pp_srv || !pp_tex) return false;


	// シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.Format = format;
	srvDesc.ViewDimension = view_dimension;
	srvDesc.Texture2D.MipLevels = mip_levels;

	// シェーダリソースビューの生成
	if (FAILED(D3D11::GetDevice()->CreateShaderResourceView(pp_tex, &srvDesc, pp_srv))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateSRV\n");
#endif
		return false;
	}


	return true;
}



// ---------------------------------------------------------
//Texture2Dからレンダーターゲットビューを作成する
// ---------------------------------------------------------
bool GALib::D3D11::CreateRenderTargetView(ID3D11RenderTargetView** pp_rtv, ID3D11Texture2D* pp_tex){
	if (!pp_rtv || !pp_tex) return false;

	//レンダーターゲットビューの作成
	if (FAILED(D3D11::GetDevice()->CreateRenderTargetView(pp_tex, NULL, pp_rtv))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateRTV\n");
#endif
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//ラスタライザーステートの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateRasterizerState(ID3D11RasterizerState** pp_rrs, D3D11_FILL_MODE fill, D3D11_CULL_MODE cull, bool front, int depth_bias, float depth_clamp, float slope_ccale_depth_bias, bool depth_clip_enable, bool scissor_enable, bool multi_sample_enable, bool antialiased_line_enable){
	D3D11_RASTERIZER_DESC hRasterizerDesc = {
		fill,
		cull,
		front,
		depth_bias,
		depth_clamp,
		slope_ccale_depth_bias,
		depth_clip_enable,
		scissor_enable,
		multi_sample_enable,
		antialiased_line_enable
	};

	if (FAILED(D3D11::GetDevice()->CreateRasterizerState(&hRasterizerDesc, pp_rrs))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateRS\n");
#endif
		return false;
	}


	return true;
}

// ---------------------------------------------------------
//ステンシルステートの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateDepthStencilState(ID3D11DepthStencilState** pp_dst, bool depth_enable, D3D11_DEPTH_WRITE_MASK mask, D3D11_COMPARISON_FUNC func, bool stencil_enable, UINT8 stencil_read_mask, UINT8 stencil_write_mask, D3D11_DEPTH_STENCILOP_DESC* front_desc, D3D11_DEPTH_STENCILOP_DESC* back_desc){
	//深度ステンシルステートの作成
	D3D11_DEPTH_STENCIL_DESC  sdc;
	ZeroMemory(&sdc, sizeof(sdc));
	sdc.DepthEnable = depth_enable;
	sdc.DepthWriteMask = mask;
	sdc.DepthFunc = func;

	sdc.StencilEnable = stencil_enable;
	sdc.StencilReadMask = stencil_read_mask;
	sdc.StencilWriteMask = stencil_write_mask;
	if (front_desc) sdc.FrontFace = *front_desc;
	if (back_desc) sdc.BackFace = *back_desc;


	if (FAILED(D3D11::GetDevice()->CreateDepthStencilState(&sdc, pp_dst))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateDSS\n");
#endif

		return false;
	}


	return true;
}

// ---------------------------------------------------------
//ステンシルビューの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateDepthStencilView(ID3D11DepthStencilView** pp_dst, ID3D11Texture2D* pp_tex, DXGI_FORMAT format, D3D11_DSV_DIMENSION view_dimension){
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = format;
	descDSV.ViewDimension = view_dimension;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;

	if (FAILED(D3D11::GetDevice()->CreateDepthStencilView(pp_tex, &descDSV, pp_dst))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateDSV\n");
#endif
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//サンプラーの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateSampleState(ID3D11SamplerState** ptr, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_uvw, UINT anisotropy, D3D11_COMPARISON_FUNC comparison)
{
	// サンプラを作成する
	D3D11_SAMPLER_DESC hDescSampler;
	//D3D11_FILTER_MIN_MAG_MIP_POINTで補完無し
	hDescSampler.Filter = filter;
	hDescSampler.AddressU = address_uvw;
	hDescSampler.AddressV = address_uvw;
	hDescSampler.AddressW = address_uvw;
	hDescSampler.BorderColor[0] = 0.0f;
	hDescSampler.BorderColor[1] = 0.0f;
	hDescSampler.BorderColor[2] = 0.0f;
	hDescSampler.BorderColor[3] = 0.0f;
	hDescSampler.MipLODBias = 0.0f;
	hDescSampler.MaxAnisotropy = anisotropy;
	hDescSampler.MinLOD = FLT_MAX * (-1);
	hDescSampler.MaxLOD = FLT_MAX;
	hDescSampler.ComparisonFunc = comparison;

	if (FAILED(D3D11::GetDevice()->CreateSamplerState(&hDescSampler, ptr))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateSampler\n");
#endif
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//ブレンドステートの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateBlendState(ID3D11BlendState** ptr, bool blend_enable, D3D11_BLEND src_blend, D3D11_BLEND dest_blend, D3D11_BLEND_OP blend_op, D3D11_BLEND src_alpha, D3D11_BLEND dest_alpha, D3D11_BLEND_OP blend_alpha_op, D3D11_COLOR_WRITE_ENABLE mask)
{
	D3D11_BLEND_DESC blend_desc;
	blend_desc.AlphaToCoverageEnable = FALSE;
	blend_desc.IndependentBlendEnable = FALSE;

	blend_desc.RenderTarget[0].BlendEnable = blend_enable;
	blend_desc.RenderTarget[0].SrcBlend = src_blend;
	blend_desc.RenderTarget[0].DestBlend = dest_blend;
	blend_desc.RenderTarget[0].BlendOp = blend_op;
	blend_desc.RenderTarget[0].SrcBlendAlpha = src_alpha;
	blend_desc.RenderTarget[0].DestBlendAlpha = dest_alpha;
	blend_desc.RenderTarget[0].BlendOpAlpha = blend_alpha_op;
	blend_desc.RenderTarget[0].RenderTargetWriteMask = mask;

	if (FAILED(D3D11::GetDevice()->CreateBlendState(&blend_desc, ptr))){
#ifdef GA_LIB_DEBUG_MODE
		DebugPrint("FAILED CreateBlendState\n");
#endif
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//ビューポートの作成
// ---------------------------------------------------------
void GALib::D3D11::CreateViewPort(D3D11_VIEWPORT &out, int x1, int y1, int width, int height, float min_depth, float max_depth){
	out.TopLeftX = (float)x1;
	out.TopLeftY = (float)y1;
	out.Width = (float)width;
	out.Height = (float)height;
	out.MinDepth = min_depth;
	out.MaxDepth = max_depth;

}

// ---------------------------------------------------------
//シェーダ作成
// ---------------------------------------------------------
bool GALib::D3D11::CreatePixelShader(ID3D11PixelShader** pp_px, void* byte_code, std::size_t size, ID3D11ClassLinkage* linkage){
	if (FAILED(D3D11::GetDevice()->CreatePixelShader(byte_code, size, linkage, pp_px))){

		return false;
	}
	return true;
}

bool GALib::D3D11::CreateVertexShader(ID3D11VertexShader** pp_vs, void* byte_code, std::size_t size, ID3D11ClassLinkage* linkage){
	if (FAILED(D3D11::GetDevice()->CreateVertexShader(byte_code, size, linkage, pp_vs))){
		return false;
	}
	return true;
}

bool GALib::D3D11::CreateGeometryShader(ID3D11GeometryShader** pp_gs, void* byte_code, std::size_t size, ID3D11ClassLinkage* linkage){
	if (FAILED(D3D11::GetDevice()->CreateGeometryShader(byte_code, size, linkage, pp_gs))){
		return false;
	}
	return true;
}

// ---------------------------------------------------------
//テクスチャ読み込み
// ---------------------------------------------------------
bool GALib::D3D11::CreateWICTexture(const char* file_path, ID3D11ShaderResourceView** srv){
	FileSystem::C_FileReader reader(file_path);

	auto buffer = reader.Read();

	if (FAILED(DirectX::CreateWICTextureFromMemory(D3D11::GetDevice(),static_cast<uint8_t*>(buffer.m_p_buffer), buffer.m_length,nullptr, srv))){
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//インプットレイアウトの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateInputLayout(ID3D11InputLayout** input, D3D11_INPUT_ELEMENT_DESC* desc, UINT array_size,void* shader_byte_code, std::size_t size){
	if (FAILED(D3D11::GetDevice()->CreateInputLayout(desc, array_size, shader_byte_code, size, input))){
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//ディファードコンテキストの作成
// ---------------------------------------------------------
bool GALib::D3D11::CreateDeferredContext(ID3D11DeviceContext** context){
	if (FAILED(D3D11::GetDevice()->CreateDeferredContext(0, context))){
		return false;
	}

	return true;
}

// ---------------------------------------------------------
//ビューポートの設定
// ---------------------------------------------------------
void GALib::D3D11::SetViewPort(ID3D11DeviceContext* context, D3D11_VIEWPORT* view, UINT num){
	context->RSSetViewports(num, view);
}

void GALib::D3D11::SetViewPort(ID3D11DeviceContext* context, int x1, int y1, int w, int h){
	D3D11_VIEWPORT view;
	CreateViewPort(view, x1, y1, w, h);
	SetViewPort(context,&view);
}

// ---------------------------------------------------------
//コマンドリストを作成しそこにグラフィックコマンドを記録
//コマンドを記録したコマンドリストを返却する
//context		:	ディファードコンテキスト
//restor~~		:	コマンドリストの記録後にディファードコンテキストの状態を復元するかのフラグ
// ---------------------------------------------------------
ComPtr<ID3D11CommandList> GALib::D3D11::FinishCommandList(ID3D11DeviceContext* context, bool restore_defferd_context_state){
	ComPtr<ID3D11CommandList> command ;
	context->FinishCommandList(restore_defferd_context_state, command.GetAddressOf());

	return command;
}

// ---------------------------------------------------------
//コマンドリストの再生
//contextq		:	コンテキスト
//command		:	再生するコマンドリスト
//restor		:	再生後にステートを戻すか
// ---------------------------------------------------------
void GALib::D3D11::ExecuteCommandList(ID3D11DeviceContext* context, ID3D11CommandList* command, bool restore_context_state ){
	context->ExecuteCommandList(command, restore_context_state);
}

// ---------------------------------------------------------
//レンダーターゲットのクリア
// ---------------------------------------------------------
void GALib::D3D11::ClearRenderTargetView(ID3D11DeviceContext* context, ID3D11RenderTargetView* view, float r, float g, float b, float a){
	float col[4] = { r, g, b, a };
	context->ClearRenderTargetView(view, col);
}

// ---------------------------------------------------------
//深度バッファのクリア
//context		:	コンテキスト
//view			:	深度ビュー
//clear_flag		:	クリアフラグ
//depth			:	初期化する深度値
//stencil		:	初期化するステンシル値
void GALib::D3D11::ClearDepthStencilView(ID3D11DeviceContext* context, ID3D11DepthStencilView* view, UINT clear_flag, float depth, UINT8 stencil){
	context->ClearDepthStencilView(view, clear_flag, depth, stencil);

}

// ---------------------------------------------------------
//サブリソース更新
// ---------------------------------------------------------
void GALib::D3D11::UpdateConstantBuffer(ID3D11DeviceContext* context, ID3D11Resource* resource, void* src_data){
	context->UpdateSubresource(resource, 0, nullptr, src_data, 0, 0);

}

// ---------------------------------------------------------
//インデックスバッファの設定
// ---------------------------------------------------------
void GALib::D3D11::IASetIndexBuffer(ID3D11DeviceContext* context, ID3D11Buffer* buffer){
	context->IASetIndexBuffer(buffer, DXGI_FORMAT_R16_UINT, 0);
}

