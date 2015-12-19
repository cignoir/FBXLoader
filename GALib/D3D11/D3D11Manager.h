#pragma once
#include "../common.h"
#include "ContextState.h"
/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	D3D11関連の名前空間

	*/
	namespace D3D11{
		void Initialize();
		void Finalize();

		void Wait();
		void Swap(int vsync);
		void Clear();

		C_ContextState*	GetContextState();
		ID3D11DeviceContext*	GetImmediateContext();
		ID3D11Device*			GetDevice();
		DXGI_SAMPLE_DESC	GetSampleDesc();
		void SaveToTexture(const wchar_t* save_name);
	}
}