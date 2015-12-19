#pragma once
#include "../NullPointer/NullPointer.h"

/**

*	@brief	�L���X�g�ptemplate�֐��̓W�J

*	@param[in]	FuncName	�֐���
*	@param[in]	ClassName	RTTI�̊��N���X��

*	@return	�L���X�g���\�ł���΃|�C���^���L���X�g�����
			�s�\�Ȃ�null���Ԃ�

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

*	@brief	RTTI��L��������N���X�̃����o��W�J����

*	@param[in]	__VA_ARGS__	���g���p�����Ă�����N���X��
				template�N���X�̏ꍇ��T<A0,A1>�̂悤�ɓn��

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

*	@brief	static�����o�ɃN���X����W�J����
			cpp���œW�J���邱��

*	@param[in]	Type	GA_LIB_RTTI_MEMBER_IMPL��W�J�����N���X��

*/
#define GA_LIB_RTTI_CLASS_NAME_MEMBER_IMPL(Type)\
	const char* const Type::CLASS_NAME = #Type;

/**

*	@brief	template class��static�����o�ɃN���X����W�J����
			cpp���œW�J���邱��

*	@param[in]	__VA_ARGS__	GA_LIB_RTTI_MEMBER_IMPL��W�J����template�N���X��
				��F T<int,int>
						

*/
#define GA_LIB_RTTI_TEMPLATE_CLASS_NAME_MEMBER_IMPL(...)\
	template<>\
	const char* const __VA_ARGS__::CLASS_NAME = #__VA_ARGS__;

/**

*	@brief	RTTI���T�|�[�g����Ŋ��N���X��W�J����
			RTTI��L��������N���X�͑S�Ă��̃N���X����h�����Ȃ���΂����Ȃ�
			�S�̃N���X�ɑ΂���
			GA_LIB_RTTI_MEMBER_IMPL��
			GA_LIB_RTTI_CLASS_NAME_MEMBER_IMPL��
			GA_LIB_RTTI_TEMPLATE_CLASS_NAME_MEMBER_IMPL��
			�W�J���Ȃ���΂����Ȃ�

*	@param[in]	ClassName	�N���X��

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

*	@brief	GALib�̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	�Ǝ�RTTI�֘A�̖��O���
	
	*/
	namespace RTTI{
		GA_LIB_RTTI_BASE_CLASS_IMPL(C_RTTI);
		GA_LIB_RTTI_CAST_IMPL(RTTICast, C_RTTI);
	}
}

