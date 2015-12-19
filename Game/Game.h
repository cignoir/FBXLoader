#pragma once
#include "../GALib/GALib.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	ゲーム関連の名前空間
				関数名を消さない、いじらない

	*/
	namespace Game{
		void Initialize();
		bool Update();
		void Finalize();
	}
}