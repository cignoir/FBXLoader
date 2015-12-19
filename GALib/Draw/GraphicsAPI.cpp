#include "GraphicsAPI.h"
#include "../D3D11/D3D11Manager.h"
#include "../D3D11/D3DUser.h"
#include "GeneralBuffer.h"

///>グローバル変数
static	GALib::D3D11::GeneralBuffer*	g_p_matrices_buffer = nullptr;	        //行列用バッファ
static  GALib::D3D11::GeneralBuffer*    g_p_model_matrices_buffer = nullptr;
static  GALib::D3D11::GeneralBuffer*    g_p_materials_buffer = nullptr;
static GALib::D3D11::GeneralBuffer*     g_p_light_buffer = nullptr;

///>カリング
static ID3D11RasterizerState*	g_p_cull_front = nullptr;
static ID3D11RasterizerState*	g_p_cull_none = nullptr;
static ID3D11RasterizerState*	g_p_cull_back = nullptr;

///>深度
static ID3D11DepthStencilState*	g_p_depth_write_check = nullptr;
static ID3D11DepthStencilState*	g_p_depth_no_wirte_check = nullptr;
static ID3D11DepthStencilState*	g_p_depth_write_no_check = nullptr;
static ID3D11DepthStencilState*	g_p_depth_no_write_no_check = nullptr;

//ブレンドモード
static ID3D11BlendState*	g_p_blend_normal = nullptr;
static ID3D11BlendState*	g_p_blend_add = nullptr;
static ID3D11BlendState*	g_p_blend_subtract = nullptr;
static ID3D11BlendState*	g_p_blend_multiple = nullptr;

/**

*	@brief	GraphicAPi関連の初期化関数

*	@param	なし

*	@return	なし

*/
void GALib::Draw::GraphicsAPIInitialize(){
	g_p_matrices_buffer = new GALib::D3D11::GeneralBuffer();
	g_p_matrices_buffer->Initialize(sizeof(Matrix4x4) * 3, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0);

    g_p_model_matrices_buffer = new GALib::D3D11::GeneralBuffer();
	g_p_model_matrices_buffer->Initialize(sizeof(Matrix4x4) * 4, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0);
	
    g_p_materials_buffer = new GALib::D3D11::GeneralBuffer();
	g_p_materials_buffer->Initialize(sizeof(Vector4) * 3 + sizeof(float) * 4, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0);

    g_p_light_buffer = new GALib::D3D11::GeneralBuffer();
	g_p_light_buffer->Initialize(sizeof(Vector4), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0);

	D3D11::CreateRasterizerState(&g_p_cull_none, D3D11_FILL_SOLID, D3D11_CULL_NONE);
	D3D11::CreateRasterizerState(&g_p_cull_front, D3D11_FILL_SOLID, D3D11_CULL_FRONT);
	D3D11::CreateRasterizerState(&g_p_cull_back, D3D11_FILL_SOLID, D3D11_CULL_BACK);

	D3D11::CreateDepthStencilState(&g_p_depth_write_check);
	D3D11::CreateDepthStencilState(&g_p_depth_no_wirte_check, true, D3D11_DEPTH_WRITE_MASK_ZERO);
	D3D11::CreateDepthStencilState(&g_p_depth_write_no_check, false, D3D11_DEPTH_WRITE_MASK_ALL);
	D3D11::CreateDepthStencilState(&g_p_depth_no_write_no_check, false, D3D11_DEPTH_WRITE_MASK_ZERO);

	D3D11::CreateBlendState(&g_p_blend_normal,true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD);
	D3D11::CreateBlendState(&g_p_blend_add, true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD);
	D3D11::CreateBlendState(&g_p_blend_subtract, true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE, D3D11_BLEND_OP_REV_SUBTRACT, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD);
	D3D11::CreateBlendState(&g_p_blend_multiple, true, D3D11_BLEND_ZERO, D3D11_BLEND_SRC_COLOR, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD);

	auto context = D3D11::GetImmediateContext();
	
	D3D11::RSSetState(context, g_p_cull_back);
	D3D11::OMSetDepthStencilState(context, g_p_depth_write_check);

	SetBlendMode(eBlendMode::BLEND_NORMAL);
	SetDepth(true, true);
	SetCulling(eCullingType::CULLING_FRONT);
}

