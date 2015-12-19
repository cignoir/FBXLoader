#pragma once
#include "../Utility/GASTL.h"
#include "ShaderInputFormat.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	���\�[�X�֘A�̖��O���
	
	*/
	namespace Resource{
		/**

		*	@brief	�V�F�[�_�Ǘ��̖��O���

		*/
		namespace ShaderManager{
			/**
			
			*	@brief	�V�F�[�_�Ǘ��N���X
			
			*/
			class IC_ShaderObject{
			public:
				virtual ~IC_ShaderObject(){}
				virtual void* GetShader() const = 0;
			private:
			};

			using	SHADERHANDLE = Utility::C_SharedPtr < IC_ShaderObject > ;

			SHADERHANDLE	LoadVertexShader(const char* file_path);
			SHADERHANDLE	LoadPixelShader(const char* file_path);
			SHADERHANDLE	CreateInputLayoutHandle(SHADERHANDLE& vertex_shader);
			void AddInputLayoutElement(SHADERHANDLE& input_layout_handle, const char* semantics, std::size_t buffer_index,  int format);
			void CreateInputLayout(SHADERHANDLE& input_layout_handle);

			//windows�p
			SHADERHANDLE LoadVertexShaderFromMem(void* byte, std::size_t size);
			SHADERHANDLE LoadPixelShaderFromMem(void* byte, std::size_t size);
		}
		using SHADERHANDLE = ShaderManager::SHADERHANDLE;
	}
}