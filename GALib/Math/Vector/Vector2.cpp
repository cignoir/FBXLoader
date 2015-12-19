/* �w�b�_�t�@�C�� */
#include "Vector2.h"


// ���O��Ԃ��ȗ�
using namespace GALib::Math;


#pragma region �ÓI�����o�ϐ��̏�����


template<class T>
const S_Vector2<T> S_Vector2<T>::m_s_RIGHT_DIRECTION(static_cast<T>(1), 0);

template<class T>
const S_Vector2<T> S_Vector2<T>::m_s_LEFT_DIRECTION(-static_cast<T>(-1), 0);

template<class T>
const S_Vector2<T> S_Vector2<T>::m_s_UP_DIRECTION(0, static_cast<T>(1));

template<class T>
const S_Vector2<T> S_Vector2<T>::m_s_DOWN_DIRECTION(0, static_cast<T>(-1));

template<class T>
const S_Vector2<T> S_Vector2<T>::m_s_ZERO;

template<class T>
const S_Vector2<T> S_Vector2<T>::m_s_ONE(static_cast<T>(1));


#pragma endregion


/* 

 @brief �R���X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Vector2<T>::S_Vector2() :

    m_x(0),
    m_y(0)

{
}


/* 

 @brief     �R���X�g���N�^
 @param[in] value �l

*/
template<class T>
S_Vector2<T>::S_Vector2(T value) : 

    m_x(value), 
    m_y(value)

{
}


/* 

 @brief     �R���X�g���N�^
 @param[in] x X����
 @param[in] y Y����

*/
template<class T>
S_Vector2<T>::S_Vector2(T x, T y) :

    m_x(x),
    m_y(y)

{
}


/* 

 @brief     �R���X�g���N�^
 @param[in] ELEMENTS �v�f��2�̔z��

*/
template<class T>
S_Vector2<T>::S_Vector2(const T ELEMENTS[2]) :

    m_x(ELEMENTS[0]),
    m_y(ELEMENTS[1])

{
}


/* 

 @brief �f�X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Vector2<T>::~S_Vector2()
{
}


/* 

 @brief  �[���x�N�g��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector2<T>::Zero()
{
    this->m_x = 0;
    this->m_y = 0;
}


/* 

 @brief     �e���������̒l�ɕύX����
 @param[in] value �l
 @return    �Ȃ�

*/
template<class T>
void S_Vector2<T>::Fill(T value)
{
    this->m_x = value;
    this->m_y = value;
}


/* 

 @brief  �P�ʃx�N�g��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector2<T>::Normalize()
{
    // �傫�����擾
    T magnitude = this->GetMagnitude();
    assert(magnitude != 0);

    // �P�ʃx�N�g����
    this->m_x /= magnitude;
    this->m_y /= magnitude;
}


/* 

 @brief  �x�N�g���𔽓]����
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector2<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
}


/* 

 @brief  �����ȃx�N�g���ɕϊ�����
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Vector2<T>::Perpendicular()
{
    T temp_x = this->m_x;

    // �����ȃx�N�g���ɕϊ�
    this->m_x = -this->m_y;
    this->m_y = temp_x;
}


/* 

 @brief     �x�N�g������]����
 @param[in] angle �p�x( ���W�A���l )
 @return    �Ȃ�

*/
template<class T>
void S_Vector2<T>::Rotate(T angle)
{
    T temp_x = this->m_x;
    this->m_x = temp_x * Cosine(angle) - this->m_y * Sine(angle);
    this->m_y = temp_x * Sine(angle) + this->m_y * Cosine(angle);
}



/* 

 @brief     �x�N�g���̑傫���ŃN�����v����
 @param[in] min �ŏ��̒���
 @param[in] max �ő�̒���
 @return    �Ȃ�

*/
template<class T>
void S_Vector2<T>::ClampMagnitude(T min, T max)
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
T S_Vector2<T>::GetMagnitude() const
{
    return SquareRoot(this->GetMagnitudeSquare());
}


