/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../NullPointer/NullPointer.h"

// TODO �F S_DefaultDeleter���`����w�b�_��ʓr�p�ӂ��邱��( SharedPtr.h�Ɉˑ�������͕̂ςȂ̂� )
#include "SharedPtr.h"


/**

 @brief GALib
        GA���C�u�����֘A�̖��O���

*/
namespace GALib
{
    /**

     @brief Utility
            ���p�I�ȃv���O�����֘A�̖��O���

    */
    namespace Utility
    {
        /* �ʖ� */
        typedef int Int32;
        
        
        /**

         @brief S_ArrayDeleter
                �z��Ŋm�ۂ����I�u�W�F�N�g�̃f���[�^��\���\����

        */
        template<typename T>
        struct S_ArrayDeleter
        {
            void operator()(T* p_object)
            {
                // TODO �F delete�̔z��ł��o������u�������邱��
                delete[] p_object;
            }
        };


        /**

         @brief C_UniquePtr
                �R�s�[�������Ȃ��B��̃|�C���^��\���N���X
                ��{�I�Ȏg�p���@��C++11�ȍ~�ŕW���ɒ񋟂���Ă���std::unique_ptr�Ɠ����ɂȂ��Ă���
                new[]�ŃI�u�W�F�N�g���m�ۂ��Ă���ꍇ��Deleter����L��S_ArrayDeleter�ɕύX���邱��

        */
        template<typename T, typename Deleter = S_DefaultDeleter<T> >
        class C_UniquePtr
        {
        public:
            // �R���X�g���N�^�E�f�X�g���N�^
            C_UniquePtr();
            C_UniquePtr(T* p_object);
            virtual ~C_UniquePtr();

            // �����o�֐�
            T* Get() const;
            T* Release();
            void Reset(T* p_object = GA_NULL);
            void Swap(C_UniquePtr& r_other);

            // �ÓI�����o�֐�

            // std::move�Ǝg�������قȂ�̂Œ���
            static void s_Move(C_UniquePtr& r_giver, C_UniquePtr& r_taker);

            // ���Z�q�̃I�[�o�[���[�h
            T& operator*() const;
            T* operator->() const;
            T& operator[](Int32 i) const;
            operator bool() const;
        private:
            T* m_p_object;

            // �R�s�[�R���X�g���N�^�Ƒ�����Z�q���v���C�x�[�g�ɐ錾���A�R�s�[���֎~������
            C_UniquePtr(const C_UniquePtr& r_other);
            C_UniquePtr& operator=(const C_UniquePtr& r_other);

            void SafeDelete();
        };

        /* ���� */
        #include "UniquePointerImpl.h"
    }
}
