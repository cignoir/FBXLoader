/* �w�b�_�t�@�C�� */
#include "Vector4.h"


// ���O��Ԃ��ȗ�
using namespace GALib::Math;


#pragma region �ÓI�����o�ϐ��̏�����


template<class T>
const S_Vector4<T> S_Vector4<T>::m_s_ZERO;

template<class T>
const S_Vector4<T> S_Vector4<T>::m_s_ONE(static_cast<T>(1));


#pragma endregion


/* 

 @brief �R���X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Vector4<T>::S_Vector4() : 

    m_x(0),
    m_y(0),
    m_z(0),
    m_w(0)

{
}


/* 

 @brief     �R���X�g���N�^( �w�肵��1�̒l�Ŋe������������ )
 @param[in] value �l

*/
template<class T>
S_Vector4<T>::S_Vector4(T value) : 

    m_x(value),
    m_y(value),
    m_z(value),
    m_w(value)

{
}


/* 

 @brief     �R���X�g���N�^( �w�肵���l�Ŋe������������ )
 @param[in] x X����
 @param[in] y Y����
 @param[in] z Z����
 @param[in] w W����

*/
template<class T>
S_Vector4<T>::S_Vector4(T x, T y, T z, T w) :

    m_x(x),
    m_y(y),
    m_z(z),
    m_w(w)

{
}


/* 

 @brief     �R���X�g���N�^( �w�肵���z��Ŋe������������ )
 @param[in] ELEMENTS �v�f��4�̔z��

*/
template<class T>
S_Vector4<T>::S_Vector4(const T ELEMENTS[4]) :

    m_x(ELEMENTS[0]),
    m_y(ELEMENTS[1]),
    m_z(ELEMENTS[2]),
    m_w(ELEMENTS[3])

{
}


/* 

 @brief     �R���X�g���N�^( �w�肵��2D�x�N�g���ƒl�Ŋe������������ )
 @param[in] r_XY X�EY����
 @param[in] z    Z����
 @param[in] w    W����

*/
template<class T>
S_Vector4<T>::S_Vector4(const S_Vector2<T>& r_XY, T z, T w) :

    m_x(r_XY.m_x),
    m_y(r_XY.m_y),
    m_z(z),
    m_w(w)

{
}


/* 

 @brief     �R���X�g���N�^( �w�肵��3D�x�N�g���ƒl�Ŋe������������ )
 @param[in] r_XYZ X�EY�EZ����
 @param[in] w     W����

*/
template<class T>
S_Vector4<T>::S_Vector4(const S_Vector3<T>& r_XYZ, T w) :

    m_x(r_XYZ.m_x),
    m_y(r_XYZ.m_y),
    m_z(r_XYZ.m_z),
    m_w(w)

{
}


/* 

 @brief �f�X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Vector4<T>::~S_Vector4()
{
}


/* 

 @brief  �[���x�N�g��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector4<T>::Zero()
{
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
    this->m_w = 0;
}


/* 

 @brief     �e���������̒l�ɕύX����
 @param[in] value �l
 @return    �Ȃ�

*/
template<class T>
void S_Vector4<T>::Fill(T value)
{
    this->m_x = value;
    this->m_y = value;
    this->m_z = value;
    this->m_w = value;
}


/* 

 @brief  �P�ʃx�N�g��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector4<T>::Normalize()
{
    // �傫�����擾
    T magnitude = this->GetMagnitude();
    assert(magnitude != 0);

    // �P�ʃx�N�g����
    this->m_x /= magnitude;
    this->m_y /= magnitude;
    this->m_z /= magnitude;
    this->m_w /= magnitude;
}


/* 

 @brief  �x�N�g���𔽓]����
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector4<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
    this->m_z *= static_cast<T>(-1);
    this->m_w *= static_cast<T>(-1);
}


/* 

 @brief     �傫���Ńx�N�g�����N�����v����
 @param[in] min �ŏ��̑傫��
 @param[in] max �ŏ��̑傫��
 @return    �Ȃ�

*/
template<class T>
void S_Vector4<T>::ClampMagnitude(T min, T max)
{
    // �傫�����擾���A���̑傫�����N�����v
    T magnitude = this->GetMagnitude();
    Clamp(magnitude, min, max);

    // �P�ʃx�N�g�������āA�傫�����X�P�[��
    this->Normalize();
    (*this) = (*this) * magnitude;
}


/* 

 @brief  �傫�����擾����
 @param  �Ȃ�
 @return T �傫��

*/
template<class T>
T S_Vector4<T>::GetMagnitude() const
{
    return SquareRoot(GetMagnitudeSquare());
}


/* 

 @brief  �傫����2����擾����
 @param  �Ȃ�
 @return T �傫����2��

*/
template<class T>
T S_Vector4<T>::GetMagnitudeSquare() const
{
    return Square(this->m_x) + Square(this->m_y) + Square(this->m_z) + Square(this->m_w);
}


