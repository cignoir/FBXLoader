/* �w�b�_�t�@�C�� */
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "..\Vector\Vector3.h"
#include "..\Quaternion\Quaternion.h"


// ���O��Ԃ��ȗ�
using namespace GALib::Math;


/* �v���g�^�C�v�錾 */
template<class T>
static T s_GetDeterminant(const S_Matrix3x3<T>& r_MATRIX);

template<class T>
static void s_Swap(T* p_a, T* p_b);


#pragma region �ÓI�����o�ϐ��̏�����


template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::m_s_ZERO(static_cast<T>(0));


template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::m_s_IDENTITY;


#pragma endregion


/* 

 @brief �R���X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3() :

    m_a_11(static_cast<T>(1)),
    m_a_12(0),
    m_a_13(0),

    m_a_21(0),
    m_a_22(static_cast<T>(1)),
    m_a_23(0),

    m_a_31(0),
    m_a_32(0),
    m_a_33(static_cast<T>(1))

{
}


/* 

 @brief     �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
 @param[in] value �l

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3(T value) :

    m_a_11(value),
    m_a_12(value),
    m_a_13(value),

    m_a_21(value),
    m_a_22(value),
    m_a_23(value),

    m_a_31(value),
    m_a_32(value),
    m_a_33(value)

{
}


/* 

 @brief     �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
 @param[in] a_11 �v�f1
 @param[in] a_12 �v�f2
 @param[in] a_13 �v�f3
 @param[in] a_21 �v�f4
 @param[in] a_22 �v�f5
 @param[in] a_23 �v�f6
 @param[in] a_31 �v�f7
 @param[in] a_32 �v�f8
 @param[in] a_33 �v�f9

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3(T a_11, T a_12, T a_13,
                            T a_21, T a_22, T a_23,
                            T a_31, T a_32, T a_33) :

    m_a_11(a_11),
    m_a_12(a_12),
    m_a_13(a_13),
            
    m_a_21(a_21),
    m_a_22(a_22),
    m_a_23(a_23),
            
    m_a_31(a_31),
    m_a_32(a_32),
    m_a_33(a_33)

{
}


/* 

 @brief     �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
 @param[in] ELEMENTS �v�f��9�̔z��

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3(const T ELEMENTS[9])
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] = ELEMENTS[i];
}


/* 

 @brief �f�X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Matrix3x3<T>::~S_Matrix3x3()
{
}


/* 

 @brief  �f�X�g���N�^
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::Zero()
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; i++)
    {
        this->m_elements[i] = 0;
    }
}


/* 

 @brief     �e�v�f�����̒l�ɕύX����
 @param[in] value �l
 @return    �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::Fill(T value)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; i++)
    {
        this->m_elements[i] = value;
    }
}


/* 

 @brief  �P�ʍs�񉻂���
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::Identity()
{
    this->m_a_11 = static_cast<T>(1);
    this->m_a_12 = 0;
    this->m_a_13 = 0;

    this->m_a_21 = 0;
    this->m_a_22 = static_cast<T>(1);
    this->m_a_23 = 0;

    this->m_a_31 = 0;
    this->m_a_32 = 0;
    this->m_a_33 = static_cast<T>(1);
}


/*

 @brief  �]�u�s�񉻂���
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::Transpose()
{
    ::s_Swap(&this->m_a_12, &this->m_a_21);
    ::s_Swap(&this->m_a_13, &this->m_a_31);
    ::s_Swap(&this->m_a_23, &this->m_a_32);
}


/*

 @brief  �t�s�񉻂���
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::Invert()
{
    // �s�񎮂��擾
    T determinant = ::s_GetDeterminant(*this);
    if (determinant == 0) return;

    // �s�񎮂̋t��
    T reciprocal_determinant = static_cast<T>(1) / determinant;

    // �t�s������߂�
    S_Matrix3x3 inverse_matrix;

    inverse_matrix.m_a_11 = (this->m_a_22 * this->m_a_33 - this->m_a_23 * this->m_a_32) * reciprocal_determinant;
    inverse_matrix.m_a_12 = (this->m_a_13 * this->m_a_32 - this->m_a_12 * this->m_a_33) * reciprocal_determinant;
    inverse_matrix.m_a_13 = (this->m_a_12 * this->m_a_23 - this->m_a_13 * this->m_a_22) * reciprocal_determinant;
    inverse_matrix.m_a_21 = (this->m_a_23 * this->m_a_31 - this->m_a_21 * this->m_a_33) * reciprocal_determinant;
    inverse_matrix.m_a_22 = (this->m_a_11 * this->m_a_33 - this->m_a_13 * this->m_a_31) * reciprocal_determinant;
    inverse_matrix.m_a_23 = (this->m_a_13 * this->m_a_21 - this->m_a_11 * this->m_a_23) * reciprocal_determinant;
    inverse_matrix.m_a_31 = (this->m_a_21 * this->m_a_32 - this->m_a_22 * this->m_a_31) * reciprocal_determinant;
    inverse_matrix.m_a_32 = (this->m_a_12 * this->m_a_31 - this->m_a_11 * this->m_a_32) * reciprocal_determinant;
    inverse_matrix.m_a_33 = (this->m_a_11 * this->m_a_22 - this->m_a_12 * this->m_a_21) * reciprocal_determinant;

    // �t�s�����
    (*this) = inverse_matrix;
}


/*

 @brief  �]�u�s����擾����
 @param  �Ȃ�
 @return S_Matrix3x3<T> �]�u�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::GetTranspose() const
{
    S_Matrix3x3 temp(*this);
    temp.Transpose();

    return temp;
}


/*

 @brief  �t�s����擾����
 @param  �Ȃ�
 @return S_Matrix3x3<T> �t�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::GetInvert() const
{
    S_Matrix3x3 temp(*this);
    temp.Invert();

    return temp;
}


/*

 @brief     �s���擾����
 @param[in] index �Y����
 @return    S_Matrix3x3<T> �s

*/
template<class T>
S_Vector3<T> S_Matrix3x3<T>::GetRow(Int32 index) const
{
    assert(index >= 0 && index < 3);
    return S_Vector3<T>(this->m_elements[index], this->m_elements[index + 3], this->m_elements[index + 6]);
}


