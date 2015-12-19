/* �w�b�_�t�@�C�� */
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "..\Vector\Vector3.h"
#include "..\Vector\Vector4.h"
#include "..\Quaternion\Quaternion.h"


// ���O��Ԃ��ȗ�
using namespace GALib::Math;


/* �v���g�^�C�v�錾 */
template<class T>
static T s_GetDeterminant(const S_Matrix4x4<T>& r_MATRIX);

template<class T>
static void s_Swap(T* p_a, T* p_b);
    
    
#pragma region �ÓI�����o�ϐ��̏�����
    
    
template<class T>
const T S_Matrix4x4<T>::m_s_ORTHOGRAPHIC_2D_NEAR = static_cast<T>(-1);
    
    
template<class T>
const T S_Matrix4x4<T>::m_s_ORTHOGRAPHIC_2D_FAR = static_cast<T>(1);
    
    
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::m_s_ZERO(static_cast<T>(0));
    
    
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::m_s_IDENTITY;
    
    
#pragma endregion
    
    
/* 

 @brief �R���X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4() : 
    
    m_a_11(static_cast<T>(1)),
    m_a_12(0),
    m_a_13(0),
    m_a_14(0),
    
    m_a_21(0),
    m_a_22(static_cast<T>(1)),
    m_a_23(0),
    m_a_24(0),
    
    m_a_31(0),
    m_a_32(0),
    m_a_33(static_cast<T>(1)),
    m_a_34(0),
    
    m_a_41(0),
    m_a_42(0),
    m_a_43(0),
    m_a_44(static_cast<T>(1))
    
{
}
    
    
/* 

 @brief     �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
 @param[in] value �l

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(T value) :

    m_a_11(value),
    m_a_12(value),
    m_a_13(value),
    m_a_14(value),
    
    m_a_21(value),
    m_a_22(value),
    m_a_23(value),
    m_a_24(value),
    
    m_a_31(value),
    m_a_32(value),
    m_a_33(value),
    m_a_34(value),
    
    m_a_41(value),
    m_a_42(value),
    m_a_43(value),
    m_a_44(value)


{
}
    
    
/* 

 @brief     �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
 @param[in] �v�f1
 @param[in] �v�f2
 @param[in] �v�f3
 @param[in] �v�f4
 @param[in] �v�f5
 @param[in] �v�f6
 @param[in] �v�f7
 @param[in] �v�f8
 @param[in] �v�f9
 @param[in] �v�f10
 @param[in] �v�f11
 @param[in] �v�f12
 @param[in] �v�f13
 @param[in] �v�f14
 @param[in] �v�f15
 @param[in] �v�f16

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(T a_11, T a_12, T a_13, T a_14,
                            T a_21, T a_22, T a_23, T a_24,
                            T a_31, T a_32, T a_33, T a_34,
                            T a_41, T a_42, T a_43, T a_44) :
    
    m_a_11(a_11),
    m_a_12(a_12),
    m_a_13(a_13),
    m_a_14(a_14),
    
    m_a_21(a_21),
    m_a_22(a_22),
    m_a_23(a_23),
    m_a_24(a_24),
    
    m_a_31(a_31),
    m_a_32(a_32),
    m_a_33(a_33),
    m_a_34(a_34),
    
    m_a_41(a_41),
    m_a_42(a_42),
    m_a_43(a_43),
    m_a_44(a_44)
    
{
}
    
   
/* 

 @brief     �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
 @param[in] ELEMENTS �v�f��16�̔z��

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(const T ELEMENTS[m_s_ELEMENT_COUNT])
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) m_elements[i] = ELEMENTS[i];
}
    
   
/* 

 @brief     �R���X�g���N�^( 3 * 3�s��ŗv�f�̏����� )
 @param[in] r_MATRIX 3 * 3�s��

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(const S_Matrix3x3<T>& r_MATRIX)
{
    *this = s_ConvertMatrix3x3ToMatrix4x4(r_MATRIX);
}
    
    
/* 

 @brief     �f�X�g���N�^
 @param[in] �Ȃ�

*/
template<class T>
S_Matrix4x4<T>::~S_Matrix4x4()
{
}
    
    
/* 

 @brief  �[���s�񉻂���
 @param  �Ȃ�
 @reutrn �Ȃ�

*/
template<class T>
void S_Matrix4x4<T>::Zero()
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; i++) m_elements[i] = 0;
}
    
    
/* 

 @brief  �P�ʍs�񉻂���
 @param  �Ȃ�
 @reutrn �Ȃ�

*/
template<class T>
void S_Matrix4x4<T>::Identity()
{
    this->m_a_11 = static_cast<T>(1);
    this->m_a_12 = 0;
    this->m_a_13 = 0;
    this->m_a_14 = 0;
    
    this->m_a_21 = 0;
    this->m_a_22 = static_cast<T>(1);
    this->m_a_23 = 0;
    this->m_a_24 = 0;
    
    this->m_a_31 = 0;
    this->m_a_32 = 0;
    this->m_a_33 = static_cast<T>(1);
    this->m_a_34 = 0;
    
    this->m_a_41 = 0;
    this->m_a_42 = 0;
    this->m_a_43 = 0;
    this->m_a_44 = static_cast<T>(1);
}
    
 
/* 

 @brief  �]�u�s�񉻂���
 @param  �Ȃ�
 @reutrn �Ȃ�

*/
template<class T>
void S_Matrix4x4<T>::Transpose()
{
    s_Swap(&this->m_a_12, &this->m_a_21);
    s_Swap(&this->m_a_13, &this->m_a_31);
    s_Swap(&this->m_a_14, &this->m_a_41);
    s_Swap(&this->m_a_23, &this->m_a_32);
    s_Swap(&this->m_a_24, &this->m_a_42);
    s_Swap(&this->m_a_34, &this->m_a_43);
}
    
    
/* 

 @brief  �t�s�񉻂���
 @param  �Ȃ�
 @reutrn �Ȃ�

*/
template<class T>
void S_Matrix4x4<T>::Invert()
{
    // �s�񎮂��擾
    T determinant = s_GetDeterminant(*this);
    if (determinant == 0) return;
    
    // �s�񎮂̋t��
    T reciprocal_determinant = static_cast<T>(1) / determinant;
    
    // �t�s������߂�
    S_Matrix4x4 inverse_matrix;

    inverse_matrix.m_a_11 = ((this->m_a_22 * this->m_a_33 * this->m_a_44) + (this->m_a_23 * this->m_a_34 * this->m_a_42) + (this->m_a_24 * this->m_a_32 * this->m_a_43)
                          -  (this->m_a_22 * this->m_a_34 * this->m_a_43) - (this->m_a_23 * this->m_a_32 * this->m_a_44) - (this->m_a_24 * this->m_a_33 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_12 = ((this->m_a_12 * this->m_a_34 * this->m_a_43) + (this->m_a_13 * this->m_a_32 * this->m_a_44) + (this->m_a_14 * this->m_a_33 * this->m_a_42)
                          -  (this->m_a_12 * this->m_a_33 * this->m_a_44) - (this->m_a_13 * this->m_a_34 * this->m_a_42) - (this->m_a_14 * this->m_a_32 * this->m_a_43)) * reciprocal_determinant;
    
    inverse_matrix.m_a_13 = ((this->m_a_12 * this->m_a_23 * this->m_a_44) + (this->m_a_13 * this->m_a_24 * this->m_a_42) + (this->m_a_14 * this->m_a_22 * this->m_a_43)
                          -  (this->m_a_12 * this->m_a_24 * this->m_a_43) - (this->m_a_13 * this->m_a_22 * this->m_a_44) - (this->m_a_14 * this->m_a_23 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_14 = ((this->m_a_12 * this->m_a_24 * this->m_a_33) + (this->m_a_13 * this->m_a_22 * this->m_a_34) + (this->m_a_14 * this->m_a_23 * this->m_a_32)
                          -  (this->m_a_12 * this->m_a_23 * this->m_a_34) - (this->m_a_13 * this->m_a_24 * this->m_a_32) - (this->m_a_14 * this->m_a_22 * this->m_a_33)) * reciprocal_determinant;
    
    inverse_matrix.m_a_21 = ((this->m_a_21 * this->m_a_34 * this->m_a_43) + (this->m_a_23 * this->m_a_31 * this->m_a_44) + (this->m_a_24 * this->m_a_33 * this->m_a_41)
                          -  (this->m_a_21 * this->m_a_33 * this->m_a_44) - (this->m_a_23 * this->m_a_34 * this->m_a_41) - (this->m_a_24 * this->m_a_31 * this->m_a_43)) * reciprocal_determinant;
    
    inverse_matrix.m_a_22 = ((this->m_a_11 * this->m_a_33 * this->m_a_44) + (this->m_a_13 * this->m_a_34 * this->m_a_41) + (this->m_a_14 * this->m_a_31 * this->m_a_43)
                          -  (this->m_a_11 * this->m_a_34 * this->m_a_43) - (this->m_a_13 * this->m_a_31 * this->m_a_44) - (this->m_a_14 * this->m_a_33 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_23 = ((this->m_a_11 * this->m_a_24 * this->m_a_43) + (this->m_a_13 * this->m_a_21 * this->m_a_44) + (this->m_a_14 * this->m_a_23 * this->m_a_41)
                          -  (this->m_a_11 * this->m_a_23 * this->m_a_44) - (this->m_a_13 * this->m_a_24 * this->m_a_41) - (this->m_a_14 * this->m_a_21 * this->m_a_43)) * reciprocal_determinant;
    
    inverse_matrix.m_a_24 = ((this->m_a_11 * this->m_a_23 * this->m_a_34) + (this->m_a_13 * this->m_a_24 * this->m_a_31) + (this->m_a_14 * this->m_a_21 * this->m_a_33)
                          -  (this->m_a_11 * this->m_a_24 * this->m_a_33) - (this->m_a_13 * this->m_a_21 * this->m_a_34) - (this->m_a_14 * this->m_a_23 * this->m_a_31)) * reciprocal_determinant;
    
    inverse_matrix.m_a_31 = ((this->m_a_21 * this->m_a_32 * this->m_a_44) + (this->m_a_22 * this->m_a_34 * this->m_a_41) + (this->m_a_24 * this->m_a_31 * this->m_a_42)
                          -  (this->m_a_21 * this->m_a_34 * this->m_a_42) - (this->m_a_22 * this->m_a_31 * this->m_a_44) - (this->m_a_24 * this->m_a_32 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_32 = ((this->m_a_11 * this->m_a_34 * this->m_a_42) + (this->m_a_12 * this->m_a_31 * this->m_a_44) + (this->m_a_14 * this->m_a_32 * this->m_a_41)
                          -  (this->m_a_11 * this->m_a_32 * this->m_a_44) - (this->m_a_12 * this->m_a_34 * this->m_a_41) - (this->m_a_14 * this->m_a_31 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_33 = ((this->m_a_11 * this->m_a_22 * this->m_a_44) + (this->m_a_12 * this->m_a_24 * this->m_a_41) + (this->m_a_14 * this->m_a_21 * this->m_a_42)
                          -  (this->m_a_11 * this->m_a_24 * this->m_a_42) - (this->m_a_12 * this->m_a_21 * this->m_a_44) - (this->m_a_14 * this->m_a_22 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_34 = ((this->m_a_11 * this->m_a_24 * this->m_a_32) + (this->m_a_12 * this->m_a_21 * this->m_a_34) + (this->m_a_14 * this->m_a_22 * this->m_a_31)
                          -  (this->m_a_11 * this->m_a_22 * this->m_a_34) - (this->m_a_12 * this->m_a_24 * this->m_a_31) - (this->m_a_14 * this->m_a_21 * this->m_a_32)) * reciprocal_determinant;
    
    inverse_matrix.m_a_41 = ((this->m_a_21 * this->m_a_33 * this->m_a_42) + (this->m_a_22 * this->m_a_31 * this->m_a_43) + (this->m_a_23 * this->m_a_32 * this->m_a_41)
                          -  (this->m_a_21 * this->m_a_32 * this->m_a_43) - (this->m_a_22 * this->m_a_33 * this->m_a_41) - (this->m_a_23 * this->m_a_31 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_42 = ((this->m_a_11 * this->m_a_32 * this->m_a_43) + (this->m_a_12 * this->m_a_33 * this->m_a_41) + (this->m_a_13 * this->m_a_31 * this->m_a_42)
                          -  (this->m_a_11 * this->m_a_33 * this->m_a_42) - (this->m_a_12 * this->m_a_31 * this->m_a_43) - (this->m_a_13 * this->m_a_32 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_43 = ((this->m_a_11 * this->m_a_23 * this->m_a_42) + (this->m_a_12 * this->m_a_21 * this->m_a_43) + (this->m_a_13 * this->m_a_22 * this->m_a_41)
                          -  (this->m_a_11 * this->m_a_22 * this->m_a_43) - (this->m_a_12 * this->m_a_23 * this->m_a_41) - (this->m_a_13 * this->m_a_21 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_44 = ((this->m_a_11 * this->m_a_22 * this->m_a_33) + (this->m_a_12 * this->m_a_23 * this->m_a_31) + (this->m_a_13 * this->m_a_21 * this->m_a_32)
                          -  (this->m_a_11 * this->m_a_23 * this->m_a_32) - (this->m_a_12 * this->m_a_21 * this->m_a_33) - (this->m_a_13 * this->m_a_22 * this->m_a_31)) * reciprocal_determinant;
       
    // �t�s�����
    (*this) = inverse_matrix;
}
    
    
/* 

 @brief  �]�u�s����擾����
 @param  �Ȃ�
 @reutrn S_Matrix4x4<T> �]�u�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::GetTranspose() const
{
    S_Matrix4x4 temp(*this);
    temp.Transpose();
    
    return temp;
}


/* 

 @brief  �t�s����擾����
 @param  �Ȃ�
 @reutrn S_Matrix4x4<T> �t�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::GetInvert() const
{
    S_Matrix4x4 temp(*this);
    temp.Invert();
    
    return temp;
}


/* 

 @brief  �ړ���( ���s�ړ����� )���擾����
 @param  �Ȃ�
 @reutrn S_Vector3<T> �ړ���

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetTranslationComponent() const
{
    return S_Vector3<T>(this->m_a_41, this->m_a_42, this->m_a_43);
}


/* 

 @brief  �g�k��( �g�k���� )���擾����
 @param  �Ȃ�
 @reutrn S_Vector3<T> �g�k����

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetScalingComponent() const
{
    S_Vector3<T> scaling_component;

    scaling_component.m_x = S_Vector3<T>(this->m_a_11, this->m_a_12, this->m_a_13).GetMagnitude();
    scaling_component.m_y = S_Vector3<T>(this->m_a_21, this->m_a_22, this->m_a_23).GetMagnitude();
    scaling_component.m_z = S_Vector3<T>(this->m_a_31, this->m_a_32, this->m_a_33).GetMagnitude();

    return scaling_component;
}


/* 

 @brief  ���[�J�����W��X�����擾����
 @param  �Ȃ�
 @reutrn S_Vector3<T> ���[�J�����W��X��

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisX() const
{
    return S_Vector3<T>(this->m_a_11, this->m_a_12, this->m_a_13).GetNormalize();
}


/* 

 @brief  ���[�J�����W��Y�����擾����
 @param  �Ȃ�
 @reutrn S_Vector3<T> ���[�J�����W��Y��

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisY() const
{
    return S_Vector3<T>(this->m_a_21, this->m_a_22, this->m_a_23).GetNormalize();
}


/* 

 @brief  ���[�J�����W��Z�����擾����
 @param  �Ȃ�
 @reutrn S_Vector3<T> ���[�J�����W��Z��

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisZ() const
{
    return S_Vector3<T>(this->m_a_31, this->m_a_32, this->m_a_33).GetNormalize();
}
    
    
/* 

 @brief     �s���擾����
 @param[in] index �Y����
 @reutrn    S_Vector3<T> �s

*/
template<class T>
S_Vector4<T> S_Matrix4x4<T>::GetRow(Int32 index) const
{
    assert(index >= 0 && index < 4);
    return S_Vector4<T>(this->m_elements[index], this->m_elements[index + 4], this->m_elements[index + 8], this->m_elements[index + 12]);
}
    
    
    
/* 

 @brief     ����擾����
 @param[in] index �Y����
 @reutrn    S_Vector3<T> ��

*/
template<class T>
S_Vector4<T> S_Matrix4x4<T>::GetColumn(Int32 index) const
{
    assert(index >= 0 && index < 4);
    index *= 4;
    return S_Vector4<T>(this->m_elements[index], this->m_elements[index + 1], this->m_elements[index + 2], this->m_elements[index + 3]);
}
    
    
/* 

 @brief  �s��𕶎���ɕϊ����Ď擾����
 @param  �Ȃ�
 @reutrn String ��

*/
template<class T>
String S_Matrix4x4<T>::ToString() const
{
    char buffer[1024];
    
    GALib_Sprintf(buffer, "| A11 : %10f, A21 : %10f, A31 : %10f, A41 : %10f |\n"
                          "| A12 : %10f, A22 : %10f, A32 : %10f, A42 : %10f |\n"
                          "| A13 : %10f, A23 : %10f, A33 : %10f, A43 : %10f |\n"
                          "| A14 : %10f, A24 : %10f, A34 : %10f, A44 : %10f |",
                          this->m_a_11, this->m_a_21, this->m_a_31, this->m_a_41,
                          this->m_a_12, this->m_a_22, this->m_a_32, this->m_a_42,
                          this->m_a_13, this->m_a_23, this->m_a_33, this->m_a_43,
                          this->m_a_14, this->m_a_24, this->m_a_34, this->m_a_44);

    return buffer;
}
    
    
/* 

 @brief     �s��ݒ肷��
 @param[in] r_ROW �s
 @param[in] index �Y����
 @reutrn    �Ȃ�

*/
template<class T>
void S_Matrix4x4<T>::SetRow(const S_Vector4<T>& r_ROW, Int32 index)
{
    assert(index >= 0 && index < 4);
    for (Int32 i = 0; i < 4; ++i) this->m_elements[index + i * 4] = r_ROW.m_elements[i];
}
    
    
/* 

 @brief     ���ݒ肷��
 @param[in] r_ROW ��
 @param[in] index �Y����
 @reutrn    �Ȃ�

*/
template<class T>
void S_Matrix4x4<T>::SetColumn(const S_Vector4<T>& r_COLUMN, Int32 index)
{
    assert(index >= 0 && index < 4);
    for (Int32 i = 0; i < 4; ++i) this->m_elements[index + i] = r_COLUMN.m_elements[i];
}
    
    
/* 

 @brief     X�������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @reutrn    S_Matrix4x4<T> ��]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationX(T angle)
{
    S_Matrix4x4 rotation_matrix;
    
    T sine = Sine(angle);
    T cosine = Cosine(angle);
    
    rotation_matrix.m_a_22 = cosine;
    rotation_matrix.m_a_23 = sine;
    rotation_matrix.m_a_32 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_33 = cosine;
    
    return rotation_matrix;
}
    
    
/* 

 @brief     Y�������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @reutrn    S_Matrix4x4<T> ��]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationY(T angle)
{
    S_Matrix4x4 rotation_matrix;
    
    T sine = Sine(angle);
    T cosine = Cosine(angle);
    
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_13 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_31 = sine;
    rotation_matrix.m_a_33 = cosine;
    
    return rotation_matrix;
}
    
    
/* 

 @brief     Z�������]�s����쐬����
 @param[in] angle �p�x( ���W�A���l )
 @reutrn    S_Matrix4x4<T> ��]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationZ(T angle)
{
    S_Matrix4x4 rotation_matrix;
    
    T sine = Sine(angle);
    T cosine = Cosine(angle);
    
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_12 = sine;
    rotation_matrix.m_a_21 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_22 = cosine;
    
    return rotation_matrix;
}
    
    
/* 

 @brief     �C�ӎ������]�s����쐬����
 @param[in] r_AXIS ��
 @param[in] angle  �p�x( ���W�A���l )
 @reutrn    S_Matrix4x4<T> ��]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // ��]�s��
    S_Matrix4x4 rotation_matrix;
    
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

 @brief     3���̉�]�s����|�����킹���s����쐬����
 @param[in] pitch �s�b�`( X���̊p�x�E���W�A���l )
 @param[in] yaw   ���[( Y���̊p�x�E���W�A���l )
 @param[in] roll  ���[��( Z���̊p�x�E���W�A���l 
 @reutrn    S_Matrix4x4<T> ��]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationYawPitchRoll(T pitch,
                                                            T yaw,
                                                            T roll)
{
    S_Quaternion<T> rotation_quaternion = S_Quaternion<T>::s_CreateRotationPitchYawRoll(pitch, yaw, roll);
    return s_ConvertQuaternionToMatrix4x4(rotation_quaternion);
}
    
    
/* 

 @brief     3���̉�]�s����|�����킹���s����쐬����
 @param[in] r_ROTATION 3�����̉�]��
 @reutrn    S_Matrix4x4<T> ��]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationYawPitchRoll(const S_Vector3<T>& r_ROTATION)
{
    S_Quaternion<T> rotationQuaternion = S_Quaternion<T>::s_CreateRotationPitchYawRoll(r_ROTATION);
    return s_ConvertQuaternionToMatrix4x4(rotationQuaternion);
}
    
    
/* 

 @brief     �g�k�s����쐬����
 @param[in] scaling_rate_x X�����̊g�k��
 @param[in] scaling_rate_y Y�����̊g�k��
 @param[in] scaling_rate_z Z�����̊g�k��
 @reutrn    S_Matrix4x4<T> �g�k�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateScaling(T scaling_rate_x, T scaling_rate_y, T scaling_rate_z)
{
    S_Matrix4x4 scaling_matrix;
    
    scaling_matrix.m_a_11 = scaling_rate_x;
    scaling_matrix.m_a_22 = scaling_rate_y;
    scaling_matrix.m_a_33 = scaling_rate_z;
    
    return scaling_matrix;
}
    
    
/* 

 @brief     �g�k�s����쐬����
 @param[in] r_SCALING_RATE 3�����̊g�k��
 @reutrn    S_Matrix4x4<T> �g�k�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateScaling(const S_Vector3<T>& r_SCALING_RATE)
{
    return s_CreateScaling(r_SCALING_RATE.m_x, r_SCALING_RATE.m_y, r_SCALING_RATE.m_z);
}
    
    
/* 

 @brief     ���s�ړ��s����쐬����
 @param[in] movement_x X�����̈ړ���
 @param[in] movement_y Y�����̈ړ���
 @param[in] movement_z Z�����̈ړ���
 @reutrn    S_Matrix4x4<T> ���s�ړ��s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTranslation(T movement_x, T movement_y, T movement_z)
{
    S_Matrix4x4 translation_matrix;
    
    translation_matrix.m_a_41 = movement_x;
    translation_matrix.m_a_42 = movement_y;
    translation_matrix.m_a_43 = movement_z;
    
    return translation_matrix;
}
    
    
/* 

 @brief     ���s�ړ��s����쐬����
 @param[in] r_MOVEMENT 3�����̈ړ���
 @reutrn    S_Matrix4x4<T> ���s�ړ��s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTranslation(const S_Vector3<T>& r_MOVEMENT)
{
    return s_CreateTranslation(r_MOVEMENT.m_x, r_MOVEMENT.m_y, r_MOVEMENT.m_z);
}
    
    
/* 

 @brief     �g�k�E��]�E���s�ړ����|�����킹���s����쐬
 @param[in] r_MOVEMENT     3�����̈ړ���
 @param[in] r_ROTATION     3�����̉�]��
 @param[in] r_SCALING_RATE 3�����̊g�k��
 @reutrn    S_Matrix4x4<T> �A�t�B���ϊ��s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTRS(const S_Vector3<T>& r_MOVEMENT, 
                                           const S_Vector3<T>& r_ROTATION, 
                                           const S_Vector3<T>& r_SCALING_RATE)
{
    S_Matrix4x4 trs_matrix = s_CreateRotationYawPitchRoll(r_ROTATION);

    trs_matrix.m_a_11 *= r_SCALING_RATE.m_x;
    trs_matrix.m_a_12 *= r_SCALING_RATE.m_x;
    trs_matrix.m_a_13 *= r_SCALING_RATE.m_x;

    trs_matrix.m_a_21 *= r_SCALING_RATE.m_y;
    trs_matrix.m_a_22 *= r_SCALING_RATE.m_y;
    trs_matrix.m_a_23 *= r_SCALING_RATE.m_y;

    trs_matrix.m_a_31 *= r_SCALING_RATE.m_z;
    trs_matrix.m_a_32 *= r_SCALING_RATE.m_z;
    trs_matrix.m_a_33 *= r_SCALING_RATE.m_z;
    
    trs_matrix.m_a_41 = r_MOVEMENT.m_x;
    trs_matrix.m_a_42 = r_MOVEMENT.m_y;
    trs_matrix.m_a_43 = r_MOVEMENT.m_z;
    
    return trs_matrix;
}
    
    
/* 

 @brief     �r���[�s����쐬����
 @param[in] r_EYE_POINT    ���_
 @param[in] r_TARGET_POINT �����_
 @param[in] r_UP_VECTOR    ������������x�N�g��
 @reutrn    S_Matrix4x4<T> �r���[�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR)
{
    // �r���[�s��
    S_Matrix4x4 view_matrix;
    
    // Z�������߂�
    S_Vector3<T> z_axis = r_TARGET_POINT - r_EYE_POINT;
    z_axis.Normalize();
    
    // X�������߂�
    S_Vector3<T> x_axis = S_Vector3<T>::s_CrossProduct(z_axis, r_UP_VECTOR);
    x_axis.Normalize();
    
    // Y�������߂�
    S_Vector3<T> y_axis = S_Vector3<T>::s_CrossProduct(x_axis, z_axis);
    y_axis.Normalize();
    
    // ���_�𔽓]�����x�N�g��
    S_Vector3<T> inversion_eye_vector(r_EYE_POINT.GetInvert());
    
    // Z���𔽓]����
    z_axis.Invert();
    
    // �r���[�s������߂�
    view_matrix.m_a_11 = x_axis.m_x;
    view_matrix.m_a_21 = x_axis.m_y;
    view_matrix.m_a_31 = x_axis.m_z;
    view_matrix.m_a_41 = S_Vector3<T>::s_DotProduct(x_axis, inversion_eye_vector);
    
    view_matrix.m_a_12 = y_axis.m_x;
    view_matrix.m_a_22 = y_axis.m_y;
    view_matrix.m_a_32 = y_axis.m_z;
    view_matrix.m_a_42 = S_Vector3<T>::s_DotProduct(y_axis, inversion_eye_vector);
      
    view_matrix.m_a_13 = z_axis.m_x;
    view_matrix.m_a_23 = z_axis.m_y;
    view_matrix.m_a_33 = z_axis.m_z;
    view_matrix.m_a_43 = S_Vector3<T>::s_DotProduct(z_axis, inversion_eye_vector);
    
    return view_matrix;
}
    
    
/* 

 @brief     �������e�̎ˉe�s����쐬����
 @param[in] field_of_view_y     ����̐��������̉�p( ���W�A���l )
 @param[in] aspect_ratio        �A�X�y�N�g��
 @param[in] near_clipping_plane ���_����ł��߂��N���b�v��( ���� )
 @param[in] far_clipping_plane  ���_����ł������N���b�v��( ���� )
 @reutrn    S_Matrix4x4<T> �������e�̎ˉe�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreatePerspectiveProjection(T field_of_view_y,
                                                             T aspect_ratio,
                                                             T near_clipping_plane,
                                                             T far_clipping_plane)
{
    assert(field_of_view_y != 0);
    assert(aspect_ratio > 0);
    assert(far_clipping_plane != near_clipping_plane);
    
    // �������e�̎ˉe�s��
    S_Matrix4x4 perspective_projection_matrix;
    
    // ����̐��������̉�p�̔��������߂�
    T half_field_of_view_y = field_of_view_y * static_cast<T>(0.5);
    
    // �t�@�[�N���b�s���O�v���[���ƃj�A�N���b�s���O�v���[���̍��������߂�
    T plane_difference = near_clipping_plane - far_clipping_plane;
    
    // ����̐��������̉�p�̔����̗]�������߂�
    T cot_half_fov_y = Cotangent(half_field_of_view_y);
    
    // �������e�̎ˉe�s������߂�
    perspective_projection_matrix.m_a_11 = cot_half_fov_y / aspect_ratio;
    perspective_projection_matrix.m_a_22 = cot_half_fov_y;
    perspective_projection_matrix.m_a_33 = (far_clipping_plane + near_clipping_plane) / plane_difference;
    perspective_projection_matrix.m_a_34 = static_cast<T>(-1);
    perspective_projection_matrix.m_a_43 = static_cast<T>(2) * near_clipping_plane * far_clipping_plane / plane_difference;
    
    return perspective_projection_matrix;
}
    
    
/* 

 @brief     �����e�̎ˉe�s����쐬����
 @param[in] clip_space_left     �N���b�v��Ԃ̍���
 @param[in] clip_space_right    �N���b�v��Ԃ̉E��
 @param[in] clip_space_bottom   �N���b�v��Ԃ̉���
 @param[in] clip_space_top      �N���b�v��Ԃ̏㑤
 @param[in] near_clipping_plane ���_����ł��߂��N���b�v��( ���� )
 @param[in] far_clipping_plane  ���_����ł������N���b�v��( ���� )
 @reutrn    S_Matrix4x4<T> �����e�̎ˉe�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateOrthographicProjection(T clip_space_left,             
                                                              T clip_space_right,
                                                              T clip_space_bottom,
                                                              T clip_space_top,
                                                              T near_clipping_plane,
                                                              T far_clipping_plane)
{                                                                            
    assert(clip_space_right != clip_space_left);
    assert(clip_space_top != clip_space_bottom);
    assert(near_clipping_plane != far_clipping_plane);
    
    // �����e�̎ˉe�s��
    S_Matrix4x4 orthographic_projection_matrix;
    
    // �N���b�v��Ԃ̕��ƍ����Ɖ��s�����߂�
    T clip_space_width = clip_space_right - clip_space_left;
    T clip_space_height = clip_space_top - clip_space_bottom;
    T clip_space_depth = far_clipping_plane - near_clipping_plane;
    
    // �����e�̎ˉe�s������߂�
    orthographic_projection_matrix.m_a_11 = static_cast<T>(2) / clip_space_width;
    orthographic_projection_matrix.m_a_22 = static_cast<T>(2) / clip_space_height;
    orthographic_projection_matrix.m_a_33 = T(-2) / clip_space_depth;
    
    orthographic_projection_matrix.m_a_41 = -((clip_space_right + clip_space_left) / clip_space_width);
    orthographic_projection_matrix.m_a_42 = -((clip_space_top + clip_space_bottom) / clip_space_height);
    orthographic_projection_matrix.m_a_43 = -((far_clipping_plane + near_clipping_plane) / clip_space_depth);
    
    return orthographic_projection_matrix;
}
    
    
/* 

 @brief     3 * 3�s���4 * 4�̍s��ɕϊ����A�擾����
 @param[in] r_MATRIX 3 * 3�s��
 @reutrn    S_Matrix4x4<T> 4 * 4�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& r_MATRIX)
{
    S_Matrix4x4 convertion_matrix;
    
    convertion_matrix.m_a_11 = r_MATRIX.m_a_11;
    convertion_matrix.m_a_12 = r_MATRIX.m_a_12;
    convertion_matrix.m_a_13 = r_MATRIX.m_a_13;
    
    convertion_matrix.m_a_21 = r_MATRIX.m_a_21;
    convertion_matrix.m_a_22 = r_MATRIX.m_a_22;
    convertion_matrix.m_a_23 = r_MATRIX.m_a_23;
    
    convertion_matrix.m_a_31 = r_MATRIX.m_a_31;
    convertion_matrix.m_a_32 = r_MATRIX.m_a_32;
    convertion_matrix.m_a_33 = r_MATRIX.m_a_33;

    return convertion_matrix;
}
    
    
/* 

 @brief     �N�H�[�^�j�I����4 * 4�̍s��ɕϊ����A�擾����
 @param[in] r_MATRIX �N�H�[�^�j�I��
 @reutrn    S_Matrix4x4<T> 4 * 4�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& r_QUATERNION)
{
    // �ϊ���̍s��
    S_Matrix4x4 convertion_matrix;
    
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
    
    // �N�H�[�^�j�I����4 * 4�̍s��֕ϊ�
    convertion_matrix.m_a_11 = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
    convertion_matrix.m_a_12 = static_cast<T>(2) * (xy + zt);
    convertion_matrix.m_a_13 = static_cast<T>(2) * (xz - yt);
    
    convertion_matrix.m_a_21 = static_cast<T>(2) * (xy - zt);
    convertion_matrix.m_a_22 = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
    convertion_matrix.m_a_23 = static_cast<T>(2) * (yz + xt);
    
    convertion_matrix.m_a_31 = static_cast<T>(2) * (xz + yt);
    convertion_matrix.m_a_32 = static_cast<T>(2) * (yz - xt);
    convertion_matrix.m_a_33 = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);
    
    return convertion_matrix;
}
    
    
/* 

 @brief     �r���[�|�[�g�s����쐬����
 @param[in] window_width  �E�B���h�E�̕�
 @param[in] window_height �E�B���h�E�̍���
 @reutrn    S_Matrix4x4<T> �r���[�|�[�g�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateViewport(T window_width, T window_height)
{
    // �E�B���h�E�̕��ƍ����̔���
    T half_width = window_width * static_cast<T>(0.5);
    T half_height = window_height * static_cast<T>(0.5);
    
    // �r���[�|�[�g�s��
    S_Matrix4x4 viewport_matrix(half_width,           0,                 0,                0,
                                         0, half_height,                 0,                0,
                                         0,           0, static_cast<T>(1),                0,
                                half_width, half_height,                 0, static_cast<T>(1));
    
    return viewport_matrix;
}
    
    
/* 

 @brief     ��]�s������ʐ��`��Ԃ���
 @param[in] r_START �J�n���̉�]�s��
 @param[in] r_END   �I�����̉�]�s��
 @param[in] factor  ��ԌW��
 @reutrn    S_Matrix4x4<T> ���ʐ��`��Ԃ�����]�s��

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_SlerpRotation(const S_Matrix4x4& r_START,
                                               const S_Matrix4x4& r_END,
                                               T factor)
{
    // ��]�s�񂩂�N�H�[�^�j�I�����쐬
    S_Quaternion<T> start_quaternion = S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(r_START);
    S_Quaternion<T> end_quaternion = S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(r_END);
    
    // �N�H�[�^�j�I�������ʐ��`��Ԃ���
    S_Quaternion<T> slerp_quaternion = S_Quaternion<T>::s_Slerp(start_quaternion, end_quaternion, factor);
    
    // �N�H�[�^�j�I�����s��֕ϊ�
    S_Matrix4x4 slerp_matrix = s_ConvertQuaternionToMatrix4x4(slerp_quaternion);
    
    return slerp_matrix;
}
    
    
#pragma region S_Matrix4x4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h
    
    
/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    const S_Matrix4x4<T> ���Z�����s��

*/
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::operator+(const S_Matrix4x4<T>& r_ANOTHER) const
{
    S_Matrix4x4 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] + r_ANOTHER.m_elements[i];
    
    return temp;
}
    
    
/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    const S_Matrix4x4<T> ���Z�����s��

*/
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::operator-(const S_Matrix4x4<T>& r_ANOTHER) const
{
    S_Matrix4x4 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] - r_ANOTHER.m_elements[i];
    
    return temp;
}
    
    
/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    const S_Matrix4x4<T> ��Z�����s��

*/
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::operator*(const S_Matrix4x4<T>& r_ANOTHER) const
{
    S_Matrix4x4 temp;
    
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // �e�s��̓Y���������߂�
        Uint32 index = i % 4;
        Uint32 another_index = (i / 4) * 4;
    
        // �s�񓯎m�̏�Z
        temp.m_elements[i] =  this->m_elements[index]      * r_ANOTHER.m_elements[another_index]
                            + this->m_elements[index + 4]  * r_ANOTHER.m_elements[another_index + 1]
                            + this->m_elements[index + 8]  * r_ANOTHER.m_elements[another_index + 2]
                            + this->m_elements[index + 12] * r_ANOTHER.m_elements[another_index + 3];
    }
    
    return temp;
}
    
    
/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    const S_Matrix4x4<T> ���Z�����s��

*/
template<class T>
const S_Matrix4x4<T>& S_Matrix4x4<T>::operator+=(const S_Matrix4x4<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] += r_ANOTHER.m_elements[i];
    return (*this);
}
    
    
/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    const S_Matrix4x4<T> ���Z�����s��

*/
template<class T>
const S_Matrix4x4<T>& S_Matrix4x4<T>::operator-=(const S_Matrix4x4<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] -= r_ANOTHER.m_elements[i];
    return (*this);
}
    
    
/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    const S_Matrix4x4<T> ��Z�����s��

*/
template<class T>
const S_Matrix4x4<T>& S_Matrix4x4<T>::operator*=(const S_Matrix4x4<T>& r_ANOTHER)
{
    S_Matrix4x4 temp;
    
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // �e�s��̓Y���������߂�
        Uint32 index = i % 4;
        Uint32 another_index = (i / 4) * 4;
    
        // �s�񓯎m�̏�Z
        temp.m_elements[i] =  this->m_elements[index]      * r_ANOTHER.m_elements[another_index]
                            + this->m_elements[index +  4] * r_ANOTHER.m_elements[another_index + 1]
                            + this->m_elements[index +  8] * r_ANOTHER.m_elements[another_index + 2]
                            + this->m_elements[index + 12] * r_ANOTHER.m_elements[another_index + 3];
    }
    
    // ���̍s�����
    (*this) = temp;
    
    return (*this);
}
    
    
/* 

 @brief     ���l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̍s��
 @reutrn    bool  ��r��������
 @retval    true  �����s��̏ꍇ
 @retval    false �Ⴄ�s��̏ꍇ

*/
template<class T>
bool S_Matrix4x4<T>::operator==(const S_Matrix4x4<T>& r_ANOTHER) const
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
 @reutrn    bool  ��r��������
 @retval    true  �Ⴄ�s��̏ꍇ
 @retval    false �����s��̏ꍇ

*/
template<class T>
bool S_Matrix4x4<T>::operator!=(const S_Matrix4x4<T>& r_ANOTHER) const
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        if (Absolute(this->m_elements[i] - r_ANOTHER.m_elements[i]) > GetEpsilon<T>()) return true;
    }
    
    return false;
}
    
    
    
#pragma endregion
    
    
#pragma region S_Vector4���Z�q�Ƃ̃I�[�o�[���[�h
    
    
/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_VECTOR 4D�x�N�g��
 @reutrn    const S_Vector4<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Matrix4x4<T>::operator*(const S_Vector4<T>& r_VECTOR) const
{
    S_Vector4<T> temp_vector;
        
    temp_vector.m_x = this->m_a_11 * r_VECTOR.m_x
                    + this->m_a_21 * r_VECTOR.m_y
                    + this->m_a_31 * r_VECTOR.m_z
                    + this->m_a_41 * r_VECTOR.m_w;
    
    temp_vector.m_y = this->m_a_12 * r_VECTOR.m_x
                    + this->m_a_22 * r_VECTOR.m_y
                    + this->m_a_32 * r_VECTOR.m_z
                    + this->m_a_42 * r_VECTOR.m_w;
    
    temp_vector.m_z = this->m_a_13 * r_VECTOR.m_x
                    + this->m_a_23 * r_VECTOR.m_y
                    + this->m_a_33 * r_VECTOR.m_z
                    + this->m_a_43 * r_VECTOR.m_w;
    
    temp_vector.m_w = this->m_a_14 * r_VECTOR.m_x
                    + this->m_a_24 * r_VECTOR.m_y
                    + this->m_a_34 * r_VECTOR.m_z
                    + this->m_a_44 * r_VECTOR.m_w;
    
    return temp_vector;
}
    
    
#pragma endregion
    
    
#pragma region �L���X�g
    
    
/* 

 @brief  S_Matrix3x3<T>�^�ւ̃L���X�g
 @param  �Ȃ�
 @reutrn S_Matrix3x3<T> 3 * 3�s��

*/
template<class T>
S_Matrix4x4<T>::operator S_Matrix3x3<T>() const
{
    return S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(*this);
}
    
    
/* 

 @brief  String�^�ւ̃L���X�g
 @param  �Ȃ�
 @reutrn String ������ɕϊ������s��

*/
template<class T>
S_Matrix4x4<T>::operator String() const
{
    return this->ToString();
}
    
    
#pragma endregion 


/* 

 @brief     �s�񎮂��擾����
 @param[in] r_MATRIX 4 * 4�s��
 @reutrn    T �s��

*/    
template<class T>
static T s_GetDeterminant(const S_Matrix4x4<T>& r_MATRIX)
{
    return (r_MATRIX.m_a_11 * r_MATRIX.m_a_22 * r_MATRIX.m_a_33 * r_MATRIX.m_a_44) 
         + (r_MATRIX.m_a_11 * r_MATRIX.m_a_23 * r_MATRIX.m_a_34 * r_MATRIX.m_a_42)
         + (r_MATRIX.m_a_11 * r_MATRIX.m_a_24 * r_MATRIX.m_a_32 * r_MATRIX.m_a_43)
       
         + (r_MATRIX.m_a_12 * r_MATRIX.m_a_21 * r_MATRIX.m_a_34 * r_MATRIX.m_a_43)
         + (r_MATRIX.m_a_12 * r_MATRIX.m_a_23 * r_MATRIX.m_a_31 * r_MATRIX.m_a_44)
         + (r_MATRIX.m_a_12 * r_MATRIX.m_a_24 * r_MATRIX.m_a_33 * r_MATRIX.m_a_41)
       
         + (r_MATRIX.m_a_13 * r_MATRIX.m_a_21 * r_MATRIX.m_a_32 * r_MATRIX.m_a_44)
         + (r_MATRIX.m_a_13 * r_MATRIX.m_a_22 * r_MATRIX.m_a_34 * r_MATRIX.m_a_41)
         + (r_MATRIX.m_a_13 * r_MATRIX.m_a_24 * r_MATRIX.m_a_31 * r_MATRIX.m_a_42)
          
         + (r_MATRIX.m_a_14 * r_MATRIX.m_a_21 * r_MATRIX.m_a_33 * r_MATRIX.m_a_42)
         + (r_MATRIX.m_a_14 * r_MATRIX.m_a_22 * r_MATRIX.m_a_31 * r_MATRIX.m_a_43)
         + (r_MATRIX.m_a_14 * r_MATRIX.m_a_23 * r_MATRIX.m_a_32 * r_MATRIX.m_a_41)
       
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_22 * r_MATRIX.m_a_34 * r_MATRIX.m_a_43)
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_23 * r_MATRIX.m_a_32 * r_MATRIX.m_a_44)
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_24 * r_MATRIX.m_a_33 * r_MATRIX.m_a_42)
       
         - (r_MATRIX.m_a_12 * r_MATRIX.m_a_21 * r_MATRIX.m_a_33 * r_MATRIX.m_a_44)
         - (r_MATRIX.m_a_12 * r_MATRIX.m_a_23 * r_MATRIX.m_a_34 * r_MATRIX.m_a_41)
         - (r_MATRIX.m_a_12 * r_MATRIX.m_a_24 * r_MATRIX.m_a_31 * r_MATRIX.m_a_43)
       
         - (r_MATRIX.m_a_13 * r_MATRIX.m_a_21 * r_MATRIX.m_a_34 * r_MATRIX.m_a_42)
         - (r_MATRIX.m_a_13 * r_MATRIX.m_a_22 * r_MATRIX.m_a_31 * r_MATRIX.m_a_44)
         - (r_MATRIX.m_a_13 * r_MATRIX.m_a_24 * r_MATRIX.m_a_32 * r_MATRIX.m_a_41)
       
         - (r_MATRIX.m_a_14 * r_MATRIX.m_a_21 * r_MATRIX.m_a_32 * r_MATRIX.m_a_43)
         - (r_MATRIX.m_a_14 * r_MATRIX.m_a_22 * r_MATRIX.m_a_33 * r_MATRIX.m_a_41)
         - (r_MATRIX.m_a_14 * r_MATRIX.m_a_23 * r_MATRIX.m_a_31 * r_MATRIX.m_a_42);
}


/* 

 @brief     �l�̌������s��
 @param[in] p_a �l�̃|�C���^
 @param[in] p_b ������̒l�̃|�C���^
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
template struct S_Matrix4x4<float>;
template struct S_Matrix4x4<double>;