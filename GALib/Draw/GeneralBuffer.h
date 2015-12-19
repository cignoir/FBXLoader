#pragma once
#include "../common.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	D3D11関連の名前空間
	
	*/
	namespace D3D11{

		/**
		
		*	@brief	汎用バッファクラス
		
		*/
		class GeneralBuffer final{
		public:
			~GeneralBuffer(){};			///>コンストラクタ
			GeneralBuffer();			///>デストラクタ

			bool Initialize(std::size_t bufferSize, D3D11_USAGE usage, UINT bindFlags, UINT cpuAccessFlags, void* initialData = nullptr, UINT structureByteStride = 0);


			void UpdateBuffer(void* src);
			std::size_t WriteBuffer(void *src, std::size_t size);
			void BufferDiscard();


			std::size_t GetWriteOffset(){ return this->m_write_offset; }
			std::size_t GetBufferSize(){ return this->m_buffer_size; }
			ID3D11Buffer*	GetBuffer(){ return this->m_p_buffer.Get(); }
		private:
			void* BufferLock(std::size_t writeSize);

			ComPtr<ID3D11Buffer> m_p_buffer;					///>バッファ
			ID3D11DeviceContext* m_p_context = nullptr;			///>コンテキスト
			std::size_t m_buffer_size = 0;						///>バッファのサイズ
			std::size_t m_write_offset = 0;						///>書き込みオフセット
			std::size_t m_draw_start = 0;						///>描画開始オフセット
		};
	}
}

