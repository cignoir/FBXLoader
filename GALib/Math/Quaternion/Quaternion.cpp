/* �w�b�_�t�@�C�� */
#include "Quaternion.h"
#include "..\Matrix\Matrix3x3.h"
#include "..\Matrix\Matrix4x4.h"


// ���O��Ԃ��ȗ�
using namespace GALib::Math;


/* �v���g�^�C�v�錾 */
template<class T>
static S_Quaternion<T> m_s_LerpQuaternion(const S_Quaternion<T>& r_START_QUATERNION,
                                          const S_Quaternion<T>& r_END_QUATERNION,
                                          T factor);


#pragma region �ÓI�����o�ϐ��̏�����


template<class T>
const S_Quaternion<T> S_Quaternion<T>::m_s_IDENTITY(static_cast<T>(1), 0, 0, 0);


#pragma endregion


/* 

 @brief �R���X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Quaternion<T>::S_Quaternion() : 
    
    m_t(0),
    m_x(0),
    m_y(0),
    m_z(0)

{
}


/* 

 @brief     �R���X�g���N�^( �l�őS�v�f�������� )
 @param[in] value �l

*/
template<class T>
S_Quaternion<T>::S_Quaternion(T value) :

    m_t(value),
    m_x(value),
    m_y(value),
    m_z(value)

{
}


/* 

 @brief     �R���X�g���N�^( �e�v�f�ŏ����� )
 @param[in] t T����
 @param[in] x X����
 @param[in] y Y����
 @param[in] z Z����

*/
template<class T>
S_Quaternion<T>::S_Quaternion(T t, T x, T y, T z) :

    m_t(t),
    m_x(x),
    m_y(y),
    m_z(z)

{
}


/* 

 @brief     �R���X�g���N�^( T������3D�x�N�g���ŏ����� )
 @param[in] t     T����
 @param[in] r_XYZ X�EY�EZ����

*/
template<class T>
S_Quaternion<T>::S_Quaternion(T t, const S_Vector3<T>& r_XYZ) :

    m_t(t),
    m_x(r_XYZ.m_x),
    m_y(r_XYZ.m_y),
    m_z(r_XYZ.m_z)

{
}


/* 

 @brief �f�X�g���N�^
 @param �Ȃ�

*/
template<class T>
S_Quaternion<T>::~S_Quaternion()
{
}


/* 

 @brief     �e���������̒l�ɕύX����
 @param[in] value �l
 @return    �Ȃ�

*/
template<class T>
void S_Quaternion<T>::Fill(T value)
{
    this->m_t = value;
    this->m_x = value;
    this->m_y = value;
    this->m_z = value;
}


/* 

 @brief  �P�ʃN�H�[�^�j�I��������
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Quaternion<T>::Identity()
{
    this->m_t = static_cast<T>(1);
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
}


/* 

 @brief  ���K�����s��
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Quaternion<T>::Normalize()
{
    // �傫�����擾
    T magnitude = GetMagnitude();
    assert(magnitude != 0);

    // ���K��
    this->m_t /= magnitude;
    this->m_x /= magnitude;
    this->m_y /= magnitude;
    this->m_z /= magnitude;
}


/* 

 @brief  �t�N�H�[�^�j�I�������s��
 @param  �Ȃ�
 @return �Ȃ�

*/
template<class T>
void S_Quaternion<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
    this->m_z *= static_cast<T>(-1);
}


/* 

 @brief  �傫�����擾����
 @param  �Ȃ�
 @return T �傫��

*/
template<class T>
T S_Quaternion<T>::GetMagnitude() const
{
    return SquareRoot(GetMagnitudeSquare());
}


/* 

 @brief  �傫����2����擾����
 @param  �Ȃ�
 @return T �傫����2��

*/
template<class T>
T S_Quaternion<T>::GetMagnitudeSquare() const
{
    return Square(this->m_t) + Square(this->m_x) + Square(this->m_y) + Square(this->m_z);
}


/* 

 @brief  ���K�������N�H�[�^�j�I�����擾����
 @param  �Ȃ�
 @return S_Quaternion<T> ���K�������N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::GetNormalize() const
{
    S_Quaternion temp(*this);
    temp.Normalize();

    return temp;
}


/* 

 @brief  �t�N�H�[�^�j�I�����擾����
 @param  �Ȃ�
 @return S_Quaternion<T> �t�N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::GetInvert() const
{
    S_Quaternion temp(*this);
    temp.Invert();

    return temp;
}


/* 

 @brief  X������̊p�x���擾����
 @param  �Ȃ�
 @return T �p�x( ���W�A���l )

*/
template<class T>
T S_Quaternion<T>::GetAngleFromXAxis() const
{
    T angle = std::atan2(static_cast<T>(2) * (this->m_y * this->m_z + this->m_t * this->m_x),
                         Square(this->m_t) - Square(this->m_x) - Square(this->m_y) + Square(this->m_z));

    return angle;
}


