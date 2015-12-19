/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Utility/UtilityMath.h"



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
        
         @brief S_Vector2
                2D�x�N�g����\���\����

        */
        template<class T>
        struct S_Vector2
        {
            /* �萔 */
            static const S_Vector2 m_s_RIGHT_DIRECTION;                                             ///< @brief �E���� ( 1,  0)
            static const S_Vector2 m_s_LEFT_DIRECTION;                                              ///< @brief ������ (-1,  0)
            static const S_Vector2 m_s_UP_DIRECTION;                                                ///< @brief ����� ( 0,  1)
            static const S_Vector2 m_s_DOWN_DIRECTION;                                              ///< @brief ������ ( 0, -1)
            static const S_Vector2 m_s_ZERO;                                                        ///< @brief �[���x�N�g��
            static const S_Vector2 m_s_ONE;                                                         ///< @brief �S�Ă̗v�f��1

            /* �����o�ϐ� */
            union
            {
                T m_elements[2];                                                                    ///< @brief 2�̗v�f�����z��

                struct
                {
                    T m_x;                                                                          ///< @brief X����
                    T m_y;                                                                          ///< @brief Y����
                };

                struct
                {
                    T m_u;                                                                          ///< @brief U����
                    T m_v;                                                                          ///< @brief V����
                };

                struct
                {
                    T m_width;                                                                      ///< @brief ��
                    T m_height;                                                                     ///< @brief ����
                };
            };

            /* �����o�֐� */
            S_Vector2();                                                                            // �R���X�g���N�^
            S_Vector2(T value);                                                                     // �R���X�g���N�^
            S_Vector2(T x, T y);                                                                    // �R���X�g���N�^
            S_Vector2(const T ELEMENTS[2]);                                                         // �R���X�g���N�^
            ~S_Vector2();                                                                           // �f�X�g���N�^
            void Zero();                                                                            // �[���x�N�g����
            void Fill(T value);                                                                     // �e���������̒l�ɕύX
            void Normalize();                                                                       // �P�ʃx�N�g����
            void Invert();                                                                          // �x�N�g���𔽓]
            void Perpendicular();                                                                   // �����ȃx�N�g���ɕϊ�
            void Rotate(T angle);                                                                   // �x�N�g������]
            void ClampMagnitude(T min, T max);                                                      // �傫���Ńx�N�g�����N�����v
            T GetMagnitude() const;                                                                 // �傫�����擾
            T GetMagnitudeSquare() const;                                                           // �傫����2����擾
            S_Vector2 GetNormalize() const;                                                         // �P�ʃx�N�g�����擾
            S_Vector2 GetInvert() const;                                                            // ���]�����x�N�g�����擾
            S_Vector2 GetPerpendicular() const;                                                     // �����ȃx�N�g�����擾
            S_Vector2 GetRotate(T angle) const;                                                     // ��]�����x�N�g�����擾
            T GetAngle() const;                                                                     // �x�N�g���̊p�x���擾
            S_Vector2 GetClampMagnitude(T min, T max) const;                                        // �傫���ŃN�����v�����x�N�g�����擾
            std::string ToString() const;                                                           // �x�N�g���𕶎���֕ϊ����Ď擾

            /* Swizzle */
            template<eVectorFactor factor_0>
            S_Vector2 Get() const
            {
                return S_Vector2(a_[factor_0], a_[factor_0]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1>
            S_Vector2 Get() const
            {
                return S_Vector2(a_[factor_0], a_[factor_1]);
            }

            /* �ÓI�����o�֐� */
            static T s_DotProduct(const S_Vector2& r_LHS, const S_Vector2& r_RHS);                  // ����
            static T s_CrossProduct(const S_Vector2& r_LHS, const S_Vector2& r_RHS);                // �O��
            static S_Vector2 s_Lerp(const S_Vector2& r_START_POINT,                                 // ���`���
                                    const S_Vector2& r_END_POINT,
                                    T coefficient);
            static S_Vector2 s_Slerp(const S_Vector2& r_START_POINT,                                // ���ʐ��`���
                                     const S_Vector2& r_END_POINT,
                                     T coefficient);
            static S_Vector2 s_Hermite(const S_Vector2& r_START_POINT,                              // �G���~�[�g���
                                       const S_Vector2& r_START_TANGENT,
                                       const S_Vector2& r_END_POINT,
                                       const S_Vector2& r_END_TANGENT,
                                       T coefficient);
            static S_Vector2 s_CatmullRomSpline(const S_Vector2& r_PREVIOUS_START_POINT,            // Catmull-Rom�X�v���C�����
                                                const S_Vector2& r_START_POINT,
                                                const S_Vector2& r_END_POINT,
                                                const S_Vector2& r_NEXT_END_POINT,
                                                T coefficient);
            static S_Vector2 s_Bezier(const S_Vector2& r_START_POINT,                               // �x�W�F���
                                      const S_Vector2& r_END_POINT,
                                      const S_Vector2& r_CONTROL_POINT_1,
                                      const S_Vector2& r_CONTROL_POINT_2,
                                      T coefficient);
            static S_Vector2 s_CreateWithAngle(T angle, T length = static_cast<T>(1));              // �p�x����x�N�g�����쐬
            static S_Vector2 s_InterceptPoint(const S_Vector2& r_POSITION,                          // �}���|�C���g���擾
                                              const S_Vector2& r_VELOCITY,
                                              const S_Vector2& r_ANOTHER_POSITION,
                                              const S_Vector2& r_ANOTHER_VELOCITY);
            static T s_AngleBetweenVectors(const S_Vector2& r_LHS, const S_Vector2& r_RHS);         // �x�N�g���Ԃ̊p�x���擾
            static T s_DistanceBetweenVectors(const S_Vector2& r_LHS, const S_Vector2& r_RHS);      // �x�N�g���Ԃ̋������擾
            static S_Vector2 s_Minimize(const S_Vector2& r_LHS, const S_Vector2& r_RHS);            // �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾
            static S_Vector2 s_Maximize(const S_Vector2& r_LHS, const S_Vector2& r_RHS);            // �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾
            static S_Vector2 s_MoveTowards(const S_Vector2& r_START_POINT,                          // 2�_�Ԃ���̋����������i�񂾓_���擾
                                           const S_Vector2& r_END_POINT,
                                           T distance);
            static S_Vector2 s_Project(const S_Vector2& r_VECTOR, const S_Vector2& r_NORMAL);       // ���e�x�N�g�����擾
            static S_Vector2 s_Reflect(const S_Vector2& r_VECTOR, const S_Vector2& r_NORMAL);       // ���˃x�N�g�����擾
            static S_Vector2 s_Refract(const S_Vector2& r_INCIDENT_VECTOR,                          // ���܃x�N�g�����擾
                                       const S_Vector2& r_NORMAL,
                                       T REFRACTIVE_INDEX);
            static S_Vector2 s_Slide(const S_Vector2& r_VECTOR, const S_Vector2& r_NORMAL);         // ����x�N�g�����擾
            static S_Vector2 s_CenterOfGravityWith3Points(const S_Vector2& r_A,                     // 3�_����d�S���擾
                                                          const S_Vector2& r_B,
                                                          const S_Vector2& r_C);


            /* S_Vector2�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector2 operator+(const S_Vector2& r_ANOTHER) const;                            // +���Z�q�̃I�[�o�[���[�h
            const S_Vector2 operator-(const S_Vector2& r_ANOTHER) const;                            // -���Z�q�̃I�[�o�[���[�h
            const S_Vector2 operator*(const S_Vector2& r_ANOTHER) const;                            // *���Z�q�̃I�[�o�[���[�h
            const S_Vector2 operator/(const S_Vector2& r_ANOTHER) const;                            // /���Z�q�̃I�[�o�[���[�h
            const S_Vector2& operator+=(const S_Vector2& r_ANOTHER);                                // +=���Z�q�̃I�[�o�[���[�h
            const S_Vector2& operator-=(const S_Vector2& r_ANOTHER);                                // -=���Z�q�̃I�[�o�[���[�h
            const S_Vector2& operator*=(const S_Vector2& r_ANOTHER);                                // *=���Z�q�̃I�[�o�[���[�h
            const S_Vector2& operator/=(const S_Vector2& r_ANOTHER);                                // /=���Z�q�̃I�[�o�[���[�h
            bool operator==(const S_Vector2& r_ANOTHER) const;                                      // ==���Z�q�̃I�[�o�[���[�h
            bool operator!=(const S_Vector2& r_ANOTHER) const;                                      // !=���Z�q�̃I�[�o�[���[�h

            /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector2 operator*(T value) const;                                               // *���Z�q�̃I�[�o�[���[�h
            const S_Vector2 operator/(T value) const;                                               // /���Z�q�̃I�[�o�[���[�h
            const S_Vector2& operator*=(T value);                                                   // *=���Z�q�̃I�[�o�[���[�h
            const S_Vector2& operator/=(T value);                                                   // /=���Z�q�̃I�[�o�[���[�h

            /* �L���X�g */
            operator String() const;                                                                // String�^�ւ̃L���X�g


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


            /* 
            
             @brief     ��Z���Z�q�̃I�[�o�[���[�h
             @param[in] value    �l
             @param[in] r_VECTOR �x�N�g��
             @return    const S_Vector2 ��Z�����x�N�g��
            
            */
            friend const S_Vector2 operator*(T value, const S_Vector2& r_VECTOR)
            {
                return S_Vector2(r_VECTOR.m_x * value, r_VECTOR.m_y * value);
            }


#pragma endregion

        };

        /* �ʖ� */
        typedef S_Vector2<float> Vector2;                                                           // Vector2�^
    }
}