/* 

 @brief  �傫����2����擾����
 @param  �Ȃ�
 @return T �傫����2��

*/
template<class T>
T S_Vector2<T>::GetMagnitudeSquare() const
{
    return Square(this->m_x) + Square(this->m_y);
}


/* 

 @brief  �P�ʃx�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector2<T> �P�ʃx�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::GetNormalize() const
{
    S_Vector2 unit_vector(*this);
    unit_vector.Normalize();
    return unit_vector;
}


/* 

 @brief  ���]�����x�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector2<T> ���]�����x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::GetInvert() const
{
    return S_Vector2(-this->m_x, -this->m_y);
}


/* 

 @brief  �����ȃx�N�g�����擾����
 @param  �Ȃ�
 @return S_Vector2<T> �����ȃx�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::GetPerpendicular() const
{
    return S_Vector2(-m_y, m_x);
}


/* 

 @brief     ��]�����x�N�g�����擾����
 @param[in] angle �p�x( ���W�A���l )
 @return    S_Vector2<T> ��]�����x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::GetRotate(T angle) const
{
    S_Vector2 rotation_vector(*this);
    rotation_vector.Rotate(angle);
    return rotation_vector;
}


/* 

 @brief  �x�N�g���̊p�x���擾����
 @param  �Ȃ�
 @return T �p�x( ���W�A���l )

*/
template<class T>
T S_Vector2<T>::GetAngle() const
{
    return std::atan2(m_y, m_x);
}


/* 

 @brief     �傫���ŃN�����v�����x�N�g�����擾����
 @param[in] min �ŏ��̑傫��
 @param[in] max �ő�̑傫��
 @return    S_Vector2<T> �N�����v�����x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::GetClampMagnitude(T min, T max) const
{
    S_Vector2 clamp_vector = (*this);
    clamp_vector.ClampMagnitude(min, max);
    return clamp_vector;
}


/* 

 @brief  �x�N�g���𕶎���ɕϊ����Ď擾����
 @param  �Ȃ�
 @return String ������ɕϊ������x�N�g��

*/
template<class T>
String S_Vector2<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( X : %f, Y : %f )", this->m_x, this->m_y);
    return buffer;
}


/* 

 @brief     ���ς��擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T ����

*/
template<class T>
T S_Vector2<T>::s_DotProduct(const S_Vector2<T>& r_LHS, const S_Vector2<T>& r_RHS)
{
    return (r_LHS.m_x * r_RHS.m_x) + (r_LHS.m_y * r_RHS.m_y);
}


/* 

 @brief     �O�ς��擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T �O��

*/
template<class T>
T S_Vector2<T>::s_CrossProduct(const S_Vector2<T>& r_LHS, const S_Vector2<T>& r_RHS)
{
    return (r_LHS.m_x * r_RHS.m_y) - (r_RHS.m_x * r_LHS.m_y);
}


