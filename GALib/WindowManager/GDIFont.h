#pragma once
#include "WindowBase.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	win32api�̖��O���
	
	*/
	namespace Win32api{
		/**
		
		*	@brief	win32api�̃t�H���g�n���h�����b�p�[�N���X
		
		*/
		class C_GDIFont{
		public:
			/**
			
			*	@brief	�R���X�g���N�^

			*	@param[in]	font_name	�t�H���g��
			*	@param[in]	font_height	�t�H���g����
			*	@param[in]	font_width	�t�H���g��
			*	@param[in]	font_weight	�t�H���g�̏d���i�����j0�ŕW���A1000�ōő�

			*/
			C_GDIFont(const wchar_t* font_name, int font_height, int font_width, int font_weight){
				this->m_Font = CreateFont(
					font_height,    //�t�H���g����
					font_width,                    //������
					0,                    //�e�L�X�g�̊p�x
					0,                    //�x�[�X���C���Ƃ����Ƃ̊p�x
					font_weight,            //�t�H���g�̏d���i�����j
					FALSE,                //�C�^���b�N��
					FALSE,                //�A���_�[���C��
					FALSE,                //�ł�������
					SHIFTJIS_CHARSET,    //�����Z�b�g
					OUT_DEFAULT_PRECIS,    //�o�͐��x
					CLIP_DEFAULT_PRECIS,//�N���b�s���O���x
					PROOF_QUALITY,        //�o�͕i��
					FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
					font_name);    //���̖�
			}
			/**
			
			*	@brief	�f�X�g���N�^

			*	@param	�Ȃ�

			*/
			~C_GDIFont(){
				DeleteObject(this->m_Font);
			}

			/**
			
			*	@brief	�t�H���g�n���h�����擾����

			*	@param	�Ȃ�

			*	@return	�t�H���g�n���h��
			
			*/
			HFONT GetFont(){ return this->m_Font; }

			/**
			
			*	@brief	�f�o�C�X�R���e�L�X�g�Ɏ��g�̃t�H���g����������

			*	@param[in]	hdc	�f�o�C�X����Ă�����

			*	@return	�Ȃ�

			*/
			void StartFont(HDC hdc){
				this->m_OldFont = (HFONT)SelectObject(hdc, this->m_Font);
			}

			/**
			
			*	@brief	�f�o�C�X�R���e�L�X�g�̃t�H���g��߂�

			*	@param[in]	hdc	�f�o�C�X�R���e�L�X�g

			*	@return	�Ȃ�

			*/
			void EndFont(HDC hdc){
				SelectObject(hdc, this->m_OldFont);
			}
		private:
			HFONT m_Font = NULL;
			HFONT m_OldFont = NULL;
		};
	}
}