/* 

 @brief  �P�ʃx�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector4<T> �P�ʃx�N�g��

*/
template<class T>
S_Vector4<T> S_Vector4<T>::GetNormalize() const
{
    S_Vector4 temp(*this);
    temp.Normalize();

    return temp;
}


/* 

 @brief  ���]�����x�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector4<T> ���]�����x�N�g��

*/
template<class T>
S_Vector4<T> S_Vector4<T>::GetInvert() const
{
    return S_Vector4(-this->m_x, -this->m_y, -this->m_z, -this->m_w);
}


/* 

 @brief     �傫���ŃN�����v�����x�N�g�����擾����
 @param[in] min �ŏ��̑傫��
 @param[in] max �ő�̑傫��
 @return    S_Vector4<T> �N�����v�����x�N�g��

*/
template<class T>
S_Vector4<T> S_Vector4<T>::GetClampMagnitude(T min, T max) const
{
    S_Vector4 temp = (*this);
    temp.ClampMagnitude(min, max);

    return temp;
}


/* 

 @brief  �x�N�g���𕶎���Ƃ��Ď擾����
 @param  �Ȃ�
 @return String ������ɕϊ������x�N�g��

*/
template<class T>
String S_Vector4<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( X : %f, Y : %f, Z : %f, W : %f )", this->m_x, this->m_y, this->m_z, this->m_w);
    return buffer;
}


/* 

 @brief     ���ς����߂�
 @param[in] r_VECTOR
 @param[in] r_ANOTHER_VECTOR
 @return    T ����

*/
template<class T>
T S_Vector4<T>::s_DotProduct(const S_Vector4<T>& r_VECTOR, const S_Vector4<T>& r_ANOTHER_VECTOR)
{
    return (r_VECTOR.m_x * r_ANOTHER_VECTOR.m_x)
         + (r_VECTOR.m_y * r_ANOTHER_VECTOR.m_y)
         + (r_VECTOR.m_z * r_ANOTHER_VECTOR.m_z)
         + (r_VECTOR.m_w * r_ANOTHER_VECTOR.m_w);
}


/* 

 @brief     ���`��Ԃ��s��
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] factor        ��ԌW��( 0 �` 1 )
 @return    S_Vector4<T> ��̓_����`��Ԃ����_

*/
template<class T>
S_Vector4<T> S_Vector4<T>::s_Lerp(const S_Vector4<T>& r_START_POINT,
                                  const S_Vector4<T>& r_END_POINT,
                                  T factor)
{
    S_Vector4 lerp_point;

    lerp_point.m_x = (r_END_POINT.m_x - r_START_POINT.m_x) * factor + r_START_POINT.m_x;
    lerp_point.m_y = (r_END_POINT.m_y - r_START_POINT.m_y) * factor + r_START_POINT.m_y;
    lerp_point.m_z = (r_END_POINT.m_z - r_START_POINT.m_z) * factor + r_START_POINT.m_z;
    lerp_point.m_w = (r_END_POINT.m_w - r_START_POINT.m_w) * factor + r_START_POINT.m_w;

    return lerp_point;
}


