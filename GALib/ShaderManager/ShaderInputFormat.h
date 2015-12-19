#pragma once

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
			
			*	@brief	入力レイアウトフォーマット用に再定義するクラス
			
			*/
			class C_ShaderInputFormat{
			public:
				static const int FORMAT_RGBA32_FLOAT;
				static const int FORMAT_RGB32_FLOAT;
				static const int FORMAT_RG32_FLOAT;
				static const int FORMAT_R32_FLOAT;
				static const int FORMAT_RGBA32_UINT;
			};

			int GetFormatByteSize(int format);
		}
	}
}