/* 

 @brief     ���`��Ԃ��s��
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] factor        ��ԌW��
 @return    S_Vector2<T> 2�̓_����`��Ԃ����_

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Lerp(const S_Vector2<T>& r_START_POINT,
                                  const S_Vector2<T>& r_END_POINT,
                                  T factor)
{
    S_Vector2 lerp_point;
    lerp_point.m_x = (r_END_POINT.m_x - r_START_POINT.m_x) * factor + r_START_POINT.m_x;
    lerp_point.m_y = (r_END_POINT.m_y - r_START_POINT.m_y) * factor + r_START_POINT.m_y;
    
    return lerp_point;
}


/* 

 @brief     ���ʐ��`��Ԃ��s��
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] factor        ��ԌW��
 @return    S_Vector2<T> 2�̓_�����ʐ��`��Ԃ����_

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Slerp(const S_Vector2<T>& r_START_POINT,
                                   const S_Vector2<T>& r_END_POINT,
                                   T factor)
{
    // �p�x�ƃT�C�������߂�
    T angle = s_AngleBetweenVectors(r_START_POINT, r_END_POINT);
    T sine = Sine(angle);

    // �e��ԌW�������߂�
    T start_factor = Sine(angle * (static_cast<T>(1) - factor));
    T end_factor = Sine(angle * factor);

    // ���ʐ��`��Ԃ����_�����߂�
    S_Vector2 slerp_point = r_START_POINT * start_factor + r_END_POINT * end_factor;
    return slerp_point;
}


/* 

 @brief     �G���~�[�g��Ԃ��s��
 @param[in] r_START_POINT   �n�_
 @param[in] r_START_TANGENT �n�_�̐ڐ�
 @param[in] r_END_POINT     �I�_
 @param[in] r_END_TANGENT   �I�_�̐ڐ�
 @param[in] factor          ��ԌW��
 @return    S_Vector2<T> 2�̓_���G���~�[�g��Ԃ����_

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Hermite(const S_Vector2<T>& r_START_POINT,
                                     const S_Vector2<T>& r_START_TANGENT,
                                     const S_Vector2<T>& r_END_POINT,
                                     const S_Vector2<T>& r_END_TANGENT,
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
    S_Vector2 hermite_point;

    hermite_point.m_x = r_START_POINT.m_x   * p_0 
                      + r_START_TANGENT.m_x * t_0 
                      + r_END_POINT.m_x     * p_1 
                      + r_END_TANGENT.m_x   * t_1;
    
    hermite_point.m_y = r_START_POINT.m_y   * p_0 
                      + r_START_TANGENT.m_y * t_0 
                      + r_END_POINT.m_y     * p_1
                      + r_END_TANGENT.m_y   * t_1;

    return hermite_point;
}


/* 

 @brief     Catmull-Rom�X�v���C����Ԃ��s��
 @param[in] r_PREVIOUS_START_POINT �n�_�̑O�̓_
 @param[in] r_START_POINT          �n�_
 @param[in] r_END_POINT            �I�_
 @param[in] r_NEXT_END_POINT       �I�_�̎�
 @param[in] factor                 ��ԌW��
 @return    S_Vector2<T> 2�̓_��Catmull-Rom�X�v���C����Ԃ����_

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_CatmullRomSpline(const S_Vector2<T>& r_PREVIOUS_START_POINT,
                                                const S_Vector2<T>& r_START_POINT,
                                                const S_Vector2<T>& r_END_POINT,
                                                const S_Vector2<T>& r_NEXT_END_POINT,
                                                T factor)
{
    // ���T�C�h�̓_����ڐ������߂�
    S_Vector2 start_tangent = (r_END_POINT - r_PREVIOUS_START_POINT) * static_cast<T>(0.5);
    S_Vector2 end_tangent = (r_NEXT_END_POINT - r_START_POINT) * static_cast<T>(0.5);

    // �ڐ��𗘗p���āA�G���~�[�g���
    S_Vector2 catmull_rom_spline_point = s_Hermite(r_START_POINT, start_tangent, r_END_POINT, end_tangent, factor);
    return catmull_rom_spline_point;
}


/* 

 @brief     �x�W�F��Ԃ��s��
 @param[in] r_START_POINT     �n�_
 @param[in] r_END_POINT       �I�_
 @param[in] r_CONTROL_POINT_1 ����_1
 @param[in] r_CONTROL_POINT_2 ����_2
 @param[in] factor            ��ԌW��
 @return    S_Vector2<T> 2�̓_���x�W�F�\��Ԃ����_

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Bezier(const S_Vector2<T>& r_START_POINT,
                                    const S_Vector2<T>& r_END_POINT,
                                    const S_Vector2<T>& r_CONTROL_POINT_1,
                                    const S_Vector2<T>& r_CONTROL_POINT_2,
                                    T factor)
{
    // �e�_�̌W�������߂�
    T one_minus_factor = static_cast<T>(1) - factor;

    T p_0 = Cubic(one_minus_factor);
    T p_1 = Cubic(factor);
    T c_0 = static_cast<T>(3) * factor * Square(one_minus_factor);
    T c_1 = static_cast<T>(3) * Square(factor) * one_minus_factor;

    // �x�W�F��Ԃ���
    S_Vector2 bezier_point;

    bezier_point.m_x = r_START_POINT.m_x    * p_0 
                    + r_END_POINT.m_x       * p_1
                    + r_CONTROL_POINT_1.m_x * c_0
                    + r_CONTROL_POINT_2.m_x * c_1;

    bezier_point.m_y = r_START_POINT.m_y    * p_0 
                    + r_END_POINT.m_y       * p_1
                    + r_CONTROL_POINT_1.m_y * c_0 
                    + r_CONTROL_POINT_2.m_y * c_1;

    return bezier_point;
}


/* 

 @brief     �p�x����x�N�g�����쐬����
 @param[in] angle  �p�x( ���W�A���l )
 @param[in] length ����
 @return    S_Vector2<T> �x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_CreateWithAngle(T angle, T length)
{
    return S_Vector2(Cosine(angle), Sine(angle)) * length;
}


/* 

 @brief     �}���|�C���g( �����ʒu )�����߂�
 @param[in] r_POSITION         ���W
 @param[in] r_VELOCITY         ���x
 @param[in] r_ANOTHER_POSITION ����1�̍��W
 @param[in] r_ANOTHER_VELOCITY ����1�̑��x
 @return    S_Vector2<T> �}���|�C���g

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_InterceptPoint(const S_Vector2<T>& r_POSITION,
                                            const S_Vector2<T>& r_VELOCITY,
                                            const S_Vector2<T>& r_ANOTHER_POSITION,
                                            const S_Vector2<T>& r_ANOTHER_VELOCITY)
{
    // �����Ƒ��x�̍������߂�
    S_Vector2 distance = r_POSITION - r_ANOTHER_POSITION;
    S_Vector2 velocity_difference = r_VELOCITY - r_ANOTHER_VELOCITY;

    // �������瑬�x������A���Ԃ�����
    T time = distance.GetMagnitude() / velocity_difference.GetMagnitude();

    // �}���|�C���g�����߂�
    S_Vector2 intercept_point = r_POSITION + (r_VELOCITY * time);
    return intercept_point;
}



/* 

 @brief     �x�N�g���Ԃ̊p�x�����߂�
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T �p�x( ���W�A���l )

*/
template<class T>
T S_Vector2<T>::s_AngleBetweenVectors(const S_Vector2<T>& r_LHS, const S_Vector2<T>& r_RHS)
{
    T cosine = s_DotProduct(r_LHS.GetNormalize(), r_RHS.GetNormalize());
    T angle = std::acos(cosine);
    return angle;
}


