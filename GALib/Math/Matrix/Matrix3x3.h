/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "..\Utility\UtilityMath.h"


/* 

 @brief GALib
        GA���C�u�����֘A�̖��O���

*/
namespace GALib
{
    /*

     @brief Math
            ���w�֘A�̖��O���

    */
    namespace Math
    {
        /* �O���錾 */
        template<class T>
        struct S_Vector2;

        template<class T>
        struct S_Vector3;

        template<class T>
        struct S_Matrix4x4;

        template<class T>
        struct S_Quaternion;


        /*

         @brief S_Matrix3x3
                3 * 3�̍s���\���\����

        */
        template<class T>
        struct S_Matrix3x3
        {
            /* �萔 */
            static const Uint32 m_s_ELEMENT_COUNT = 9;                                                      ///< @brief �v�f��
            static const S_Matrix3x3 m_s_ZERO;                                                              ///< @brief �[���s��
            static const S_Matrix3x3 m_s_IDENTITY;                                                          ///< @brief �P�ʍs��

            /* �����o�ϐ� */
            union
            {
                struct
                {
                    T m_elements[9];                                                                        ///< @brief 9�̗v�f�����z��
                };

                struct
                {
                    T m_elements_3x3[3][3];                                                                 ///< @brief 3 * 3�̓񎟌��z��
                };

                /// @brief �s��̊e�v�f
                struct
                {
                    T m_a_11, m_a_12, m_a_13;
                    T m_a_21, m_a_22, m_a_23;
                    T m_a_31, m_a_32, m_a_33;
                };
            };

            /* �����o�֐� */
            S_Matrix3x3();                                                                                  // �R���X�g���N�^
            S_Matrix3x3(T value);                                                                           // �R���X�g���N�^
            S_Matrix3x3(T a_11, T a_12, T a_13,                                                             // �R���X�g���N�^
                        T a_21, T a_22, T a_23,
                        T a_31, T a_32, T a_33);
            S_Matrix3x3(const T ELEMENTS[9]);                                                               // �R���X�g���N�^
            ~S_Matrix3x3();                                                                                 // �f�X�g���N�^
            void Zero();                                                                                    // �[���s��
            void Fill(T value);                                                                             // �e�v�f�����̒l�ɕύX
            void Identity();                                                                                // �P�ʍs��
            void Transpose();                                                                               // �]�u�s��
            void Invert();                                                                                  // �t�s��
            S_Matrix3x3 GetTranspose() const;                                                               // �]�u�s����擾
            S_Matrix3x3 GetInvert() const;                                                                  // �t�s����擾
            S_Vector3<T> GetRow(Int32 index = 0) const;                                                     // �s���擾
            S_Vector3<T> GetColumn(Int32 index = 0) const;                                                  // ����擾
            String ToString() const;                                                                        // �s��𕶎���Ƃ��Ď擾
            void SetRow(const S_Vector3<T>& r_ROW, Int32 index = 0);                                        // �s��ݒ�
            void SetColumn(const S_Vector3<T>& r_COLUMN, Int32 index = 0);                                  // ���ݒ�

            /* �ÓI�����o�֐� */
            static S_Matrix3x3 s_CreateRotation(T angle);                                                   // ��]�s����쐬
            static S_Matrix3x3 s_CreateRotationX(T angle);                                                  // X�������]�s����쐬
            static S_Matrix3x3 s_CreateRotationY(T angle);                                                  // Y�������]�s����쐬
            static S_Matrix3x3 s_CreateRotationZ(T angle);                                                  // Z�������]�s����쐬
            static S_Matrix3x3 s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle);                   // �C�ӎ������]�s����쐬 
            static S_Matrix3x3 s_CreateScaling(T scaling_rate_x, T scaling_rate_y);                         // �g�k�s����쐬
            static S_Matrix3x3 s_CreateScaling(const S_Vector2<T>& r_SCALING_RATE);                         // �g�k�s����쐬
            static S_Matrix3x3 s_CreateTranslation(T movement_x, T movement_y);                             // ���s�ړ��s����쐬
            static S_Matrix3x3 s_CreateTranslation(const S_Vector2<T>& r_MOVEMENT);                         // ���s�ړ��s����쐬
            static S_Matrix3x3 s_CreateTRS(const S_Vector2<T>& r_MOVEMENT,                                  // �g�k�E��]�E���s�ړ����|�����킹���s����쐬 
                                           T angle,
                                           const S_Vector2<T>& r_SCALING_RATE);
            static S_Matrix3x3 s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& r_MATRIX);               // 4 * 4�̍s���3 * 3�̍s��ɕϊ�
            static S_Matrix3x3 s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& r_QUATERNION);         // �N�H�[�^�j�I������3 * 3�̍s��֕ϊ����A�擾
            static S_Matrix3x3 s_CreateNormal(const S_Matrix4x4<T>& r_MATRIX);                              // �@���s����쐬
            static S_Matrix3x3 s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,                              // �r���[�s����쐬
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR);

            /* S_Matrix3x3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Matrix3x3 operator+(const S_Matrix3x3& r_ANOTHER) const;                                // +���Z�q�̃I�[�o�[���[�h
            const S_Matrix3x3 operator-(const S_Matrix3x3& r_ANOTHER) const;                                // -���Z�q�̃I�[�o�[���[�h
            const S_Matrix3x3 operator*(const S_Matrix3x3& r_ANOTHER) const;                                // *���Z�q�̃I�[�o�[���[�h
            const S_Matrix3x3& operator+=(const S_Matrix3x3& r_ANOTHER);                                    // +=���Z�q�̃I�[�o�[���[�h
            const S_Matrix3x3& operator-=(const S_Matrix3x3& r_ANOTHER);                                    // -=���Z�q�̃I�[�o�[���[�h
            const S_Matrix3x3& operator*=(const S_Matrix3x3& r_ANOTHER);                                    // *=���Z�q�̃I�[�o�[���[�h
            bool operator==(const S_Matrix3x3& r_ANOTHER) const;                                            // ==���Z�q�̃I�[�o�[���[�h
            bool operator!=(const S_Matrix3x3& r_ANOTHER) const;                                            // !=���Z�q�̃I�[�o�[���[�h

            /* S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector3<T> operator*(const S_Vector3<T>& r_VECTOR) const;                               // *���Z�q�̃I�[�o�[���[�h

            /* �L���X�g���Z�q�̃I�[�o�[���[�h */
            operator String() const;                                                                        // String�^�ւ̃L���X�g
        };


        /* �ʖ� */
        typedef S_Matrix3x3<float> Matrix3x3;                                                               // Matrix3x3�^
    }
}