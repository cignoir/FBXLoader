#include "D3D11Manager.h"
#include "../WindowManager/WindowBase.h"
#include "D3DUser.h"
#ifdef GA_LIB_SCREEN_SHOT
#include "C:\\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX11.h"
#include <ScreenGrab.h>
#endif

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	D3D11関連の名前空間
	
	*/
	namespace D3D11{
		/**
		
		*	@brief	D3D11関連のホルダークラス
		
		*/
		class C_D3D11{
		public:
			/**
			
			*	@brief	コンストラクタ

			*	@param	なし
			
			*/
			C_D3D11(){};

			/**
			
			*	@brief	デストラクタ

			*	@param	なし
			
			*/
			~C_D3D11(){};


			/**
			
			*	@brief	D3D11の初期化

			*	@param[in]	msaa_level	MSAAのレベル、2の累乗

			*	@return true	成功
			*	@return	false	失敗
			
			*/
			bool InitializeD3D11(int msaa_level){
				if (FAILED(this->CreateDevice()))return false;
				if (FAILED(this->GetInterface()))return false;
				if (FAILED(this->GetAdapter()))return false;
				if (FAILED(this->GetParent()))return false;
				if (FAILED(this->CreateSwapChain(msaa_level)))return false;
				if (FAILED(this->CreateRenderTarget()))return false;
				if (FAILED(this->CreateDepthStencilView()))return false;

				//とりあえずイミディエイトなコンテキストに設定しておく
				D3D11::OMSetRenderTargets(D3D11::GetImmediateContext(), this->GetDepthStencilView(), this->GetRenderTargetView());
				D3D11::SetViewPort(D3D11::GetImmediateContext(), 0, 0, Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowWidth(), Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowHeight());

				return true;
			}

			/**
			
			*	@brief	デバイスの取得

			*	@param	なし

			*	@return	デバイスのポインタ
			
			*/
			ID3D11Device* GetDevice(){
				return this->m_p_device.Get();
			}

			/**
			
			*	@brief	イミディエイトコンテキストの取得

			*	@param	なし

			*	@return	イミディエイトコンテキストのポインタ
			
			*/
			ID3D11DeviceContext* GetImmediateContext(){
				return this->m_p_context.Get();
			}

			/**
			
			*	@brief	スワップチェインの取得

			*	@parma	なし

			*	@return	スワップチェインのポインタ
			
			*/
			IDXGISwapChain* GetSwapChain(){
				return this->m_p_swap_chain.Get();
			}

			/**
			
			*	@brief	スクリーンフリップ

			*	@param[in]	vsync	n番目の垂直同期で表示、0で同期しなし

			*	@return true	成功
			*	@return	false	失敗
			
			*/
			bool ScreenFlip(int vsync = 1){
				if (FAILED(this->GetSwapChain()->Present(vsync, 0))){
					return false;
				}

				return true;
			}

			/**
			
			*	@brief	レンダーターゲットの取得

			*	@param	なし

			*	@return	レンダーターゲットのポインタ

			*/
			ID3D11RenderTargetView* GetRenderTargetView(){
				return this->m_p_render_target.Get();
			}

			/**
			
			*	@brief	深度ビューの取得

			*	@param	なし

			*	@return	深度ビューのポインタ
			
			*/
			ID3D11DepthStencilView* GetDepthStencilView(){
				return this->m_p_depth_stencil_view.Get();
			}

			/**
			
			*	@brief	設定されたサンプル数の取得

			*	@param	なし

			*	@return 設定されたDXGI_SAMPLE_DESC
			
			*/
			DXGI_SAMPLE_DESC GetSampleDesc(){
				return this->m_sample_desc;
			}


		private:
			

			/**
			
			*	@brief	デバイス及びコンテキストの作成

			*	@param	なし

			*	@return	HRESULT
			*/
			HRESULT CreateDevice(){
				UINT createDeviceFlags = 0;
#ifdef _DEBUG
				createDeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG;
#else
				createDeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#endif
				HRESULT hr = S_OK;


				D3D_DRIVER_TYPE driverTypes[] =
				{
					D3D_DRIVER_TYPE_HARDWARE,
					D3D_DRIVER_TYPE_WARP,
					D3D_DRIVER_TYPE_REFERENCE,
				};
				UINT numDriverTypes = ARRAYSIZE(driverTypes);

				D3D_FEATURE_LEVEL featureLevels[] =
				{
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
				};
				UINT numFeatureLevels = ARRAYSIZE(featureLevels);

				// DirectX11のデバイスを作成
				for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
				{
					this->m_driver_type = driverTypes[driverTypeIndex];
					hr = D3D11CreateDevice(NULL, this->m_driver_type, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
						D3D11_SDK_VERSION, &this->m_p_device, &m_feature_level, &this->m_p_context);
					if (SUCCEEDED(hr))
						break;
				}

				return hr;
			}

			/**
			
			*	@brief	インターフェースの作成

			*	@param	なし

			*	@return HRESULT
			
			*/
			HRESULT GetInterface(){
				return this->GetDevice()->QueryInterface(__uuidof(this->m_p_dxgi_device), &this->m_p_dxgi_device);
			}

			/**
			
			*	@brief	アダプターの取得

			*	@param	なし

			*	@return HRESULT
			
			*/
			HRESULT GetAdapter(){
				return this->m_p_dxgi_device->GetAdapter(&this->m_p_dxgi_adapter);
			}

			/**
			
			*	@brief	ファクトリーの取得

			*	@param	なし

			*	@return	HRESULT

			*/
			HRESULT GetParent(){
				return this->m_p_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), &this->m_p_dxgi_factory);
			}

			/**
			
			*	@brief	スワップチェインの作成

			*	@param[in]	msaa	MSAAレベル

			*	@return	なし
			
			*/
			HRESULT CreateSwapChain(UINT msaa){
				//使用可能なマルチサンプルを取得
				for (UINT i = 1; i <= msaa; i++){
					UINT quality;
					if (SUCCEEDED(this->GetDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, i, &quality))){
						if (quality > 0){
							DXGI_SAMPLE_DESC desc = { i, quality - 1 };
							this->m_sample_desc = desc;
						}
					}
				}

				//スワップチェインの作成
				DXGI_SWAP_CHAIN_DESC sd;
				ZeroMemory(&sd, sizeof(sd));
				sd.BufferCount = 1;
				sd.BufferDesc.Width = Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowWidth();
				sd.BufferDesc.Height = Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowHeight();
				sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
				sd.BufferDesc.RefreshRate.Numerator = 60;
				sd.BufferDesc.RefreshRate.Denominator = 1;
				sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				sd.OutputWindow = Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowHandle();
				sd.SampleDesc = this->m_sample_desc;
				sd.Windowed = true;
				sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				HRESULT hr = this->m_p_dxgi_factory->CreateSwapChain(this->GetDevice(), &sd, &this->m_p_swap_chain);
				return hr;

			}

			/**
			
			*	@brief	レンダーターゲットの作成

			*	@param	なし

			*	@return	HRESULT
			
			*/
			HRESULT CreateRenderTarget(){
				ComPtr<ID3D11Texture2D> buffer = nullptr;
				HRESULT hr = this->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D),&buffer);

				if (FAILED(hr)){
					return hr;
				}

				return this->GetDevice()->CreateRenderTargetView(buffer.Get(), nullptr, &this->m_p_render_target);
			}

			/**
			
			*	@brief	深度ビューの作成

			*	@param	なし

			*	@return	HRSULT
			
			*/
			HRESULT CreateDepthStencilView(){
				ComPtr<ID3D11Texture2D> buffer;
				int w = Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowWidth();
				int h = Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowHeight();
				if (!D3D11::CreateTexture2D(buffer.GetAddressOf(), D3D11_BIND_DEPTH_STENCIL, w, h, DXGI_FORMAT_D24_UNORM_S8_UINT)){
					return S_FALSE;
				}

				if (!D3D11::CreateDepthStencilView(&this->m_p_depth_stencil_view, buffer.Get())){
					return S_FALSE;
				}

				return S_OK;
			}
			

			ComPtr<ID3D11Device> m_p_device;							///>デバイス
			ComPtr<ID3D11DeviceContext> m_p_context;					///>コンテキスト
			ComPtr<IDXGISwapChain> m_p_swap_chain;						///>スワップチェイン
			ComPtr<IDXGIDevice1> m_p_dxgi_device;						///>DXGIデバイス
			ComPtr<IDXGIAdapter> m_p_dxgi_adapter;						///>DXGIアダプタ
			ComPtr<IDXGIFactory> m_p_dxgi_factory;						///>DXGIファクトリ
			ComPtr<ID3D11RenderTargetView> m_p_render_target;			///>レンダーターゲット
			ComPtr<ID3D11DepthStencilView> m_p_depth_stencil_view;		///>深度ビュー

			D3D_DRIVER_TYPE m_driver_type = D3D_DRIVER_TYPE_NULL;
			D3D_FEATURE_LEVEL m_feature_level = D3D_FEATURE_LEVEL_11_0;
			DXGI_SAMPLE_DESC m_sample_desc;
		};
	}
}

