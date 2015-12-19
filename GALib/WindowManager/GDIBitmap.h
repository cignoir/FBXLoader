#pragma once
#include "WindowBase.h"

namespace GALib{
	namespace Win32api{
		/**
		
		*	@brief	リソースに組み込まれたbmpを読み込むクラス
		
		*/
		class CGDIBitmap : public C_WindowHandler{
		public:
			/**
			
			*	@brief	コンストラクタ

			*	@param[in]	bitmap_id	指定されたbmpID
			
			*/
			CGDIBitmap(int bitmap_id){
				this->m_bitmap = LoadBitmap(this->GetInstance(), MAKEINTRESOURCE(bitmap_id));
			}
			/**
			
			*	@brief	デストラクタ

			*	@param	なし
			
			*/
			~CGDIBitmap(){
				DeleteObject(this->m_bitmap);
			}

			/**
			
			*	@brief	読み込んだbmpを描画する
						この関数はWM_PAINTでしか呼び出せない
			*	@param[in]	hWnd 描画先ウィンドウハンドル
			*	@param[in]	x,y  描画先左上座標
			*	@param[in]	w,h  描画先幅と高さ
			*	@param[in]	cx,cy bitmapの左上座標
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
			
			*	@brief	bmpハンドルを取得する

			*	@param	なし

			*	@return	bmpハンドル
			
			*/
			HBITMAP GetBitmap(){ return this->m_bitmap; }
		private:
			HBITMAP m_bitmap = NULL;
		};
	}
}