/* 

 @brief  Y������̊p�x���擾����
 @param  �Ȃ�
 @return T �p�x( ���W�A���l )

*/
template<class T>
T S_Quaternion<T>::GetAngleFromYAxis() const
{
    T angle = std::asin(static_cast<T>(-2) * (this->m_x * this->m_z - this->m_t * this->m_y));
    return angle;
}


/* 

 @brief  Z������̊p�x���擾����
 @param  �Ȃ�
 @return T �p�x( ���W�A���l )

*/
template<class T>
T S_Quaternion<T>::GetAngleFromZAxis() const
{
    T angle = std::atan2(static_cast<T>(2) * (this->m_x * this->m_y + this->m_t * this->m_z),
                         Square(this->m_t) + Square(this->m_x) - Square(this->m_y) - Square(this->m_z));

    return angle;
}


/* 

 @brief     ���Ɗp�x���擾����
 @param[in] p_axis  ��
 @param[in] p_angle �p�x( ���W�A���l )
 @return    �Ȃ�

*/
template<class T>
void S_Quaternion<T>::GetAxisAndAngle(S_Vector3<T>* p_axis, T* p_angle) const
{
    assert(p_axis && p_angle);

    // �p�x�̔����ƃT�C�������߂�
    T half_angle = 0, sine = 0;

    half_angle = static_cast<T>(std::acos(this->m_t));

    sine = SquareRoot(Square(this->m_x) + Square(this->m_y) + Square(this->m_z));
    T absolute_sine = Absolute(sine);

    // �T�C�����玲�Ɗp�x��ݒ�
    if (absolute_sine < GetEpsilon<T>() || Absolute(absolute_sine - Get2Pi<T>()) < GetEpsilon<T>())
    {
        *p_angle = 0;

        p_axis->m_x = 0;
        p_axis->m_y = 0;
        p_axis->m_z = static_cast<T>(1);
    }
    else
    {
        *p_angle = half_angle * static_cast<T>(2);
        
        p_axis->m_x = this->m_x / sine;
        p_axis->m_y = this->m_y / sine;
        p_axis->m_z = this->m_z / sine;
        p_axis->Normalize();
    }
}


/* 

 @brief  �x�N�g���𕶎���Ƃ��Ď擾����
 @param  �Ȃ�
 @return String ������ɕϊ������x�N�g��

*/
template<class T>
String S_Quaternion<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( T : %f, X : %f, Y : %f, Z : %f )", this->m_t, this->m_x, this->m_y, this->m_z);
    return buffer;
}


/* 

 @brief  ���ς����߂�
 @param  �Ȃ�
 @return T ����

*/
template<class T>
T S_Quaternion<T>::s_DotProduct(const S_Quaternion<T>& rLhs, const S_Quaternion<T>& rRhs)
{
    return (rLhs.m_t * rRhs.m_t)
         + (rLhs.m_x * rRhs.m_x)
         + (rLhs.m_y * rRhs.m_y)
         + (rLhs.m_z * rRhs.m_z);
}


