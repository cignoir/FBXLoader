#pragma once
#include "WindowBase.h"

namespace GALib{
	namespace Win32api{
		/**
		
		*	@brief	���\�[�X�ɑg�ݍ��܂ꂽbmp��ǂݍ��ރN���X
		
		*/
		class CGDIBitmap : public C_WindowHandler{
		public:
			/**
			
			*	@brief	�R���X�g���N�^

			*	@param[in]	bitmap_id	�w�肳�ꂽbmpID
			
			*/
			CGDIBitmap(int bitmap_id){
				this->m_bitmap = LoadBitmap(this->GetInstance(), MAKEINTRESOURCE(bitmap_id));
			}
			/**
			
			*	@brief	�f�X�g���N�^

			*	@param	�Ȃ�
			
			*/
			~CGDIBitmap(){
				DeleteObject(this->m_bitmap);
			}

			/**
			
			*	@brief	�ǂݍ���bmp��`�悷��
						���̊֐���WM_PAINT�ł����Ăяo���Ȃ�
			*	@param[in]	hWnd �`���E�B���h�E�n���h��
			*	@param[in]	x,y  �`��捶����W
			*	@param[in]	w,h  �`��敝�ƍ���
			*	@param[in]	cx,cy bitmap�̍�����W
			*/
			void DrawBitmap(HWND hWnd, int x, int y, int width, int height, int cx, int cy){
				PAINTSTRUCT ps;
				auto hdc = BeginPaint(hWnd, &ps);
				auto hBuffer = CreateCompatibleDC(hdc);
				SelectObject(hBuffer, this->m_bitmap);

				BitBlt(hdc, x, y, width, height, hBuffer, cx, cy, SRCCOPY);

				DeleteDC(hBuffer);
				EndPaint(hWnd, &ps);
			}

			/**
			
			*	@brief	bmp�n���h�����擾����

			*	@param	�Ȃ�

			*	@return	bmp�n���h��
			
			*/
			HBITMAP GetBitmap(){ return this->m_bitmap; }
		private:
			HBITMAP m_bitmap = NULL;
		};
	}
}