#include "GALib.h"

/**

*	@brief	�������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::GALib_Initialize(){
	D3D11::Initialize();
	Draw::GraphicsAPIInitialize();
}

/**

*	@brief	�I�������֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::GALib_Finalize(){
	Draw::GraphicsAPIFinalize();
	D3D11::Finalize();
}