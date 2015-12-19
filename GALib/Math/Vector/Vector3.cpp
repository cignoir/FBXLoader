/* �w�b�_�t�@�C�� */
#include "Vector3.h"
#include "../Quaternion/Quaternion.h"


// ���O��Ԃ��ȗ�
using namespace GALib::Math;


#pragma region �ÓI�����o�ϐ��̏�����
    
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_RIGHT_DIRECTION(static_cast<T>(1), 0, 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_LEFT_DIRECTION(static_cast<T>(-1), 0, 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_UP_DIRECTION(0, static_cast<T>(1), 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_DOWN_DIRECTION(0, static_cast<T>(-1), 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_FRONT_DIRECTION(0, 0, static_cast<T>(-1));
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_BACK_DIRECTION(0, 0, static_cast<T>(1));
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_ZERO;
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_ONE(static_cast<T>(1));
    
    
#pragma endregion
    

/* 

 @brief �R���X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Vector3<T>::S_Vector3() :

    m_x(0),
    m_y(0),
    m_z(0)

{
}
    

/* 

 @brief     �R���X�g���N�^( �w�肵��1�̒l�Ŋe�����̏����� )
 @param[in] value �l

*/
template<class T>
S_Vector3<T>::S_Vector3(T value) :

    m_x(value),
    m_y(value),
    m_z(value)

{
}
    

/* 

 @brief     �R���X�g���N�^( �w�肵���l�Ŋe�����̏����� )
 @param[in] x X����
 @param[in] y Y����
 @param[in] z Z����

*/
template<class T>
S_Vector3<T>::S_Vector3(T x, T y, T z) : 
    
    m_x(x),
    m_y(y),
    m_z(z)
    
{
}
    
 
/* 

 @brief     �R���X�g���N�^( �w�肵���z��Ŋe�����̏����� )
 @param[in] ELEMENTS �v�f��3�̔z��

*/
template<class T>
S_Vector3<T>::S_Vector3(const T ELEMENTS[3]) :

    m_x(ELEMENTS[0]),
    m_y(ELEMENTS[1]),
    m_z(ELEMENTS[2])

{
}
    
    
/* 

 @brief     �R���X�g���N�^( 2D�x�N�g����Z�����ŏ����������� )
 @param[in] r_XY X�EY����
 @param[in] z    Z����

*/
template<class T>
S_Vector3<T>::S_Vector3(const S_Vector2<T>& r_XY, T z) : 
    
    m_x(r_XY.m_x),
    m_y(r_XY.m_y),
    m_z(z)
    
{
}
    
    
    
/* 

 @brief �f�X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Vector3<T>::~S_Vector3()
{
}
    

/* 

 @brief  �[���x�N�g��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector3<T>::Zero()
{
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
}
    

/* 

 @brief     �e���������̒l�ɕύX����
 @param[in] value �l
 @return    �Ȃ�

*/
template<class T>
void S_Vector3<T>::Fill(T value)
{
    this->m_x = value;
    this->m_y = value;
    this->m_z = value;
}
    

/* 

 @brief  �P�ʃx�N�g��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector3<T>::Normalize()
{
    // �傫�����擾
    T magnitude = this->GetMagnitude();
    assert(magnitude != 0);
    
    // �P�ʃx�N�g����
    this->m_x /= magnitude;
    this->m_y /= magnitude;
    this->m_z /= magnitude;
}
    

/* 

 @brief  �x�N�g���𔽓]����
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector3<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
    this->m_z *= static_cast<T>(-1);
}
    
    
/* 

 @brief     X������x�N�g������]����
 @param[in] angle �p�x( ���W�A���l )
 @return    �Ȃ�

*/
template<class T>
void S_Vector3<T>::RotateX(T angle)
{
    T temp_z = this->m_z;
    this->m_z = temp_z * Cosine(angle) - this->m_y * Sine(angle);
    this->m_y = temp_z * Sine(angle) + this->m_y * Cosine(angle);
}
    

/* 

 @brief     Y������x�N�g������]����
 @param[in] angle �p�x( ���W�A���l )
 @return    �Ȃ�

*/
template<class T>
void S_Vector3<T>::RotateY(T angle)
{
    T temp_x = this->m_x;
    this->m_x = temp_x * Cosine(angle) - this->m_z * Sine(angle);
    this->m_z = temp_x * Sine(angle) + this->m_z * Cosine(angle);
}
    
    
/* 

 @brief     Z������x�N�g������]����
 @param[in] angle �p�x( ���W�A���l )
 @return    �Ȃ�

*/
template<class T>
void S_Vector3<T>::RotateZ(T angle)
{
    T temp_x = this->m_x;
    this->m_x = temp_x * Cosine(angle) - this->m_y * Sine(angle);
    this->m_y = temp_x * Sine(angle) + this->m_y * Cosine(angle);
}
    
    
/* 

 @brief     �C�ӎ�����x�N�g������]����
 @param[in] r_AXIS ��
 @param[in] angle  �p�x( ���W�A���l )
 @return    �Ȃ�

*/
template<class T>
void S_Vector3<T>::RotateAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // ��]����x�N�g��
    S_Quaternion<T> rotation_vector(0, *this);
    
    // ��]�N�H�[�^�j�I�����쐬
    S_Quaternion<T> rotation_quaternion = S_Quaternion<T>::s_CreateRotationAxis(r_AXIS, angle);
    S_Quaternion<T> inverse_rotation_quaternion = S_Quaternion<T>::s_CreateRotationAxis(r_AXIS.GetInvert(), angle);
    
    // �x�N�g������]���A���g�ɑ��
    rotation_vector =  inverse_rotation_quaternion * rotation_vector * rotation_quaternion;

    this->m_x = rotation_vector.m_x;
    this->m_y = rotation_vector.m_y;
    this->m_z = rotation_vector.m_z;
}
    
    
/* 

 @brief     �傫���Ńx�N�g�����N�����v����
 @param[in] min �ŏ��̑傫��
 @param[in] max �ő�̑傫��
 @return    �Ȃ�

*/
template<class T>
void S_Vector3<T>::ClampMagnitude(T min, T max)
{
    // �傫�����擾���A���̑傫�����N�����v
    T magnitude = GetMagnitude();
    magnitude = Clamp(magnitude, min, max);
    
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
T S_Vector3<T>::GetMagnitude() const
{
    return SquareRoot(GetMagnitudeSquare());
}
    
    
/* 

 @brief  �傫����2����擾����
 @param  �Ȃ�
 @return T �傫����2��

*/
template<class T>
T S_Vector3<T>::GetMagnitudeSquare() const
{
    return Square(this->m_x) + Square(this->m_y) + Square(this->m_z);
}
    
  
/* 

 @brief  �P�ʃx�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector3<T> �P�ʃx�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetNormalize() const
{
    S_Vector3 temp(*this);
    temp.Normalize();
    
    return temp;
}
    
   
/* 

 @brief  ���]�����x�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector3<T> ���]�����x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetInvert() const
{
    return S_Vector3(-this->m_x, -this->m_y, -this->m_z);
}

    
/* 

 @brief     X�������]�����x�N�g�����擾����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Vector3<T> ��]�����x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateX(T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateX(angle);
    return temp;
}
    
    
/* 

 @brief     Y�������]�����x�N�g�����擾����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Vector3<T> ��]�����x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateY(T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateY(angle);
    return temp;
}
    
   
/* 

 @brief     Z�������]�����x�N�g�����擾����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Vector3<T> ��]�����x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateZ(T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateZ(angle);
    return temp;
}
    

/* 

 @brief     �C�ӎ������]�����x�N�g�����擾����
 @param[in] r_AXIS ��
 @param[in] angle  �p�x( ���W�A���l )
 @return    S_Vector3<T> ��]�����x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateAxis(const S_Vector3<T>& r_AXIS, T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateAxis(r_AXIS, angle);
    return temp;
}
    
    
/* 

 @brief     �傫���ŃN�����v�����x�N�g�����擾����
 @param[in] min �ŏ��̑傫��
 @param[in] max �ő�̑傫��
 @return    S_Vector3<T> �N�����v�����x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetClampMagnitude(T min, T max) const
{
    S_Vector3 temp = (*this);
    temp.ClampMagnitude(min, max);
    return temp;
}
    

/* 

 @brief  �x�N�g���𕶎���Ƃ��Ď擾����
 @param  �Ȃ�
 @return String ������ɕϊ������x�N�g��

*/
template<class T>
String S_Vector3<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( X : %f, Y : %f, Z : %f )", this->m_x, this->m_y, this->m_z);
    return buffer;
}
    
    
/* 

 @brief     ���ς����߂�
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T ����

*/
template<class T>
T S_Vector3<T>::s_DotProduct(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    return (r_LHS.m_x * r_RHS.m_x) + (r_LHS.m_y * r_RHS.m_y) + (r_LHS.m_z * r_RHS.m_z);
}
    
    
/* 

 @brief     �O�ς����߂�
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    S_Vector3<T> �O��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_CrossProduct(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 cross_vector;
    
    cross_vector.m_x = (r_LHS.m_y * r_RHS.m_z) - (r_LHS.m_z * r_RHS.m_y);
    cross_vector.m_y = (r_LHS.m_z * r_RHS.m_x) - (r_LHS.m_x * r_RHS.m_z);
    cross_vector.m_z = (r_LHS.m_x * r_RHS.m_y) - (r_LHS.m_y * r_RHS.m_x);
        
    return cross_vector;
}
    
   
/* 

 @brief     �X�J���[�O�d�ς����߂�
 @param[in] r_A 1�ڂ̃x�N�g��
 @param[in] r_B 2�ڂ̃x�N�g��
 @param[in] r_C 3�ڂ̃x�N�g��
 @return    T �X�J���[�O�d��

*/
template<class T>
T S_Vector3<T>::s_ScalarTripleProduct(const S_Vector3<T>& r_A,
                                      const S_Vector3<T>& r_B,
                                      const S_Vector3<T>& r_C)
{
    return s_DotProduct(r_A, s_CrossProduct(r_B, r_C));
}
    
    
/* 

 @brief     �x�N�g���O�d�ς����߂�
 @param[in] r_A 1�ڂ̃x�N�g��
 @param[in] r_B 2�ڂ̃x�N�g��
 @param[in] r_C 3�ڂ̃x�N�g��
 @return    T �x�N�g���O�d��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_VectorTripleProduct(const S_Vector3<T>& r_A,
                                                 const S_Vector3<T>& r_B,
                                                 const S_Vector3<T>& r_C)
{
    return s_CrossProduct(r_A, s_CrossProduct(r_B, r_C));
}
    
    
/* 

 @brief     ���`��Ԃ��s��
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] factor        ��ԌW��( 0 �` 1 )
 @return    S_Vector3<T> ��̓_����`��Ԃ����_

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Lerp(const S_Vector3<T>& r_START_POINT,
                                  const S_Vector3<T>& r_END_POINT,
                                  T factor)
{
    S_Vector3 lerp_point;
    
    lerp_point.m_x = (r_END_POINT.m_x - r_START_POINT.m_x) * factor + r_START_POINT.m_x;
    lerp_point.m_y = (r_END_POINT.m_y - r_START_POINT.m_y) * factor + r_START_POINT.m_y;
    lerp_point.m_z = (r_END_POINT.m_z - r_START_POINT.m_z) * factor + r_START_POINT.m_z;
    
    return lerp_point;
}
    
    
/* 

 @brief     ���ʐ��`��Ԃ��s��
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] factor        ��ԌW��( 0 �` 1 )
 @return    S_Vector3<T> ��̓_�����ʐ��`��Ԃ����_

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Slerp(const S_Vector3<T>& r_START_POINT,
                                   const S_Vector3<T>& r_END_POINT,
                                   T factor)
{
    // �p�x�ƃT�C�������߂�
    T angle = s_AngleBetweenVectors(r_START_POINT, r_END_POINT);
    T sine = Sine(angle);
    
    // �e��ԌW�������߂�
    T start_factor = Sine(angle * (static_cast<T>(1) - factor));
    T end_factor = Sine(angle * factor);
    
    // ���ʐ��`��Ԃ����_�����߂�
    S_Vector3 slerp_point = r_START_POINT * start_factor + r_END_POINT * end_factor;
    
    return slerp_point;
}
    
    
/* 

 @brief     �G���~�[�g��Ԃ��s��
 @param[in] r_START_POINT   �n�_
 @param[in] r_START_TANGENT �n�_�̐ڐ�
 @param[in] r_END_POINT     �I�_
 @param[in] r_END_TANGENT   �I�_�̐ڐ�
 @param[in] factor          ��ԌW��( 0 �` 1 )
 @return    S_Vector3<T> ��̓_���G���~�[�g��Ԃ����_

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Hermite(const S_Vector3<T>& r_START_POINT,
                                     const S_Vector3<T>& r_START_TANGENT,
                                     const S_Vector3<T>& r_END_POINT,
                                     const S_Vector3<T>& r_END_TANGENT,
                                     T factor)
{
    // �e�_�Ɗe�ړ_�̌W�������߂�
    T u_1 = factor;
    T u_2 = Square(factor);
    T u_3 = u_2 * factor;
    
    T p_0 = (static_cast<T>(2) * u_3) - (static_cast<T>(3) * u_2) + static_cast<T>(1);
    T t_0 = u_3 - (static_cast<T>(2) * u_2) + u_1;
    T p_1 = (static_cast<T>(-2) * u_3) + static_cast<T>(3) * u_2;
    T t_1 = u_3 - u_2;
    
    // �G���~�[�g��Ԃ���
    S_Vector3 hermite_point;
    
    hermite_point.m_x = r_START_POINT.m_x   * p_0 
                      + r_START_TANGENT.m_x * t_0 
                      + r_END_POINT.m_x     * p_1 
                      + r_END_TANGENT.m_x   * t_1;

    hermite_point.m_y = r_START_POINT.m_y   * p_0 
                      + r_START_TANGENT.m_y * t_0
                      + r_END_POINT.m_y     * p_1
                      + r_END_TANGENT.m_y   * t_1;

    hermite_point.m_z = r_START_POINT.m_z   * p_0 
                      + r_START_TANGENT.m_z * t_0 
                      + r_END_POINT.m_z     * p_1 
                      + r_END_TANGENT.m_z   * t_1;
    
    return hermite_point;
}
    

/* 

 @brief     Catmull-Rom�X�v���C����Ԃ��s��
 @param[in] r_PREVIOUS_START_POINT �n�_�̑O�̓_
 @param[in] r_START_POINT          �n�_
 @param[in] r_END_POINT            �I�_
 @param[in] r_NEXT_END_POINT       �I�_�̎��̓_
 @param[in] factor                 ��ԌW��( 0 �` 1 )
 @return    S_Vector3<T> ��̓_��Catmull-Rom�X�v���C����Ԃ����_

*/    
template<class T>
S_Vector3<T> S_Vector3<T>::s_CatmullRomSpline(const S_Vector3<T>& r_PREVIOUS_START_POINT,
                                              const S_Vector3<T>& r_START_POINT,
                                              const S_Vector3<T>& r_END_POINT,
                                              const S_Vector3<T>& r_NEXT_END_POINT,
                                              T factor)
{
    // ���T�C�h�̓_����ڐ������߂�
    S_Vector3 start_tangent = (r_END_POINT - r_PREVIOUS_START_POINT) * static_cast<T>(0.5);
    S_Vector3 end_tangent = (r_NEXT_END_POINT - r_START_POINT) * static_cast<T>(0.5);
    
    // �ڐ��𗘗p���āA�G���~�[�g���
    S_Vector3 catmull_rom_spline_point = s_Hermite(r_START_POINT, start_tangent, r_END_POINT, end_tangent, factor);
    return catmull_rom_spline_point;
}
    
    
/* 

 @brief     �x�W�F��Ԃ��s��
 @param[in] r_START_POINT     �n�_
 @param[in] r_END_POINT       �I�_
 @param[in] r_CONTROL_POINT_1 ����_1
 @param[in] r_CONTROL_POINT_2 ����_2
 @param[in] factor            ��ԌW��( 0 �` 1 )
 @return    S_Vector3<T> ��̓_���x�W�F��Ԃ����_

*/    
template<class T>
S_Vector3<T> S_Vector3<T>::s_Bezier(const S_Vector3<T>& r_START_POINT,
                                    const S_Vector3<T>& r_END_POINT,
                                    const S_Vector3<T>& r_CONTROL_POINT_1,
                                    const S_Vector3<T>& r_CONTROL_POINT_2,
                                    T factor)
{
    // �e�_�̌W�������߂�
    T one_minus_factor = static_cast<T>(1) - factor;
        
    T p_0 = Cubic(one_minus_factor);
    T p_1 = Cubic(factor);
    T c_0 = static_cast<T>(3) * factor * Square(one_minus_factor);
    T c_1 = static_cast<T>(3) * Square(factor) * one_minus_factor;
    
    // �x�W�F��Ԃ���
    S_Vector3 bezier_point;
    
    bezier_point.m_x = r_START_POINT.m_x           * p_0 
                           + r_END_POINT.m_x       * p_1
                           + r_CONTROL_POINT_1.m_x * c_0 
                           + r_CONTROL_POINT_2.m_x * c_1;

    bezier_point.m_y = r_START_POINT.m_y           * p_0
                           + r_END_POINT.m_y       * p_1 
                           + r_CONTROL_POINT_1.m_y * c_0 
                           + r_CONTROL_POINT_2.m_y * c_1;

    bezier_point.m_z = r_START_POINT.m_z           * p_0
                           + r_END_POINT.m_z       * p_1
                           + r_CONTROL_POINT_1.m_z * c_0
                           + r_CONTROL_POINT_2.m_z * c_1;

    return bezier_point;
}
    
    
/* 

 @brief     �}���|�C���g( �����ʒu )�����߂�
 @param[in] r_POSITION         ���W
 @param[in] r_VELOCITY         ���x
 @param[in] r_ANOTHER_POSITION ����1�̍��W
 @param[in] r_ANOTHER_VELOCITY ����1�̑��x
 @return    S_Vector3<T> �}���|�C���g

*/  
template<class T>
S_Vector3<T> S_Vector3<T>::s_InterceptPoint(const S_Vector3<T>& r_POSITION,
                                            const S_Vector3<T>& r_VELOCITY,
                                            const S_Vector3<T>& r_ANOTHER_POSITION,
                                            const S_Vector3<T>& r_ANOTHER_VELOCITY)
{
    // �����Ƒ��x�̍������߂�
    S_Vector3 distance = r_POSITION - r_ANOTHER_POSITION;
    S_Vector3 velocity_difference = r_VELOCITY - r_ANOTHER_VELOCITY;
    
    // �������瑬�x������A���Ԃ�����
    T time = distance.GetMagnitude() / velocity_difference.GetMagnitude();
    
    // �}���|�C���g�����߂�
    S_Vector3 intercept_point = r_POSITION + (r_VELOCITY * time);
    return intercept_point;
}
    

/* 

 @brief     �x�N�g���Ԃ̊p�x�����߂�
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T �p�x( ���W�A���l )

*/  
template<class T>
T S_Vector3<T>::s_AngleBetweenVectors(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    T cosine = s_DotProduct(r_LHS.GetNormalize(), r_RHS.GetNormalize());
    T angle = static_cast<T>(std::acos(static_cast<double>(cosine)));
        
    return angle;
}
    
    
/* 

 @brief     �x�N�g���Ԃ̋��������߂�
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T ����

*/  
template<class T>
T S_Vector3<T>::s_DistanceBetweenVectors(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 distance = r_LHS - r_RHS;
    return distance.GetMagnitude();
}
    

/* 

 @brief     �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T �ŏ��l�𐬕��ɂ����x�N�g��

*/  
template<class T>
S_Vector3<T> S_Vector3<T>::s_Minimize(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 min_vector;

    min_vector.m_x = (r_LHS.m_x < r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    min_vector.m_y = (r_LHS.m_y < r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    min_vector.m_z = (r_LHS.m_z < r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;

    return min_vector;
}
    
    
/* 

 @brief     �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T �ő�l�𐬕��ɂ����x�N�g��

*/ 
template<class T>
S_Vector3<T> S_Vector3<T>::s_Maximize(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 max_vector;

    max_vector.m_x = (r_LHS.m_x > r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    max_vector.m_y = (r_LHS.m_y > r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    max_vector.m_z = (r_LHS.m_z > r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;

    return max_vector;
}
    
    
/* 

 @brief     2�_�Ԃ���̋����������i�񂾓_���擾����
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] distance      ����
 @return    S_Vector3<T> �n�_���狗���������i�񂾓_

*/ 
template<class T>
S_Vector3<T> S_Vector3<T>::s_MoveTowards(const S_Vector3<T>& r_START_POINT, 
                                         const S_Vector3<T>& r_END_POINT,
                                         T distance)
{
    if (distance < 0) return r_START_POINT;
    
    S_Vector3 difference = r_START_POINT - r_END_POINT;
    S_Vector3 movement = difference.GetNormalize() * distance;
    
    if (movement.GetMagnitudeSquare() >= difference.GetMagnitudeSquare()) return r_END_POINT;
    return r_START_POINT + movement;
}
    
   
/* 

 @brief     ���e�x�N�g�����擾����
 @param[in] r_VECTOR �x�N�g��
 @param[in] r_NORMAL �@���x�N�g��
 @return    S_Vector3<T> ���e�x�N�g��

*/ 
template<class T>
S_Vector3<T> S_Vector3<T>::s_Project(const S_Vector3<T>& r_VECTOR, 
                                     const S_Vector3<T>& r_NORMAL)
{
    // �P�ʃx�N�g���������@���Ɠ��e�̑傫�����擾
    S_Vector3 unit_normal = r_NORMAL.GetNormalize();
    T project_length = s_DotProduct(r_VECTOR, unit_normal);
    
    return unit_normal * project_length;
}
    

/* 

 @brief     ���˃x�N�g�����擾����
 @param[in] r_VECTOR �x�N�g��
 @param[in] r_NORMAL �@���x�N�g��
 @return    S_Vector3<T> ���˃x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Reflect(const S_Vector3<T>& r_VECTOR, 
                                     const S_Vector3<T>& r_NORMAL)
{
    // �P�ʃx�N�g���������@�����擾
    S_Vector3 unit_normal = r_NORMAL.GetNormalize();
    
    // ���˃x�N�g�������߂�
    S_Vector3 reflection_vector = r_VECTOR - static_cast<T>(2) * s_DotProduct(r_VECTOR, unit_normal) * unit_normal;
    return reflection_vector;
}
    

/* 

 @brief     ���܃x�N�g�����擾����
 @param[in] r_VECTOR         �x�N�g��
 @param[in] r_NORMAL         �@���x�N�g��
 @param[in] refractive_index ���ܗ�
 @return    S_Vector3<T> ���܃x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Refract(const S_Vector3<T>& r_INCIDENT_VECTOR, 
                                     const S_Vector3<T>& r_NORMAL,
                                     T refractive_index)
{
    // �e�x�N�g����P�ʃx�N�g����
    S_Vector3 unit_incident_vector = r_INCIDENT_VECTOR.GetNormalize();
    S_Vector3 unit_normal = r_NORMAL.GetNormalize();
    
    // ���˃x�N�g���Ɩ@���x�N�g���̓��ς����߂�
    T dot = s_DotProduct(unit_incident_vector, unit_normal);
    
    // ���܂̊p�x
    T refract_angle = static_cast<T>(1) - Square(refractive_index) * (static_cast<T>(1) - Square(dot));
    
    // ���܃x�N�g�������߂�
    S_Vector3 refract_vector;
    if (refract_angle < 0) return refract_vector;
    
    refract_vector = refractive_index * unit_incident_vector 
                   - (refractive_index * dot * SquareRoot(refract_angle)) * unit_normal;
    
    return refract_vector;
}
    

/* 

 @brief     ���肵���x�N�g�����擾����
 @param[in] r_VECTOR �x�N�g��
 @param[in] r_NORMAL �@���x�N�g��
 @return    S_Vector3<T> ���肵���x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Slide(const S_Vector3<T>& rVector, 
                                const S_Vector3<T>& rNormal)
{
    // �P�ʃx�N�g���������@�����擾
    S_Vector3 unit_normal = rNormal.GetNormalize();
    
    // ����x�N�g�������߂�
    S_Vector3 slider_vector = rVector - s_DotProduct(rVector, unit_normal) * unit_normal;
    return slider_vector;
}
    

/* 

 @brief     �@���x�N�g�����쐬
 @param[in] r_POSITION_A 1�ڂ̍��W
 @param[in] r_POSITION_B 2�ڂ̍��W
 @param[in] r_POSITION_C 3�ڂ̍��W
 @return    S_Vector3<T> �@���x�N�g��

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_CreateNormal(const S_Vector3<T>& r_POSITION_A, 
                                          const S_Vector3<T>& r_POSITION_B,
                                          const S_Vector3<T>& r_POSITION_C)
{
    // �e���W����x�N�g�������߂�
    S_Vector3 vector_ab = r_POSITION_B - r_POSITION_A;
    S_Vector3 vector_bc = r_POSITION_C - r_POSITION_B;
    
    // �@���x�N�g�������߂�
    S_Vector3 normal = s_CrossProduct(vector_ab, vector_bc);
    normal.Normalize();
    return normal;
}
    

/* 

 @brief      �ڐ��x�N�g���Ə]�@�����쐬
 @param[in]  r_POSITION_A      1�ڂ̍��W
 @param[in]  r_TEXTURE_COORD_A 1�ڂ̃e�N�X�`�����W
 @param[in]  r_POSITION_B      2�ڂ̍��W
 @param[in]  r_TEXTURE_COORD_B 2�ڂ̃e�N�X�`�����W
 @param[in]  r_POSITION_C      3�ڂ̍��W
 @param[in]  r_TEXTURE_COORD_C 3�ڂ̃e�N�X�`�����W
 @param[out] p_tangent         �ڃx�N�g��
 @param[out] p_binormal        �]�@��
 @return     �Ȃ�

*/
template<class T>
void S_Vector3<T>::s_CreateTangentAndBinormal(const S_Vector3<T>& r_POSITION_A,   
                                              const S_Vector2<T>& r_TEXTURE_COORD_A,
                                              const S_Vector3<T>& r_POSITION_B,
                                              const S_Vector2<T>& r_TEXTURE_COORD_B,
                                              const S_Vector3<T>& r_POSITION_C,
                                              const S_Vector2<T>& r_TEXTURE_COORD_C,
                                              S_Vector3* p_tangent,
                                              S_Vector3* p_binormal)
{
    assert(p_tangent || p_binormal);

    // ���_A�ɑ΂��鑊�ΓI�ȃx�N�g�������߂�
    S_Vector3 vector_position_ab = r_POSITION_B - r_POSITION_A;
    S_Vector3 vector_position_ac = r_POSITION_C - r_POSITION_A;
    
    S_Vector2<T> vector_texture_coord_ab = r_TEXTURE_COORD_B - r_TEXTURE_COORD_A;
    S_Vector2<T> vector_texture_coord_ac = r_TEXTURE_COORD_C - r_TEXTURE_COORD_A;
    
    // �ڐ��x�N�g���Ə]�@���x�N�g�������߂�
    T denominator = vector_texture_coord_ab.m_x * vector_texture_coord_ac.m_y 
                  - vector_texture_coord_ab.m_y * vector_texture_coord_ac.m_x;
    assert(denominator != 0);
        
    T part_of_inverse_matrix = static_cast<T>(1) / denominator;
    
    if (p_tangent)
    {
        S_Vector3 tangent((vector_texture_coord_ac.m_y * vector_position_ab.m_x - vector_texture_coord_ab.m_y * vector_position_ac.m_x) * part_of_inverse_matrix,
                          (vector_texture_coord_ac.m_y * vector_position_ab.m_y - vector_texture_coord_ab.m_y * vector_position_ac.m_y) * part_of_inverse_matrix,
                          (vector_texture_coord_ac.m_y * vector_position_ab.m_z - vector_texture_coord_ab.m_y * vector_position_ac.m_z) * part_of_inverse_matrix);

        *p_tangent = tangent;
    }

    if (p_binormal)
    {
        S_Vector3 binormal((vector_texture_coord_ab.m_x * vector_position_ac.m_x - vector_texture_coord_ac.m_x * vector_position_ab.m_x) * part_of_inverse_matrix,
                           (vector_texture_coord_ab.m_x * vector_position_ac.m_y - vector_texture_coord_ac.m_x * vector_position_ab.m_y) * part_of_inverse_matrix,
                           (vector_texture_coord_ab.m_x * vector_position_ac.m_z - vector_texture_coord_ac.m_x * vector_position_ab.m_z) * part_of_inverse_matrix);
    
        *p_binormal = binormal;
    }
}
    
    
/* 

 @brief     3�_����d�S���擾����
 @param[in] r_A 1�ڂ̍��W
 @param[in] r_B 2�ڂ̍��W
 @param[in] r_C 3�ڂ̍��W
 @return    S_Vector3<T> �d�S

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_CenterOfGravityWith3Points(const S_Vector3<T>& r_A,
                                                        const S_Vector3<T>& r_B,
                                                        const S_Vector3<T>& r_C)
{
    S_Vector3 center_of_gravity(r_A + r_B + r_C);
    center_of_gravity /= static_cast<T>(3);
    return center_of_gravity;
}
    
    
#pragma region S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h
    
    
/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator+(const S_Vector3<T>& r_ANOTHER) const
{
return S_Vector3(this->m_x + r_ANOTHER.m_x, 
                 this->m_y + r_ANOTHER.m_y,
                 this->m_z + r_ANOTHER.m_z);
}
    
    
/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator-(const S_Vector3<T>& r_ANOTHER) const
{
return S_Vector3(this->m_x - r_ANOTHER.m_x,
                 this->m_y - r_ANOTHER.m_y,
                 this->m_z - r_ANOTHER.m_z);
}
    
    
/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator*(const S_Vector3<T>& r_ANOTHER) const
{
return S_Vector3(this->m_x * r_ANOTHER.m_x,
                 this->m_y * r_ANOTHER.m_y,
                 this->m_z * r_ANOTHER.m_z);
}
    
    
/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator/(const S_Vector3<T>& r_ANOTHER) const
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    
    return S_Vector3(this->m_x / r_ANOTHER.m_x,
                     this->m_y / r_ANOTHER.m_y,
                     this->m_z / r_ANOTHER.m_z);
}
    
    
/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator+=(const S_Vector3<T>& r_ANOTHER)
{
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;
    this->m_z += r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator-=(const S_Vector3<T>& r_ANOTHER)
{
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;
    this->m_z -= r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T>& ��Z�����x�N�g��

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator*=(const S_Vector3<T>& r_ANOTHER)
{
    this->m_x *= r_ANOTHER.m_x;
    this->m_y *= r_ANOTHER.m_y;
    this->m_z *= r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector3<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator/=(const S_Vector3<T>& r_ANOTHER)
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    
    this->m_x /= r_ANOTHER.m_x;
    this->m_y /= r_ANOTHER.m_y;
    this->m_z /= r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     ���l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    bool  ��r��������
 @retval    true  �����x�N�g���̏ꍇ
 @retval    false �Ⴄ���x�N�g���̏ꍇ

*/
template<class T>
bool S_Vector3<T>::operator==(const S_Vector3<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) < GetEpsilon<T>()
        && Absolute(this->m_y - r_ANOTHER.m_y) < GetEpsilon<T>()
        && Absolute(this->m_z - r_ANOTHER.m_z) < GetEpsilon<T>();
}
    
   
/* 

 @brief     �񓙒l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    bool  ��r��������
 @retval    true  �Ⴄ�x�N�g���̏ꍇ
 @retval    false �����x�N�g���̏ꍇ

*/
template<class T>
bool S_Vector3<T>::operator!=(const S_Vector3<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) > GetEpsilon<T>()
        || Absolute(this->m_y - r_ANOTHER.m_y) > GetEpsilon<T>()
        || Absolute(this->m_z - r_ANOTHER.m_z) > GetEpsilon<T>();
}
    
    
#pragma endregion


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h
    
    
/* 

 @brief     T�^�̒l���e�����ɏ�Z�����x�N�g�������߂�
 @param[in] value T�^�̒l
 @return    const S_Vector3<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator*(T value) const
{
    return S_Vector3(this->m_x * value, this->m_y * value, this->m_z * value);
}
    
    
/* 

 @brief     T�^�̒l�Ŋe���������Z�����x�N�g�������߂�
 @param[in] value T�^�̒l
 @return    const S_Vector3<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator/(T value) const
{
    assert(value != 0);
    return S_Vector3(this->m_x / value, this->m_y / value, this->m_z / value);
}
    
    
/* 

 @brief     T�^�̒l���e�����ɏ�Z����
 @param[in] value T�^�̒l
 @return    const S_Vector3<T>& ��Z�����x�N�g��

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator*=(T value)
{
    this->m_x *= value;
    this->m_y *= value;
    this->m_z *= value;
    
    return (*this);
}
    
    
/* 

 @brief     T�^�̒l�Ŋe���������Z����
 @param[in] value T�^�̒l
 @return    const S_Vector3<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator/=(T value)
{
    assert(value != 0);
    
    this->m_x /= value;
    this->m_y /= value;
    this->m_z /= value;
    
    return (*this);
}
    
    
#pragma endregion
    
    
#pragma region �L���X�g
    
    
/* 

 @brief  S_Vector2�^�ւ̃L���X�g����
 @param  �Ȃ�
 @return S_Vector2<T> 2D�x�N�g��

*/
template<class T>
S_Vector3<T>::operator S_Vector2<T>() const
{
    return S_Vector2<T>(this->m_x, this->m_y);
}
    
    
/* 

 @brief  String�^�փL���X�g����
 @param  �Ȃ�
 @return String ������ɕϊ������x�N�g��

*/
template<class T>
S_Vector3<T>::operator String() const
{
    return this->ToString();
}
    
    
#pragma endregion


/* �����I�C���X�^���X�� */
template struct S_Vector3<float>;
template struct S_Vector3<double>;