/*

 @brief     ����擾����
 @param[in] index �Y����
 @return    S_Matrix3x3<T> ��

*/
template<class T>
S_Vector3<T> S_Matrix3x3<T>::GetColumn(Int32 index) const
{
    assert(index >= 0 && index < 3);

    index *= 3;
    return S_Vector3<T>(this->m_elements[index], this->m_elements[index + 1], this->m_elements[index + 2]);
}


/*

 @brief  �s��𕶎���Ƃ��Ď擾����
 @param  �Ȃ�
 @return String ������ɕϊ������s��

*/
template<class T>
String S_Matrix3x3<T>::ToString() const
{
    char buffer[1024];

    GALib_Sprintf(buffer, "| A11 : %10f, A21 : %10f, A31 : %10f |\n"
                          "| A12 : %10f, A22 : %10f, A32 : %10f |\n"
                          "| A13 : %10f, A23 : %10f, A33 : %10f |",
                          this->m_a_11, this->m_a_21, this->m_a_31,
                          this->m_a_12, this->m_a_22, this->m_a_32,
                          this->m_a_13, this->m_a_23, this->m_a_33);

    return buffer;
}


/*

 @brief     �s��ݒ肷��
 @param[in] r_ROW �s
 @param[in] index �Y����
 @return    �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::SetRow(const S_Vector3<T>& r_ROW, Int32 index)
{
    assert(index >= 0 && index < 3);
    for (Int32 i = 0; i < 3; ++i) this->m_elements[index + i * 3] = r_ROW.m_elements[i];
}


/*

 @brief     ���ݒ肷��
 @param[in] r_COLUMN ��
 @param[in] index    �Y����
 @return    �Ȃ�

*/
template<class T>
void S_Matrix3x3<T>::SetColumn(const S_Vector3<T>& r_COLUMN, Int32 index)
{
    assert(index >= 0 && index < 3);
    for (Int32 i = 0; i < 3; ++i) this->m_elements[index + i] = r_COLUMN.m_elements[i];
}


