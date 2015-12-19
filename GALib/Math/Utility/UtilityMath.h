/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <string>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <string>


// 環境によってsprintfとsprint_sのどちらかに変更する
#define GALib_Sprintf sprintf_s


/* 

 @brief GALib
        GAライブラリ関連の名前空間

*/
namespace GALib
{
    /*

     @brief Math
            数学関連の名前空間

    */
    namespace Math
    {
        /* 別名 */
        typedef std::string String;                 ///< @brief String型
        typedef int Int32;                          ///< @brief Int32型
        typedef unsigned int Uint32;                ///< @brief Uint32型

        /* Vectorの各成分 */
        enum eVectorFactor
        {
            X = 0,                                  ///< @brief X成分
            Y = 1,                                  ///< @brief Y成分
            Z = 2,                                  ///< @brief Z成分
            W = 3,                                  ///< @brief W成分
        };


        /* 

         @brief  π / 4を取得する
         @param  なし
         @return T π / 4
        
        */
        template<class T>
        T GetPiDivision4()
        {
            return T(0.785398163397447);
        }


        /* 

         @brief  π / 3を取得する
         @param  なし
         @return T π / 3
        
        */
        template<class T>
        T GetPiDivision3()
        {
            return T(1.047197551196596);
        }


        /* 

         @brief  π / 2を取得する
         @param  なし
         @return T π / 2
        
        */
        template<class T>
        T GetPiDivision2()
        {
            return T(1.570796326794895);
        }


        /* 

         @brief  πを取得する
         @param  なし
         @return T π
        
        */
        template<class T>
        T GetPi()
        {
            return T(3.14159265358979);
        }


        /* 

         @brief  2πを取得する
         @param  なし
         @return T 2π
        
        */
        template<class T>
        T Get2Pi()
        {
            return T(6.2831853071795);
        }


        /* 

         @brief  √πを取得する
         @param  なし
         @return T √π
        
        */
        template<class T>
        T GetRootPi()
        {
            return T(1.77245385090551);
        }


        /* 

         @brief  √2πを取得する
         @param  なし
         @return T √2π
        
        */
        template<class T>
        T GetRoot2Pi()
        {
            return T(2.50662827463100);
        }


        /* 

         @brief  1 / πを取得する
         @param  なし
         @return T 1 / π
        
        */
        template<class T>
        T Get1DivisionPi()
        {
            return T(0.31830988618379);
        }


        /* 

         @brief  2 / πを取得する
         @param  なし
         @return T 2 / π
        
        */
        template<class T>
        T Get2DivisionPi()
        {
            return T(0.63661977236758);
        }


        /* 

         @brief  2 / √πを取得する
         @param  なし
         @return T 2 / √π
        
        */
        template<class T>
        T Get2DivisionRootPi()
        {
            return T(1.12837916709551);
        }


        /* 

         @brief  180 / πを取得する
         @param  なし
         @return T 180 / π
        
        */
        template<class T>
        T GetStraightDivisionPi()
        {
            return T(57.295779513082379);
        }


        /* 

         @brief  1ラジアンを取得する
         @param  なし
         @return T 1ラジアン
        
        */
        template<class T>
        T Get1Radian()
        {
            return T(0.017453292519943);
        }


        /* 

         @brief  √2を取得する
         @param  なし
         @return T √2
        
        */
        template<class T>
        T GetRoot2()
        {
            return T(1.414213562373095);
        }


        /* 

         @brief  1 / √2を取得する
         @param  なし
         @return T 1 / √2
        
        */
        template<class T>
        T Get1DivisionRoot2()
        {
            return T(0.707106781186547);
        }


        /* 

         @brief  √3を取得する
         @param  なし
         @return T √3
        
        */
        template<class T>
        T GetRoot3()
        {
            return T(1.732050807568877);
        }


        /* 

         @brief  指数関数eを取得する
         @param  なし
         @return T 指数関数e
        
        */
        template<class T>
        T GetE()
        {
            return T(2.718281828459045);
        }


