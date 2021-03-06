#include "GALib.h"

/**

*	@brief	初期化関数

*	@param	なし

*	@return	なし

*/
void GALib::GALib_Initialize(){
	D3D11::Initialize();
	Draw::GraphicsAPIInitialize();
}

/**

*	@brief	終了処理関数

*	@param	なし

*	@return	なし

*/
void GALib::GALib_Finalize(){
	Draw::GraphicsAPIFinalize();
	D3D11::Finalize();
}