/*

 @brief     ��]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Matrix3x3<T> ��]�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotation(T angle)
{
    // ��]�s��
    S_Matrix3x3 rotation_matrix;

    // �T�C���ƃR�T�C�������߂�
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // ��]�s������߂�
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_12 = sine;
    rotation_matrix.m_a_21 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_22 = cosine;

    return rotation_matrix;
}


/*

 @brief     X�������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Matrix3x3<T> ��]�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationX(T angle)
{
    return s_CreateRotationZ(angle);
}


/*

 @brief     Y�������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Matrix3x3<T> ��]�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationY(T angle)
{
    // ��]�s��
    S_Matrix3x3 rotation_matrix;

    // �T�C���ƃR�T�C�������߂�
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // ��]�s������߂�
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_13 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_31 = sine;
    rotation_matrix.m_a_33 = cosine;

    return rotation_matrix;
}


/*

 @brief     Z�������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Matrix3x3<T> ��]�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationZ(T angle)
{
    // ��]�s��
    S_Matrix3x3 rotation_matrix;

    // �T�C���ƃR�T�C�������߂�
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // ��]�s������߂�
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_12 = sine;
    rotation_matrix.m_a_21 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_22 = cosine;

    return rotation_matrix;
}


/*

 @brief     �C�ӎ������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Matrix3x3<T> ��]�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // ��]�s��
    S_Matrix3x3 rotation_matrix;

    // �T�C���ƃR�T�C�������߂�
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // 1 - cosine �̒l�����߂�
    T one_minus_cosine = static_cast<T>(1) - cosine;

    // ���̊e�l�̃T�C�������߂�
    T axis_x_sine = r_AXIS.m_x * sine;
    T axis_y_sine = r_AXIS.m_y * sine;
    T axis_z_sine = r_AXIS.m_z * sine;

    // ���̐����� 1 - cosine ���������l�����߂�
    T one_minus_cosine_x = r_AXIS.m_x * one_minus_cosine;
    T one_minus_cosine_y = r_AXIS.m_y * one_minus_cosine;
    T one_minus_cosine_z = r_AXIS.m_z * one_minus_cosine;

    // ��]�s������߂�
    rotation_matrix.m_a_11 = (r_AXIS.m_x * one_minus_cosine_x) + cosine;
    rotation_matrix.m_a_21 = (r_AXIS.m_x * one_minus_cosine_y) - axis_z_sine;
    rotation_matrix.m_a_31 = (r_AXIS.m_x * one_minus_cosine_z) + axis_y_sine;

    rotation_matrix.m_a_12 = (r_AXIS.m_y * one_minus_cosine_x) + axis_z_sine;
    rotation_matrix.m_a_22 = (r_AXIS.m_y * one_minus_cosine_y) + cosine;
    rotation_matrix.m_a_32 = (r_AXIS.m_y * one_minus_cosine_z) - axis_x_sine;

    rotation_matrix.m_a_13 = (r_AXIS.m_z * one_minus_cosine_x) - axis_y_sine;
    rotation_matrix.m_a_23 = (r_AXIS.m_z * one_minus_cosine_y) + axis_x_sine;
    rotation_matrix.m_a_33 = (r_AXIS.m_z * one_minus_cosine_z) + cosine;

    return rotation_matrix;
}


/*

 @brief     �g�k�s����쐬����
 @param[in] rate_x X�����̊g�嗦
 @param[in] rate_y Y�����̊g�嗦
 @return    S_Matrix3x3<T> �g�k�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateScaling(T scaling_rate_x, T scaling_rate_y)
{
    S_Matrix3x3 scaling_matrix;

    scaling_matrix.m_a_11 = scaling_rate_x;
    scaling_matrix.m_a_22 = scaling_rate_y;

    return scaling_matrix;
}


/*

 @brief     �g�k�s����쐬����
 @param[in] r_SCALING_RATE �g�嗦
 @return    S_Matrix3x3<T> �g�k�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateScaling(const S_Vector2<T>& r_SCALING_RATE)
{
    S_Matrix3x3 scaling_matrix;

    scaling_matrix.m_a_11 = r_SCALING_RATE.m_x;
    scaling_matrix.m_a_22 = r_SCALING_RATE.m_y;

    return scaling_matrix;
}


/*

 @brief     ���s�ړ��s����쐬����
 @param[in] movement_x X�����̈ړ���
 @param[in] movement_y Y�����̈ړ���
 @return    S_Matrix3x3<T> ���s�ړ��s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTranslation(T movement_x, T movement_y)
{
    S_Matrix3x3 translation_matrix;

    translation_matrix.m_a_31 = movement_x;
    translation_matrix.m_a_32 = movement_y;

    return translation_matrix;
}


/*

 @brief     ���s�ړ��s����쐬����
 @param[in] r_MOVEMENT �ړ���
 @return    S_Matrix3x3<T> ���s�ړ��s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTranslation(const S_Vector2<T>& r_MOVEMENT)
{
    S_Matrix3x3 translation_matrix;

    translation_matrix.m_a_31 = r_MOVEMENT.m_x;
    translation_matrix.m_a_32 = r_MOVEMENT.m_y;

    return translation_matrix;
}


/*

 @brief     �g�k�E��]�E���s�ړ����|�����킹���s����쐬����
 @param[in] r_MOVEMENT �ړ���
 @return    S_Matrix3x3<T> ���s�ړ��s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTRS(const S_Vector2<T>& r_MOVEMENT,
                                           T angle,
                                           const S_Vector2<T>& r_SCALING_RATE)
{
    S_Matrix3x3 trs_matrix = s_CreateRotation(angle);

    trs_matrix.m_a_11 *= r_SCALING_RATE.m_x;
    trs_matrix.m_a_12 *= r_SCALING_RATE.m_x;

    trs_matrix.m_a_21 *= r_SCALING_RATE.m_y;
    trs_matrix.m_a_22 *= r_SCALING_RATE.m_y;

    trs_matrix.m_a_31 = r_MOVEMENT.m_x;
    trs_matrix.m_a_32 = r_MOVEMENT.m_y;

    return trs_matrix;
}


/*

 @brief     4 * 4�̍s���3 * 3�̍s��ɕϊ����A�擾����
 @param[in] r_MATRIX_4x4 4 * 4�̍s��
 @return    S_Matrix3x3<T> 3 * 3�̍s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& r_MATRIX_4x4)
{
    // �ϊ���̍s��
    S_Matrix3x3 convertion_matrix;

    // 4 * 4�s���3 * 3�ɕϊ�
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        Uint32 shift_index = i / 3;
        convertion_matrix.m_elements[i] = r_MATRIX_4x4.m_elements[i + shift_index];
    }

    return convertion_matrix;
}


/*

 @brief     �N�H�[�^�j�I����3 * 3�̍s��ɕϊ����A�擾����
 @param[in] r_QUATERNION �N�H�[�^�j�I��
 @return    S_Matrix3x3<T> 3 * 3�̍s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& r_QUATERNION)
{
    // �ϊ���̍s��
    S_Matrix3x3 convertion_matrix;

    // �e�����̊|�����킹���l�����߂�
    T xx = Square(r_QUATERNION.m_x);
    T xy = r_QUATERNION.m_x * r_QUATERNION.m_y;
    T xz = r_QUATERNION.m_x * r_QUATERNION.m_z;
    T xt = r_QUATERNION.m_x * r_QUATERNION.m_t;

    T yy = Square(r_QUATERNION.m_y);
    T yz = r_QUATERNION.m_y * r_QUATERNION.m_z;
    T yt = r_QUATERNION.m_y * r_QUATERNION.m_t;

    T zz = Square(r_QUATERNION.m_z);
    T zt = r_QUATERNION.m_z * r_QUATERNION.m_t;

    // �N�H�[�^�j�I����3 * 3�̍s��֕ϊ�
    convertion_matrix.m_a_11 = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
    convertion_matrix.m_a_12 = static_cast<T>(2) * (xy + zt);
    convertion_matrix.m_a_13 = static_cast<T>(2) * (xz - yt);

    convertion_matrix.m_a_21 = static_cast<T>(2) * (xy - zt);
    convertion_matrix.m_a_22 = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
    convertion_matrix.m_a_23 = static_cast<T>(2) * (yt + xt);

    convertion_matrix.m_a_31 = static_cast<T>(2) * (xz + yt);
    convertion_matrix.m_a_32 = static_cast<T>(2) * (yz - xt);
    convertion_matrix.m_a_33 = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);

    return convertion_matrix;
}


/*

 @brief     �@���s����쐬����
 @param[in] r_MATRIX 4 * 4�̍s��
 @return    S_Matrix3x3<T> �@���s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateNormal(const S_Matrix4x4<T>& r_MATRIX)
{
    S_Matrix3x3 normal_matrix(s_ConvertMatrix4x4ToMatrix3x3(r_MATRIX));

    normal_matrix.Invert();
    normal_matrix.Transpose();

    return normal_matrix;
}


/*

 @brief     �r���[�s����쐬����
 @param[in] r_EYE_POINT    ���_
 @param[in] r_TARGET_POINT �����_
 @param[in] r_UP_VECTOR    �����
 @return    S_Matrix3x3<T> �r���[�s��

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR)
{
    // �r���[�s��
    S_Matrix3x3 view_matrix;

    // Z�������߂�
    S_Vector3<T> z_axis = r_TARGET_POINT - r_EYE_POINT;
    z_axis.Normalize();

    // X�������߂�
    S_Vector3<T> x_axis = S_Vector3<T>::s_CrossProduct(z_axis, r_UP_VECTOR);
    x_axis.Normalize();

    // Y�������߂�
    S_Vector3<T> y_axis = S_Vector3<T>::s_CrossProduct(x_axis, z_axis);
    y_axis.Normalize();

    // Z���𔽓]����
    z_axis.Invert();

    // �r���[�s������߂�
    view_matrix.m_a_11 = x_axis.m_x;
    view_matrix.m_a_21 = x_axis.m_y;
    view_matrix.m_a_31 = x_axis.m_z;

    view_matrix.m_a_12 = y_axis.m_x;
    view_matrix.m_a_22 = y_axis.m_y;
    view_matrix.m_a_32 = y_axis.m_z;

    view_matrix.m_a_13 = z_axis.m_x;
    view_matrix.m_a_23 = z_axis.m_y;
    view_matrix.m_a_33 = z_axis.m_z;

    return view_matrix;
}


#pragma region S_Matrix3x3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/*

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    const S_Matrix3x3<T> ���Z�����s��

*/
template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::operator+(const S_Matrix3x3<T>& r_ANOTHER) const
{
    S_Matrix3x3 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] + r_ANOTHER.m_elements[i];

    return temp;
}


