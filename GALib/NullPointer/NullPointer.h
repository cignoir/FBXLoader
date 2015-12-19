/* ��d�C���N���[�h�h�~ */
#pragma once


/**

 @brief  GALib
 @brief  GA���C�u�����֘A�̖��O���

*/
namespace GALib
{
    /**

     @brief  C_NullPointer
             �k���|�C���^��\���N���X

    */
    class C_NullPointer
    {
    public:
        /**

         @brief     �L���X�g���Z�q�̃I�[�o�[���[�h
                    �|�C���^�^�ɂ�������������Ȃ�
         @param     �Ȃ�
         @return    T* 0( �k�� )

        */
        template<typename T>
        operator T*() const
        {
            return 0;
        }
    private:

        // �A�h���X���Z�q���v���C�x�[�g�ɒu�����ƂŁA�A�h���X�̎擾�������Ȃ�
        void operator&() const;
    };

    typedef C_NullPointer NullType;
}


/* �}�N����` */
#define GA_NULL (GALib::NullType())