/* 

 @brief     �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    S_Vector4<T> �ŏ��l�𐬕��ɂ����x�N�g��

*/
template<class T>
S_Vector4<T> S_Vector4<T>::s_Minimize(const S_Vector4<T>& r_LHS, const S_Vector4<T>& r_RHS)
{
    S_Vector4 min_vector;

    min_vector.m_x = (r_LHS.m_x < r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    min_vector.m_y = (r_LHS.m_y < r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    min_vector.m_z = (r_LHS.m_z < r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;
    min_vector.m_w = (r_LHS.m_w < r_RHS.m_w) ? r_LHS.m_w : r_RHS.m_w;

    return min_vector;
}


/* 

 @brief     �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    S_Vector4<T> �ő�l�𐬕��ɂ����x�N�g��

*/
template<class T>
S_Vector4<T> S_Vector4<T>::s_Maximize(const S_Vector4<T>& r_LHS, const S_Vector4<T>& r_RHS)
{
    S_Vector4 max_vector;

    max_vector.m_x = (r_LHS.m_x > r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    max_vector.m_y = (r_LHS.m_y > r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    max_vector.m_z = (r_LHS.m_z > r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;
    max_vector.m_w = (r_LHS.m_w > r_RHS.m_w) ? r_LHS.m_w : r_RHS.m_w;

    return max_vector;
}


#pragma region S_Vector4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator+(const S_Vector4<T>& r_ANOTHER) const
{
    return S_Vector4(this->m_x + r_ANOTHER.m_x,
                     this->m_y + r_ANOTHER.m_y,
                     this->m_z + r_ANOTHER.m_z,
                     this->m_w + r_ANOTHER.m_w);
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator-(const S_Vector4<T>& r_ANOTHER) const
{
    return S_Vector4(this->m_x - r_ANOTHER.m_x,
                     this->m_y - r_ANOTHER.m_y,
                     this->m_z - r_ANOTHER.m_z,
                     this->m_w - r_ANOTHER.m_w);
}


/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator*(const S_Vector4<T>& r_ANOTHER) const
{
    return S_Vector4(this->m_x * r_ANOTHER.m_x,
                     this->m_y * r_ANOTHER.m_y,
                     this->m_z * r_ANOTHER.m_z,
                     this->m_w * r_ANOTHER.m_w);
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator/(const S_Vector4<T>& r_ANOTHER) const
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    assert(r_ANOTHER.m_w != 0);

    return S_Vector4(this->m_x / r_ANOTHER.m_x,
                     this->m_y / r_ANOTHER.m_y,
                     this->m_z / r_ANOTHER.m_z,
                     this->m_w / r_ANOTHER.m_w);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator+=(const S_Vector4<T>& r_ANOTHER)
{
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;
    this->m_z += r_ANOTHER.m_z;
    this->m_w += r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator-=(const S_Vector4<T>& r_ANOTHER)
{
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;
    this->m_z -= r_ANOTHER.m_z;
    this->m_w -= r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator*=(const S_Vector4<T>& r_ANOTHER)
{
    this->m_x *= r_ANOTHER.m_x;
    this->m_y *= r_ANOTHER.m_y;
    this->m_z *= r_ANOTHER.m_z;
    this->m_w *= r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator/=(const S_Vector4<T>& r_ANOTHER)
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    assert(r_ANOTHER.m_w != 0);

    this->m_x /= r_ANOTHER.m_x;
    this->m_y /= r_ANOTHER.m_y;
    this->m_z /= r_ANOTHER.m_z;
    this->m_w /= r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     ���l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    bool  ��r��������
 @retval    true  �����x�N�g���̏ꍇ
 @retval    false �Ⴄ�x�N�g���̏ꍇ

*/
template<class T>
bool S_Vector4<T>::operator==(const S_Vector4<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) < GetEpsilon<T>()
        && Absolute(this->m_y - r_ANOTHER.m_y) < GetEpsilon<T>()
        && Absolute(this->m_z - r_ANOTHER.m_z) < GetEpsilon<T>()
        && Absolute(this->m_w - r_ANOTHER.m_w) < GetEpsilon<T>();
}


/* 

 @brief     �񓙒l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    bool  ��r��������
 @retval    true  �Ⴄ�x�N�g���̏ꍇ
 @retval    false �����x�N�g���̏ꍇ

*/
template<class T>
bool S_Vector4<T>::operator!=(const S_Vector4<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) > GetEpsilon<T>()
        || Absolute(this->m_y - r_ANOTHER.m_y) > GetEpsilon<T>()
        || Absolute(this->m_z - r_ANOTHER.m_z) > GetEpsilon<T>()
        || Absolute(this->m_w - r_ANOTHER.m_w) > GetEpsilon<T>();
}


#pragma endregion


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector4<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator*(T value) const
{
    return S_Vector4(this->m_x * value,
                     this->m_y * value,
                     this->m_z * value,
                     this->m_w * value);
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator/(T value) const
{
    assert(value != 0);

    return S_Vector4(this->m_x / value,
                        this->m_y / value,
                        this->m_z / value,
                        this->m_w / value);
}


/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector4<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator*=(T value)
{
    this->m_x *= value;
    this->m_y *= value;
    this->m_z *= value;
    this->m_w *= value;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector4<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator/=(T value)
{
    assert(value != 0);

    this->m_x /= value;
    this->m_y /= value;
    this->m_z /= value;
    this->m_w /= value;

    return (*this);
}


#pragma endregion


#pragma region �L���X�g


/* 

 @brief  S_Vector2�^�ւ̃L���X�g
 @param  �Ȃ�
 @return S_Vector2<T> 2D�x�N�g��

*/
template<class T>
S_Vector4<T>::operator S_Vector2<T>() const
{
    return S_Vector2<T>(this->m_x, this->m_y);
}


/* 

 @brief  S_Vector3�^�ւ̃L���X�g
 @param  �Ȃ�
 @return S_Vector3<T> 3D�x�N�g��

*/
template<class T>
S_Vector4<T>::operator S_Vector3<T>() const
{
    return S_Vector3<T>(this->m_x, this->m_y, this->m_z);
}


/* 

 @brief  String�^�ւ̃L���X�g
 @param  �Ȃ�
 @return String ������

*/
template<class T>
S_Vector4<T>::operator String() const
{
    return this->ToString();
}


#pragma endregion


/* �����I�C���X�^���X�� */
template struct S_Vector4<float>;
template struct S_Vector4<double>;

