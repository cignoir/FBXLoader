#include "ShaderInputFormat.h"
#include "../common.h"


const int GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGBA32_FLOAT = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
const int GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGB32_FLOAT = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
const int GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RG32_FLOAT = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
const int GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_R32_FLOAT = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
const int GALib::Resource::ShaderManager::C_ShaderInputFormat::FORMAT_RGBA32_UINT = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;

/**

*	@brief	入力フォーマットのバイト数の取得

*	@parma[in]	format	C_ShaderInputFormatのフォーマット

*	@return	バイト数、指定フォーマット以外は0を返す

*/
int GALib::Resource::ShaderManager::GetFormatByteSize(int format){
	switch (format)
	{
	case C_ShaderInputFormat::FORMAT_R32_FLOAT:
		return 4;
	case C_ShaderInputFormat::FORMAT_RG32_FLOAT:
		return 8;
	case C_ShaderInputFormat::FORMAT_RGB32_FLOAT:
		return 12;
	case C_ShaderInputFormat::FORMAT_RGBA32_FLOAT:
		return 16;
	case C_ShaderInputFormat::FORMAT_RGBA32_UINT:
		return 16;
	default:
		break;
	}

	return 0;
}