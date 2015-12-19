/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Utility/UtilityMath.h"



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
        
         @brief S_Vector2
                2Dベクトルを表す構造体

        */
        template<class T>
        struct S_Vector2
        {
            /* 定数 */
            static const S_Vector2 m_s_RIGHT_DIRECTION;                                             ///< @brief 右向き ( 1,  0)
            static const S_Vector2 m_s_LEFT_DIRECTION;                                              ///< @brief 左向き (-1,  0)
            static const S_Vector2 m_s_UP_DIRECTION;                                                ///< @brief 上向き ( 0,  1)
            static const S_Vector2 m_s_DOWN_DIRECTION;                                              ///< @brief 下向き ( 0, -1)
            static const S_Vector2 m_s_ZERO;                                                        ///< @brief ゼロベクトル
            static const S_Vector2 m_s_ONE;                                                         ///< @brief 全ての要素が1

            /* メンバ変数 */
            union
            {
                T m_elements[2];                                                                    ///< @brief 2つの要素を持つ配列

                struct
                {
                    T m_x;                                                                          ///< @brief X成分
                    T m_y;                                                                          ///< @brief Y成分
                };

                struct
                {
                    T m_u;                                                                          ///< @brief U成分
                    T m_v;                                                                          ///< @brief V成分
                };

                struct
                {
                    T m_width;                                                                      ///< @brief 幅
                    T m_height;                                                                     ///< @brief 高さ
                };
            };

            /* メンバ関数 */
            S_Vector2();                                                                            // コンストラクタ
            S_Vector2(T value);                                                                     // コンストラクタ
            S_Vector2(T x, T y);                                                                    // コンストラクタ
            S_Vector2(const T ELEMENTS[2]);                                                         // コンストラクタ
            ~S_Vector2();                                                                           // デストラクタ
            void Zero();                                                                            // ゼロベクトル化
            void Fill(T value);                                                                     // 各成分を特定の値に変更
            void Normalize();                                                                       // 単位ベクトル化
            void Invert();                                                                          // ベクトルを反転
            void Perpendicular();                                                                   // 垂直なベクトルに変換
            void Rotate(T angle);                                                                   // ベクトルを回転
            void ClampMagnitude(T min, T max);                                                      // 大きさでベクトルをクランプ
            T GetMagnitude() const;                                                                 // 大きさを取得
            T GetMagnitudeSquare() const;                                                           // 大きさの2乗を取得
            S_Vector2 GetNormalize() const;                                                         // 単位ベクトルを取得
            S_Vector2 GetInvert() const;                                                            // 反転したベクトルを取得
            S_Vector2 GetPerpendicular() const;                                                     // 垂直なベクトルを取得
            S_Vector2 GetRotate(T angle) const;                                                     // 回転したベクトルを取得
            T GetAngle() const;                                                                     // ベクトルの角度を取得
            S_Vector2 GetClampMagnitude(T min, T max) const;                                        // 大きさでクランプしたベクトルを取得
            std::string ToString() const;                                                           // ベクトルを文字列へ変換して取得

            /* Swizzle */
            template<eVectorFactor factor_0>
            S_Vector2 Get() const
            {
                return S_Vector2(a_[factor_0], a_[factor_0]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1>
            S_Vector2 Get() const
            {
                return S_Vector2(a_[factor_0], a_[factor_1]);
            }

            /* 静的メンバ関数 */
            static T s_DotProduct(const S_Vector2& r_LHS, const S_Vector2& r_RHS);                  // 内積
            static T s_CrossProduct(const S_Vector2& r_LHS, const S_Vector2& r_RHS);                // 外積
            static S_Vector2 s_Lerp(const S_Vector2& r_START_POINT,                                 // 線形補間
                                    const S_Vector2& r_END_POINT,
                                    T coefficient);
            static S_Vector2 s_Slerp(const S_Vector2& r_START_POINT,                                // 球面線形補間
                                     const S_Vector2& r_END_POINT,
                                     T coefficient);
            static S_Vector2 s_Hermite(const S_Vector2& r_START_POINT,                              // エルミート補間
                                       const S_Vector2& r_START_TANGENT,
                                       const S_Vector2& r_END_POINT,
                                       const S_Vector2& r_END_TANGENT,
                                       T coefficient);
            static S_Vector2 s_CatmullRomSpline(const S_Vector2& r_PREVIOUS_START_POINT,            // Catmull-Romスプライン補間
                                                const S_Vector2& r_START_POINT,
                                                const S_Vector2& r_END_POINT,
                                                const S_Vector2& r_NEXT_END_POINT,
                                                T coefficient);
            static S_Vector2 s_Bezier(const S_Vector2& r_START_POINT,                               // ベジェ補間
                                      const S_Vector2& r_END_POINT,
                                      const S_Vector2& r_CONTROL_POINT_1,
                                      const S_Vector2& r_CONTROL_POINT_2,
                                      T coefficient);
            static S_Vector2 s_CreateWithAngle(T angle, T length = static_cast<T>(1));              // 角度からベクトルを作成
            static S_Vector2 s_InterceptPoint(const S_Vector2& r_POSITION,                          // 迎撃ポイントを取得
                                              const S_Vector2& r_VELOCITY,
                                              const S_Vector2& r_ANOTHER_POSITION,
                                              const S_Vector2& r_ANOTHER_VELOCITY);
            static T s_AngleBetweenVectors(const S_Vector2& r_LHS, const S_Vector2& r_RHS);         // ベクトル間の角度を取得
            static T s_DistanceBetweenVectors(const S_Vector2& r_LHS, const S_Vector2& r_RHS);      // ベクトル間の距離を取得
            static S_Vector2 s_Minimize(const S_Vector2& r_LHS, const S_Vector2& r_RHS);            // 各成分の最小値を成分にしたベクトルを取得
            static S_Vector2 s_Maximize(const S_Vector2& r_LHS, const S_Vector2& r_RHS);            // 各成分の最大値を成分にしたベクトルを取得
            static S_Vector2 s_MoveTowards(const S_Vector2& r_START_POINT,                          // 2点間からの距離分だけ進んだ点を取得
                                           const S_Vector2& r_END_POINT,
                                           T distance);
            static S_Vector2 s_Project(const S_Vector2& r_VECTOR, const S_Vector2& r_NORMAL);       // 投影ベクトルを取得
            static S_Vector2 s_Reflect(const S_Vector2& r_VECTOR, const S_Vector2& r_NORMAL);       // 反射ベクトルを取得
            static S_Vector2 s_Refract(const S_Vector2& r_INCIDENT_VECTOR,                          // 屈折ベクトルを取得
                                       const S_Vector2& r_NORMAL,
                                       T REFRACTIVE_INDEX);
            static S_Vector2 s_Slide(const S_Vector2& r_VECTOR, const S_Vector2& r_NORMAL);         // 滑りベクトルを取得
            static S_Vector2 s_CenterOfGravityWith3Points(const S_Vector2& r_A,                     // 3点から重心を取得
                                                          const S_Vector2& r_B,
                                                          const S_Vector2& r_C);


            /* S_Vector2型との演算子のオーバーロード */
            const S_Vector2 operator+(const S_Vector2& r_ANOTHER) const;                            // +演算子のオーバーロード
            const S_Vector2 operator-(const S_Vector2& r_ANOTHER) const;                            // -演算子のオーバーロード
            const S_Vector2 operator*(const S_Vector2& r_ANOTHER) const;                            // *演算子のオーバーロード
            const S_Vector2 operator/(const S_Vector2& r_ANOTHER) const;                            // /演算子のオーバーロード
            const S_Vector2& operator+=(const S_Vector2& r_ANOTHER);                                // +=演算子のオーバーロード
            const S_Vector2& operator-=(const S_Vector2& r_ANOTHER);                                // -=演算子のオーバーロード
            const S_Vector2& operator*=(const S_Vector2& r_ANOTHER);                                // *=演算子のオーバーロード
            const S_Vector2& operator/=(const S_Vector2& r_ANOTHER);                                // /=演算子のオーバーロード
            bool operator==(const S_Vector2& r_ANOTHER) const;                                      // ==演算子のオーバーロード
            bool operator!=(const S_Vector2& r_ANOTHER) const;                                      // !=演算子のオーバーロード

            /* T型との演算子のオーバーロード */
            const S_Vector2 operator*(T value) const;                                               // *演算子のオーバーロード
            const S_Vector2 operator/(T value) const;                                               // /演算子のオーバーロード
            const S_Vector2& operator*=(T value);                                                   // *=演算子のオーバーロード
            const S_Vector2& operator/=(T value);                                                   // /=演算子のオーバーロード

            /* キャスト */
            operator String() const;                                                                // String型へのキャスト


#pragma region T型との演算子のオーバーロード


            /* 
            
             @brief     乗算演算子のオーバーロード
             @param[in] value    値
             @param[in] r_VECTOR ベクトル
             @return    const S_Vector2 乗算したベクトル
            
            */
            friend const S_Vector2 operator*(T value, const S_Vector2& r_VECTOR)
            {
                return S_Vector2(r_VECTOR.m_x * value, r_VECTOR.m_y * value);
            }


#pragma endregion

        };

        /* 別名 */
        typedef S_Vector2<float> Vector2;                                                           // Vector2型
    }
}