#pragma once
#include "SamplerTypes.h"
#include "../Utility/GASTL.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	描画関連の名前空間
	
	*/
	namespace Draw{
		/**
		
		*	@brief	サンプラ管理の名前空間
		
		*/
		namespace SamplerManager{
			/**
			
			*	@brief	サンプラーハンドルのインターフェース
			
			*/
			class IC_SamplerHandle{
			public:
				virtual ~IC_SamplerHandle(){}
				virtual void* GetSampler() const = 0;
			protected:
				IC_SamplerHandle(){}
			};

			using SAMPLERHANDLE = Utility::C_SharedPtr < IC_SamplerHandle > ;

			
			SAMPLERHANDLE CreateSampler(int filter, int clamp);
		}
		using SAMPLERHANDLE = SamplerManager::SAMPLERHANDLE;
	}
}
