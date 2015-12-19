#pragma once
#include "../common.h"
#include "../Pointer/SharedPtr.h"
#include "../Pointer/UniquePointer.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	STL周りの名前空間
	
	*/
	namespace Utility{


		template<class _Type,class... _Args>
		C_SharedPtr<_Type>	MakeShared(_Args&&... args){
			typedef std::allocator < _Type > allocator;
			static const allocator alloc;
			return Utility::AllocateShared<_Type, allocator>(alloc, std::forward<_Args>(args)...);
		}


	}
}