///>D3D11クラス
GALib::D3D11::C_D3D11*	g_p_d3d11 = nullptr;
GALib::D3D11::C_ContextState*	g_p_context_state = nullptr;

/**

*	@brief	初期化関数

*	@param	なし

*	@return	なし

*/
void GALib::D3D11::Initialize(){
	g_p_d3d11 = new C_D3D11();
	g_p_d3d11->InitializeD3D11(1);
	g_p_context_state = new C_ContextState();
}

/**

*	@brief	終了処理関数

*	@param	なし

*	@return	なし

*/
void GALib::D3D11::Finalize(){
	delete(g_p_d3d11);
	delete(g_p_context_state);
}

/**

*	@brief	コンテキストステートのポインタを取得

*	@param	なし

*	@return	ポインタ

*/
GALib::D3D11::C_ContextState*	GALib::D3D11::GetContextState(){
	return g_p_context_state;
}


/**

*	@brief	イミディエイトコンテキストの取得

*	@param	なし

*	@return	コンテキストのポインタ

*/
ID3D11DeviceContext*	GALib::D3D11::GetImmediateContext(){
	return g_p_d3d11->GetImmediateContext();
}

/**

*	@brief	デバイスの取得

*	@param	なし

*	@return	デバイスのポインタ

*/
ID3D11Device*	GALib::D3D11::GetDevice(){
	return g_p_d3d11->GetDevice();
}

