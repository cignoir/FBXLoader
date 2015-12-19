#include "SamplerManager.h"
#include "../D3D11/D3DUser.h"


using namespace GALib::Draw;

/**

*	@brief	�T���v���n���h���̎����N���X

*/
class C_SamplerHandle final : public SamplerManager::IC_SamplerHandle{
public:

	/**
	
	*	@brief	�T���v���ւ̃|�C���^�̎擾

	*	@param	�Ȃ�

	*	@return	�|�C���^
	
	*/
	void* GetSampler()const override { return this->m_p_sampler.Get(); }

	/**
	
	*	@brief	�T���v���̃A�h���X�̃|�C���^���擾

	*	@param	�Ȃ�

	*	@return	ID3D11SamplerState**;
	
	*/
	ID3D11SamplerState** GetAddressOf(){ return &this->m_p_sampler; }
private:
	ComPtr<ID3D11SamplerState>	m_p_sampler;
};

/**

*	@brief	�T���v���̍쐬

*	@param[in]	filter	�t�B���^�[�^�C�v
*	@param[in]	clamp	�N�����v�^�C�v

*	@return	�T���v���[�n���h��

*/
SAMPLERHANDLE SamplerManager::CreateSampler(int filter, int clamp){
	auto ptr = Utility::MakeShared<C_SamplerHandle>();

	D3D11::CreateSampleState(ptr->GetAddressOf(), static_cast<D3D11_FILTER>(filter), static_cast<D3D11_TEXTURE_ADDRESS_MODE>(clamp));

	return ptr;
}