/* 

 @brief     �C�ӎ������]�N�H�[�^�j�I�����쐬����
 @param[in] r_AXIS ��
 @param[in] angle  �p�x( ���W�A���l )
 @return    S_Quaternion<T> ��]�N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // �p�x�̔����Ƃ��̃T�C�������߂�
    T half_angle = angle * static_cast<T>(0.5);
    T sine = static_cast<T>(Sine(static_cast<T>(half_angle)));

    // ��]�N�H�[�^�j�I�������߂�
    S_Quaternion rotation_quaternion(Cosine(half_angle),
                                     r_AXIS.m_x * sine,
                                     r_AXIS.m_y * sine,
                                     r_AXIS.m_z * sine);

    rotation_quaternion.Normalize();
    return rotation_quaternion;
}


/* 

 @brief     3���̉�]�𔽉f������]�N�H�[�^�j�I�����쐬����
 @param[in] pitch �s�b�`( X���̊p�x�E���W�A���l )
 @param[in] yaw   ���[( Y���̊p�x�E���W�A���l )
 @param[in] roll  ���[��( Z���̊p�x�E���W�A���l )
 @return    S_Quaternion<T> ��]�N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(T pitch,
                                                              T yaw,
                                                              T roll)
{
    // �e�p�x�𒲐�
    pitch = AdjustRadianFrom0To2pi(pitch);
    yaw = AdjustRadianFrom0To2pi(yaw);
    roll = AdjustRadianFrom0To2pi(roll);

    // �e���̃T�C���ƃR�T�C�������߂�
    T sine_x = Sine(pitch * static_cast<T>(0.5));
    T cosine_x = Cosine(pitch * static_cast<T>(0.5));

    T sine_y = Sine(yaw * static_cast<T>(0.5));
    T cosine_y = Cosine(yaw * static_cast<T>(0.5));

    T sine_z = Sine(roll * static_cast<T>(0.5));
    T cosine_z = Cosine(roll * static_cast<T>(0.5));

    // ��]�N�H�[�^�j�I�������߂�
    S_Quaternion rotation_quaternion;

    rotation_quaternion.m_t = (cosine_y * cosine_z * cosine_x) - (sine_y   * sine_z   * sine_x);
    rotation_quaternion.m_x = (sine_y   * sine_z   * cosine_x) + (cosine_y * cosine_z * sine_x);
    rotation_quaternion.m_y = (sine_y   * cosine_z * cosine_x) + (cosine_y * sine_z   * sine_x);
    rotation_quaternion.m_z = (cosine_y * sine_z   * cosine_x) - (sine_y   * cosine_z * sine_x);

    return rotation_quaternion;
}


/* 

 @brief     3���̉�]�𔽉f������]�N�H�[�^�j�I�����쐬����
 @param[in] r_ROTATION ��]��
 @return    S_Quaternion<T> ��]�N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(const S_Vector3<T>& r_ROTATION)
{
    return s_CreateRotationPitchYawRoll(r_ROTATION.m_x, r_ROTATION.m_y, r_ROTATION.m_z);
}


/* 

 @brief     �C�ӂ̌����֌������߂̉�]�N�H�[�^�j�I�����쐬����
 @param[in] r_DIRECTION ����
 @param[in] r_UP_VECTOR �����
 @return    S_Quaternion<T> ��]�N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateLookRotation(const S_Vector3<T>& r_DIRECTION,
                                                      const S_Vector3<T>& r_UP_VECTOR)
{
    // 3 * 3�s��̃r���[�s����쐬���A�N�H�[�^�j�I���ɕϊ�
    S_Matrix3x3<T> view_matrix;
    view_matrix = S_Matrix3x3<T>::s_CreateLookAt(S_Vector3<T>::m_s_ZERO, r_DIRECTION, r_UP_VECTOR);

    S_Quaternion rotation_quaternion = s_ConvertMatrix3x3ToQuaternion(view_matrix);
    rotation_quaternion.Normalize();

    return rotation_quaternion;
}


/* 

 @brief     ������������։�]�������]�N�H�[�^�j�I�����쐬����
 @param[in] r_FROM_DIRECTION ��]�O�̌���
 @param[in] r_TO_DIRECTION   �����
 @return    S_Quaternion<T> ��]�N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateFromToRotation(const S_Vector3<T>& r_FROM_DIRECTION,
                                                        const S_Vector3<T>& r_TO_DIRECTION)
{
    // �p�x�Ǝ������߂�
    T angle = S_Vector3<T>::s_AngleBetweenVectors(r_FROM_DIRECTION, r_TO_DIRECTION);
    S_Vector3<T> axis = S_Vector3<T>::s_CrossProduct(r_FROM_DIRECTION, r_TO_DIRECTION);

    // ��]�N�H�[�^�j�I�����쐬
    S_Quaternion rotation_quaternion = s_CreateRotationAxis(axis, angle);
    return rotation_quaternion;
}


/* 

 @brief     3 * 3�̍s�񂩂�N�H�[�^�j�I���֕ϊ����A�擾����
 @param[in] r_MATRIX 3 * 3�̍s�����
 @return    S_Quaternion<T> �N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& r_MATRIX)
{
    // �ϊ���̃N�H�[�^�j�I��
    S_Quaternion<T> convertion_quaternion;

    // �]�u�s����擾
    S_Matrix3x3<T> transpose_matrix(r_MATRIX.GetTranspose());

    // ( 4x4�s��̏ꍇ�� )�Ίp���̍��v
    T diagonal_sum = transpose_matrix.m_a_11
                   + transpose_matrix.m_a_22
                   + transpose_matrix.m_a_33
                   + static_cast<T>(1);

    // �Ίp���̃X�P�[��
    T diagonal_scale = 0;

    // �Ίp���̍��v��0���߂̏ꍇ
    if (diagonal_sum > GetEpsilon<T>())
    {
        // �Ίp���̃X�P�[�������߂�
        diagonal_scale = SquareRoot(diagonal_sum) * static_cast<T>(2);

        // �e���������߂�
        convertion_quaternion.m_t = static_cast<T>(0.25) * diagonal_scale;
        convertion_quaternion.m_x = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
        convertion_quaternion.m_y = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
        convertion_quaternion.m_z = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
    }
    else
    {
        // �Ίp���̍ő�l�ɉ����Đ��������߂�
        if (transpose_matrix.m_a_11 > transpose_matrix.m_a_22 && transpose_matrix.m_a_11 > transpose_matrix.m_a_33)
        {
            // �Ίp���̃X�P�[�������߂�
            diagonal_scale = SquareRoot(static_cast<T>(1) + transpose_matrix.m_a_11 - transpose_matrix.m_a_22 - transpose_matrix.m_a_33) * static_cast<T>(2);

            // �e���������߂�
            convertion_quaternion.m_t = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
            convertion_quaternion.m_x = static_cast<T>(0.25) * diagonal_scale;
            convertion_quaternion.m_y = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
            convertion_quaternion.m_z = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
        }
        else if (transpose_matrix.m_a_22 > transpose_matrix.m_a_33)
        {
            // �Ίp���̃X�P�[�������߂�
            diagonal_scale = SquareRoot(static_cast<T>(1) + transpose_matrix.m_a_22 - transpose_matrix.m_a_11 - transpose_matrix.m_a_33) * static_cast<T>(2);

            // �e���������߂�
            convertion_quaternion.m_t = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
            convertion_quaternion.m_x = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
            convertion_quaternion.m_y = static_cast<T>(0.25) * diagonal_scale;
            convertion_quaternion.m_z = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
        }
        else
        {
            // �Ίp���̃X�P�[�������߂�
            diagonal_scale = SquareRoot(static_cast<T>(1) + transpose_matrix.m_a_33 - transpose_matrix.m_a_11 - transpose_matrix.m_a_22) * static_cast<T>(2);

            // �e���������߂�
            convertion_quaternion.m_t = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
            convertion_quaternion.m_x = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
            convertion_quaternion.m_y = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
            convertion_quaternion.m_z = static_cast<T>(0.25) * diagonal_scale;
        }
    }

    return convertion_quaternion;
}


/* 

 @brief     4 * 4�̍s�񂩂�N�H�[�^�j�I���֕ϊ����A�擾����
 @param[in] r_MATRIX 4 * 4�̍s��
 @return    S_Quaternion<T> �N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& r_MATRIX)
{
    return s_ConvertMatrix3x3ToQuaternion(S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(r_MATRIX));
}


/* 

 @brief     ���`��Ԃ��s��
 @param[in] r_START �J�n�l
 @param[in] r_END   �I���l
 @param[in] factor  ��ԌW��
 @return    S_Quaternion<T> ��̃N�H�[�^�j�I������`��Ԃ����N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_Lerp(const S_Quaternion<T>& r_START,
                                        const S_Quaternion<T>& r_END,
                                        T factor)
{
    S_Quaternion lerp_point;

    if (s_DotProduct(r_START, r_END) > 0)
    {
        lerp_point = s_LerpQuaternion(r_START, r_END, factor);
    }
    else
    {
        lerp_point = s_LerpQuaternion(r_START, r_END * T(-1), factor);
    }

    return lerp_point;
}


/* 

 @brief     ���ʐ��`��Ԃ��s��
 @param[in] r_START �J�n�l
 @param[in] r_END   �I���l
 @param[in] factor  ��ԌW��
 @return    S_Quaternion<T> ��̃N�H�[�^�j�I�������ʐ��`��Ԃ����N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_Slerp(const S_Quaternion<T>& r_START,
                                         const S_Quaternion<T>& r_END,
                                         T factor)
{
    // ���ʐ��`��Ԍ�̃N�H�[�^�j�I��
    S_Quaternion slerp_quaternion;

    // ����
    T dot = s_DotProduct(r_START, r_END);

    // ���ς̂������l
    const T DOT_THRESHOLD = static_cast<T>(0.9995);

    if (dot > DOT_THRESHOLD)
    {
        // ����1�̃N�H�[�^�j�I���Ƃ̍�
        S_Quaternion difference(r_END - r_START);

        // ���ɕ�ԌW�����|���A����Ɏ��g�𑫂����l�����߂�
        difference *= factor;
        slerp_quaternion = r_START + difference;

        // �N�H�[�^�j�I���𐳋K��
        slerp_quaternion.Normalize();
    }
    else
    {
        // ���ς��N�����v���A�p�x�����߂�
        dot = Clamp(dot, T(-1), static_cast<T>(1));
        T angle = T(std::acos(static_cast<double>(dot)));

        // �p�x�ɕ�ԌW�����|����
        T interpolation_angle = angle * factor;

        // ���g�ɓ��ς��������l�����߁A����1�̃N�H�[�^�j�I���Ƃ̍��������߂�
        S_Quaternion dot_quaternion(r_START * dot);
        S_Quaternion difference(r_END - dot_quaternion);

        // �����𐳋K��
        difference.Normalize();

        // ���g�ƕ�ԌW�����|�����p�x�̃R�T�C�����|�����N�H�[�^�j�I��
        S_Quaternion cosine_quaternion(r_START * Cosine(interpolation_angle));

        // �����ƕ�ԌW�����������p�x�̃T�C�����|�����N�H�[�^�j�I��
        S_Quaternion sine_quaternion(difference * Sine(interpolation_angle));

        // 2�̃N�H�[�^�j�I�������킹��
        slerp_quaternion = cosine_quaternion + sine_quaternion;
    }

    return slerp_quaternion;
}


#pragma region S_Quaternion�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T> ���Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator+(const S_Quaternion<T>& r_ANOTHER) const
{
    S_Quaternion temp;

    temp.m_t = this->m_t + r_ANOTHER.m_t;
    temp.m_x = this->m_x + r_ANOTHER.m_x;
    temp.m_y = this->m_y + r_ANOTHER.m_y;
    temp.m_z = this->m_z + r_ANOTHER.m_z;

    return temp;
}


/* 

 @brief     ���Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T> ���Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator-(const S_Quaternion<T>& r_ANOTHER) const
{
    S_Quaternion temp;

    temp.m_t = this->m_t - r_ANOTHER.m_t;
    temp.m_x = this->m_x - r_ANOTHER.m_x;
    temp.m_y = this->m_y - r_ANOTHER.m_y;
    temp.m_z = this->m_z - r_ANOTHER.m_z;

    return temp;
}


/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T> ��Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator*(const S_Quaternion<T>& r_ANOTHER) const
{
    S_Vector3<T> xyz(this->m_x, this->m_y, this->m_z);
    S_Vector3<T> another_xyz(r_ANOTHER.m_x, r_ANOTHER.m_y, r_ANOTHER.m_z);

    // ���������߂�
    T temp_t = (this->m_t * r_ANOTHER.m_t)
             - S_Vector3<T>::s_DotProduct(xyz, another_xyz);

    // ���������߂�
    S_Vector3<T> temp_xyz = (this->m_t * another_xyz)
                          + (r_ANOTHER.m_t * xyz)
                          + S_Vector3<T>::s_CrossProduct(xyz, another_xyz);

    return S_Quaternion(temp_t, temp_xyz);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T>& ���Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator+=(const S_Quaternion<T>& r_ANOTHER)
{
    this->m_t += r_ANOTHER.m_t;
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;
    this->m_z += r_ANOTHER.m_z;

    return (*this);
}


/* 

 @brief     ���Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T>& ���Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator-=(const S_Quaternion<T>& r_ANOTHER)
{
    this->m_t -= r_ANOTHER.m_t;
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;
    this->m_z -= r_ANOTHER.m_z;

    return (*this);
}


/* 

 @brief     ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T>& ��Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator*=(const S_Quaternion<T>& r_ANOTHER)
{
    S_Quaternion temp;

    S_Vector3<T> xyz(this->m_x, this->m_y, this->m_z);
    S_Vector3<T> another_xyz(r_ANOTHER.m_x, r_ANOTHER.m_y, r_ANOTHER.m_z);

    // ���������߂�
    T temp_t = (this->m_t * r_ANOTHER.m_t)
             - S_Vector3<T>::s_DotProduct(xyz, another_xyz);

    // ���������߂�
    S_Vector3<T> temp_xyz = (this->m_t * another_xyz)
                          + (r_ANOTHER.m_t * xyz)
                          + S_Vector3<T>::s_CrossProduct(xyz, another_xyz);

    this->m_t = temp_t;
    this->m_x = temp_xyz.m_x;
    this->m_y = temp_xyz.m_y;
    this->m_z = temp_xyz.m_z;

    (*this) = temp;

    return (*this);
}


/* 

 @brief     ���l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    bool  ��r��������
 @retval    true  �����N�H�[�^�j�I���̏ꍇ
 @retval    false �Ⴄ�N�H�[�^�j�I���̏ꍇ

*/
template<class T>
bool S_Quaternion<T>::operator==(const S_Quaternion<T>& r_ANOTHER) const
{
    return Absolute(this->m_t - r_ANOTHER.m_t) < GetEpsilon<T>()
        && Absolute(this->m_x - r_ANOTHER.m_x) < GetEpsilon<T>()
        && Absolute(this->m_y - r_ANOTHER.m_y) < GetEpsilon<T>()
        && Absolute(this->m_z - r_ANOTHER.m_z) < GetEpsilon<T>();
}


