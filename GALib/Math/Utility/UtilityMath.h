/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <string>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <string>


// ���ɂ����sprintf��sprint_s�̂ǂ��炩�ɕύX����
#define GALib_Sprintf sprintf_s


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
        /* �ʖ� */
        typedef std::string String;                 ///< @brief String�^
        typedef int Int32;                          ///< @brief Int32�^
        typedef unsigned int Uint32;                ///< @brief Uint32�^

        /* Vector�̊e���� */
        enum eVectorFactor
        {
            X = 0,                                  ///< @brief X����
            Y = 1,                                  ///< @brief Y����
            Z = 2,                                  ///< @brief Z����
            W = 3,                                  ///< @brief W����
        };


        /* 

         @brief  �� / 4���擾����
         @param  �Ȃ�
         @return T �� / 4
        
        */
        template<class T>
        T GetPiDivision4()
        {
            return T(0.785398163397447);
        }


        /* 

         @brief  �� / 3���擾����
         @param  �Ȃ�
         @return T �� / 3
        
        */
        template<class T>
        T GetPiDivision3()
        {
            return T(1.047197551196596);
        }


        /* 

         @brief  �� / 2���擾����
         @param  �Ȃ�
         @return T �� / 2
        
        */
        template<class T>
        T GetPiDivision2()
        {
            return T(1.570796326794895);
        }


        /* 

         @brief  �΂��擾����
         @param  �Ȃ�
         @return T ��
        
        */
        template<class T>
        T GetPi()
        {
            return T(3.14159265358979);
        }


        /* 

         @brief  2�΂��擾����
         @param  �Ȃ�
         @return T 2��
        
        */
        template<class T>
        T Get2Pi()
        {
            return T(6.2831853071795);
        }


        /* 

         @brief  ��΂��擾����
         @param  �Ȃ�
         @return T ���
        
        */
        template<class T>
        T GetRootPi()
        {
            return T(1.77245385090551);
        }


        /* 

         @brief  ��2�΂��擾����
         @param  �Ȃ�
         @return T ��2��
        
        */
        template<class T>
        T GetRoot2Pi()
        {
            return T(2.50662827463100);
        }


        /* 

         @brief  1 / �΂��擾����
         @param  �Ȃ�
         @return T 1 / ��
        
        */
        template<class T>
        T Get1DivisionPi()
        {
            return T(0.31830988618379);
        }


        /* 

         @brief  2 / �΂��擾����
         @param  �Ȃ�
         @return T 2 / ��
        
        */
        template<class T>
        T Get2DivisionPi()
        {
            return T(0.63661977236758);
        }


        /* 

         @brief  2 / ��΂��擾����
         @param  �Ȃ�
         @return T 2 / ���
        
        */
        template<class T>
        T Get2DivisionRootPi()
        {
            return T(1.12837916709551);
        }


        /* 

         @brief  180 / �΂��擾����
         @param  �Ȃ�
         @return T 180 / ��
        
        */
        template<class T>
        T GetStraightDivisionPi()
        {
            return T(57.295779513082379);
        }


        /* 

         @brief  1���W�A�����擾����
         @param  �Ȃ�
         @return T 1���W�A��
        
        */
        template<class T>
        T Get1Radian()
        {
            return T(0.017453292519943);
        }


        /* 

         @brief  ��2���擾����
         @param  �Ȃ�
         @return T ��2
        
        */
        template<class T>
        T GetRoot2()
        {
            return T(1.414213562373095);
        }


        /* 

         @brief  1 / ��2���擾����
         @param  �Ȃ�
         @return T 1 / ��2
        
        */
        template<class T>
        T Get1DivisionRoot2()
        {
            return T(0.707106781186547);
        }


        /* 

         @brief  ��3���擾����
         @param  �Ȃ�
         @return T ��3
        
        */
        template<class T>
        T GetRoot3()
        {
            return T(1.732050807568877);
        }


        /* 

         @brief  �w���֐�e���擾����
         @param  �Ȃ�
         @return T �w���֐�e
        
        */
        template<class T>
        T GetE()
        {
            return T(2.718281828459045);
        }


        /* 

         @brief  �덷�l���擾����
         @param  �Ȃ�
         @return T �덷�l
        
        */
        template<class T>
        T GetEpsilon()
        {
            return T(0.000001);
        }


        /* 

         @brief     �ŏ��l�𔻕ʂ���
         @param[in] lhs �l
         @param[in] rhs ����1�̒l
         @return    T �ŏ��l
        
        */
        template<class T>
        T Minimum(T lhs, T rhs)
        {
            return  lhs < rhs ? lhs : rhs;
        }


        /* 

         @brief     �ő�l�𔻕ʂ���
         @param[in] lhs �l
         @param[in] rhs ����1�̒l
         @return    T �ő�l
        
        */
        template<class T>
        T Maximum(T lhs, T rhs)
        {
            return  lhs > rhs ? lhs : rhs;
        }


        /* 

         @brief     �l���ŏ��l����A�ő�l�܂łɌŒ肷��
         @param[in] value �l
         @param[in] min   �ŏ��l
         @param[in] max   �ő�l
         @return    T �Œ肵���l
        
        */
        template<class T>
        T Clamp(T value, T min, T max)
        {
            return value < min ? min : (value > max ? max : value);
        }


        /* 

         @brief     �x�����烉�W�A���l�֕ϊ�����
         @param[in] degree �x���l
         @return    T ���W�A���l
        
        */
        template<class T>
        T ConvertDegreeToRadian(T degree)
        {
            return degree * Get1Radian<T>();
        }


        /* 

         @brief     ���W�A���l����x���֕ϊ�����
         @param[in] radian ���W�A���l
         @return    T �x���l
        
        */
        template<class T>
        T ConvertRadianToDegree(T radian)
        {
            return radian * GetStraightDivisionPi<T>();
        }


        /* 

         @brief     ���W�A���l��0����2�΂܂łɒ��߂���
         @param[in] radian ���W�A���l
         @return    T 0����2�΂܂ł̃��W�A���l
        
        */
        template<class T>
        T AdjustRadianFrom0To2pi(T radian)
        {
            while (radian < 0) radian += Get2Pi<T>();
            while (radian > Get2Pi<T>()) radian -= Get2Pi<T>();

            return radian;
        }


        /* 

         @brief     �x���l��0����360�܂łɒ��߂���
         @param[in] degree �x���l
         @return    T 0����360�܂ł̓x���l
        
        */
        template<class T>
        T AdjustDegreeFrom0To360(T degree)
        {
            while (degree < 0) degree += 360;
            while (degree > 360) degree -= 360;

            return degree;
        }


        /* 

         @brief     �l�̕��������擾����
         @param[in] value �l
         @return    T �l�̕�����
        
        */
        template<class T>
        T SquareRoot(T value)
        {
            assert(value >= T(0));
            return T(std::sqrt(static_cast<double>(value)));
        }


        /* 

         @brief     �l�̗��������擾����
         @param[in] value �l
         @return    T �l�̗�����
        
        */
        template<class T>
        T CubicRoot(T value)
        {
            assert(value >= T(0));
            return T(std::cbrt(static_cast<double>(value)));
        }


        /* 

         @brief     �l�̓����擾����
         @param[in] value �l
         @return    T �l�̓��
        
        */
        template<class T>
        T Square(T value)
        {
            return value * value;
        }


        /* 

         @brief     �l�̎O����擾����
         @param[in] value �l
         @return    T �l�̎O��
        
        */
        template<class T>
        T Cubic(T value)
        {
            return value * value * value;
        }


        /* 

         @brief     �l�̗ݏ���擾����
         @param[in] value �l
         @param[in] n     �w��
         @return    T �l�̗ݏ�
        
        */
        template<class T, class U>
        T Power(T value, U n)
        {
            return T(std::pow(static_cast<double>(value), static_cast<double>(n)));
        }


        /* 

         @brief     �l�̐�Βl���擾����
         @param[in] value �l
         @return    T �l�̐�Βl
        
        */
        template<class T>
        T Absolute(T value)
        {
            return T(std::abs(static_cast<double>(value)));
        }


        /* 

         @brief     �w���֐�e��n����擾����
         @param[in] n �w��
         @return    T �w���֐�e��n��
        
        */
        template<class T>
        T Exponential(T n)
        {
            return T(std::exp(static_cast<double>(n)));
        }


        /* 

         @brief     �l�̎��R�ΐ����擾����
         @param[in] value �l
         @return    T �l�̎��R�ΐ�
        
        */
        template<class T>
        T Log(T value)
        {
            return T(std::log(static_cast<double>(value)));
        }


        /* 

         @brief     ��p�ΐ����擾����
         @param[in] value �l
         @return    T ��p�ΐ�
        
        */
        template<class T>
        T Log10(T value)
        {
            return T(std::log10(static_cast<double>(value)));
        }


        /* 

         @brief     �������擾����
         @param[in] radian ���W�A���l
         @return    T ����
        
        */
        template<class T>
        T Sine(T radian)
        {
            radian = AdjustRadianFrom0To2pi(radian);

            T sum = radian;
            T add = radian;

            const Uint32 LOOP_COUNT = 30;
            const T TWO = 2;

            for (size_t i = 1; i <= LOOP_COUNT; ++i)
            {
                add *= -(radian * radian) / ((TWO * T(i) + 1) * (TWO * T(i)));
                sum += add;
            }

            return sum;
        }


        /* 

         @brief     �]�����擾����
         @param[in] radian ���W�A���l
         @return    T �]��
        
        */
        template<class T>
        T Cosine(T radian)
        {
            return Sine(GetPiDivision2<T>() - radian);
        }


        /* 

         @brief     ���ڂ��擾����
         @param[in] radian ���W�A���l
         @return    T ����
        
        */
        template<class T>
        T Tangent(T radian)
        {
            return Sine(radian) / Cosine(radian);
        }


        /* 

         @brief     �]�ڂ��擾����
         @param[in] radian ���W�A���l
         @return    T �]��
        
        */
        template<class T>
        T Cotangent(T radian)
        {
            return Cosine(radian) / Sine(radian);
        }


        /* 

         @brief     ���ς��擾����
         @param[in] x_1 1�ڂ�X���W
         @param[in] y_1 1�ڂ�Y���W
         @param[in] x_2 2�ڂ�X���W
         @param[in] y_2 2�ڂ�Y���W
         @return    T ����
        
        */
        template<class T>
        T DotProduct(T x_1, T y_1, T x_2, T y_2)
        {
            return (x_1 * x_2) + (y_1 * y_2);
        }


        /* 

         @brief     ���ς��擾����
         @param[in] x_1 1�ڂ�X���W
         @param[in] y_1 1�ڂ�Y���W
         @param[in] z_1 1�ڂ�Z���W
         @param[in] x_2 2�ڂ�X���W
         @param[in] y_2 2�ڂ�Y���W
         @param[in] z_2 2�ڂ�Z���W
         @return    T ����
        
        */
        template<class T>
        T DotProduct(T x_1, T y_1, T z_1, T x_2, T y_2, T z_2)
        {
            return (x_1 * x_2) + (y_1 * y_2) + (z_1 * z_2);
        }


        /* 

         @brief     �O�ς��擾����
         @param[in] x_1 1�ڂ�X���W
         @param[in] y_1 1�ڂ�Y���W
         @param[in] x_2 2�ڂ�X���W
         @param[in] y_2 2�ڂ�Y���W
         @return    T �O��
        
        */
        template<class T>
        T CrossProduct(T x_1, T y_1, T x_2, T y_2)
        {
            return (x_1 * y_2) - (x_2 * y_1);
        }


        /* 

         @brief     2�̌��q�Ԃ̈ʒu�G�l���M�[�����߂�
         @param[in] repulsion_strength            �˗͋��x
         @param[in] attraction_strength           ���͋��x
         @param[in] distance                      ����
         @param[in] repulsion_attenuation_factor  �˗͌����W��
         @param[in] attraction_attenuation_factor ���͌����W��
         @return    T �ʒu�G�l���M�[
        
        */
        template<class T>
        T LennardJonesPotential(T repulsion_strength,
                                T attraction_strength,
                                T distance,
                                T repulsion_attenuation_factor,
                                T attraction_attenuation_factor)
        {
            return (repulsion_strength / Power(distance, repulsion_attenuation_factor))
                 - (attraction_strength / Power(distance, attraction_attenuation_factor));
        }


        /* 

         @brief     �V�O���C�h�֐�����l�����߂�
         @param[in] x    �l
         @param[in] gain �Q�C��
         @return    T 0����1�܂ł̒l
        
        */
        template<class T>
        T Sigmoid(T x, T gain)
        {
            assert(gain);

            const T ONE = 1.0;
            return ONE / ONE + Exponential(-x * gain);
        }


        /* 

         @brief     1�����K�E�V�A���֐�����l�����߂�
         @param[in] x    �l
         @param[in] gain �W���΍�( �� )
         @return    T 0����1�܂ł̒l
        
        */
        template<class T>
        T OneDimensionalGaussian(T x, T standard_deviation)
        {
            T left_side = T(1.0) / (GetRoot2Pi<T>() * standard_deviation);
            T right_side = Exponential(-Square(x) / (T(2.0) * Square(standard_deviation)));
            T result = left_side * right_side;

            return result;
        }


        /* 

         @brief     2�����K�E�V�A���֐�����l�����߂�
         @param[in] x    �l1
         @param[in] y    �l2
         @param[in] dispersion ���U( ��^2 )
         @return    T 0����1�܂ł̒l
        
        */
        template<class T>
        T TwoDimensionsGaussian(T x, T y, T dispersion)
        {
            T left_side = T(1.0) / (T(Get2Pi) * dispersion);
            T right_side = Exponential(-(Square(x) + Square(y)) / (T(2.0) * Square(dispersion)));
            T result = left_side * right_side;

            return result;
        }
    }
}