#include "GeneralBuffer.h"
#include "../D3D11/D3DUser.h"
#include "../D3D11/D3D11Manager.h"

/**

*	@brief	�R���X�g���N�^

*	@param	�Ȃ�

*/
GALib::D3D11::GeneralBuffer::GeneralBuffer() : 
m_p_context(GALib::D3D11::GetImmediateContext())
{
}


/**

*	@brief	�������A�o�b�t�@�𐶐�����

*	@param[in]	buffer_size				�o�b�t�@�T�C�Y
*	@param[in]	usage					�o�b�t�@�ւ�CPU/GPU�A�N�Z�X�w��
*	@param[in]	bind_flags				�o�b�t�@�̃o�C���h�w��
*	@param[in]	cpu_access_flags			CPU�A�N�Z�X�w��
*	@param[in]	initial_data				�������f�[�^
*	@param[in]	structure_byte_stride		�\�����o�b�t�@�[�̃X�g���C�h

*	@return	������
*	@retval	true	����
*	@retval	false	���s

*/
bool GALib::D3D11::GeneralBuffer::Initialize(std::size_t buffer_size, D3D11_USAGE usage, UINT bind_flags, UINT cpu_access_flags, void* initial_data, UINT structure_byte_stride){
	this->m_buffer_size = buffer_size;
	return D3D11::CreateBuffer(this->m_p_buffer.GetAddressOf(), buffer_size, usage, bind_flags, cpu_access_flags, 0, structure_byte_stride, initial_data);

}

/**
*	@brief	�o�b�t�@���T�C�Y����������
			�������݌�͏������݃T�C�Y���L�^���A����͂��̃I�t�Z�b�g����ĊJ����
			�I�[�܂ŒB����ƈ�xDISCARD���čŏ����珑�����݂��J�n����
			�Ԃ�l�͕`��J�n�I�t�Z�b�g�A�X�g���C�h�l�Ŋ���ƕ`��J�n���_�����߂���

*	@param[in]	srv		�������݃f�[�^�ւ̃|�C���^
*	@param[in]	size	�������݃T�C�Y

*	@return	�������݊J�n�I�t�Z�b�g

*/
std::size_t GALib::D3D11::GeneralBuffer::WriteBuffer(void* src, std::size_t size){
	void* buf = this->BufferLock(size);

	memcpy_s(buf, size, src, size);
	this->m_p_context->Unmap(this->m_p_buffer.Get(), D3D11CalcSubresource(0, 0, 1));

	return this->m_draw_start;
}

/**

*	@brief	�����I�Ƀo�b�t�@��DISCARD����

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::D3D11::GeneralBuffer::BufferDiscard(){
	D3D11_MAPPED_SUBRESOURCE resource;
	D3D11_MAP type = D3D11_MAP_WRITE_DISCARD;
	this->m_write_offset = 0;
	this->m_draw_start = 0;

	this->m_p_context->Map(this->m_p_buffer.Get(), D3D11CalcSubresource(0, 0, 1), type, 0, &resource);
	this->m_p_context->Unmap(this->m_p_buffer.Get(), D3D11CalcSubresource(0, 0, 1));
}

/**

*	@brief	�o�b�t�@�����b�N����

*	@param[in]	

*/
void* GALib::D3D11::GeneralBuffer::BufferLock(std::size_t write_size){

	D3D11_MAPPED_SUBRESOURCE resource;
	D3D11_MAP type = D3D11_MAP_WRITE_NO_OVERWRITE;

	//�o�b�t�@�T�C�Y�𒴂�����0�ɖ߂�
	if (write_size + this->m_write_offset > this->m_buffer_size){
		this->m_write_offset = 0;
		type = D3D11_MAP_WRITE_DISCARD;

	}

	//�I�t�Z�b�g���Z
	this->m_draw_start = this->m_write_offset;
	this->m_write_offset += write_size;

	this->m_p_context->Map(this->m_p_buffer.Get(), D3D11CalcSubresource(0, 0, 1), type, 0, &resource);

	return ((static_cast<BYTE*>(resource.pData)) + m_draw_start);
}

/**

*	@brief	GPU�R�}���h�ɂ��o�b�t�@�X�V

*	@param[in]	src	�X�V�f�[�^

*	@return	�Ȃ�

*/
void GALib::D3D11::GeneralBuffer::UpdateBuffer(void* src){
	D3D11::UpdateConstantBuffer(this->m_p_context, this->m_p_buffer.Get(), src);
}