/* 

 @brief     �x�N�g���Ԃ̋��������߂�
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    T ����

*/
template<class T>
T S_Vector2<T>::s_DistanceBetweenVectors(const S_Vector2<T>& r_LHS, const S_Vector2<T>& r_RHS)
{
    S_Vector2 distance = r_LHS - r_RHS;
    return distance.GetMagnitude();
}


/* 

 @brief     �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    S_Vector2<T> �ŏ��l�𐬕��ɂ����x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Minimize(const S_Vector2<T>& r_LHS, const S_Vector2<T>& r_RHS)
{
    S_Vector2 min_vector;

    min_vector.m_x = (r_LHS.m_x < r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    min_vector.m_y = (r_LHS.m_y < r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;

    return min_vector;
}


/* 

 @brief     �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾����
 @param[in] r_LHS 1�ڂ̃x�N�g��
 @param[in] r_RHS 2�ڂ̃x�N�g��
 @return    S_Vector2<T> �ő�l�𐬕��ɂ����x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Maximize(const S_Vector2<T>& r_LHS, const S_Vector2<T>& r_RHS)
{
    S_Vector2 max_vector;

    max_vector.m_x = (r_LHS.m_x > r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    max_vector.m_y = (r_LHS.m_y > r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;

    return max_vector;
}


/* 

 @brief     2�_�Ԃ���̋����������i�񂾓_���擾����
 @param[in] r_START_POINT �n�_
 @param[in] r_END_POINT   �I�_
 @param[in] distance      ����
 @return    S_Vector2<T> �ő�l�𐬕��ɂ����x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_MoveTowards(const S_Vector2<T>& r_START_POINT,
                                         const S_Vector2<T>& r_END_POINT,
                                         T distance)
{
    if (distance < 0) return r_START_POINT;

    S_Vector2 difference = r_START_POINT - r_END_POINT;
    S_Vector2 movement = difference.GetNormalize() * distance;

    if (movement.GetMagnitudeSquare() >= difference.GetMagnitudeSquare()) return r_END_POINT;
    return r_START_POINT + movement;
}


/* 

 @brief     ���e�x�N�g�����擾����
 @param[in] r_VECTOR �x�N�g��
 @param[in] r_NORMAL �@���x�N�g��
 @return    S_Vector2<T> ���e�x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Project(const S_Vector2<T>& r_VECTOR,
                                     const S_Vector2<T>& r_NORMAL)
{
    // �P�ʃx�N�g���������@���Ɠ��e�̒������擾
    S_Vector2 unit_normal = r_NORMAL.GetNormalize();
    T length = s_DotProduct(r_VECTOR, unit_normal);

    return unit_normal * length;
}


/* 

 @brief     ���˃x�N�g�����擾����
 @param[in] r_VECTOR �x�N�g��
 @param[in] r_NORMAL �@���x�N�g��
 @return    S_Vector2<T> ���˃x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Reflect(const S_Vector2<T>& r_VECTOR,
                                     const S_Vector2<T>& r_NORMAL)
{
    // �P�ʃx�N�g���������@�����擾
    S_Vector2 unit_normal = r_NORMAL.GetNormalize();

    // ���˃x�N�g�������߂�
    S_Vector2 reflection_vector = r_VECTOR - static_cast<T>(2) * s_DotProduct(r_VECTOR, unit_normal) * unit_normal;
    return reflection_vector;
}


/* 

 @brief     ���܃x�N�g�����擾����
 @param[in] r_INCIDENT_VECTOR ���˃x�N�g��
 @param[in] r_NORMAL          �@���x�N�g��
 @param[in] refractive_index  ���ܗ�
 @return    S_Vector2<T> ���܃x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Refract(const S_Vector2<T>& r_INCIDENT_VECTOR,
                                     const S_Vector2<T>& r_NORMAL,
                                     T refractive_index)
{
    // �e�x�N�g����P�ʃx�N�g����
    S_Vector2 unit_incident_vector = r_INCIDENT_VECTOR.GetNormalize();
    S_Vector2 unit_normal = r_NORMAL.GetNormalize();

    // ���˃x�N�g���Ɩ@���x�N�g���̓��ς����߂�
    T dot = s_DotProduct(unit_incident_vector, unit_normal);

    // ���܂̊p�x
    T refract_angle = static_cast<T>(1) - Square(refractive_index) * (static_cast<T>(1) - Square(dot));

    // ���܃x�N�g�������߂�
    S_Vector2 refract_vector;
    if (refract_angle < 0) return refract_vector;

    refract_vector = refractive_index * unit_incident_vector
                   - (refractive_index * dot * Square(refract_angle) * unit_normal);

    return refract_vector;
}


/* 

 @brief     ���肵���x�N�g�����擾����
 @param[in] r_VECTOR �x�N�g��
 @param[in] r_NORMAL �@���x�N�g��
 @return    S_Vector2<T> ���肵���x�N�g��

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_Slide(const S_Vector2<T>& r_VECTOR, const S_Vector2<T>& r_NORMAL)
{
    // �P�ʃx�N�g���������@�����擾
    S_Vector2 unit_normal = r_NORMAL.GetNormalize();

    // ����x�N�g�������߂�
    S_Vector2 slide_vector = r_VECTOR - s_DotProduct(r_VECTOR, unit_normal) * unit_normal;
    return slide_vector;
}


/* 

 @brief     3�_����d�S���擾����
 @param[in] rA 1�ڂ̓_
 @param[in] rB 2�ڂ̓_
 @param[in] rC 3�ڂ̓_
 @return    S_Vector2<T> �d�S

*/
template<class T>
S_Vector2<T> S_Vector2<T>::s_CenterOfGravityWith3Points(const S_Vector2<T>& rA,
                                                        const S_Vector2<T>& rB,
                                                        const S_Vector2<T>& rC)
{
    S_Vector2 center_of_gravity(rA + rB + rC);
    center_of_gravity /= static_cast<T>(3);
    return center_of_gravity;
}


