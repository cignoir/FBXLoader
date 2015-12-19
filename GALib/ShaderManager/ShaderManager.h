#pragma once
#include "../Utility/GASTL.h"
#include "ShaderInputFormat.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	リソース関連の名前空間
	
	*/
	namespace Resource{
		/**

		*	@brief	シェーダ管理の名前空間

		*/
		namespace ShaderManager{
			/**
			
			*	@brief	シェーダ管理クラス
			
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

			//windows用
			SHADERHANDLE LoadVertexShaderFromMem(void* byte, std::size_t size);
			SHADERHANDLE LoadPixelShaderFromMem(void* byte, std::size_t size);
		}
		using SHADERHANDLE = ShaderManager::SHADERHANDLE;
	}
}