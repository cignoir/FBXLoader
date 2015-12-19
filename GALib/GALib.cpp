#include "GALib.h"

/**

*	@brief	‰Šú‰»ŠÖ”

*	@param	‚È‚µ

*	@return	‚È‚µ

*/
void GALib::GALib_Initialize(){
	D3D11::Initialize();
	Draw::GraphicsAPIInitialize();
}

/**

*	@brief	I—¹ˆ—ŠÖ”

*	@param	‚È‚µ

*	@return	‚È‚µ

*/
void GALib::GALib_Finalize(){
	Draw::GraphicsAPIFinalize();
	D3D11::Finalize();
}