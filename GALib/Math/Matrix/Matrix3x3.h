/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "..\Utility\UtilityMath.h"


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
        /* 前方宣言 */
        template<class T>
        struct S_Vector2;

        template<class T>
        struct S_Vector3;

        template<class T>
        struct S_Matrix4x4;

        template<class T>
        struct S_Quaternion;


        /*

         @brief S_Matrix3x3
                3 * 3の行列を表す構造体

        */
        template<class T>
        struct S_Matrix3x3
        {
            /* 定数 */
            static const Uint32 m_s_ELEMENT_COUNT = 9;                                                      ///< @brief 要素数
            static const S_Matrix3x3 m_s_ZERO;                                                              ///< @brief ゼロ行列
            static const S_Matrix3x3 m_s_IDENTITY;                                                          ///< @brief 単位行列

            /* メンバ変数 */
            union
            {
                struct
                {
                    T m_elements[9];                                                                        ///< @brief 9個の要素を持つ配列
                };

                struct
                {
                    T m_elements_3x3[3][3];                                                                 ///< @brief 3 * 3の二次元配列
                };

                /// @brief 行列の各要素
                struct
                {
                    T m_a_11, m_a_12, m_a_13;
                    T m_a_21, m_a_22, m_a_23;
                    T m_a_31, m_a_32, m_a_33;
                };
            };

            /* メンバ関数 */
            S_Matrix3x3();                                                                                  // コンストラクタ
            S_Matrix3x3(T value);                                                                           // コンストラクタ
            S_Matrix3x3(T a_11, T a_12, T a_13,                                                             // コンストラクタ
                        T a_21, T a_22, T a_23,
                        T a_31, T a_32, T a_33);
            S_Matrix3x3(const T ELEMENTS[9]);                                                               // コンストラクタ
            ~S_Matrix3x3();                                                                                 // デストラクタ
            void Zero();                                                                                    // ゼロ行列化
            void Fill(T value);                                                                             // 各要素を特定の値に変更
            void Identity();                                                                                // 単位行列化
            void Transpose();                                                                               // 転置行列化
            void Invert();                                                                                  // 逆行列化
            S_Matrix3x3 GetTranspose() const;                                                               // 転置行列を取得
            S_Matrix3x3 GetInvert() const;                                                                  // 逆行列を取得
            S_Vector3<T> GetRow(Int32 index = 0) const;                                                     // 行を取得
            S_Vector3<T> GetColumn(Int32 index = 0) const;                                                  // 列を取得
            String ToString() const;                                                                        // 行列を文字列として取得
            void SetRow(const S_Vector3<T>& r_ROW, Int32 index = 0);                                        // 行を設定
            void SetColumn(const S_Vector3<T>& r_COLUMN, Int32 index = 0);                                  // 列を設定

            /* 静的メンバ関数 */
            static S_Matrix3x3 s_CreateRotation(T angle);                                                   // 回転行列を作成
            static S_Matrix3x3 s_CreateRotationX(T angle);                                                  // X軸から回転行列を作成
            static S_Matrix3x3 s_CreateRotationY(T angle);                                                  // Y軸から回転行列を作成
            static S_Matrix3x3 s_CreateRotationZ(T angle);                                                  // Z軸から回転行列を作成
            static S_Matrix3x3 s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle);                   // 任意軸から回転行列を作成 
            static S_Matrix3x3 s_CreateScaling(T scaling_rate_x, T scaling_rate_y);                         // 拡縮行列を作成
            static S_Matrix3x3 s_CreateScaling(const S_Vector2<T>& r_SCALING_RATE);                         // 拡縮行列を作成
            static S_Matrix3x3 s_CreateTranslation(T movement_x, T movement_y);                             // 平行移動行列を作成
            static S_Matrix3x3 s_CreateTranslation(const S_Vector2<T>& r_MOVEMENT);                         // 平行移動行列を作成
            static S_Matrix3x3 s_CreateTRS(const S_Vector2<T>& r_MOVEMENT,                                  // 拡縮・回転・平行移動を掛け合わせた行列を作成 
                                           T angle,
                                           const S_Vector2<T>& r_SCALING_RATE);
            static S_Matrix3x3 s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& r_MATRIX);               // 4 * 4の行列を3 * 3の行列に変換
            static S_Matrix3x3 s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& r_QUATERNION);         // クォータニオンから3 * 3の行列へ変換し、取得
            static S_Matrix3x3 s_CreateNormal(const S_Matrix4x4<T>& r_MATRIX);                              // 法線行列を作成
            static S_Matrix3x3 s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,                              // ビュー行列を作成
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR);

            /* S_Matrix3x3型との演算子のオーバーロード */
            const S_Matrix3x3 operator+(const S_Matrix3x3& r_ANOTHER) const;                                // +演算子のオーバーロード
            const S_Matrix3x3 operator-(const S_Matrix3x3& r_ANOTHER) const;                                // -演算子のオーバーロード
            const S_Matrix3x3 operator*(const S_Matrix3x3& r_ANOTHER) const;                                // *演算子のオーバーロード
            const S_Matrix3x3& operator+=(const S_Matrix3x3& r_ANOTHER);                                    // +=演算子のオーバーロード
            const S_Matrix3x3& operator-=(const S_Matrix3x3& r_ANOTHER);                                    // -=演算子のオーバーロード
            const S_Matrix3x3& operator*=(const S_Matrix3x3& r_ANOTHER);                                    // *=演算子のオーバーロード
            bool operator==(const S_Matrix3x3& r_ANOTHER) const;                                            // ==演算子のオーバーロード
            bool operator!=(const S_Matrix3x3& r_ANOTHER) const;                                            // !=演算子のオーバーロード

            /* S_Vector3型との演算子のオーバーロード */
            const S_Vector3<T> operator*(const S_Vector3<T>& r_VECTOR) const;                               // *演算子のオーバーロード

            /* キャスト演算子のオーバーロード */
            operator String() const;                                                                        // String型へのキャスト
        };


        /* 別名 */
        typedef S_Matrix3x3<float> Matrix3x3;                                                               // Matrix3x3型
    }
}