/**

*	@brief	サンプル数の取得

*	@param	なし

*	@return	サンプルデスク

*/
DXGI_SAMPLE_DESC GALib::D3D11::GetSampleDesc(){
	return g_p_d3d11->GetSampleDesc();
}

/**

*	@brief	同期処理関数

*	@param	なし

*	@return	なし

*/
void GALib::D3D11::Wait(){
	// ****************************************************** //
	//タイマー同期処理を実装する
	// ****************************************************** //
}

/**

*	@brief	スワップ処理

*	@param[in]	vsync	n番目の垂直同期に同期する,0で同期しない

*	@return	なし

*/
void GALib::D3D11::Swap(int vsync){
	g_p_d3d11->ScreenFlip(vsync);
}

/**

*	@brief	深度、レンダーターゲットのクリア処理

*	@param	なし

*	@return	なし

*/
void GALib::D3D11::Clear(){
	D3D11::ClearRenderTargetView(g_p_d3d11->GetImmediateContext(), g_p_d3d11->GetRenderTargetView(), 0, 0, 0,1);
	D3D11::ClearDepthStencilView(g_p_d3d11->GetImmediateContext(), g_p_d3d11->GetDepthStencilView());
}

void GALib::D3D11::SaveToTexture(const wchar_t* save_name){
#ifdef GA_LIB_SCREEN_SHOT
	ComPtr<ID3D11Texture2D> p_tex;
	if (FAILED(g_p_d3d11->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), &p_tex))) return;



	D3DX11SaveTextureToFile(D3D11::GetContextState()->GetDeviceContext(), p_tex.Get(), D3DX11_IFF_PNG, save_name);
#endif

}