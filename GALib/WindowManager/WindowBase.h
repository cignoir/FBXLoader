#pragma once
#include <Windows.h>

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	Win32api関連の名前空間
	
	*/
	namespace Win32api{
		/**
		
		*	@brief	ウィンドウハンドル保持クラウｓ
		
		*/
		class C_WindowHandler{
		public:

			HWND GetParentHandle(){ return this->m_parent_handle; }
			HWND GetWindowHandle(){ return this->m_window_handle; }
			HINSTANCE GetInstance(){ return GetModuleHandle(NULL); }

		protected:
			HWND m_parent_handle = NULL;
			HWND m_window_handle = NULL;
		};

		/**
		
		*	@brief	ウィンドウ生成、ループ基底クラウｓ
		
		*/
		class C_WindowBase : public C_WindowHandler{
		public:
			C_WindowBase(){ m_s_p_window = this; }
			~C_WindowBase(){ UnregisterClass(this->m_window_class, this->GetInstance()); }

			bool MakeWindow(const wchar_t* window_class,const wchar_t* window_title, int width, int height, int icon_id);
			void Initialize(){ this->DoInit(); }
			void Release(){this->DoRelease();}

			//ウィンドウを破棄しループから抜ける
			void Destroy(){
				this->WindowLoopEnd();
				DestroyWindow(this->GetWindowHandle());
			}

			//ウィンドウプロシージャラッパ
			virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = 0;

			//ウィンドウループ
			int Update(){
				while (this->GetWindowLoopFlag()){
					if (PeekMessage(&m_window_massage, NULL, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&m_window_massage);
						DispatchMessage(&m_window_massage);
					}
					else {
						this->DoUpdate();
					}
				}

				return static_cast<int>(this->m_window_massage.wParam);
			}

			//ウィンドウメッセージを取得する
			UINT GetWindowMessage(){ return this->m_window_massage.message; }

			//ウィンドウ幅を取得する
			int GetWindowWidth(){ return this->m_width; }

			//ウィンドウ高さを取得する
			int GetWindowHeight(){ return this->m_height; }

			static C_WindowBase*	s_GetCurrentWindow(){ return m_s_p_window; }
		protected:

			virtual void DoInit() = 0;
			virtual void DoUpdate() = 0;
			virtual void DoRelease() = 0;


			void WindowLoopEnd(){ this->m_window_loop = false; }
		private:
			//生成されたウィンドウ
			static C_WindowBase* m_s_p_window;

			bool GetWindowLoopFlag(){ return this->m_window_loop; }

			const wchar_t* m_window_class = nullptr;
			MSG m_window_massage;
			int m_width = 0;
			int m_height = 0;
			bool m_window_loop = true;
		};

		// ---------------------------------------------------------
		//ウィンドウプロシージャラッパ
		// ---------------------------------------------------------
		LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		// ---------------------------------------------------------
		//クライアント領域のリサイズ
		// ---------------------------------------------------------
		bool SetClientSize(HWND hWnd, int width, int height);
	}
}