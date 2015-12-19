#pragma once
#include "../NullPointer/NullPointer.h"

/**

*	@brief	キャスト用template関数の展開

*	@param[in]	FuncName	関数名
*	@param[in]	ClassName	RTTIの基底クラス名

*	@return	キャストが可能であればポインタがキャストされる
			不可能ならnullが返る

*/
#define GA_LIB_RTTI_CAST_IMPL(FuncName,ClassName)\
	template<class _CastType>\
	_CastType* FuncName(ClassName* ptr){\
	if (ptr->IsSame(_CastType::CLASS_NAME)){\
		return static_cast<_CastType*>(ptr);\
				}\
	return GA_NULL;\
		}

/**

*	@brief	RTTIを有効化するクラスのメンバを展開する

*	@param[in]	__VA_ARGS__	自身が継承している基底クラス名
				templateクラスの場合はT<A0,A1>のように渡す

*/
#define GA_LIB_RTTI_MEMBER_IMPL(...)\
	static const char* const CLASS_NAME;\
	virtual bool IsSame(const char* class_name){\
		if(CLASS_NAME == class_name) return true;\
		return __VA_ARGS__::IsSame(class_name);\
		}\
	virtual const char* GetThisClassName(){\
		return CLASS_NAME;\
		}

/**

*	@brief	staticメンバにクラス名を展開する
			cpp内で展開すること

*	@param[in]	Type	GA_LIB_RTTI_MEMBER_IMPLを展開したクラス名

*/
#define GA_LIB_RTTI_CLASS_NAME_MEMBER_IMPL(Type)\
	const char* const Type::CLASS_NAME = #Type;

/**

*	@brief	template classにstaticメンバにクラス名を展開する
			cpp内で展開すること

*	@param[in]	__VA_ARGS__	GA_LIB_RTTI_MEMBER_IMPLを展開したtemplateクラス名
				例： T<int,int>
						

*/
#define GA_LIB_RTTI_TEMPLATE_CLASS_NAME_MEMBER_IMPL(...)\
	template<>\
	const char* const __VA_ARGS__::CLASS_NAME = #__VA_ARGS__;

/**

*	@brief	RTTIをサポートする最基底クラスを展開する
			RTTIを有効化するクラスは全てこのクラスから派生しなければいけない
			全のクラスに対して
			GA_LIB_RTTI_MEMBER_IMPLと
			GA_LIB_RTTI_CLASS_NAME_MEMBER_IMPLか
			GA_LIB_RTTI_TEMPLATE_CLASS_NAME_MEMBER_IMPLを
			展開しなければいけない

*	@param[in]	ClassName	クラス名

*/
#define GA_LIB_RTTI_BASE_CLASS_IMPL(ClassName)\
class ClassName\
{\
public:\
	ClassName(){}\
	virtual ~ClassName(){}\
	virtual bool IsSame(const char* class_name){\
		return false;\
	}\
	virtual const char* GetThisClassName(){\
		return GA_NULL;\
	}\
};

/**

*	@brief	GALibの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	独自RTTI関連の名前空間
	
	*/
	namespace RTTI{
		GA_LIB_RTTI_BASE_CLASS_IMPL(C_RTTI);
		GA_LIB_RTTI_CAST_IMPL(RTTICast, C_RTTI);
	}
}

