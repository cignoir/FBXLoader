/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Vector2.h"


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
        
         @brief S_Vector3
                3Dベクトルを表す構造体

        */
        template<class T>
        struct S_Vector3
        {
            /* 定数 */
            static const S_Vector3 m_s_RIGHT_DIRECTION;                                                                 ///< @brief 右向き ( 1,  0,  0)
            static const S_Vector3 m_s_LEFT_DIRECTION;                                                                  ///< @brief 左向き (-1,  0,  0)
            static const S_Vector3 m_s_UP_DIRECTION;                                                                    ///< @brief 上向き ( 0,  1,  0)
            static const S_Vector3 m_s_DOWN_DIRECTION;                                                                  ///< @brief 下向き ( 0, -1,  0)
            static const S_Vector3 m_s_FRONT_DIRECTION;                                                                 ///< @brief 前向き ( 0,  0,  1)
            static const S_Vector3 m_s_BACK_DIRECTION;                                                                  ///< @brief 後向き ( 0,  0, -1)
            static const S_Vector3 m_s_ZERO;                                                                            ///< @brief ゼロベクトル
            static const S_Vector3 m_s_ONE;                                                                             ///< @brief 全ての要素が1


            /* メンバ変数 */
            union
            {
                struct
                {
                    T m_elements[3];                                                                                    ///< @brief 3つの要素を持つ配列
                };

                struct
                {
                    T m_x;                                                                                              ///< @brief X成分
                    T m_y;                                                                                              ///< @brief Y成分
                    T m_z;                                                                                              ///< @brief Z成分
                };

                struct
                {
                    T m_u;                                                                                              ///< @brief U成分
                    T m_v;                                                                                              ///< @brief V成分
                    T m_w;                                                                                              ///< @brief W成分
                };

                struct
                {
                    T m_red;                                                                                            ///< @brief 赤
                    T m_green;                                                                                          ///< @brief 緑
                    T m_blue;                                                                                           ///< @brief 青
                };

                struct
                {
                    T m_width;                                                                                          ///< @brief 幅
                    T m_height;                                                                                         ///< @brief 高さ
                    T m_depth;                                                                                          ///< @brief 奥行き
                };
            };

            /* メンバ関数 */
            S_Vector3();                                                                                                // コンストラクタ
            S_Vector3(T value);                                                                                         // コンストラクタ
            S_Vector3(T x, T y, T z);                                                                                   // コンストラクタ
            S_Vector3(const T a[3]);                                                                                    // コンストラクタ
            S_Vector3(const S_Vector2<T>& r_XY, T z);                                                                   // コンストラクタ
            ~S_Vector3();                                                                                               // デストラクタ
            void Zero();                                                                                                // ゼロベクトル化
            void Fill(T value);                                                                                         // 各成分を特定の値に変更
            void Normalize();                                                                                           // 単位ベクトル化
            void Invert();                                                                                              // ベクトルを反転
            void RotateX(T angle);                                                                                      // X軸からベクトルを回転
            void RotateY(T angle);                                                                                      // Y軸からベクトルを回転
            void RotateZ(T angle);                                                                                      // Z軸からベクトルを回転
            void RotateAxis(const S_Vector3<T>& r_AXIS, T angle);                                                       // 任意軸からベクトルを回転
            void ClampMagnitude(T min, T max);                                                                          // 大きさでベクトルをクランプ
            T GetMagnitude() const;                                                                                     // 大きさを取得
            T GetMagnitudeSquare() const;                                                                               // 大きさの2乗を取得
            S_Vector3 GetNormalize() const;                                                                             // 単位ベクトルを取得
            S_Vector3 GetInvert() const;                                                                                // 反転したベクトルを取得
            S_Vector3 GetRotateX(T angle) const;                                                                        // X軸から回転したベクトルを取得
            S_Vector3 GetRotateY(T angle) const;                                                                        // Y軸から回転したベクトルを取得
            S_Vector3 GetRotateZ(T angle) const;                                                                        // Z軸から回転したベクトルを取得
            S_Vector3 GetRotateAxis(const S_Vector3<T>& r_AXIS, T angle) const;                                         // 任意軸から回転したベクトルを取得
            S_Vector3 GetClampMagnitude(T min, T max) const;                                                            // 大きさでクランプしたベクトルを取得
            String ToString() const;                                                                                    // ベクトルを文字列として取得

            /* Swizzle */
            template<eVectorFactor factor_0>
            S_Vector3 Get() const
            {
                return S_Vector3(a_[factor_0], a_[factor_0], a_[factor_0]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1>
            S_Vector3 Get() const
            {
                return S_Vector3(a_[factor_0], a_[factor_1], a_[factor_1]);
            }

            template<eVectorFactor factor_0, eVectorFactor factor_1, eVectorFactor factor_2>
            S_Vector3 Get() const
            {
                return S_Vector3(a_[factor_0], a_[factor_1], a_[factor_2]);
            }

            /* 静的メンバ変数 */
            static T s_DotProduct(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                                      // 内積
            static S_Vector3 s_CrossProduct(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                            // 外積
            static T s_ScalarTripleProduct(const S_Vector3& r_A,                                                        // スカラー三重積
                                           const S_Vector3& r_B,
                                           const S_Vector3& r_C);
            static S_Vector3 s_VectorTripleProduct(const S_Vector3& r_A,                                                // ベクトル三重積
                                                   const S_Vector3& r_B,
                                                   const S_Vector3& r_C);
            static S_Vector3 s_Lerp(const S_Vector3& r_START_POINT,                                                     // 線形補間
                                    const S_Vector3& r_END_POINT,
                                    T factor);
            static S_Vector3 s_Slerp(const S_Vector3& r_START_POINT,                                                    // 球面線形補間
                                     const S_Vector3& r_END_POINT,
                                     T factor);
            static S_Vector3 s_Hermite(const S_Vector3& r_START_POINT,                                                  // エルミート補間
                                       const S_Vector3& r_START_TANGETNT,
                                       const S_Vector3& r_END_POINT,
                                       const S_Vector3& r_END_TANGENT,
                                       T factor);
            static S_Vector3 s_CatmullRomSpline(const S_Vector3& r_PREVIOUS_START_POINT,                                // Catmull-Romスプライン補間
                                                const S_Vector3& r_START_POINT,
                                                const S_Vector3& r_END_POINT,
                                                const S_Vector3& r_NEXT_END_POINT,
                                                T factor);
            static S_Vector3 s_Bezier(const S_Vector3& r_START_POINT,                                                   // ベジェ補間
                                      const S_Vector3& r_END_POINT,
                                      const S_Vector3& r_CONTROL_POINT_1,
                                      const S_Vector3& r_CONTROL_POINT_2,
                                      T factor);
            static S_Vector3 s_InterceptPoint(const S_Vector3& r_POSITION,                                              // 迎撃ポイントを取得
                                              const S_Vector3& r_VECTOR,
                                              const S_Vector3& r_ANOTHER_POSITION,
                                              const S_Vector3& r_ANOTHER_VELOCITY);
            static T s_AngleBetweenVectors(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                             // ベクトル間の角度を取得
            static T s_DistanceBetweenVectors(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                          // ベクトル間の距離を取得
            static S_Vector3 s_Minimize(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                                // 各成分の最小値を成分にしたベクトルを取得
            static S_Vector3 s_Maximize(const S_Vector3& r_LHS, const S_Vector3& r_RHS);                                // 各成分の最大値を成分にしたベクトルを取得
            static S_Vector3 s_MoveTowards(const S_Vector3& r_START_POINT,                                              // 2点間からの距離分だけ進んだ点を取得
                                           const S_Vector3& r_END_POINT,
                                           T distance);
            static S_Vector3 s_Project(const S_Vector3& r_VECTOR, const S_Vector3& r_NORMAL);                           // 投影ベクトルを取得
            static S_Vector3 s_Reflect(const S_Vector3& r_VECTOR, const S_Vector3& r_NORMAL);                           // 反射ベクトルを取得
            static S_Vector3 s_Refract(const S_Vector3& r_INCIDENT_VECTOR,                                              // 屈折ベクトルを取得
                                       const S_Vector3& r_NORMAL,
                                       T refractive_index);
            static S_Vector3 s_Slide(const S_Vector3& r_VECTOR, const S_Vector3& r_NORMAL);                             // 滑りベクトルを取得
            static S_Vector3 s_CreateNormal(const S_Vector3& r_POSITION_A,                                              // 法線ベクトルを作成
                                            const S_Vector3& r_POSITION_B,
                                            const S_Vector3& r_POSITION_C);
            static void s_CreateTangentAndBinormal(const S_Vector3& r_POSITION_A,                                       // 接線ベクトルと従法線を作成( 直行化はされてない )
                                                   const S_Vector2<T>& r_TEXTURE_COORD_A,
                                                   const S_Vector3& r_POSITION_B,
                                                   const S_Vector2<T>& r_TEXTURE_COORD_B,
                                                   const S_Vector3& r_POSITION_C,
                                                   const S_Vector2<T>& r_TEXTURE_COORD_C,
                                                   S_Vector3* p_tangent = GA_NULL,
                                                   S_Vector3* p_binormal = GA_NULL);
            static S_Vector3 s_CenterOfGravityWith3Points(const S_Vector3& r_A,                                         // 3点から重心を取得
                                                          const S_Vector3& r_B,
                                                          const S_Vector3& r_C);


            /* S_Vector3型との演算子のオーバーロード */
            const S_Vector3 operator+(const S_Vector3& r_ANOTHER) const;                                                // +演算子のオーバーロード
            const S_Vector3 operator-(const S_Vector3& r_ANOTHER) const;                                                // -演算子のオーバーロード
            const S_Vector3 operator*(const S_Vector3& r_ANOTHER) const;                                                // *演算子のオーバーロード
            const S_Vector3 operator/(const S_Vector3& r_ANOTHER) const;                                                // /演算子のオーバーロード
            const S_Vector3& operator+=(const S_Vector3& r_ANOTHER);                                                    // +=演算子のオーバーロード
            const S_Vector3& operator-=(const S_Vector3& r_ANOTHER);                                                    // -=演算子のオーバーロード
            const S_Vector3& operator*=(const S_Vector3& r_ANOTHER);                                                    // *=演算子のオーバーロード
            const S_Vector3& operator/=(const S_Vector3& r_ANOTHER);                                                    // /=演算子のオーバーロード
            bool operator==(const S_Vector3& r_ANOTHER) const;                                                          // ==演算子のオーバーロード
            bool operator!=(const S_Vector3& r_ANOTHER) const;                                                          // !=演算子のオーバーロード

            /* T型との演算子のオーバーロード */
            const S_Vector3 operator*(T value) const;                                                                   // *演算子のオーバーロード
            const S_Vector3 operator/(T value) const;                                                                   // /演算子のオーバーロード
            const S_Vector3& operator*=(T value);                                                                       // *=演算子のオーバーロード
            const S_Vector3& operator/=(T value);                                                                       // /=演算子のオーバーロード

            /* キャスト */
            operator S_Vector2<T>() const;                                                                              // S_Vector2型へのキャスト
            operator String() const;                                                                                    // String型へのキャスト


#pragma region T型との演算子のオーバーロード


            /* 
            
             @brief     乗算演算子のオーバーロード
             @param[in] value    値
             @param[in] r_VECTOR ベクトル
             @return    const S_Vector3 乗算したベクトル
            
            */
            friend const S_Vector3 operator*(T value, const S_Vector3& r_VECTOR)
            {
                return S_Vector3(r_VECTOR.m_x * value, r_VECTOR.m_y * value, r_VECTOR.m_z * value);
            }


#pragma endregion

        };

        /* 別名 */
        typedef S_Vector3<float> Vector3;                                                                               // Vector3型
    }
}