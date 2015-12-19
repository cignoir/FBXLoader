/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Vector3.h"


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
        /*

         @brief S_Vector4
                4D�x�N�g����\���\����

        */
        template<class T>
        struct S_Vector4
        {
            /* �萔 */
            static const S_Vector4 m_s_ZERO;                                                        ///< @brief �[���x�N�g��
            static const S_Vector4 m_s_ONE;                                                         ///< @brief �S�Ă̗v�f��1

            /* �����o�ϐ� */
            union
            {
                struct
                {
                    T m_elements[4];                                                                ///< @brief 4�̗v�f�����z��
                };

                struct
                {
                    T m_x;                                                                          ///< @brief X����
                    T m_y;                                                                          ///< @brief Y����
                    T m_z;                                                                          ///< @brief Z����
                    T m_w;                                                                          ///< @brief W����
                };

                struct
                {
                    T m_red;                                                                        ///< @brief ��
                    T m_green;                                                                      ///< @brief ��
                    T m_blue;                                                                       ///< @brief ��
                    T m_alpha;                                                                      ///< @brief �A���t�@
                };
            };


            /* �����o�֐� */
            S_Vector4();                                                                            // �R���X�g���N�^
            S_Vector4(T value);                                                                     // �R���X�g���N�^
            S_Vector4(T x, T y, T z, T w);                                                          // �R���X�g���N�^
            S_Vector4(const T ELEMENTS[4]);                                                         // �R���X�g���N�^
            S_Vector4(const S_Vector2<T>& r_XY, T z, T w);                                          // �R���X�g���N�^
            S_Vector4(const S_Vector3<T>& r_XYX, T w);                                              // �R���X�g���N�^
            ~S_Vector4();                                                                           // �f�X�g���N�^
            void Zero();                                                                            // �[���x�N�g����
            void Fill(T value);                                                                     // �e���������̒l�ɕύX
            void Normalize();                                                                       // �P�ʃx�N�g����
            void Invert();                                                                          // �x�N�g���𔽓]
            void ClampMagnitude(T min, T max);                                                      // �x�N�g���̑傫���ŃN�����v
            T GetMagnitude() const;                                                                 // �傫�����擾
            T GetMagnitudeSquare() const;                                                           // �傫����2����擾
            S_Vector4 GetNormalize() const;                                                         // �P�ʃx�N�g�����擾
            S_Vector4 GetInvert() const;                                                            // ���]�����x�N�g�����擾
            S_Vector4 GetClampMagnitude(T min, T max) const;                                        // �傫���ŃN�����v�����x�N�g�����擾
            String ToString() const;                                                                // �x�N�g���𕶎���Ƃ��Ď擾

            /* Swizzle */
            template<eVectorFactor factor_0>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_0], a_[factor_0], a_[factor_0]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_1], a_[factor_1], a_[factor_1]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1, eVectorFactor factor_2>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_1], a_[factor_2], a_[factor_2]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1, eVectorFactor factor_2, eVectorFactor factor_3>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_1], a_[factor_2], a_[factor_3]);
            }

            /* �ÓI�����o�֐� */
            static T s_DotProduct(const S_Vector4& r_VECTOR, const S_Vector4& r_ANOTHER_VECTOR);    // ����
            static S_Vector4 s_Lerp(const S_Vector4& r_START_POINT,                                 // ���`���
                                    const S_Vector4& r_END_POINT,
                                    T factor);
            static S_Vector4 s_Minimize(const S_Vector4& r_LHS, const S_Vector4& r_RHS);            // �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾
            static S_Vector4 s_Maximize(const S_Vector4& r_LHS, const S_Vector4& r_RHS);            // �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾

            /* S_Vector4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector4 operator+(const S_Vector4& r_ANOTHER) const;                            // +���Z�q�̃I�[�o�[���[�h
            const S_Vector4 operator-(const S_Vector4& r_ANOTHER) const;                            // -���Z�q�̃I�[�o�[���[�h
            const S_Vector4 operator*(const S_Vector4& r_ANOTHER) const;                            // *���Z�q�̃I�[�o�[���[�h
            const S_Vector4 operator/(const S_Vector4& r_ANOTHER) const;                            // /���Z�q�̃I�[�o�[���[�h
            const S_Vector4& operator+=(const S_Vector4& r_ANOTHER);                                // +=���Z�q�̃I�[�o�[���[�h
            const S_Vector4& operator-=(const S_Vector4& r_ANOTHER);                                // -=���Z�q�̃I�[�o�[���[�h
            const S_Vector4& operator*=(const S_Vector4& r_ANOTHER);                                // *=���Z�q�̃I�[�o�[���[�h
            const S_Vector4& operator/=(const S_Vector4& r_ANOTHER);                                // /=���Z�q�̃I�[�o�[���[�h
            bool operator==(const S_Vector4& r_ANOTHER) const;                                      // ==���Z�q�̃I�[�o�[���[�h
            bool operator!=(const S_Vector4& r_ANOTHER) const;                                      // !=���Z�q�̃I�[�o�[���[�h

            /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector4 operator*(T value) const;                                               // *���Z�q�̃I�[�o�[���[�h
            const S_Vector4 operator/(T value) const;                                               // /���Z�q�̃I�[�o�[���[�h
            const S_Vector4& operator*=(T value);                                                   // *=���Z�q�̃I�[�o�[���[�h
            const S_Vector4& operator/=(T value);                                                   // /=���Z�q�̃I�[�o�[���[�h

            /* �L���X�g���Z�q�̃I�[�o�[���[�h */
            operator S_Vector2<T>() const;                                                          // S_Vector2�^�ւ̃L���X�g
            operator S_Vector3<T>() const;                                                          // S_Vector3�^�ւ̃L���X�g
            operator String() const;                                                                // String�^�ւ̃L���X�g

#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


            /* 
            
             @brief     ��Z���Z�q�̃I�[�o�[���[�h
             @param[in] value    �l
             @param[in] r_VECTOR �x�N�g��
             @return    const S_Vector4 ��Z�����x�N�g��
            
            */
            friend const S_Vector4 operator*(T value, const S_Vector4& r_VECTOR)
            {
                return S_Vector4(r_VECTOR.m_x * value, r_VECTOR.m_y * value, r_VECTOR.m_z * value, r_VECTOR.m_w * value);
            }


#pragma endregion

        };


        /* �ʖ� */
        typedef S_Vector4<float> Vector4;                                                           // Vector4�^
    }
}