/**

*	@brief	GraphicsAPI関連の終了処理関数

*	@param	なし

*	@return	なし

*/
void GALib::Draw::GraphicsAPIFinalize(){

	delete g_p_matrices_buffer;
	delete (g_p_model_matrices_buffer);
	delete(g_p_materials_buffer);
	delete(g_p_light_buffer);

	SAFE_RELEASE(g_p_cull_front);
	SAFE_RELEASE(g_p_cull_none);
	SAFE_RELEASE(g_p_cull_back);

	SAFE_RELEASE(g_p_depth_write_check);
	SAFE_RELEASE(g_p_depth_no_wirte_check);
	SAFE_RELEASE(g_p_depth_write_no_check);
	SAFE_RELEASE(g_p_depth_no_write_no_check);

	SAFE_RELEASE(g_p_blend_add);
	SAFE_RELEASE(g_p_blend_multiple);
	SAFE_RELEASE(g_p_blend_normal);
	SAFE_RELEASE(g_p_blend_subtract);
}

/**

*	@brief	サンプルロケーションの取得
			directxにはそういうのないので渡された値（レジスタ番号）をそのまま返却する
*	@param[in]	pixel_shader_handle	ピクセルシェーダのハンドル
*	@parma[in]	slot_number			レジスタ番号

*	@return	レジスタ番号

*/
UINT GALib::Draw::GetSamplerLocation(const GALib::Resource::SHADERHANDLE& pixel_shader_handle, UINT slot_number){
	return slot_number;
}

/**

*	@brief	サンプラーをコンテキストにバインドする

*	@param[in]	handle	サンプラーハンドル
*	@param[in]	location レジスタ番号

*	@return	なし

*/
void GALib::Draw::SetSampler(const GALib::Draw::SAMPLERHANDLE& handle, UINT location){
	GALib::D3D11::PSSetSampler(D3D11::GetImmediateContext(), location, static_cast<ID3D11SamplerState*>(handle->GetSampler()));
}

/**

*	@brief	テクスチャをコンテキストにバインドする

*	@param[in]	handle	テクスチャハンドル
*	@param[in]	location	レジスタ番号

*	@return	なし

*/
void GALib::Draw::SetTexture(const GALib::Resource::GHANDLE& handle, UINT location){
	GALib::D3D11::PSSetShaderResource(D3D11::GetImmediateContext(), location, static_cast<ID3D11ShaderResourceView*>(handle->GetTextureAPIPtr()));
}

/**

*	@brief	行列の更新

*	@param[in]	handle	シェーダハンドル（意味なし）
*	@param[in]	r_WORLD	ワールド行列の参照
*	@param[in]	r_VIEW	ビュー行列の参照
*	@param[in]	r_PROJECTION	プロジェクション行列の参照

*	@return	なし

*/
void GALib::Draw::SetMatricesInVertexShader(const GALib::Draw::SHADERHANDLE& handle,
	                                        const Matrix4x4& r_WORLD,
	                                        const Matrix4x4& r_VIEW,
	                                        const Matrix4x4& r_PROJECTION)
{
	Matrix4x4 mat[3] = { r_WORLD, r_VIEW, r_PROJECTION };
	g_p_matrices_buffer->UpdateBuffer((void*)mat);
	D3D11::VSSetConstantBuffers(D3D11::GetImmediateContext(), 0, g_p_matrices_buffer->GetBuffer());
}


/**

*	@brief	行列の更新

*	@param[in]	handle	     シェーダハンドル（意味なし）
*	@param[in]	r_WORLD	     ワールド行列の参照
*	@param[in]	r_VIEW	     ビュー行列の参照
*	@param[in]	r_PROJECTION プロジェクション行列の参照
*	@param[in]	r_NORMAL	 法線行列行列の参照

*	@return	なし

*/
void GALib::Draw::SetMatricesInVertexShader(const GALib::Draw::SHADERHANDLE& handle,
	                                        const Matrix4x4& r_WORLD,
	                                        const Matrix4x4& r_VIEW,
	                                        const Matrix4x4& r_PROJECTION,
	                                        const Matrix3x3& r_NORMAL)
{
    struct S_MatrixData
    {
        Matrix4x4 m_world;
        Matrix4x4 m_view;
        Matrix4x4 m_projection;
        Matrix4x4 m_normal;
    };

    S_MatrixData data;

    data.m_world      = r_WORLD;
    data.m_view       = r_VIEW;
    data.m_projection = r_PROJECTION;
    data.m_normal     = Matrix4x4::s_ConvertMatrix3x3ToMatrix4x4(r_NORMAL);

	g_p_model_matrices_buffer->UpdateBuffer((void*)&data);
	D3D11::VSSetConstantBuffers(D3D11::GetImmediateContext(), 0, g_p_model_matrices_buffer->GetBuffer());
}


