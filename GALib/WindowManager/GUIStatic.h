#pragma once
#include "WindowBase.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	Win32api�֘A�̖��O���
	
	*/
	namespace Win32api{
		/**
		
		*	@brief	�e�L�X�g���x���N���X
		
		*/
		class C_GUITextLabel : public C_WindowHandler{
		public:
			/**
			
			*	@brief	�R���X�g���N�^

			*	@param[in]	parent_hwnd	�e�E�B���h�E�n���h��
			*	@param[in]	name		�N���X��
			*	@param[in]	id			�w��id
			*	@param[in]	x			x�ʒu
			*	@param[in]	y			y�ʒu
			*	@param[in]	width		����
			*	@param[in]	height		�c��
			*	@param[in]	pos			�Z���^�����O(SS_LEFT�Ȃ�
			
			*/
			C_GUITextLabel(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height, int pos){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"STATIC", name, WS_CHILD | WS_VISIBLE | pos,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}

			/**
			
			*	@brief	�`��e�L�X�g�̐ݒ�

			*	@param[in]	text	�e�L�X�g

			*	@return	�Ȃ�
			
			*/
			void SetText(const wchar_t* text){
				SetWindowText(this->m_window_handle, text);
			}

			/**
			
			*	@brief	�`��t�H���g�̐ݒ�

			*	@param[in]	font	�t�H���g�n���h��

			*	@return	�Ȃ�
			
			*/
			void SetFont(HFONT font){
				SendMessageA(this->m_window_handle, WM_SETFONT, (WPARAM)font, 0);
			}
		private:
		};
	}
}