#pragma region S_Vector2�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector2<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T> S_Vector2<T>::operator+(const S_Vector2<T>& r_ANOTHER) const
{
    return S_Vector2(this->m_x + r_ANOTHER.m_x, this->m_y + r_ANOTHER.m_y);
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector2<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T> S_Vector2<T>::operator-(const S_Vector2<T>& r_ANOTHER) const
{
    return S_Vector2(this->m_x - r_ANOTHER.m_x, this->m_y - r_ANOTHER.m_y);
}


/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector2<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector2<T> S_Vector2<T>::operator*(const S_Vector2<T>& r_ANOTHER) const
{
    return S_Vector2(m_x * r_ANOTHER.m_x, m_y * r_ANOTHER.m_y);
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    S_Vector2<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T> S_Vector2<T>::operator/(const S_Vector2<T>& r_ANOTHER) const
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);

    return S_Vector2(this->m_x / r_ANOTHER.m_x, this->m_y / r_ANOTHER.m_y);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector2<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T>& S_Vector2<T>::operator+=(const S_Vector2<T>& r_ANOTHER)
{
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector2<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T>& S_Vector2<T>::operator-=(const S_Vector2<T>& r_ANOTHER)
{
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;

    return (*this);
}


/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector2<T>& ��Z�����x�N�g��

*/
template<class T>
const S_Vector2<T>& S_Vector2<T>::operator*=(const S_Vector2<T>& r_ANOTHER)
{
    this->m_x *= r_ANOTHER.m_x;
    this->m_y *= r_ANOTHER.m_y;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    const S_Vector2<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T>& S_Vector2<T>::operator/=(const S_Vector2<T>& r_ANOTHER)
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);

    this->m_x /= r_ANOTHER.m_x;
    this->m_y /= r_ANOTHER.m_y;

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
bool S_Vector2<T>::operator==(const S_Vector2<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) < static_cast<T>(GetEpsilon<T>())
        && Absolute(this->m_y - r_ANOTHER.m_y) < static_cast<T>(GetEpsilon<T>());
}


/* 

 @brief     �񓙒l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃x�N�g��
 @return    bool  ��r��������
 @retval    true  �Ⴄ�x�N�g���̏ꍇ
 @retval    false �����x�N�g���̏ꍇ

*/
template<class T>
bool S_Vector2<T>::operator!=(const S_Vector2<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) > static_cast<T>(GetEpsilon<T>())
        || Absolute(this->m_y - r_ANOTHER.m_y) > static_cast<T>(GetEpsilon<T>());
}


