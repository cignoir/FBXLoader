#pragma once
#include "common.h"
#include "FileSystem\FileReader.h"
#include "WindowManager\WindowBase.h"
#include "D3D11\D3D11Manager.h"
#include "ResourceManager\TextureManager.h"
#include "ShaderManager\ShaderManager.h"
#include "SamplerManager\SamplerManager.h"
#include "Math\MathAll.h"
#include "NullPointer\NullPointer.h"
#include "Draw\GraphicsAPI.h"
#include "D3D11\D3DUser.h"
#include "Draw\GeneralBuffer.h"
/**

*	@brief	GAƒ‰ƒCƒuƒ‰ƒŠ‚Ì–¼‘O‹óŠÔ

*/
namespace GALib{
	void GALib_Initialize();
	void GALib_Finalize();
}