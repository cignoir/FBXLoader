#include "MainWindow.h"
#include "../Game/Game.h"
using namespace GALib::Game;

/**

*	@brief	ウィンドウ初期化

*/
void C_MainWindow::DoInit(){
	Game::Initialize();

}

/**

*	@brief	ウィンドウ更新

*/
void C_MainWindow::DoUpdate(){
	
	GALib::D3D11::Clear();
	if (!Game::Update()){
		this->Destroy();
	}

	GALib::D3D11::Swap(1);
}

/**

*	@brief	ウィンドウ終了

*/
void C_MainWindow::DoRelease(){
	Game::Finalize();
}
