#include "MainWindow.h"
#include "../Game/Game.h"
using namespace GALib::Game;

/**

*	@brief	�E�B���h�E������

*/
void C_MainWindow::DoInit(){
	Game::Initialize();

}

/**

*	@brief	�E�B���h�E�X�V

*/
void C_MainWindow::DoUpdate(){
	
	GALib::D3D11::Clear();
	if (!Game::Update()){
		this->Destroy();
	}

	GALib::D3D11::Swap(1);
}

/**

*	@brief	�E�B���h�E�I��

*/
void C_MainWindow::DoRelease(){
	Game::Finalize();
}
