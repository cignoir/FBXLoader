#pragma once
#include "../common.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	D3D11�֘A�̖��O���
	
	*/
	namespace D3D11{
		/**
		
		*	@brief	�R���e�L�X�g�̃X�e�[�g�̕ۑ�
		
		*/
		class C_ContextState{
		public:
			C_ContextState();
			~C_ContextState(){}
			void SetVertexShader(ID3D11VertexShader* vs);
			void SetPixelShader(ID3D11PixelShader* ps);
			void SetInputLayout(ID3D11InputLayout* il);
			void SetPrimitiveType(UINT type);
			ID3D11DeviceContext*	GetDeviceContext(){ return this->m_p_context; }
		private:
			ID3D11DeviceContext*	m_p_context = nullptr;
			ID3D11VertexShader*	m_p_vertex_shader = nullptr;
			ID3D11PixelShader*	m_p_pixel_shader = nullptr;
			ID3D11InputLayout*	m_p_input_layout = nullptr;
			UINT	m_primitive_type = 0;
		};
	}
}