/*

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    const S_Matrix3x3<T> ���Z�����s��

*/
template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::operator-(const S_Matrix3x3<T>& r_ANOTHER) const
{
    S_Matrix3x3 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] - r_ANOTHER.m_elements[i];

    return temp;
}


/*

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    const S_Matrix3x3<T> ��Z�����s��

*/
template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::operator*(const S_Matrix3x3<T>& r_ANOTHER) const
{
    // ���̍s��
    S_Matrix3x3 temp;

    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // �e�s��̓Y���������߂�
        Uint32 index = i % 3;
        Uint32 another_index = (i / 3) * 3;

        // �s�񓯎m�̏�Z
        temp.m_elements[i] = this->m_elements[index]     * r_ANOTHER.m_elements[another_index]
                           + this->m_elements[index + 3] * r_ANOTHER.m_elements[another_index + 1]
                           + this->m_elements[index + 6] * r_ANOTHER.m_elements[another_index + 2];
    }

    return temp;
}


/*

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    const S_Matrix3x3<T>& ���Z�����s��

*/
template<class T>
const S_Matrix3x3<T>& S_Matrix3x3<T>::operator+=(const S_Matrix3x3<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] += r_ANOTHER.m_elements[i];

    return (*this);
}


/*

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    const S_Matrix3x3<T>& ���Z�����s��

*/
template<class T>
const S_Matrix3x3<T>& S_Matrix3x3<T>::operator-=(const S_Matrix3x3<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] -= r_ANOTHER.m_elements[i];

    return (*this);
}


