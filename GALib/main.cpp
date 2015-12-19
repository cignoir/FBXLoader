#include "MainWindow.h"
#include "../Game/Settings.h"

/**

*	@brief	エントリポイント

*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	{
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		setlocale(0, "ja");

		auto window = new GALib::Game::C_MainWindow();
		window->MakeWindow(L"main_window", s_GAME_WINDOW_TITLE, s_GAME_SCREEN_WIDTH, s_GAME_SCREEN_HEIGHT, 0);

		GALib::GALib_Initialize();
		window->Initialize();
		window->Update();
		window->Release();
		GALib::GALib_Finalize();

	}
	CoUninitialize();
	return 0;
}