#pragma endregion


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector2<T> ��Z�����x�N�g��

*/
template<class T>
const S_Vector2<T> S_Vector2<T>::operator*(T value) const
{
    return S_Vector2(this->m_x * value, this->m_y * value);
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector2<T> ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T> S_Vector2<T>::operator/(T value) const
{
    assert(value != 0);
    return S_Vector2(this->m_x / value, this->m_y / value);
}


/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector2<T>& ��Z�����x�N�g��

*/
template<class T>
const S_Vector2<T>& S_Vector2<T>::operator*=(T value)
{
    this->m_x *= value;
    this->m_y *= value;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] value �l
 @return    const S_Vector2<T>& ���Z�����x�N�g��

*/
template<class T>
const S_Vector2<T>& S_Vector2<T>::operator/=(T value)
{
    assert(value != 0);

    this->m_x /= value;
    this->m_y /= value;

    return (*this);
}


#pragma endregion


#pragma region �L���X�g


/* 

 @brief  String�^�ւ̃L���X�g
 @param  �Ȃ�
 @return String ������ɕϊ������x�N�g��

*/
template<class T>
S_Vector2<T>::operator String() const
{
    return this->ToString();
}


#pragma endregion


/* �����I�C���X�^���X�� */
template struct S_Vector2<float>;
template struct S_Vector2<double>;

