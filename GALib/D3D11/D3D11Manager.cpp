#include "D3D11Manager.h"
#include "../WindowManager/WindowBase.h"
#include "D3DUser.h"
#ifdef GA_LIB_SCREEN_SHOT
#include "C:\\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX11.h"
#include <ScreenGrab.h>
#endif

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	D3D11�֘A�̖��O���
	
	*/
	namespace D3D11{
		/**
		
		*	@brief	D3D11�֘A�̃z���_�[�N���X
		
		*/
		class C_D3D11{
		public:
			/**
			
			*	@brief	�R���X�g���N�^

			*	@param	�Ȃ�
			
			*/
			C_D3D11(){};

			/**
			
			*	@brief	�f�X�g���N�^

			*	@param	�Ȃ�
			
			*/
			~C_D3D11(){};


			/**
			
			*	@brief	D3D11�̏�����

			*	@param[in]	msaa_level	MSAA�̃��x���A2�̗ݏ�

			*	@return true	����
			*	@return	false	���s
			
			*/
			bool InitializeD3D11(int msaa_level){
				if (FAILED(this->CreateDevice()))return false;
				if (FAILED(this->GetInterface()))return false;
				if (FAILED(this->GetAdapter()))return false;
				if (FAILED(this->GetParent()))return false;
				if (FAILED(this->CreateSwapChain(msaa_level)))return false;
				if (FAILED(this->CreateRenderTarget()))return false;
				if (FAILED(this->CreateDepthStencilView()))return false;

				//�Ƃ肠�����C�~�f�B�G�C�g�ȃR���e�L�X�g�ɐݒ肵�Ă���
				D3D11::OMSetRenderTargets(D3D11::GetImmediateContext(), this->GetDepthStencilView(), this->GetRenderTargetView());
				D3D11::SetViewPort(D3D11::GetImmediateContext(), 0, 0, Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowWidth(), Win32api::C_WindowBase::s_GetCurrentWindow()->GetWindowHeight());

				return true;
			}

			/**
			
			*	@brief	�f�o�C�X�̎擾

			*	@param	�Ȃ�

			*	@return	�f�o�C�X�̃|�C���^
			
			*/
			ID3D11Device* GetDevice(){
				return this->m_p_device.Get();
			}

			/**
			
			*	@brief	�C�~�f�B�G�C�g�R���e�L�X�g�̎擾

			*	@param	�Ȃ�

			*	@return	�C�~�f�B�G�C�g�R���e�L�X�g�̃|�C���^
			
			*/
			ID3D11DeviceContext* GetImmediateContext(){
				return this->m_p_context.Get();
			}

			/**
			
			*	@brief	�X���b�v�`�F�C���̎擾

			*	@parma	�Ȃ�

			*	@return	�X���b�v�`�F�C���̃|�C���^
			
			*/
			IDXGISwapChain* GetSwapChain(){
				return this->m_p_swap_chain.Get();
			}

			/**
			
			*	@brief	�X�N���[���t���b�v

			*	@param[in]	vsync	n�Ԗڂ̐��������ŕ\���A0�œ������Ȃ�

			*	@return true	����
			*	@return	false	���s
			
			*/
			bool ScreenFlip(int vsync = 1){
				if (FAILED(this->GetSwapChain()->Present(vsync, 0))){
					return false;
				}

				return true;
			}

			/**
			
			*	@brief	�����_�[�^�[�Q�b�g�̎擾

			*	@param	�Ȃ�

			*	@return	�����_�[�^�[�Q�b�g�̃|�C���^

			*/
			ID3D11RenderTargetView* GetRenderTargetView(){
				return this->m_p_render_target.Get();
			}

			/**
			
			*	@brief	�[�x�r���[�̎擾

			*	@param	�Ȃ�

			*	@return	�[�x�r���[�̃|�C���^
			
			*/
			ID3D11DepthStencilView* GetDepthStencilView(){
				return this->m_p_depth_stencil_view.Get();
			}

			/**
			
			*	@brief	�ݒ肳�ꂽ�T���v�����̎擾

			*	@param	�Ȃ�

			*	@return �ݒ肳�ꂽDXGI_SAMPLE_DESC
			
			*/
			DXGI_SAMPLE_DESC GetSampleDesc(){
				return this->m_sample_desc;
			}


		private:
			

			/**
			
			*	@brief	�f�o�C�X�y�уR���e�L�X�g�̍쐬

			*	@param	�Ȃ�

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

				// DirectX11�̃f�o�C�X���쐬
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
			
			*	@brief	�C���^�[�t�F�[�X�̍쐬

			*	@param	�Ȃ�

			*	@return HRESULT
			
			*/
			HRESULT GetInterface(){
				return this->GetDevice()->QueryInterface(__uuidof(this->m_p_dxgi_device), &this->m_p_dxgi_device);
			}

			/**
			
			*	@brief	�A�_�v�^�[�̎擾

			*	@param	�Ȃ�

			*	@return HRESULT
			
			*/
			HRESULT GetAdapter(){
				return this->m_p_dxgi_device->GetAdapter(&this->m_p_dxgi_adapter);
			}

			/**
			
			*	@brief	�t�@�N�g���[�̎擾

			*	@param	�Ȃ�

			*	@return	HRESULT

			*/
			HRESULT GetParent(){
				return this->m_p_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), &this->m_p_dxgi_factory);
			}

			/**
			
			*	@brief	�X���b�v�`�F�C���̍쐬

			*	@param[in]	msaa	MSAA���x��

			*	@return	�Ȃ�
			
			*/
			HRESULT CreateSwapChain(UINT msaa){
				//�g�p�\�ȃ}���`�T���v�����擾
				for (UINT i = 1; i <= msaa; i++){
					UINT quality;
					if (SUCCEEDED(this->GetDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, i, &quality))){
						if (quality > 0){
							DXGI_SAMPLE_DESC desc = { i, quality - 1 };
							this->m_sample_desc = desc;
						}
					}
				}

				//�X���b�v�`�F�C���̍쐬
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
			
			*	@brief	�����_�[�^�[�Q�b�g�̍쐬

			*	@param	�Ȃ�

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
			
			*	@brief	�[�x�r���[�̍쐬

			*	@param	�Ȃ�

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
			

			ComPtr<ID3D11Device> m_p_device;							///>�f�o�C�X
			ComPtr<ID3D11DeviceContext> m_p_context;					///>�R���e�L�X�g
			ComPtr<IDXGISwapChain> m_p_swap_chain;						///>�X���b�v�`�F�C��
			ComPtr<IDXGIDevice1> m_p_dxgi_device;						///>DXGI�f�o�C�X
			ComPtr<IDXGIAdapter> m_p_dxgi_adapter;						///>DXGI�A�_�v�^
			ComPtr<IDXGIFactory> m_p_dxgi_factory;						///>DXGI�t�@�N�g��
			ComPtr<ID3D11RenderTargetView> m_p_render_target;			///>�����_�[�^�[�Q�b�g
			ComPtr<ID3D11DepthStencilView> m_p_depth_stencil_view;		///>�[�x�r���[

			D3D_DRIVER_TYPE m_driver_type = D3D_DRIVER_TYPE_NULL;
			D3D_FEATURE_LEVEL m_feature_level = D3D_FEATURE_LEVEL_11_0;
			DXGI_SAMPLE_DESC m_sample_desc;
		};
	}
}

///>D3D11�N���X
GALib::D3D11::C_D3D11*	g_p_d3d11 = nullptr;
GALib::D3D11::C_ContextState*	g_p_context_state = nullptr;

/**

*	@brief	�������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::D3D11::Initialize(){
	g_p_d3d11 = new C_D3D11();
	g_p_d3d11->InitializeD3D11(1);
	g_p_context_state = new C_ContextState();
}

/**

*	@brief	�I�������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::D3D11::Finalize(){
	delete(g_p_d3d11);
	delete(g_p_context_state);
}

/**

*	@brief	�R���e�L�X�g�X�e�[�g�̃|�C���^���擾

*	@param	�Ȃ�

*	@return	�|�C���^

*/
GALib::D3D11::C_ContextState*	GALib::D3D11::GetContextState(){
	return g_p_context_state;
}


/**

*	@brief	�C�~�f�B�G�C�g�R���e�L�X�g�̎擾

*	@param	�Ȃ�

*	@return	�R���e�L�X�g�̃|�C���^

*/
ID3D11DeviceContext*	GALib::D3D11::GetImmediateContext(){
	return g_p_d3d11->GetImmediateContext();
}

/**

*	@brief	�f�o�C�X�̎擾

*	@param	�Ȃ�

*	@return	�f�o�C�X�̃|�C���^

*/
ID3D11Device*	GALib::D3D11::GetDevice(){
	return g_p_d3d11->GetDevice();
}

/**

*	@brief	�T���v�����̎擾

*	@param	�Ȃ�

*	@return	�T���v���f�X�N

*/
DXGI_SAMPLE_DESC GALib::D3D11::GetSampleDesc(){
	return g_p_d3d11->GetSampleDesc();
}

/**

*	@brief	���������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::D3D11::Wait(){
	// ****************************************************** //
	//�^�C�}�[������������������
	// ****************************************************** //
}

/**

*	@brief	�X���b�v����

*	@param[in]	vsync	n�Ԗڂ̐��������ɓ�������,0�œ������Ȃ�

*	@return	�Ȃ�

*/
void GALib::D3D11::Swap(int vsync){
	g_p_d3d11->ScreenFlip(vsync);
}

/**

*	@brief	�[�x�A�����_�[�^�[�Q�b�g�̃N���A����

*	@param	�Ȃ�

*	@return	�Ȃ�

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