        /* 

         @brief  誤差値を取得する
         @param  なし
         @return T 誤差値
        
        */
        template<class T>
        T GetEpsilon()
        {
            return T(0.000001);
        }


        /* 

         @brief     最小値を判別する
         @param[in] lhs 値
         @param[in] rhs もう1つの値
         @return    T 最小値
        
        */
        template<class T>
        T Minimum(T lhs, T rhs)
        {
            return  lhs < rhs ? lhs : rhs;
        }


        /* 

         @brief     最大値を判別する
         @param[in] lhs 値
         @param[in] rhs もう1つの値
         @return    T 最大値
        
        */
        template<class T>
        T Maximum(T lhs, T rhs)
        {
            return  lhs > rhs ? lhs : rhs;
        }


        /* 

         @brief     値を最小値から、最大値までに固定する
         @param[in] value 値
         @param[in] min   最小値
         @param[in] max   最大値
         @return    T 固定した値
        
        */
        template<class T>
        T Clamp(T value, T min, T max)
        {
            return value < min ? min : (value > max ? max : value);
        }


        /* 

         @brief     度数からラジアン値へ変換する
         @param[in] degree 度数値
         @return    T ラジアン値
        
        */
        template<class T>
        T ConvertDegreeToRadian(T degree)
        {
            return degree * Get1Radian<T>();
        }


        /* 

         @brief     ラジアン値から度数へ変換する
         @param[in] radian ラジアン値
         @return    T 度数値
        
        */
        template<class T>
        T ConvertRadianToDegree(T radian)
        {
            return radian * GetStraightDivisionPi<T>();
        }


        /* 

         @brief     ラジアン値を0から2πまでに調節する
         @param[in] radian ラジアン値
         @return    T 0から2πまでのラジアン値
        
        */
        template<class T>
        T AdjustRadianFrom0To2pi(T radian)
        {
            while (radian < 0) radian += Get2Pi<T>();
            while (radian > Get2Pi<T>()) radian -= Get2Pi<T>();

            return radian;
        }


        /* 

         @brief     度数値を0から360までに調節する
         @param[in] degree 度数値
         @return    T 0から360までの度数値
        
        */
        template<class T>
        T AdjustDegreeFrom0To360(T degree)
        {
            while (degree < 0) degree += 360;
            while (degree > 360) degree -= 360;

            return degree;
        }


        /* 

         @brief     値の平方根を取得する
         @param[in] value 値
         @return    T 値の平方根
        
        */
        template<class T>
        T SquareRoot(T value)
        {
            assert(value >= T(0));
            return T(std::sqrt(static_cast<double>(value)));
        }


        /* 

         @brief     値の立方根を取得する
         @param[in] value 値
         @return    T 値の立方根
        
        */
        template<class T>
        T CubicRoot(T value)
        {
            assert(value >= T(0));
            return T(std::cbrt(static_cast<double>(value)));
        }


        /* 

         @brief     値の二乗を取得する
         @param[in] value 値
         @return    T 値の二乗
        
        */
        template<class T>
        T Square(T value)
        {
            return value * value;
        }


        /* 

         @brief     値の三乗を取得する
         @param[in] value 値
         @return    T 値の三乗
        
        */
        template<class T>
        T Cubic(T value)
        {
            return value * value * value;
        }


        /* 

         @brief     値の累乗を取得する
         @param[in] value 値
         @param[in] n     指数
         @return    T 値の累乗
        
        */
        template<class T, class U>
        T Power(T value, U n)
        {
            return T(std::pow(static_cast<double>(value), static_cast<double>(n)));
        }


        /* 

         @brief     値の絶対値を取得する
         @param[in] value 値
         @return    T 値の絶対値
        
        */
        template<class T>
        T Absolute(T value)
        {
            return T(std::abs(static_cast<double>(value)));
        }


