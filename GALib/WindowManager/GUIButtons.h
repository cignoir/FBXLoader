#pragma once
#include "WindowBase.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	win32api関連の名前空間

	*/
	namespace Win32api{
		/**
		
		*	@brief	GUIボタン基底クラス
		
		*/
		class C_GUIButtonBase : public C_WindowHandler{
		public:
			/**
			
			*	@brief	フォントを変える

			*	@param[in]	font	フォントハンドル

			*	@return		なし
			
			*/
			void SetFont(HFONT font){ SendMessageA(this->m_window_handle, WM_SETFONT, (WPARAM)font, 0); }

			/**
			
			*	@brief	ボタンのチェック状態を変更する

			*	@param[in]	flag	チェック状態

			*	@return	なし
			
			*/
			void SetChecked(bool flag){ SendMessage(this->m_window_handle, BM_SETCHECK, flag ? BST_CHECKED : BST_UNCHECKED, 0); }

			/**
			
			*	@brief	ボタンのチェック状態を取得する

			*	@param	なし

			*	@return true	チェック
			*	@return	false	非チェック
			
			*/
			bool GetChecked(){ return SendMessage(this->m_window_handle, BM_GETCHECK, 0, 0) == BST_CHECKED; }
		};

		/**
		
		*	@brief	通常のボタンクラス
		
		*/
		class CGUIButton : public C_GUIButtonBase{
		public:
			/**
			
			*	@brief	コンストラクタ

			*	@param[in]	parent_hwnd			親ウィンドウハンドル
			*	@param[in]	name				ウィンドウクラス名
			*	@param[in]	id					指定id
			*	@param[in]	x					x位置
			*	@param[in]	y					y位置
			*	@param[in]	width				横幅
			*	@param[in]	height				縦幅
			
			*/
			CGUIButton(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}
		private:
		};


		/**
		
		*	@brief	ラジオボタンクラス、グループボックスなどにまとめて使う
		
		*/
		class C_GUIRadioButton : public C_GUIButtonBase{
		public:
			/**

			*	@brief	コンストラクタ

			*	@param[in]	parent_hwnd			親ウィンドウハンドル
			*	@param[in]	name				ウィンドウクラス名
			*	@param[in]	id					指定id
			*	@param[in]	x					x位置
			*	@param[in]	y					y位置
			*	@param[in]	width				横幅
			*	@param[in]	height				縦幅

			*/
			C_GUIRadioButton(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
					x, y, width, height, parent_hwnd, (HMENU)id, GetModuleHandle(NULL), NULL);

			}
		};

		/**
		
		*	@brief	チェックボックスクラス
		
		*/
		class C_GUICheckBox : public C_GUIButtonBase{
		public:
			/**

			*	@brief	コンストラクタ

			*	@param[in]	parent_hwnd			親ウィンドウハンドル
			*	@param[in]	name				ウィンドウクラス名
			*	@param[in]	id					指定id
			*	@param[in]	x					x位置
			*	@param[in]	y					y位置
			*	@param[in]	width				横幅
			*	@param[in]	height				縦幅

			*/
			C_GUICheckBox(HWND ParentHWND, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = ParentHWND;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					x, y, width, height, ParentHWND, (HMENU)id, this->GetInstance(), NULL);
			}
		};

		/**
		
		*	@brief	グループボックスクラス
		
		*/
		class CGUIGroupBox : public C_GUIButtonBase{
		public:
			/**

			*	@brief	コンストラクタ

			*	@param[in]	parent_hwnd			親ウィンドウハンドル
			*	@param[in]	name				ウィンドウクラス名
			*	@param[in]	id					指定id
			*	@param[in]	x					x位置
			*	@param[in]	y					y位置
			*	@param[in]	width				横幅
			*	@param[in]	height				縦幅

			*/
			CGUIGroupBox(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}
		};

		/**
		
		*	@brief	コンボボックスクラス
		
		*/
		class C_GUIComboBoxDropDownList : public C_GUIButtonBase{
		public:
			/**

			*	@brief	コンストラクタ

			*	@param[in]	parent_hwnd			親ウィンドウハンドル
			*	@param[in]	name				ウィンドウクラス名
			*	@param[in]	id					指定id
			*	@param[in]	x					x位置
			*	@param[in]	y					y位置
			*	@param[in]	width				横幅
			*	@param[in]	height				縦幅

			*/
			C_GUIComboBoxDropDownList(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"COMBOBOX", name, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}

			/**
			
			*	@brief	新たな文字列を挿入する
			
			*	@param[in]	str	文字列

			*	@return	なし
			
			*/
			void AddString(const wchar_t* str){
				SendMessage(this->m_window_handle, CB_ADDSTRING, 0, (LPARAM)str);
			}
			
			/**
			
			*	@brief	指定インデックスに文字列を挿入する

			*	@param[in]	str	文字列
			*	@param[in]	index	挿入インデックス
			
			*	@return	なし
			
			*/
			void InsertString(const wchar_t* str, int index){
				SendMessage(this->m_window_handle, CB_INSERTSTRING, (WPARAM)index, (LPARAM)str);
			}

			/**
			
			*	@brief	コンボボックスのセレクトインデックスを変更する

			*	@param[in]	index	インデックス

			*	@return	なし
			
			*/
			void SelectedIndexChanged(int index){
				SendMessage(this->m_window_handle, CB_SETCURSEL, (WPARAM)index, 0);
			}

			/**
			
			*	@brief	選択中のインデックスを返す

			*	@param	なし

			*	@return	選択中のインデックス
			
			*/
			int GetSelectedIndex(){
				return SendMessage(this->m_window_handle, CB_GETCURSEL, 0, 0);
			}

			/**
			
			*	@brief	コンボボックスに登録された要素の数を返す

			*	@param	なし

			*	@return	要素数
			
			*/
			int GetListCount(){
				return SendMessage(this->m_window_handle, CB_GETCOUNT, 0, 0);
			}
		private:
		};
	}
}