#pragma once
#include "WindowBase.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	Win32api関連の名前空間
	
	*/
	namespace Win32api{
		/**
		
		*	@brief	テキストラベルクラス
		
		*/
		class C_GUITextLabel : public C_WindowHandler{
		public:
			/**
			
			*	@brief	コンストラクタ

			*	@param[in]	parent_hwnd	親ウィンドウハンドル
			*	@param[in]	name		クラス名
			*	@param[in]	id			指定id
			*	@param[in]	x			x位置
			*	@param[in]	y			y位置
			*	@param[in]	width		横幅
			*	@param[in]	height		縦幅
			*	@param[in]	pos			センタリング(SS_LEFTなど
			
			*/
			C_GUITextLabel(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height, int pos){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"STATIC", name, WS_CHILD | WS_VISIBLE | pos,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}

			/**
			
			*	@brief	描画テキストの設定

			*	@param[in]	text	テキスト

			*	@return	なし
			
			*/
			void SetText(const wchar_t* text){
				SetWindowText(this->m_window_handle, text);
			}

			/**
			
			*	@brief	描画フォントの設定

			*	@param[in]	font	フォントハンドル

			*	@return	なし
			
			*/
			void SetFont(HFONT font){
				SendMessageA(this->m_window_handle, WM_SETFONT, (WPARAM)font, 0);
			}
		private:
		};
	}
}