/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Utility/UtilityMath.h"


/**

 @brief GALib
        GAライブラリ関連の名前空間

*/
namespace GALib
{
    /**

     @brief Math
            数学関連の名前空間

    */
    namespace Math
    {
        /**

         @brief Interpolation
                補間関連の名前空間

        */
        namespace Interpolation
        {
            // 参考URL : http://gizma.com/easing/
            // ※ 各補間関数の補間係数には0.0 ～ 1.0までの値を設定すること


            /**
            
             @brief     線形補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T Linear(const T& r_START, const T& r_END, FactorType factor)
            {
                return (r_END - r_START) * factor + r_START;
            }


            /**
            
             @brief     イーズインの二次補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T EaseInQuadratic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = Square(factor);
                return Linear(r_START, r_END, calculated_factor);
            }


            /**
            
             @brief     イーズアウトの二次補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T EaseOutQuadratic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = factor * (factor - FactorType(2));
                return -(r_END - r_START) * calculated_factor + r_START;
            }


            /**
            
             @brief     イーズインアウトの二次補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T EaseInOutQuadratic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType twice_factor = factor * FactorType(2);

                // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
                if (twice_factor < FactorType(1))
                {
                    FactorType calculated_factor = Square(twice_factor);
                    return (r_END - r_START) / FactorType(2) * calculated_factor + r_START;
                }

                // 補間係数を0.0 ～ 1.0に正規化し、係数を計算
                FactorType unit_factor = twice_factor - FactorType(1);
                FactorType calculated_factor = (unit_factor * (unit_factor - FactorType(2))) - FactorType(1);

                return -(r_END - r_START) / FactorType(2) * calculated_factor + r_START;
            }


            /**
            
             @brief     イーズインの三次補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T EaseInCubic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = Cubic(factor);
                return Linear(r_START, r_END, calculated_factor);
            }


            /**
            
             @brief     イーズアウトの三次補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T EaseOutCubic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType calculated_factor = Cubic(factor - FactorType(1)) + FactorType(1);
                return (r_END - r_START) * calculated_factor + r_START;
            }


            /**
            
             @brief     イーズインアウトの三次補間を行う
             @param[in] r_START 開始値
             @param[in] r_END   終了値
             @param[in] factor  補間係数
             @return    T 補完した値

            */
            template<class T, class FactorType>
            T EaseInOutCubic(const T& r_START, const T& r_END, FactorType factor)
            {
                FactorType twice_factor = factor * FactorType(2);

                // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
                if (twice_factor < FactorType(1))
                {
                    FactorType calculated_factor = Cubic(twiceFactor);
                    return (r_END - r_START) / FactorType(2) * calculated_factor + r_START;
                }

                // 補間係数を-1.0 ～ 0.0に正規化し、係数を計算
                FactorType unit_factor = twice_factor - FactorType(2);
                FactorType calculated_factor = Cubic(unit_factor) + FactorType(2);

                return (r_END - r_START) / FactorType(2) * calculated_factor + r_START;
            }
        }
    }
}