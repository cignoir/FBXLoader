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
        /* �O���錾 */
        template<class T>
        struct S_Vector3;

        template<class T>
        struct S_Vector4;

        template<class T>
        struct S_Quaternion;

        template <class T>
        struct S_Matrix3x3;


        /*

         @brief S_Matrix4x4
                4 * 4�̍s���\���\����

        */
        template<class T>
        struct S_Matrix4x4
        {
            /* �萔 */
            static const Uint32 m_s_ELEMENT_COUNT = 16;                                                                 ///< @brief �v�f��
            static const T m_s_ORTHOGRAPHIC_2D_NEAR;                                                                    ///< @brief 2D�p�̐����e�̎ˉe�s����쐬���̎��_����ł��߂��N���b�v��
            static const T m_s_ORTHOGRAPHIC_2D_FAR;                                                                     ///< @brief 2D�p�̐����e�̎ˉe�s����쐬���̎��_����ł������N���b�v��
            static const S_Matrix4x4 m_s_ZERO;                                                                          ///< @brief �[���s��
            static const S_Matrix4x4 m_s_IDENTITY;                                                                      ///< @brief �P�ʍs��

            /* �����o�ϐ� */
            union
            {
                T m_elements[m_s_ELEMENT_COUNT];                                                                        ///< @brief 16�̗v�f�����z��
                T m_elements_4x4[4][4];                                                                                 ///< @brief 4 * 4�̓񎟌��z��

                /// @brief �s��̊e�v�f
                struct
                {
                    T m_a_11, m_a_12, m_a_13, m_a_14;
                    T m_a_21, m_a_22, m_a_23, m_a_24;
                    T m_a_31, m_a_32, m_a_33, m_a_34;
                    T m_a_41, m_a_42, m_a_43, m_a_44;
                };
            };

            /* �����o�֐� */
            S_Matrix4x4();                                                                                              // �R���X�g���N�^
            S_Matrix4x4(T value);                                                                                       // �R���X�g���N�^
            S_Matrix4x4(T a_11, T a_12, T a_13, T a_14,                                                                 // �R���X�g���N�^
                        T a_21, T a_22, T a_23, T a_24,
                        T a_31, T a_32, T a_33, T a_34,
                        T a_41, T a_42, T a_43, T a_44);
            S_Matrix4x4(const T ELEMENTS[m_s_ELEMENT_COUNT]);                                                           // �R���X�g���N�^
            S_Matrix4x4(const S_Matrix3x3<T>& r_MATRIX);                                                                // �R���X�g���N�^
            ~S_Matrix4x4();                                                                                             // �f�X�g���N�^
            void Zero();                                                                                                // �[���s��
            void Identity();                                                                                            // �P�ʍs��
            void Transpose();                                                                                           // �]�u�s��
            void Invert();                                                                                              // �t�s��
            S_Matrix4x4 GetTranspose() const;                                                                           // �]�u�s����擾
            S_Matrix4x4 GetInvert() const;                                                                              // �t�s����擾
            S_Vector3<T> GetTranslationComponent() const;                                                               // ���s�ړ��������擾
            S_Vector3<T> GetScalingComponent() const;                                                                   // �g�k�������擾
            S_Vector3<T> GetLocalAxisX() const;                                                                         // ���[�J�����W��X�����擾
            S_Vector3<T> GetLocalAxisY() const;                                                                         // ���[�J�����W��Y�����擾
            S_Vector3<T> GetLocalAxisZ() const;                                                                         // ���[�J�����W��Z�����擾
            S_Vector4<T> GetRow(Int32 index = 0) const;                                                                 // �s���擾
            S_Vector4<T> GetColumn(Int32 index = 0) const;                                                              // ����擾
            String ToString() const;                                                                                    // �s��𕶎���Ƃ��Ď擾
            void SetRow(const S_Vector4<T>& r_ROM, Int32 index = 0);                                                    // �s��ݒ�
            void SetColumn(const S_Vector4<T>& r_COLUMN, Int32 index = 0);                                              // ���ݒ�

            /* �ÓI�����o�֐� */
            static S_Matrix4x4 s_CreateRotationX(T angle);                                                              // X�������]�s����쐬
            static S_Matrix4x4 s_CreateRotationY(T angle);                                                              // Y�������]�s����쐬
            static S_Matrix4x4 s_CreateRotationZ(T angle);                                                              // Z�������]�s����쐬
            static S_Matrix4x4 s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle);                               // �C�ӎ������]�s����쐬
            static S_Matrix4x4 s_CreateRotationYawPitchRoll(T pitch,                                                    // 3���̉�]�𔽉f������]�s����쐬
                                                            T yaw,
                                                            T roll);
            static S_Matrix4x4 s_CreateRotationYawPitchRoll(const S_Vector3<T>& r_ROTATION);                            // 3���̉�]�𔽉f������]�s����쐬
            static S_Matrix4x4 s_CreateScaling(T scaling_rate_x, T scaling_rate_y, T scaling_rate_z);                   // �g�k�s����쐬
            static S_Matrix4x4 s_CreateScaling(const S_Vector3<T>& r_scaling_rate);                                     // �g�k�s����쐬
            static S_Matrix4x4 s_CreateTranslation(T movement_x,                                                        // ���s�ړ��s����쐬
                                                   T movement_y,
                                                   T movement_z);
            static S_Matrix4x4 s_CreateTranslation(const S_Vector3<T>& r_MOVEMENT);                                     // ���s�ړ��s����쐬
            static S_Matrix4x4 s_CreateTRS(const S_Vector3<T>& r_MOVEMENT,                                              // �g�k�E��]�E���s�ړ����|�����킹���s����쐬 
                                           const S_Vector3<T>& r_ROTATION,
                                           const S_Vector3<T>& r_SCALING_RATE);
            static S_Matrix4x4 s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,                                          // �r���[�s����쐬
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR);
            static S_Matrix4x4 s_CreatePerspectiveProjection(T field_of_view_y,                                         // �������e�̎ˉe�s����쐬
                                                             T aspect_ratio,
                                                             T near_clipping_plane,
                                                             T far_clipping_plane);
            static S_Matrix4x4 s_CreateOrthographicProjection(T clip_space_left,                                        // �����e�̎ˉe�s����쐬
                                                              T clip_space_right,
                                                              T clip_space_bottom,
                                                              T clip_space_top,
                                                              T near_clipping_plane = m_s_ORTHOGRAPHIC_2D_NEAR,
                                                              T far_clipping_plane = m_s_ORTHOGRAPHIC_2D_FAR);
            static S_Matrix4x4 s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& r_MATRIXS);                          // 3 * 3�s�񂩂�4 * 4�̍s��֕ϊ����A�擾
            static S_Matrix4x4 s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& r_QUATERNION);                     // �N�H�[�^�j�I������4 * 4�̍s��֕ϊ����A�擾
            static S_Matrix4x4 s_CreateViewport(T width, T height);                                                     // �r���[�|�[�g�s����쐬 
            static S_Matrix4x4 s_SlerpRotation(const S_Matrix4x4& r_START_MATRIX,                                       // ��]�s������ʐ��`���
                                               const S_Matrix4x4& r_END_MATRIX,
                                               T factor);

            /* S_Matrix4x4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Matrix4x4 operator+(const S_Matrix4x4& r_ANOTHER) const;                                            // +���Z�q�̃I�[�o�[���[�h
            const S_Matrix4x4 operator-(const S_Matrix4x4& r_ANOTHER) const;                                            // -���Z�q�̃I�[�o�[���[�h
            const S_Matrix4x4 operator*(const S_Matrix4x4& r_ANOTHER) const;                                            // *���Z�q�̃I�[�o�[���[�h
            const S_Matrix4x4& operator+=(const S_Matrix4x4& r_ANOTHER);                                                // +=���Z�q�̃I�[�o�[���[�h
            const S_Matrix4x4& operator-=(const S_Matrix4x4& r_ANOTHER);                                                // -=���Z�q�̃I�[�o�[���[�h
            const S_Matrix4x4& operator*=(const S_Matrix4x4& r_ANOTHER);                                                // *=���Z�q�̃I�[�o�[���[�h
            bool operator==(const S_Matrix4x4& r_ANOTHER) const;                                                        // ==���Z�q�̃I�[�o�[���[�h
            bool operator!=(const S_Matrix4x4& r_ANOTHER) const;                                                        // !=���Z�q�̃I�[�o�[���[�h

            /* S_Vector4�Ƃ̉��Z�q�̃I�[�o�[���[�h */
            const S_Vector4<T> operator*(const S_Vector4<T>& r_VECTOR) const;                                           // *���Z�q�̃I�[�o�[���[�h

            /* �L���X�g���Z�q�̃I�[�o�[���[�h */
            operator S_Matrix3x3<T>() const;                                                                            // S_Matrix3x3�^�ւ̃L���X�g
            operator String() const;                                                                                    // String�^�ւ̃L���X�g
        };


        /* �ʖ� */
        typedef S_Matrix4x4<float> Matrix4x4;                                                                           // Matrix4x4�^
    }
}