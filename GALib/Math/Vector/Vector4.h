/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Vector3.h"


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
        /*

         @brief S_Vector4
                4Dベクトルを表す構造体

        */
        template<class T>
        struct S_Vector4
        {
            /* 定数 */
            static const S_Vector4 m_s_ZERO;                                                        ///< @brief ゼロベクトル
            static const S_Vector4 m_s_ONE;                                                         ///< @brief 全ての要素が1

            /* メンバ変数 */
            union
            {
                struct
                {
                    T m_elements[4];                                                                ///< @brief 4つの要素を持つ配列
                };

                struct
                {
                    T m_x;                                                                          ///< @brief X成分
                    T m_y;                                                                          ///< @brief Y成分
                    T m_z;                                                                          ///< @brief Z成分
                    T m_w;                                                                          ///< @brief W成分
                };

                struct
                {
                    T m_red;                                                                        ///< @brief 赤
                    T m_green;                                                                      ///< @brief 緑
                    T m_blue;                                                                       ///< @brief 青
                    T m_alpha;                                                                      ///< @brief アルファ
                };
            };


            /* メンバ関数 */
            S_Vector4();                                                                            // コンストラクタ
            S_Vector4(T value);                                                                     // コンストラクタ
            S_Vector4(T x, T y, T z, T w);                                                          // コンストラクタ
            S_Vector4(const T ELEMENTS[4]);                                                         // コンストラクタ
            S_Vector4(const S_Vector2<T>& r_XY, T z, T w);                                          // コンストラクタ
            S_Vector4(const S_Vector3<T>& r_XYX, T w);                                              // コンストラクタ
            ~S_Vector4();                                                                           // デストラクタ
            void Zero();                                                                            // ゼロベクトル化
            void Fill(T value);                                                                     // 各成分を特定の値に変更
            void Normalize();                                                                       // 単位ベクトル化
            void Invert();                                                                          // ベクトルを反転
            void ClampMagnitude(T min, T max);                                                      // ベクトルの大きさでクランプ
            T GetMagnitude() const;                                                                 // 大きさを取得
            T GetMagnitudeSquare() const;                                                           // 大きさの2乗を取得
            S_Vector4 GetNormalize() const;                                                         // 単位ベクトルを取得
            S_Vector4 GetInvert() const;                                                            // 反転したベクトルを取得
            S_Vector4 GetClampMagnitude(T min, T max) const;                                        // 大きさでクランプしたベクトルを取得
            String ToString() const;                                                                // ベクトルを文字列として取得

            /* Swizzle */
            template<eVectorFactor factor_0>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_0], a_[factor_0], a_[factor_0]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_1], a_[factor_1], a_[factor_1]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1, eVectorFactor factor_2>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_1], a_[factor_2], a_[factor_2]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1, eVectorFactor factor_2, eVectorFactor factor_3>
            S_Vector4 Get() const
            {
                return S_Vector4(a_[factor_0], a_[factor_1], a_[factor_2], a_[factor_3]);
            }

            /* 静的メンバ関数 */
            static T s_DotProduct(const S_Vector4& r_VECTOR, const S_Vector4& r_ANOTHER_VECTOR);    // 内積
            static S_Vector4 s_Lerp(const S_Vector4& r_START_POINT,                                 // 線形補間
                                    const S_Vector4& r_END_POINT,
                                    T factor);
            static S_Vector4 s_Minimize(const S_Vector4& r_LHS, const S_Vector4& r_RHS);            // 各成分の最小値を成分にしたベクトルを取得
            static S_Vector4 s_Maximize(const S_Vector4& r_LHS, const S_Vector4& r_RHS);            // 各成分の最大値を成分にしたベクトルを取得

            /* S_Vector4型との演算子のオーバーロード */
            const S_Vector4 operator+(const S_Vector4& r_ANOTHER) const;                            // +演算子のオーバーロード
            const S_Vector4 operator-(const S_Vector4& r_ANOTHER) const;                            // -演算子のオーバーロード
            const S_Vector4 operator*(const S_Vector4& r_ANOTHER) const;                            // *演算子のオーバーロード
            const S_Vector4 operator/(const S_Vector4& r_ANOTHER) const;                            // /演算子のオーバーロード
            const S_Vector4& operator+=(const S_Vector4& r_ANOTHER);                                // +=演算子のオーバーロード
            const S_Vector4& operator-=(const S_Vector4& r_ANOTHER);                                // -=演算子のオーバーロード
            const S_Vector4& operator*=(const S_Vector4& r_ANOTHER);                                // *=演算子のオーバーロード
            const S_Vector4& operator/=(const S_Vector4& r_ANOTHER);                                // /=演算子のオーバーロード
            bool operator==(const S_Vector4& r_ANOTHER) const;                                      // ==演算子のオーバーロード
            bool operator!=(const S_Vector4& r_ANOTHER) const;                                      // !=演算子のオーバーロード

            /* T型との演算子のオーバーロード */
            const S_Vector4 operator*(T value) const;                                               // *演算子のオーバーロード
            const S_Vector4 operator/(T value) const;                                               // /演算子のオーバーロード
            const S_Vector4& operator*=(T value);                                                   // *=演算子のオーバーロード
            const S_Vector4& operator/=(T value);                                                   // /=演算子のオーバーロード

            /* キャスト演算子のオーバーロード */
            operator S_Vector2<T>() const;                                                          // S_Vector2型へのキャスト
            operator S_Vector3<T>() const;                                                          // S_Vector3型へのキャスト
            operator String() const;                                                                // String型へのキャスト

#pragma region T型との演算子のオーバーロード


            /* 
            
             @brief     乗算演算子のオーバーロード
             @param[in] value    値
             @param[in] r_VECTOR ベクトル
             @return    const S_Vector4 乗算したベクトル
            
            */
            friend const S_Vector4 operator*(T value, const S_Vector4& r_VECTOR)
            {
                return S_Vector4(r_VECTOR.m_x * value, r_VECTOR.m_y * value, r_VECTOR.m_z * value, r_VECTOR.m_w * value);
            }


#pragma endregion

        };


        /* 別名 */
        typedef S_Vector4<float> Vector4;                                                           // Vector4型
    }
}
