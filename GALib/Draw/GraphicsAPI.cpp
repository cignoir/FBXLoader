#include "GraphicsAPI.h"
#include "../D3D11/D3D11Manager.h"
#include "../D3D11/D3DUser.h"
#include "GeneralBuffer.h"

///>�O���[�o���ϐ�
static	GALib::D3D11::GeneralBuffer*	g_p_matrices_buffer = nullptr;	        //�s��p�o�b�t�@
static  GALib::D3D11::GeneralBuffer*    g_p_model_matrices_buffer = nullptr;
static  GALib::D3D11::GeneralBuffer*    g_p_materials_buffer = nullptr;
static GALib::D3D11::GeneralBuffer*     g_p_light_buffer = nullptr;

///>�J�����O
static ID3D11RasterizerState*	g_p_cull_front = nullptr;
static ID3D11RasterizerState*	g_p_cull_none = nullptr;
static ID3D11RasterizerState*	g_p_cull_back = nullptr;

///>�[�x
static ID3D11DepthStencilState*	g_p_depth_write_check = nullptr;
static ID3D11DepthStencilState*	g_p_depth_no_wirte_check = nullptr;
static ID3D11DepthStencilState*	g_p_depth_write_no_check = nullptr;
static ID3D11DepthStencilState*	g_p_depth_no_write_no_check = nullptr;

//�u�����h���[�h
static ID3D11BlendState*	g_p_blend_normal = nullptr;
static ID3D11BlendState*	g_p_blend_add = nullptr;
static ID3D11BlendState*	g_p_blend_subtract = nullptr;
static ID3D11BlendState*	g_p_blend_multiple = nullptr;

/**

*	@brief	GraphicAPi�֘A�̏������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

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

*	@brief	GraphicsAPI�֘A�̏I�������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

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

*	@brief	�T���v�����P�[�V�����̎擾
			directx�ɂ͂��������̂Ȃ��̂œn���ꂽ�l�i���W�X�^�ԍ��j�����̂܂ܕԋp����
*	@param[in]	pixel_shader_handle	�s�N�Z���V�F�[�_�̃n���h��
*	@parma[in]	slot_number			���W�X�^�ԍ�

*	@return	���W�X�^�ԍ�

*/
UINT GALib::Draw::GetSamplerLocation(const GALib::Resource::SHADERHANDLE& pixel_shader_handle, UINT slot_number){
	return slot_number;
}

/**

*	@brief	�T���v���[���R���e�L�X�g�Ƀo�C���h����

*	@param[in]	handle	�T���v���[�n���h��
*	@param[in]	location ���W�X�^�ԍ�

*	@return	�Ȃ�

*/
void GALib::Draw::SetSampler(const GALib::Draw::SAMPLERHANDLE& handle, UINT location){
	GALib::D3D11::PSSetSampler(D3D11::GetImmediateContext(), location, static_cast<ID3D11SamplerState*>(handle->GetSampler()));
}

/**

*	@brief	�e�N�X�`�����R���e�L�X�g�Ƀo�C���h����

*	@param[in]	handle	�e�N�X�`���n���h��
*	@param[in]	location	���W�X�^�ԍ�

*	@return	�Ȃ�

*/
void GALib::Draw::SetTexture(const GALib::Resource::GHANDLE& handle, UINT location){
	GALib::D3D11::PSSetShaderResource(D3D11::GetImmediateContext(), location, static_cast<ID3D11ShaderResourceView*>(handle->GetTextureAPIPtr()));
}

/**

*	@brief	�s��̍X�V

*	@param[in]	handle	�V�F�[�_�n���h���i�Ӗ��Ȃ��j
*	@param[in]	r_WORLD	���[���h�s��̎Q��
*	@param[in]	r_VIEW	�r���[�s��̎Q��
*	@param[in]	r_PROJECTION	�v���W�F�N�V�����s��̎Q��

*	@return	�Ȃ�

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

*	@brief	�s��̍X�V

*	@param[in]	handle	     �V�F�[�_�n���h���i�Ӗ��Ȃ��j
*	@param[in]	r_WORLD	     ���[���h�s��̎Q��
*	@param[in]	r_VIEW	     �r���[�s��̎Q��
*	@param[in]	r_PROJECTION �v���W�F�N�V�����s��̎Q��
*	@param[in]	r_NORMAL	 �@���s��s��̎Q��

*	@return	�Ȃ�

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

*	@brief	�}�e���A���̍X�V

*	@param[in]	handle	       �V�F�[�_�n���h���i�Ӗ��Ȃ��j
*	@param[in]	r_DIFFUSE	   �g�U���ˌ�
*	@param[in]	r_AMBIENT	   ����
*	@param[in]	r_SPECULAR	   ���ʔ��ˌ�
*	@param[in]	specular_power ���ʔ��ˌ��p�x

*	@return	�Ȃ�

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

*	@brief	���C�g�̍X�V

*	@param[in]	handle	                 �V�F�[�_�n���h���i�Ӗ��Ȃ��j
*	@param[in]	r_LIGHT_POSITION_OF_VIEW �J�������W�̃��C�g���W

*	@return	�Ȃ�

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

*	@brief	�J�����O�^�C�v�̐ݒ�

*	@param[in]	type	�J�����O�^�C�v

*	@return	�Ȃ�

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

*	@brief	�u�����h���[�h�̐ݒ�

*	@param[in]	mode	�u�����h���[�h

*	@return	�Ȃ�

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

*	@brief	�[�x�e�X�g�̐ݒ�

*	@param[in]	check	�[�x�`�F�b�N�̉�
*	@param[in]	write	�[�x�������݂̉�

*	@return	�Ȃ�

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