/*

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    const S_Matrix3x3<T>& ��Z�����s��

*/
template<class T>
const S_Matrix3x3<T>& S_Matrix3x3<T>::operator*=(const S_Matrix3x3<T>& r_ANOTHER)
{
    // ���̍s��
    S_Matrix3x3 temp;

    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // �e�s��̓Y���������߂�
        Uint32 index = i % 3;
        Uint32 another_index = (i / 3) * 3;

        // �s�񓯎m�̏�Z
        temp.m_elements[i] = this->m_elements[index]     * r_ANOTHER.m_elements[another_index]
                           + this->m_elements[index + 3] * r_ANOTHER.m_elements[another_index + 1]
                           + this->m_elements[index + 6] * r_ANOTHER.m_elements[another_index + 2];
    }

    // ���̍s�����
    (*this) = temp;

    return (*this);
}


/*

 @brief     ���l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    bool  ��r��������
 @retval    true  �����s��̏ꍇ
 @retval    false �Ⴄ�s��̏ꍇ

*/
template<class T>
bool S_Matrix3x3<T>::operator==(const S_Matrix3x3<T>& r_ANOTHER) const
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        if (Absolute(this->m_elements[i] - r_ANOTHER.m_elements[i]) > GetEpsilon<T>()) return false;
    }

    return true;
}