/* 

 @brief     �񓙒l���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    bool  ��r��������
 @retval    true  �Ⴄ�N�H�[�^�j�I���̏ꍇ
 @retval    false �����N�H�[�^�j�I���̏ꍇ

*/
template<class T>
bool S_Quaternion<T>::operator!=(const S_Quaternion<T>& r_ANOTHER) const
{
    return Absolute(this->m_t - r_ANOTHER.m_t) > GetEpsilon<T>()
        || Absolute(this->m_x - r_ANOTHER.m_x) > GetEpsilon<T>()
        || Absolute(this->m_y - r_ANOTHER.m_y) > GetEpsilon<T>()
        || Absolute(this->m_z - r_ANOTHER.m_z) > GetEpsilon<T>();
}



#pragma endregion


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


/* 

 @brief     ��Z���Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T>  ��Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator*(T value) const
{
    return S_Quaternion(this->m_t * value, this->m_x * value, this->m_y * value, this->m_z * value);
}


/* 

 @brief   ��Z������Z�q�̃I�[�o�[���[�h
 @param[in] r_ANOTHER ����1�̃N�H�[�^�j�I��
 @return    const S_Quaternion<T>&  ��Z�����N�H�[�^�j�I��

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator*=(T value)
{
    this->m_t *= value;
    this->m_x *= value;
    this->m_y *= value;
    this->m_z *= value;

    return (*this);
}


#pragma endregion


#pragma region �L���X�g


/* 

 @brief  S_Vector3<T>�^�ւ̃L���X�g
 @param  �Ȃ�
 @return S_Vector3<T> 3D�x�N�g��

*/
template<class T>
S_Quaternion<T>::operator S_Vector3<T>() const
{
    return S_Vector3<T>(this->m_x, this->m_y, this->m_z);
}


