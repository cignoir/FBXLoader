#pragma once
#include "../GALib/GALib.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	�Q�[���֘A�̖��O���
				�֐����������Ȃ��A������Ȃ�

	*/
	namespace Game{
		void Initialize();
		bool Update();
		void Finalize();
	}
}