/*

 @brief     �񓙒l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @return    bool  ��r��������
 @retval    true  �Ⴄ�s��̏ꍇ
 @retval    false �����s��̏ꍇ

*/
template<class T>
bool S_Matrix3x3<T>::operator!=(const S_Matrix3x3<T>& r_ANOTHER) const
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        if (Absolute(this->m_elements[i] - r_ANOTHER.m_elements[i]) > GetEpsilon<T>()) return true;
    }

    return false;
}


#pragma endregion


#pragma region S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/*

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_VACTOR 3D�x�N�g��
 @return    const S_Vector3<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Matrix3x3<T>::operator*(const S_Vector3<T>& r_VACTOR) const
{
    S_Vector3<T> temp_vactor;

    temp_vactor.m_x = this->m_a_11 * r_VACTOR.m_x
                   + this->m_a_21 * r_VACTOR.m_y
                   + this->m_a_31 * r_VACTOR.m_z;

    temp_vactor.m_y = this->m_a_12 * r_VACTOR.m_x
                   + this->m_a_22 * r_VACTOR.m_y
                   + this->m_a_32 * r_VACTOR.m_z;

    temp_vactor.m_z = this->m_a_13 * r_VACTOR.m_x
                   + this->m_a_23 * r_VACTOR.m_y
                   + this->m_a_33 * r_VACTOR.m_z;

    return temp_vactor;
}


#pragma endregion


#pragma region �L���X�g

/*

 @brief  String�^�ւ̃L���X�g
 @param  �Ȃ�
 @return String ������ɕϊ������s��

*/
template<class T>
S_Matrix3x3<T>::operator String() const
{
    return ToString();
}


#pragma endregion


/*

 @brief     �s�񎮂��擾����
 @param[in] r_MATRIX 3 * 3�s��
 @return    T �s��

*/
template<class T>
static T s_GetDeterminant(const S_Matrix3x3<T>& r_MATRIX)
{
    return (r_MATRIX.m_a_11 * r_MATRIX.m_a_22 * r_MATRIX.m_a_33)
         + (r_MATRIX.m_a_21 * r_MATRIX.m_a_32 * r_MATRIX.m_a_13)
         + (r_MATRIX.m_a_31 * r_MATRIX.m_a_12 * r_MATRIX.m_a_23)
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_32 * r_MATRIX.m_a_23)
         - (r_MATRIX.m_a_31 * r_MATRIX.m_a_22 * r_MATRIX.m_a_13)
         - (r_MATRIX.m_a_21 * r_MATRIX.m_a_12 * r_MATRIX.m_a_33);
}


/* 

 @brief     �l�̌������s��
 @param[in] p_a �l�̃|�C���^
 @param[in] p_b ����1�̒l�̃|�C���^
 @reutrn    �Ȃ�

*/ 
template<class T>
void s_Swap(T* p_a, T* p_b)
{
    T temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}


/* �����I�C���X�^���X�� */
template struct S_Matrix3x3<float>;
template struct S_Matrix3x3<double>;