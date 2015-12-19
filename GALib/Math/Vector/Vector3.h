/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Vector2.h"


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
        
         @brief S_Vector3
                3D�x�N�g����\���\����

        */
        template<class T>
        struct S_Vector3
        {
            /* �萔 */
            static const S_Vector3 m_s_RIGHT_DIRECTION;                                                                 ///< @brief �E���� ( 1,  0,  0)
            static const S_Vector3 m_s_LEFT_DIRECTION;                                                                  ///< @brief ������ (-1,  0,  0)
            static const S_Vector3 m_s_UP_DIRECTION;                                                                    ///< @brief ����� ( 0,  1,  0)
            static const S_Vector3 m_s_DOWN_DIRECTION;                                                                  ///< @brief ������ ( 0, -1,  0)
            static const S_Vector3 m_s_FRONT_DIRECTION;                                                                 ///< @brief �O���� ( 0,  0,  1)
            static const S_Vector3 m_s_BACK_DIRECTION;                                                                  ///< @brief ����� ( 0,  0, -1)
            static const S_Vector3 m_s_ZERO;                                                                            ///< @brief �[���x�N�g��
            static const S_Vector3 m_s_ONE;                                                                             ///< @brief �S�Ă̗v�f��1


            /* �����o�ϐ� */
            union
            {
                struct
                {
                    T m_elements[3];                                                                                    ///< @brief 3�̗v�f�����z��
                };

                struct
                {
                    T m_x;                                                                                              ///< @brief X����
                    T m_y;                                                                                              ///< @brief Y����
                    T m_z;                                                                                              ///< @brief Z����
                };

                struct
                {
                    T m_u;                                                                                              ///< @brief U����
                    T m_v;                                                                                              ///< @brief V����
                    T m_w;                                                                                              ///< @brief W����
                };

                struct
                {
                    T m_red;                                                                                            ///< @brief ��
                    T m_green;                                                                                          ///< @brief ��
                    T m_blue;                                                                                           ///< @brief ��
                };

                struct
                {
                    T m_width;                                                                                          ///< @brief ��
                    T m_height;                                                                                         ///< @brief ����
                    T m_depth;                                                                                          ///< @brief ���s��
                };
            };

            /* �����o�֐� */
            S_Vector3();                                                                                                // �R���X�g���N�^
            S_Vector3(T value);                                                                                         // �R���X�g���N�^
            S_Vector3(T x, T y, T z);                                                                                   // �R���X�g���N�^
            S_Vector3(const T a[3]);                                                                                    // �R���X�g���N�^
            S_Vector3(const S_Vector2<T>& r_XY, T z);                                                                   // �R���X�g���N�^
            ~S_Vector3();                                                                                               // �f�X�g���N�^
            void Zero();                                                                                                // �[���x�N�g����
            void Fill(T value);                                                                                         // �e���������̒l�ɕύX
            void Normalize();                                                                                           // �P�ʃx�N�g����
            void Invert();                                                                                              // �x�N�g���𔽓]
            void RotateX(T angle);                                                                                      // X������x�N�g������]
            void RotateY(T angle);                                                                                      // Y������x�N�g������]
            void RotateZ(T angle);                                                                                      // Z������x�N�g������]
            void RotateAxis(const S_Vector3<T>& r_AXIS, T angle);                                                       // �C�ӎ�����x�N�g������]
            void ClampMagnitude(T min, T max);                                                                          // �傫���Ńx�N�g�����N�����v
            T GetMagnitude() const;                                                                                     // �傫�����擾
            T GetMagnitudeSquare() const;                                                                               // �傫����2����擾
            S_Vector3 GetNormalize() const;                                                                             // �P�ʃx�N�g�����擾
            S_Vector3 GetInvert() const;                                                                                // ���]�����x�N�g�����擾
            S_Vector3 GetRotateX(T angle) const;                                                                        // X�������]�����x�N�g�����擾
            S_Vector3 GetRotateY(T angle) const;                                                                        // Y�������]�����x�N�g�����擾
            S_Vector3 GetRotateZ(T angle) const;                                                                        // Z�������]�����x�N�g�����擾
            S_Vector3 GetRotateAxis(const S_Vector3<T>& r_AXIS, T angle) const;                                         // �C�ӎ������]�����x�N�g�����擾
            S_Vector3 GetClampMagnitude(T min, T max) const;                                                            // �傫���ŃN�����v�����x�N�g�����擾
            String ToString() const;                                                                                    // �x�N�g���𕶎���Ƃ��Ď擾

            /* Swizzle */
            template<eVectorFactor factor_0>
            S_Vector3 Get() const
            {
                return S_Vector3(a_[factor_0], a_[factor_0], a_[factor_0]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1>
            S_Vector3 Get() const
            {
                return S_Vector3(a_[factor_0], a_[factor_1], a_[factor_1]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1, eVectorFactor factor_2>
            S_Vector3 Get() const
            {
                return S_Vector3(a_[factor_0], a_[factor_1], a_[factor_2]);
            }

            /* �ÓI�����o�ϐ� */
            static T s_DotProduct(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                                      // ����
            static S_Vector3 s_CrossProduct(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                            // �O��
            static T s_ScalarTripleProduct(const S_Vector3& r_A,                                                        // �X�J���[�O�d��
                                           const S_Vector3& r_B,
                                           const S_Vector3& r_C);
            static S_Vector3 s_VectorTripleProduct(const S_Vector3& r_A,                                                // �x�N�g���O�d��
                                                   const S_Vector3& r_B,
                                                   const S_Vector3& r_C);
            static S_Vector3 s_Lerp(const S_Vector3& r_START_POINT,                                                     // ���`���
                                    const S_Vector3& r_END_POINT,
                                    T factor);
            static S_Vector3 s_Slerp(const S_Vector3& r_START_POINT,                                                    // ���ʐ��`���
                                     const S_Vector3& r_END_POINT,
                                     T factor);
            static S_Vector3 s_Hermite(const S_Vector3& r_START_POINT,                                                  // �G���~�[�g���
                                       const S_Vector3& r_START_TANGETNT,
                                       const S_Vector3& r_END_POINT,
                                       const S_Vector3& r_END_TANGENT,
                                       T factor);
            static S_Vector3 s_CatmullRomSpline(const S_Vector3& r_PREVIOUS_START_POINT,                                // Catmull-Rom�X�v���C�����
                                                const S_Vector3& r_START_POINT,
                                                const S_Vector3& r_END_POINT,
                                                const S_Vector3& r_NEXT_END_POINT,
                                                T factor);
            static S_Vector3 s_Bezier(const S_Vector3& r_START_POINT,                                                   // �x�W�F���
                                      const S_Vector3& r_END_POINT,
                                      const S_Vector3& r_CONTROL_POINT_1,
                                      const S_Vector3& r_CONTROL_POINT_2,
                                      T factor);
            static S_Vector3 s_InterceptPoint(const S_Vector3& r_POSITION,                                              // �}���|�C���g���擾
                                              const S_Vector3& r_VECTOR,
                                              const S_Vector3& r_ANOTHER_POSITION,
                                              const S_Vector3& r_ANOTHER_VELOCITY);
            static T s_AngleBetweenVectors(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                             // �x�N�g���Ԃ̊p�x���擾
            static T s_DistanceBetweenVectors(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                          // �x�N�g���Ԃ̋������擾
            static S_Vector3 s_Minimize(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                                // �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾
            static S_Vector3 s_Maximize(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                                // �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾
            static S_Vector3 s_MoveTowards(const S_Vector3& r_START_POINT,                                              // 2�_�Ԃ���̋����������i�񂾓_���擾
                                           const S_Vector3& r_END_POINT,
                                           T distance);
            static S_Vector3 s_Project(const S_Vector3& r_VECTOR, const S_Vector3& r_NORMAL);                           // ���e�x�N�g�����擾
            static S_Vector3 s_Reflect(const S_Vector3& r_VECTOR, const S_Vector3& r_NORMAL);                           // ���˃x�N�g�����擾
            static S_Vector3 s_Refract(const S_Vector3& r_INCIDENT_VECTOR,                                              // ���܃x�N�g�����擾
                                       const S_Vector3& r_NORMAL,
                                       T refractive_index);
            static S_Vector3 s_Slide(const S_Vector3& r_VECTOR, const S_Vector3& r_NORMAL);                             // ����x�N�g�����擾
            static S_Vector3 s_CreateNormal(const S_Vector3& r_POSITION_A,                                              // �@���x�N�g�����쐬
                                            const S_Vector3& r_POSITION_B,
                                            const S_Vector3& r_POSITION_C);
            static void s_CreateTangentAndBinormal(const S_Vector3& r_POSITION_A,                                       // �ڐ��x�N�g���Ə]�@�����쐬( ���s���͂���ĂȂ� )
                                                   const S_Vector2<T>& r_TEXTURE_COORD_A,
                                                   const S_Vector3& r_POSITION_B,
                                                   const S_Vector2<T>& r_TEXTURE_COORD_B,
                                                   const S_Vector3& r_POSITION_C,
                                                   const S_Vector2<T>& r_TEXTURE_COORD_C,
                                                   S_Vector3* p_tangent = GA_NULL,
                                                   S_Vector3* p_binormal = GA_NULL);
            static S_Vector3 s_CenterOfGravityWith3Points(const S_Vector3& r_A,                                         // 3�_����d�S���擾
                                                          const S_Vector3& r_B,
                                                          const S_Vector3& r_C);


            /* S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector3 operator+(const S_Vector3& r_ANOTHER) const;                                                // +���Z�q�̃I�[�o�[���[�h
            const S_Vector3 operator-(const S_Vector3& r_ANOTHER) const;                                                // -���Z�q�̃I�[�o�[���[�h
            const S_Vector3 operator*(const S_Vector3& r_ANOTHER) const;                                                // *���Z�q�̃I�[�o�[���[�h
            const S_Vector3 operator/(const S_Vector3& r_ANOTHER) const;                                                // /���Z�q�̃I�[�o�[���[�h
            const S_Vector3& operator+=(const S_Vector3& r_ANOTHER);                                                    // +=���Z�q�̃I�[�o�[���[�h
            const S_Vector3& operator-=(const S_Vector3& r_ANOTHER);                                                    // -=���Z�q�̃I�[�o�[���[�h
            const S_Vector3& operator*=(const S_Vector3& r_ANOTHER);                                                    // *=���Z�q�̃I�[�o�[���[�h
            const S_Vector3& operator/=(const S_Vector3& r_ANOTHER);                                                    // /=���Z�q�̃I�[�o�[���[�h
            bool operator==(const S_Vector3& r_ANOTHER) const;                                                          // ==���Z�q�̃I�[�o�[���[�h
            bool operator!=(const S_Vector3& r_ANOTHER) const;                                                          // !=���Z�q�̃I�[�o�[���[�h

            /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector3 operator*(T value) const;                                                                   // *���Z�q�̃I�[�o�[���[�h
            const S_Vector3 operator/(T value) const;                                                                   // /���Z�q�̃I�[�o�[���[�h
            const S_Vector3& operator*=(T value);                                                                       // *=���Z�q�̃I�[�o�[���[�h
            const S_Vector3& operator/=(T value);                                                                       // /=���Z�q�̃I�[�o�[���[�h

            /* �L���X�g */
            operator S_Vector2<T>() const;                                                                              // S_Vector2�^�ւ̃L���X�g
            operator String() const;                                                                                    // String�^�ւ̃L���X�g


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


            /* 
            
             @brief     ��Z���Z�q�̃I�[�o�[���[�h
             @param[in] value    �l
             @param[in] r_VECTOR �x�N�g��
             @return    const S_Vector3 ��Z�����x�N�g��
            
            */
            friend const S_Vector3 operator*(T value, const S_Vector3& r_VECTOR)
            {
                return S_Vector3(r_VECTOR.m_x * value, r_VECTOR.m_y * value, r_VECTOR.m_z * value);
            }


#pragma endregion

        };

        /* �ʖ� */
        typedef S_Vector3<float> Vector3;                                                                               // Vector3�^
    }
}