/* 

 @brief  String�^�ւ̃L���X�g
 @param  �Ȃ�
 @return String ������ɕϊ������N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T>::operator String() const
{
    return ToString();
}


#pragma endregion


/* 

 @brief  �N�H�[�^�j�I���̐��`��Ԃ��s��
 @param[in] r_START �J�n���̃N�H�[�^�j�I��
 @param[in] r_END   �I�����̃N�H�[�^�j�I��
 @param[in] factor  ��ԌW��
 @return S_Quaternion<T> ���`��Ԃ����N�H�[�^�j�I��

*/
template<class T>
S_Quaternion<T> s_LerpQuaternion(const S_Quaternion<T>& r_START,
                                 const S_Quaternion<T>& r_END,
                                 T factor)
{
    S_Quaternion<T> lerp_point;

    lerp_point.m_t = (r_END.m_t - r_START.m_t) * factor + r_START.m_t;
    lerp_point.m_x = (r_END.m_x - r_START.m_x) * factor + r_START.m_x;
    lerp_point.m_y = (r_END.m_y - r_START.m_y) * factor + r_START.m_y;
    lerp_point.m_z = (r_END.m_z - r_START.m_z) * factor + r_START.m_z;

    return lerp_point;
}


/* �����I�C���X�^���X�� */
template struct S_Quaternion<float>;
template struct S_Quaternion<double>;