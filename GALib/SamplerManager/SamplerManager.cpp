#include "SamplerManager.h"
#include "../D3D11/D3DUser.h"


using namespace GALib::Draw;

/**

*	@brief	サンプラハンドルの実装クラス

*/
class C_SamplerHandle final : public SamplerManager::IC_SamplerHandle{
public:

	/**
	
	*	@brief	サンプラへのポインタの取得

	*	@param	なし

	*	@return	ポインタ
	
	*/
	void* GetSampler()const override { return this->m_p_sampler.Get(); }

	/**
	
	*	@brief	サンプラのアドレスのポインタを取得

	*	@param	なし

	*	@return	ID3D11SamplerState**;
	
	*/
	ID3D11SamplerState** GetAddressOf(){ return &this->m_p_sampler; }
private:
	ComPtr<ID3D11SamplerState>	m_p_sampler;
};

/**

*	@brief	サンプラの作成

*	@param[in]	filter	フィルタータイプ
*	@param[in]	clamp	クランプタイプ

*	@return	サンプラーハンドル

*/
SAMPLERHANDLE SamplerManager::CreateSampler(int filter, int clamp){
	auto ptr = Utility::MakeShared<C_SamplerHandle>();

	D3D11::CreateSampleState(ptr->GetAddressOf(), static_cast<D3D11_FILTER>(filter), static_cast<D3D11_TEXTURE_ADDRESS_MODE>(clamp));

	return ptr;
}