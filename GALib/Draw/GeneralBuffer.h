#pragma once
#include "../common.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	D3D11�֘A�̖��O���
	
	*/
	namespace D3D11{

		/**
		
		*	@brief	�ėp�o�b�t�@�N���X
		
		*/
		class GeneralBuffer final{
		public:
			~GeneralBuffer(){};			///>�R���X�g���N�^
			GeneralBuffer();			///>�f�X�g���N�^

			bool Initialize(std::size_t bufferSize, D3D11_USAGE usage, UINT bindFlags, UINT cpuAccessFlags, void* initialData = nullptr, UINT structureByteStride = 0);


			void UpdateBuffer(void* src);
			std::size_t WriteBuffer(void *src, std::size_t size);
			void BufferDiscard();


			std::size_t GetWriteOffset(){ return this->m_write_offset; }
			std::size_t GetBufferSize(){ return this->m_buffer_size; }
			ID3D11Buffer*	GetBuffer(){ return this->m_p_buffer.Get(); }
		private:
			void* BufferLock(std::size_t writeSize);

			ComPtr<ID3D11Buffer> m_p_buffer;					///>�o�b�t�@
			ID3D11DeviceContext* m_p_context = nullptr;			///>�R���e�L�X�g
			std::size_t m_buffer_size = 0;						///>�o�b�t�@�̃T�C�Y
			std::size_t m_write_offset = 0;						///>�������݃I�t�Z�b�g
			std::size_t m_draw_start = 0;						///>�`��J�n�I�t�Z�b�g
		};
	}
}

