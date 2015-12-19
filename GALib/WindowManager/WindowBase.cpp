#include "WindowBase.h"

/**

*	@brief	ウィンドウプロシージャラッパ
			生成されたウィンドウのプロシージャを回す

*	@param[in]	hwnd	ウィンドウハンドル
*	@param[in]	Msg		

*	@return	リザルト

*/
GALib::Win32api::C_WindowBase* GALib::Win32api::C_WindowBase::m_s_p_window = nullptr;
LRESULT CALLBACK GALib::Win32api::MainWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){
	auto window = (C_WindowBase*)GetWindowLong(hWnd, GWL_USERDATA);
	if (!window) return DefWindowProc(hWnd, Msg, wParam, lParam);
	return window->WndProc(hWnd, Msg, wParam, lParam);
}
/**

*	@brief	クライアント領域の指定

*	@param[in]	hwnd	ウィンドウハンドル
*	@param[in]	width	横幅
*	@param[in]	height	縦幅

*	@return true	成功
*	@return false	失敗

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

*	@brief	ウィンドウ生成

*	@param[in]	window_class	ウィンドウクラス名
*	@param[in]	window_title	ウィンドウタイトル
*	@param[in]	width			クライアント領域横幅
*	@param[in]	height			クライアント領域縦幅
*	@param[in]	icon_id			アイコンid

*	@return true	成功
*	@return false	失敗

*/
bool GALib::Win32api::C_WindowBase::MakeWindow(const wchar_t* window_class,const wchar_t* window_title, int width, int height, int icon_id){
	this->m_width = width;
	this->m_window_class = window_class;
	this->m_height = height;
	
	WNDCLASSEX wc;

	// ウィンドウクラスの情報を設定
	wc.cbSize = sizeof(wc);               // 構造体サイズ
	wc.style = CS_HREDRAW | CS_VREDRAW;   // スタイル
	wc.lpfnWndProc = MainWindowProc;       // ウィンドウプロシージャ
	wc.cbClsExtra = 0;                    // 拡張情報１
	wc.cbWndExtra = 0;                    // 拡張情報２
	wc.hInstance = GetModuleHandle(NULL);                 // インスタンスハンドル
	wc.hIcon = LoadIcon(this->GetInstance(), MAKEINTRESOURCE(icon_id));
	wc.hIconSm = wc.hIcon;                // 子アイコン
	wc.hCursor = (HCURSOR)LoadImage(      // マウスカーソル
		NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
		0, 0, LR_DEFAULTSIZE | LR_SHARED
		);
	wc.hbrBackground = (HBRUSH)COLOR_BTNSHADOW; // ウィンドウ背景
	wc.lpszMenuName = NULL;                     // メニュー名
	wc.lpszClassName = window_class;// ウィンドウクラス名

	// ウィンドウクラスを登録する
	if (RegisterClassEx(&wc) == 0){ return false; }

	// ---------------------------------------------------------
	//クライアント領域のサイズを指定する
	RECT rc = { 0, 0, this->m_width, this->m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//モニタの幅と高さを取得し、描画座標を出す
	int posx = GetSystemMetrics(SM_CXSCREEN) / 2 - this->m_width / 2;
	int posy = GetSystemMetrics(SM_CYSCREEN) / 2 - this->m_height / 2;

	// ウィンドウを作成する
	this->m_window_handle = CreateWindow(
		window_class,     // ウィンドウクラス名
		window_title,  // タイトルバーに表示する文字列
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,   // ウィンドウの種類
		posx,         // ウィンドウを表示する位置（X座標）
		posy,         // ウィンドウを表示する位置（Y座標）
		rc.right,         // ウィンドウの幅
		rc.bottom,         // ウィンドウの高さ
		NULL,                  // 親ウィンドウのウィンドウハンドル
		NULL,                  // メニューハンドル
		GetModuleHandle(NULL),                 // インスタンスハンドル
		NULL                   // その他の作成データ
		);

	auto error = GetLastError();
	if (m_window_handle == NULL){ return false; }
	SetWindowLong(this->m_window_handle, GWL_USERDATA, (LONG)this);

	SetClientSize(this->m_window_handle, this->m_width, this->m_height);

	ShowWindow(this->m_window_handle, SW_SHOW);
	UpdateWindow(this->m_window_handle);

	return true;
}