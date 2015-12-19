#pragma once
#include "WindowBase.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	win32api�֘A�̖��O���

	*/
	namespace Win32api{
		/**
		
		*	@brief	GUI�{�^�����N���X
		
		*/
		class C_GUIButtonBase : public C_WindowHandler{
		public:
			/**
			
			*	@brief	�t�H���g��ς���

			*	@param[in]	font	�t�H���g�n���h��

			*	@return		�Ȃ�
			
			*/
			void SetFont(HFONT font){ SendMessageA(this->m_window_handle, WM_SETFONT, (WPARAM)font, 0); }

			/**
			
			*	@brief	�{�^���̃`�F�b�N��Ԃ�ύX����

			*	@param[in]	flag	�`�F�b�N���

			*	@return	�Ȃ�
			
			*/
			void SetChecked(bool flag){ SendMessage(this->m_window_handle, BM_SETCHECK, flag ? BST_CHECKED : BST_UNCHECKED, 0); }

			/**
			
			*	@brief	�{�^���̃`�F�b�N��Ԃ��擾����

			*	@param	�Ȃ�

			*	@return true	�`�F�b�N
			*	@return	false	��`�F�b�N
			
			*/
			bool GetChecked(){ return SendMessage(this->m_window_handle, BM_GETCHECK, 0, 0) == BST_CHECKED; }
		};

		/**
		
		*	@brief	�ʏ�̃{�^���N���X
		
		*/
		class CGUIButton : public C_GUIButtonBase{
		public:
			/**
			
			*	@brief	�R���X�g���N�^

			*	@param[in]	parent_hwnd			�e�E�B���h�E�n���h��
			*	@param[in]	name				�E�B���h�E�N���X��
			*	@param[in]	id					�w��id
			*	@param[in]	x					x�ʒu
			*	@param[in]	y					y�ʒu
			*	@param[in]	width				����
			*	@param[in]	height				�c��
			
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
		
		*	@brief	���W�I�{�^���N���X�A�O���[�v�{�b�N�X�Ȃǂɂ܂Ƃ߂Ďg��
		
		*/
		class C_GUIRadioButton : public C_GUIButtonBase{
		public:
			/**

			*	@brief	�R���X�g���N�^

			*	@param[in]	parent_hwnd			�e�E�B���h�E�n���h��
			*	@param[in]	name				�E�B���h�E�N���X��
			*	@param[in]	id					�w��id
			*	@param[in]	x					x�ʒu
			*	@param[in]	y					y�ʒu
			*	@param[in]	width				����
			*	@param[in]	height				�c��

			*/
			C_GUIRadioButton(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
					x, y, width, height, parent_hwnd, (HMENU)id, GetModuleHandle(NULL), NULL);

			}
		};

		/**
		
		*	@brief	�`�F�b�N�{�b�N�X�N���X
		
		*/
		class C_GUICheckBox : public C_GUIButtonBase{
		public:
			/**

			*	@brief	�R���X�g���N�^

			*	@param[in]	parent_hwnd			�e�E�B���h�E�n���h��
			*	@param[in]	name				�E�B���h�E�N���X��
			*	@param[in]	id					�w��id
			*	@param[in]	x					x�ʒu
			*	@param[in]	y					y�ʒu
			*	@param[in]	width				����
			*	@param[in]	height				�c��

			*/
			C_GUICheckBox(HWND ParentHWND, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = ParentHWND;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					x, y, width, height, ParentHWND, (HMENU)id, this->GetInstance(), NULL);
			}
		};

		/**
		
		*	@brief	�O���[�v�{�b�N�X�N���X
		
		*/
		class CGUIGroupBox : public C_GUIButtonBase{
		public:
			/**

			*	@brief	�R���X�g���N�^

			*	@param[in]	parent_hwnd			�e�E�B���h�E�n���h��
			*	@param[in]	name				�E�B���h�E�N���X��
			*	@param[in]	id					�w��id
			*	@param[in]	x					x�ʒu
			*	@param[in]	y					y�ʒu
			*	@param[in]	width				����
			*	@param[in]	height				�c��

			*/
			CGUIGroupBox(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"BUTTON", name, WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}
		};

		/**
		
		*	@brief	�R���{�{�b�N�X�N���X
		
		*/
		class C_GUIComboBoxDropDownList : public C_GUIButtonBase{
		public:
			/**

			*	@brief	�R���X�g���N�^

			*	@param[in]	parent_hwnd			�e�E�B���h�E�n���h��
			*	@param[in]	name				�E�B���h�E�N���X��
			*	@param[in]	id					�w��id
			*	@param[in]	x					x�ʒu
			*	@param[in]	y					y�ʒu
			*	@param[in]	width				����
			*	@param[in]	height				�c��

			*/
			C_GUIComboBoxDropDownList(HWND parent_hwnd, const wchar_t* name, int id, int x, int y, int width, int height){
				this->m_parent_handle = parent_hwnd;
				this->m_window_handle = CreateWindow(
					L"COMBOBOX", name, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
					x, y, width, height, parent_hwnd, (HMENU)id, this->GetInstance(), NULL);
			}

			/**
			
			*	@brief	�V���ȕ������}������
			
			*	@param[in]	str	������

			*	@return	�Ȃ�
			
			*/
			void AddString(const wchar_t* str){
				SendMessage(this->m_window_handle, CB_ADDSTRING, 0, (LPARAM)str);
			}
			
			/**
			
			*	@brief	�w��C���f�b�N�X�ɕ������}������

			*	@param[in]	str	������
			*	@param[in]	index	�}���C���f�b�N�X
			
			*	@return	�Ȃ�
			
			*/
			void InsertString(const wchar_t* str, int index){
				SendMessage(this->m_window_handle, CB_INSERTSTRING, (WPARAM)index, (LPARAM)str);
			}

			/**
			
			*	@brief	�R���{�{�b�N�X�̃Z���N�g�C���f�b�N�X��ύX����

			*	@param[in]	index	�C���f�b�N�X

			*	@return	�Ȃ�
			
			*/
			void SelectedIndexChanged(int index){
				SendMessage(this->m_window_handle, CB_SETCURSEL, (WPARAM)index, 0);
			}

			/**
			
			*	@brief	�I�𒆂̃C���f�b�N�X��Ԃ�

			*	@param	�Ȃ�

			*	@return	�I�𒆂̃C���f�b�N�X
			
			*/
			int GetSelectedIndex(){
				return SendMessage(this->m_window_handle, CB_GETCURSEL, 0, 0);
			}

			/**
			
			*	@brief	�R���{�{�b�N�X�ɓo�^���ꂽ�v�f�̐���Ԃ�

			*	@param	�Ȃ�

			*	@return	�v�f��
			
			*/
			int GetListCount(){
				return SendMessage(this->m_window_handle, CB_GETCOUNT, 0, 0);
			}
		private:
		};
	}
}