#pragma once
#include "GALib.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	�Q�[���֘A�̖��O���
	
	*/
	namespace Game{
		/**
		
		*	@brief	���C���E�B���h�E
		
		*/
		class C_MainWindow : public GALib::Win32api::C_WindowBase{
		public:

			LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){
				PAINTSTRUCT ps;
				HDC hdc;

				switch (Msg)
				{

				case WM_PAINT:
					hdc = BeginPaint(hWnd, &ps);
					EndPaint(hWnd, &ps);
					break;
				case WM_MOUSEMOVE:

					break;

				case WM_DESTROY:
					this->WindowLoopEnd();

					break;
				case WM_QUIT:
					this->Destroy();
					break;
				default:
					return DefWindowProc(hWnd, Msg, wParam, lParam);
				}
				return DefWindowProc(hWnd, Msg, wParam, lParam);
			}
		private:
			void DoInit() override;
			void DoUpdate() override;
			void DoRelease() override;
		};
	}
}