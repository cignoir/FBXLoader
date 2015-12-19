/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Vector/Vector3.h"


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
        struct S_Matrix3x3;

        template<class T>
        struct S_Matrix4x4;


        /*

         @brief S_Quaternion
                �N�H�[�^�j�I����\���\����

        */
        template<class T>
        struct S_Quaternion
        {
            /* �萔 */
            static const S_Quaternion m_s_IDENTITY;                                                             ///< @brief �P�ʃN�H�[�^�j�I��

            /* �����o�ϐ� */
            union
            {
                struct
                {
                    T m_elements[4];                                                                            ///< brief 4�̗v�f�����z��
                };

                struct
                {
                    T m_t;                                                                                      ///< @brief T����
                    T m_x;                                                                                      ///< @brief X����
                    T m_y;                                                                                      ///< @brief Y����
                    T m_z;                                                                                      ///< @brief Z����
                };
            };

            /* �����o�֐� */
            S_Quaternion();                                                                                     // �R���X�g���N�^
            S_Quaternion(T value);                                                                              // �R���X�g���N�^
            S_Quaternion(T t, T x, T y, T z);                                                                   // �R���X�g���N�^
            S_Quaternion(T t, const S_Vector3<T>& r_XYZ);                                                       // �R���X�g���N�^
            ~S_Quaternion();                                                                                    // �f�X�g���N�^
            void Fill(T value);                                                                                 // �e���������̒l�ɕύX
            void Identity();                                                                                    // �P�ʃN�H�[�^�j�I����
            void Normalize();                                                                                   // ���K��
            void Invert();                                                                                      // �t�N�H�[�^�j�I����
            T GetMagnitude() const;                                                                             // �傫�����擾
            T GetMagnitudeSquare() const;                                                                       // �傫����2����擾
            S_Quaternion GetNormalize() const;                                                                  // ���K�������N�H�[�^�j�I�����擾
            S_Quaternion GetInvert() const;                                                                     // �t�N�H�[�^�j�I�����擾
            T GetAngleFromXAxis() const;                                                                        // X������̊p�x���擾
            T GetAngleFromYAxis() const;                                                                        // Y������̊p�x���擾
            T GetAngleFromZAxis() const;                                                                        // Z������̊p�x���擾
            void GetAxisAndAngle(S_Vector3<T>* p_axis, T* p_angle) const;                                       // ���Ɗp�x���擾
            String ToString() const;                                                                            // �N�H�[�^�j�I���𕶎���Ƃ��Ď擾

            /* �ÓI�����o�֐� */
            static T s_DotProduct(const S_Quaternion<T>& r_LHS, const S_Quaternion<T>& r_RHS);                  // ����
            static S_Quaternion s_CreateRotationAxis(const S_Vector3<T>& r_AXIS,                                // �C�ӎ�����N�H�[�^�j�I�����쐬
                                                     T angle);
            static S_Quaternion s_CreateRotationPitchYawRoll(T pitch,                                           // 3���̉�]�𔽉f�����N�H�[�^�j�I�����쐬
                                                             T yaw,
                                                             T roll);
            static S_Quaternion s_CreateRotationPitchYawRoll(const S_Vector3<T>& r_ROTATION);                   // 3���̉�]�𔽉f�����N�H�[�^�j�I�����쐬
            static S_Quaternion s_CreateLookRotation(const S_Vector3<T>& r_DIRECTION,                           // �C�ӂ̌����֌������߂̃N�H�[�^�j�I�����쐬
                                                     const S_Vector3<T>& r_UP_VECTOR);
            static S_Quaternion s_CreateFromToRotation(const S_Vector3<T>& r_FROM_DIRECTION,                    // ������������։�]������N�H�[�^�j�I�����쐬 
                                                       const S_Vector3<T>& r_TO_DIRECTION);
            static S_Quaternion s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& r_MATRIX);                 // 3 * 3�̍s�񂩂�N�H�[�^�j�I���֕ϊ����Ď擾
            static S_Quaternion s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& r_MATRIX);                 // 4 * 4�̍s�񂩂�N�H�[�^�j�I���֕ϊ����Ď擾
            static S_Quaternion s_Lerp(const S_Quaternion& r_START,                                             // ���`���
                                       const S_Quaternion& r_END,
                                       T factor);
            static S_Quaternion s_Slerp(const S_Quaternion& r_START,                                            // ���ʐ��`���
                                        const S_Quaternion& r_END,
                                        T factor);

            /* S_Quaternion�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Quaternion operator+(const S_Quaternion& r_ANOTHER) const;                                  // +���Z�q�̃I�[�o�[���[�h
            const S_Quaternion operator-(const S_Quaternion& r_ANOTHER) const;                                  // -���Z�q�̃I�[�o�[���[�h
            const S_Quaternion operator*(const S_Quaternion& r_ANOTHER) const;                                  // *���Z�q�̃I�[�o�[���[�h
            const S_Quaternion& operator+=(const S_Quaternion& r_ANOTHER);                                      // +=���Z�q�̃I�[�o�[���[�h
            const S_Quaternion& operator-=(const S_Quaternion& r_ANOTHER);                                      // -=���Z�q�̃I�[�o�[���[�h
            const S_Quaternion& operator*=(const S_Quaternion& r_ANOTHER);                                      // *=���Z�q�̃I�[�o�[���[�h
            bool operator==(const S_Quaternion& r_ANOTHER) const;                                               // ==���Z�q�̃I�[�o�[���[�h
            bool operator!=(const S_Quaternion& r_ANOTHER) const;                                               // !=���Z�q�̃I�[�o�[���[�h

            /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Quaternion operator*(T value) const;                                                        // *���Z�q�̃I�[�o�[���[�h
            const S_Quaternion& operator*=(T value);                                                            // *=���Z�q�̃I�[�o�[���[�h

            /* �L���X�g���Z�q�̃I�[�o�[���[�h */
            operator S_Vector3<T>() const;                                                                      // S_Vector3�^�ւ̃L���X�g
            operator String() const;                                                                            // String�^�ւ̃L���X�g

#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


            /* 

             @brief  ��Z���Z�q�̃I�[�o�[���[�h
             @param[in] value        �l
             @param[in] r_QUATERNION �N�H�[�^�j�I�� 
             @return const S_Quaternion<T> ��Z�����N�H�[�^�j�I��
            
            */
            friend const S_Quaternion operator*(T value, const S_Quaternion& r_QUATERNION)
            {
                return S_Quaternion(r_QUATERNION.m_t * value,
                                    r_QUATERNION.m_x * value,
                                    r_QUATERNION.m_y * value,
                                    r_QUATERNION.m_z * value);
            }


#pragma endregion
 
       };

       /* �ʖ� */
        typedef S_Quaternion<float> Quaternion;                                                             // Vector2�^
    }
}