        /* 

         @brief     指数関数eのn乗を取得する
         @param[in] n 指数
         @return    T 指数関数eのn乗
        
        */
        template<class T>
        T Exponential(T n)
        {
            return T(std::exp(static_cast<double>(n)));
        }


        /* 

         @brief     値の自然対数を取得する
         @param[in] value 値
         @return    T 値の自然対数
        
        */
        template<class T>
        T Log(T value)
        {
            return T(std::log(static_cast<double>(value)));
        }


        /* 

         @brief     常用対数を取得する
         @param[in] value 値
         @return    T 常用対数
        
        */
        template<class T>
        T Log10(T value)
        {
            return T(std::log10(static_cast<double>(value)));
        }


        /* 

         @brief     正弦を取得する
         @param[in] radian ラジアン値
         @return    T 正弦
        
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

         @brief     余弦を取得する
         @param[in] radian ラジアン値
         @return    T 余弦
        
        */
        template<class T>
        T Cosine(T radian)
        {
            return Sine(GetPiDivision2<T>() - radian);
        }


        /* 

         @brief     正接を取得する
         @param[in] radian ラジアン値
         @return    T 正接
        
        */
        template<class T>
        T Tangent(T radian)
        {
            return Sine(radian) / Cosine(radian);
        }


        /* 

         @brief     余接を取得する
         @param[in] radian ラジアン値
         @return    T 余接
        
        */
        template<class T>
        T Cotangent(T radian)
        {
            return Cosine(radian) / Sine(radian);
        }


        /* 

         @brief     内積を取得する
         @param[in] x_1 1つ目のX座標
         @param[in] y_1 1つ目のY座標
         @param[in] x_2 2つ目のX座標
         @param[in] y_2 2つ目のY座標
         @return    T 内積
        
        */
        template<class T>
        T DotProduct(T x_1, T y_1, T x_2, T y_2)
        {
            return (x_1 * x_2) + (y_1 * y_2);
        }


        /* 

         @brief     内積を取得する
         @param[in] x_1 1つ目のX座標
         @param[in] y_1 1つ目のY座標
         @param[in] z_1 1つ目のZ座標
         @param[in] x_2 2つ目のX座標
         @param[in] y_2 2つ目のY座標
         @param[in] z_2 2つ目のZ座標
         @return    T 内積
        
        */
        template<class T>
        T DotProduct(T x_1, T y_1, T z_1, T x_2, T y_2, T z_2)
        {
            return (x_1 * x_2) + (y_1 * y_2) + (z_1 * z_2);
        }


        /* 

         @brief     外積を取得する
         @param[in] x_1 1つ目のX座標
         @param[in] y_1 1つ目のY座標
         @param[in] x_2 2つ目のX座標
         @param[in] y_2 2つ目のY座標
         @return    T 外積
        
        */
        template<class T>
        T CrossProduct(T x_1, T y_1, T x_2, T y_2)
        {
            return (x_1 * y_2) - (x_2 * y_1);
        }


        /* 

         @brief     2つの原子間の位置エネルギーを求める
         @param[in] repulsion_strength            斥力強度
         @param[in] attraction_strength           引力強度
         @param[in] distance                      距離
         @param[in] repulsion_attenuation_factor  斥力減衰係数
         @param[in] attraction_attenuation_factor 引力減衰係数
         @return    T 位置エネルギー
        
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

         @brief     シグモイド関数から値を求める
         @param[in] x    値
         @param[in] gain ゲイン
         @return    T 0から1までの値
        
        */
        template<class T>
        T Sigmoid(T x, T gain)
        {
            assert(gain);

            const T ONE = 1.0;
            return ONE / ONE + Exponential(-x * gain);
        }


        /* 

         @brief     1次元ガウシアン関数から値を求める
         @param[in] x    値
         @param[in] gain 標準偏差( σ )
         @return    T 0から1までの値
        
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

         @brief     2次元ガウシアン関数から値を求める
         @param[in] x    値1
         @param[in] y    値2
         @param[in] dispersion 分散( σ^2 )
         @return    T 0から1までの値
        
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