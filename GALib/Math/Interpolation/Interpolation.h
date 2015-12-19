/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Utility/UtilityMath.h"


/**

 @brief GALib
        GA���C�u�����֘A�̖��O���

*/
namespace GALib
{
    /**

     @brief Math
            ���w�֘A�̖��O���

    */
    namespace Math
    {
        /**

         @brief Interpolation
                ��Ԋ֘A�̖��O���

        */
        namespace Interpolation
        {
            // �Q�lURL : http://gizma.com/easing/
            // �� �e��Ԋ֐��̕�ԌW���ɂ�0.0 �` 1.0�܂ł̒l��ݒ肷�邱��


            /**
            
             @brief     ���`��Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T Linear(const T& r_START, const T& r_END, FactorType factor)
            {
                return (r_END - r_START) * factor + r_START;
            }


            /**
            
             @brief     �C�[�Y�C���̓񎟕�Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T EaseInQuadratic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = Square(factor);
                return Linear(r_START, r_END, calculated_factor);
            }


            /**
            
             @brief     �C�[�Y�A�E�g�̓񎟕�Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T EaseOutQuadratic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = factor * (factor - FactorType(2));
                return -(r_END - r_START) * calculated_factor + r_START;
            }


            /**
            
             @brief     �C�[�Y�C���A�E�g�̓񎟕�Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T EaseInOutQuadratic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType twice_factor = factor * FactorType(2);

                // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
                if (twice_factor < FactorType(1))
                {
                    FactorType calculated_factor = Square(twice_factor);
                    return (r_END - r_START) / FactorType(2) * calculated_factor + r_START;
                }

                // ��ԌW����0.0 �` 1.0�ɐ��K�����A�W�����v�Z
                FactorType unit_factor = twice_factor - FactorType(1);
                FactorType calculated_factor = (unit_factor * (unit_factor - FactorType(2))) - FactorType(1);

                return -(r_END - r_START) / FactorType(2) * calculated_factor + r_START;
            }


            /**
            
             @brief     �C�[�Y�C���̎O����Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T EaseInCubic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = Cubic(factor);
                return Linear(r_START, r_END, calculated_factor);
            }


            /**
            
             @brief     �C�[�Y�A�E�g�̎O����Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T EaseOutCubic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = Cubic(factor - FactorType(1)) + FactorType(1);
                return (r_END - r_START) * calculated_factor + r_START;
            }


            /**
            
             @brief     �C�[�Y�C���A�E�g�̎O����Ԃ��s��
             @param[in] r_START �J�n�l
             @param[in] r_END   �I���l
             @param[in] factor  ��ԌW��
             @return    T �⊮�����l

            */
            template<class T, class FactorType>
            T EaseInOutCubic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType twice_factor = factor * FactorType(2);

                // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
                if (twice_factor < FactorType(1))
                {
                    FactorType calculated_factor = Cubic(twiceFactor);
                    return (r_END - r_START) / FactorType(2) * calculated_factor + r_START;
                }

                // ��ԌW����-1.0 �` 0.0�ɐ��K�����A�W�����v�Z
                FactorType unit_factor = twice_factor - FactorType(2);
                FactorType calculated_factor = Cubic(unit_factor) + FactorType(2);

                return (r_END - r_START) / FactorType(2) * calculated_factor + r_START;
            }
        }
    }
}