/**

*	@brief	マテリアルの更新

*	@param[in]	handle	       シェーダハンドル（意味なし）
*	@param[in]	r_DIFFUSE	   拡散反射光
*	@param[in]	r_AMBIENT	   環境光
*	@param[in]	r_SPECULAR	   鏡面反射光
*	@param[in]	specular_power 鏡面反射光角度

*	@return	なし

*/
void GALib::Draw::SetMaterialsInPixelShader(const SHADERHANDLE& handle,
                                            const Vector3& r_DIFFUSE,
                                            const Vector3& r_AMBIENT,
                                            const Vector3& r_SPECULAR,
                                            float specular_power)
{
    struct S_MaterialData
    {
        Vector4 m_diffuse;
        Vector4 m_ambient;
        Vector4 m_specular;
        float m_specular_power;
        float m_dummy[3];
    };

    S_MaterialData data;

    data.m_diffuse.m_x    = r_DIFFUSE.m_x;
    data.m_diffuse.m_y    = r_DIFFUSE.m_y;
    data.m_diffuse.m_z    = r_DIFFUSE.m_z;
                         
    data.m_ambient.m_x    = r_AMBIENT.m_x;
    data.m_ambient.m_y    = r_AMBIENT.m_y;
    data.m_ambient.m_z    = r_AMBIENT.m_z;

    data.m_specular.m_x   = r_SPECULAR.m_x;
    data.m_specular.m_y   = r_SPECULAR.m_y;
    data.m_specular.m_z   = r_SPECULAR.m_z;

    data.m_specular_power = specular_power;

    g_p_materials_buffer->UpdateBuffer((void*)&data);
	D3D11::PSSetConstantBuffers(D3D11::GetImmediateContext(), 0, g_p_materials_buffer->GetBuffer());
}


/**

*	@brief	ライトの更新

*	@param[in]	handle	                 シェーダハンドル（意味なし）
*	@param[in]	r_LIGHT_POSITION_OF_VIEW カメラ座標のライト座標

*	@return	なし

*/
void GALib::Draw::SetLightInPixelShader(const SHADERHANDLE& handle,
                                        const Vector4& r_LIGHT_POSITION_OF_VIEW)
{
    struct S_LightData
    {
        Vector4 m_light_position_of_view;
    };

    S_LightData data;

    data.m_light_position_of_view = r_LIGHT_POSITION_OF_VIEW;

    g_p_light_buffer->UpdateBuffer((void*)&data);
	D3D11::PSSetConstantBuffers(D3D11::GetImmediateContext(), 1, g_p_light_buffer->GetBuffer());
}


/**

*	@brief	カリングタイプの設定

*	@param[in]	type	カリングタイプ

*	@return	なし

*/
void GALib::Draw::SetCulling(eCullingType type){
	auto context = D3D11::GetImmediateContext();
	switch (type)
	{
	case GALib::Draw::CULLING_FRONT:
		D3D11::RSSetState(context, g_p_cull_front);
		return;
	case GALib::Draw::CULLING_BACK:
		D3D11::RSSetState(context, g_p_cull_back);
		return;
	case GALib::Draw::CULLING_NONE:
		D3D11::RSSetState(context, g_p_cull_none);
		return;
	}
	D3D11::RSSetState(context, g_p_cull_back);
}

/**

*	@brief	ブレンドモードの設定

*	@param[in]	mode	ブレンドモード

*	@return	なし

*/
void GALib::Draw::SetBlendMode(eBlendMode mode){
	auto context = D3D11::GetImmediateContext();
	float blend_factor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };

	switch (mode)
	{
	case GALib::Draw::BLEND_NORMAL:
		context->OMSetBlendState(g_p_blend_normal, blend_factor, 0xffffffff);
		return;
	case GALib::Draw::BLEND_ADD:
		context->OMSetBlendState(g_p_blend_add, blend_factor, 0xffffffff);
		return;
	case GALib::Draw::BLEND_SUBTRACT:
		context->OMSetBlendState(g_p_blend_subtract, blend_factor, 0xffffffff);
		return;
	case GALib::Draw::BLEND_MULTIPLE:
		context->OMSetBlendState(g_p_blend_multiple, blend_factor, 0xffffffff);
		return;
	}

	context->OMSetBlendState(g_p_blend_normal, blend_factor, 0xffffffff);
}

/**

*	@brief	深度テストの設定

*	@param[in]	check	深度チェックの可否
*	@param[in]	write	深度書き込みの可否

*	@return	なし

*/
void GALib::Draw::SetDepth(bool check, bool write){
	auto context = D3D11::GetImmediateContext();
	if (check && write){
		D3D11::OMSetDepthStencilState(context, g_p_depth_write_check);
		return;
	}
	if (check && !write){
		D3D11::OMSetDepthStencilState(context, g_p_depth_no_wirte_check);
		return;
	}
	if (!check && write){
		D3D11::OMSetDepthStencilState(context, g_p_depth_write_no_check);
		return;
	}
	D3D11::OMSetDepthStencilState(context, g_p_depth_no_write_no_check);
}