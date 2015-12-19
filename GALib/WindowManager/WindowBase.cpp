#include "WindowBase.h"

/**

*	@brief	�E�B���h�E�v���V�[�W�����b�p
			�������ꂽ�E�B���h�E�̃v���V�[�W������

*	@param[in]	hwnd	�E�B���h�E�n���h��
*	@param[in]	Msg		

*	@return	���U���g

*/
GALib::Win32api::C_WindowBase* GALib::Win32api::C_WindowBase::m_s_p_window = nullptr;
LRESULT CALLBACK GALib::Win32api::MainWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){
	auto window = (C_WindowBase*)GetWindowLong(hWnd, GWL_USERDATA);
	if (!window) return DefWindowProc(hWnd, Msg, wParam, lParam);
	return window->WndProc(hWnd, Msg, wParam, lParam);
}
/**

*	@brief	�N���C�A���g�̈�̎w��

*	@param[in]	hwnd	�E�B���h�E�n���h��
*	@param[in]	width	����
*	@param[in]	height	�c��

*	@return true	����
*	@return false	���s

*/
bool GALib::Win32api::SetClientSize(HWND hWnd, int width, int height){
	RECT rw, rc;
	::GetWindowRect(hWnd, &rw);
	::GetClientRect(hWnd, &rc);

	int new_width = (rw.right - rw.left) - (rc.right - rc.left) + width;
	int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + height;

	return SetWindowPos(hWnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER) != 0;
}

/**

*	@brief	�E�B���h�E����

*	@param[in]	window_class	�E�B���h�E�N���X��
*	@param[in]	window_title	�E�B���h�E�^�C�g��
*	@param[in]	width			�N���C�A���g�̈扡��
*	@param[in]	height			�N���C�A���g�̈�c��
*	@param[in]	icon_id			�A�C�R��id

*	@return true	����
*	@return false	���s

*/
bool GALib::Win32api::C_WindowBase::MakeWindow(const wchar_t* window_class,const wchar_t* window_title, int width, int height, int icon_id){
	this->m_width = width;
	this->m_window_class = window_class;
	this->m_height = height;
	
	WNDCLASSEX wc;

	// �E�B���h�E�N���X�̏���ݒ�
	wc.cbSize = sizeof(wc);               // �\���̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW;   // �X�^�C��
	wc.lpfnWndProc = MainWindowProc;       // �E�B���h�E�v���V�[�W��
	wc.cbClsExtra = 0;                    // �g�����P
	wc.cbWndExtra = 0;                    // �g�����Q
	wc.hInstance = GetModuleHandle(NULL);                 // �C���X�^���X�n���h��
	wc.hIcon = LoadIcon(this->GetInstance(), MAKEINTRESOURCE(icon_id));
	wc.hIconSm = wc.hIcon;                // �q�A�C�R��
	wc.hCursor = (HCURSOR)LoadImage(      // �}�E�X�J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
		0, 0, LR_DEFAULTSIZE | LR_SHARED
		);
	wc.hbrBackground = (HBRUSH)COLOR_BTNSHADOW; // �E�B���h�E�w�i
	wc.lpszMenuName = NULL;                     // ���j���[��
	wc.lpszClassName = window_class;// �E�B���h�E�N���X��

	// �E�B���h�E�N���X��o�^����
	if (RegisterClassEx(&wc) == 0){ return false; }

	// ---------------------------------------------------------
	//�N���C�A���g�̈�̃T�C�Y���w�肷��
	RECT rc = { 0, 0, this->m_width, this->m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//���j�^�̕��ƍ������擾���A�`����W���o��
	int posx = GetSystemMetrics(SM_CXSCREEN) / 2 - this->m_width / 2;
	int posy = GetSystemMetrics(SM_CYSCREEN) / 2 - this->m_height / 2;

	// �E�B���h�E���쐬����
	this->m_window_handle = CreateWindow(
		window_class,     // �E�B���h�E�N���X��
		window_title,  // �^�C�g���o�[�ɕ\�����镶����
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,   // �E�B���h�E�̎��
		posx,         // �E�B���h�E��\������ʒu�iX���W�j
		posy,         // �E�B���h�E��\������ʒu�iY���W�j
		rc.right,         // �E�B���h�E�̕�
		rc.bottom,         // �E�B���h�E�̍���
		NULL,                  // �e�E�B���h�E�̃E�B���h�E�n���h��
		NULL,                  // ���j���[�n���h��
		GetModuleHandle(NULL),                 // �C���X�^���X�n���h��
		NULL                   // ���̑��̍쐬�f�[�^
		);

	auto error = GetLastError();
	if (m_window_handle == NULL){ return false; }
	SetWindowLong(this->m_window_handle, GWL_USERDATA, (LONG)this);

	SetClientSize(this->m_window_handle, this->m_width, this->m_height);

	ShowWindow(this->m_window_handle, SW_SHOW);
	UpdateWindow(this->m_window_handle);

	return true;
}