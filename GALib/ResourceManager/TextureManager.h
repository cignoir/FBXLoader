#pragma once
#include "../Utility/GASTL.h"
#include "../Math/Vector/Vector2.h"
/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	リソース関連の名前空間
	
	*/
	namespace Resource{
		/**

		*	@brief	テクスチャ管理の名前空間

		*/
		namespace TextureManager{

			/**

			*	@brief	テクスチャハンドルのインターフェースクラス

			*/
			class IC_TextureHandle{
			public:
				virtual ~IC_TextureHandle(){}

				virtual int GetTextureWidth() const  = 0;
				virtual int GetTextureHeight()const  = 0;
				virtual Math::Vector2 GetTextureUV(int index)const = 0;
				virtual void* GetTextureAPIPtr()const = 0;
			protected:
				IC_TextureHandle(){}
			};
			using GHANDLE = Utility::C_SharedPtr < IC_TextureHandle > ;


			GHANDLE LoadGraph(const char* file_path);
			GHANDLE DerivationGraph(int tx, int ty, int tw, int th, GHANDLE& base_handle);
			void LoadDivGraph(GHANDLE& base_graph, int tx, int ty, int tw, int th, int x_num, int y_num, int div_num, GHANDLE* out);
		}

		using GHANDLE = TextureManager::GHANDLE;
	}
	
}