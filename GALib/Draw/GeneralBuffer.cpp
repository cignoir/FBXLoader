#include "GeneralBuffer.h"
#include "../D3D11/D3DUser.h"
#include "../D3D11/D3D11Manager.h"

/**

*	@brief	コンストラクタ

*	@param	なし

*/
GALib::D3D11::GeneralBuffer::GeneralBuffer() : 
m_p_context(GALib::D3D11::GetImmediateContext())
{
}


/**

*	@brief	初期化、バッファを生成する

*	@param[in]	buffer_size				バッファサイズ
*	@param[in]	usage					バッファへのCPU/GPUアクセス指定
*	@param[in]	bind_flags				バッファのバインド指定
*	@param[in]	cpu_access_flags			CPUアクセス指定
*	@param[in]	initial_data				初期化データ
*	@param[in]	structure_byte_stride		構造化バッファーのストライド

*	@return	成功可否
*	@retval	true	成功
*	@retval	false	失敗

*/
bool GALib::D3D11::GeneralBuffer::Initialize(std::size_t buffer_size, D3D11_USAGE usage, UINT bind_flags, UINT cpu_access_flags, void* initial_data, UINT structure_byte_stride){
	this->m_buffer_size = buffer_size;
	return D3D11::CreateBuffer(this->m_p_buffer.GetAddressOf(), buffer_size, usage, bind_flags, cpu_access_flags, 0, structure_byte_stride, initial_data);

}

/**
*	@brief	バッファをサイズ分書き込む
			書き込み後は書き込みサイズを記録し、次回はそのオフセットから再開する
			終端まで達すると一度DISCARDして最初から書き込みを開始する
			返り値は描画開始オフセット、ストライド値で割ると描画開始頂点が求められる

*	@param[in]	srv		書き込みデータへのポインタ
*	@param[in]	size	書き込みサイズ

*	@return	書き込み開始オフセット

*/
std::size_t GALib::D3D11::GeneralBuffer::WriteBuffer(void* src, std::size_t size){
	void* buf = this->BufferLock(size);

	memcpy_s(buf, size, src, size);
	this->m_p_context->Unmap(this->m_p_buffer.Get(), D3D11CalcSubresource(0, 0, 1));

	return this->m_draw_start;
}

/**

*	@brief	強制的にバッファをDISCARDする

*	@param	なし

*	@return	なし

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

*	@brief	バッファをロックする

*	@param[in]	

*/
void* GALib::D3D11::GeneralBuffer::BufferLock(std::size_t write_size){

	D3D11_MAPPED_SUBRESOURCE resource;
	D3D11_MAP type = D3D11_MAP_WRITE_NO_OVERWRITE;

	//バッファサイズを超えたら0に戻る
	if (write_size + this->m_write_offset > this->m_buffer_size){
		this->m_write_offset = 0;
		type = D3D11_MAP_WRITE_DISCARD;

	}

	//オフセット加算
	this->m_draw_start = this->m_write_offset;
	this->m_write_offset += write_size;

	this->m_p_context->Map(this->m_p_buffer.Get(), D3D11CalcSubresource(0, 0, 1), type, 0, &resource);

	return ((static_cast<BYTE*>(resource.pData)) + m_draw_start);
}

/**

*	@brief	GPUコマンドによるバッファ更新

*	@param[in]	src	更新データ

*	@return	なし

*/
void GALib::D3D11::GeneralBuffer::UpdateBuffer(void* src){
	D3D11::UpdateConstantBuffer(this->m_p_context, this->m_p_buffer.Get(), src);
}