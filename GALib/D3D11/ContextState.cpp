#include "ContextState.h"
#include "D3D11Manager.h"
#include "D3DUser.h"

/**

*	@brief	コンストラクタ

*	@param	なし

*/
GALib::D3D11::C_ContextState::C_ContextState(){
	this->m_p_context = D3D11::GetImmediateContext();
}

/**

*	@brief	頂点シェーダの設定

*	@param[in]	vs	頂点シェーダ

*	@return	なし

*/
void GALib::D3D11::C_ContextState::SetVertexShader(ID3D11VertexShader* vs){
	if (this->m_p_vertex_shader == vs) return;

	this->m_p_context->VSSetShader(vs, nullptr, 0);
	this->m_p_vertex_shader = vs;
}


/**

*	@brief	ピクセルシェーダの設定

*	@param[in]	ps	ピクセルシェーダ

*	@return	なし

*/
void GALib::D3D11::C_ContextState::SetPixelShader(ID3D11PixelShader* ps){
	if (this->m_p_pixel_shader == ps) return;

	this->m_p_context->PSSetShader(ps, nullptr, 0);
	this->m_p_pixel_shader = ps;
}


/**

*	@brief	入力レイアウトの設定

*	@param[in]	il	入力レイアウト

*	@return	なし

*/
void GALib::D3D11::C_ContextState::SetInputLayout(ID3D11InputLayout* il){
	if (this->m_p_input_layout == il) return;

	this->m_p_context->IASetInputLayout(il);
	this->m_p_input_layout = il;
}

/**

*	@brief	プリミティブタイプの設定

*	@param[in]	type	プリミティブタイプ

*	@return	なし

*/
void GALib::D3D11::C_ContextState::SetPrimitiveType(UINT type){
	if (this->m_primitive_type == type) return;

	this->m_p_context->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(type));
	this->m_primitive_type = type;
}