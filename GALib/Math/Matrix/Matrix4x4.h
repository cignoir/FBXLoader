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
        /* 前方宣言 */
        template<class T>
        struct S_Vector3;

        template<class T>
        struct S_Vector4;

        template<class T>
        struct S_Quaternion;

        template <class T>
        struct S_Matrix3x3;


        /*

         @brief S_Matrix4x4
                4 * 4の行列を表す構造体

        */
        template<class T>
        struct S_Matrix4x4
        {
            /* 定数 */
            static const Uint32 m_s_ELEMENT_COUNT = 16;                                                                 ///< @brief 要素数
            static const T m_s_ORTHOGRAPHIC_2D_NEAR;                                                                    ///< @brief 2D用の正投影の射影行列を作成時の視点から最も近いクリップ面
            static const T m_s_ORTHOGRAPHIC_2D_FAR;                                                                     ///< @brief 2D用の正投影の射影行列を作成時の視点から最も遠いクリップ面
            static const S_Matrix4x4 m_s_ZERO;                                                                          ///< @brief ゼロ行列
            static const S_Matrix4x4 m_s_IDENTITY;                                                                      ///< @brief 単位行列

            /* メンバ変数 */
            union
            {
                T m_elements[m_s_ELEMENT_COUNT];                                                                        ///< @brief 16個の要素を持つ配列
                T m_elements_4x4[4][4];                                                                                 ///< @brief 4 * 4の二次元配列

                /// @brief 行列の各要素
                struct
                {
                    T m_a_11, m_a_12, m_a_13, m_a_14;
                    T m_a_21, m_a_22, m_a_23, m_a_24;
                    T m_a_31, m_a_32, m_a_33, m_a_34;
                    T m_a_41, m_a_42, m_a_43, m_a_44;
                };
            };

            /* メンバ関数 */
            S_Matrix4x4();                                                                                              // コンストラクタ
            S_Matrix4x4(T value);                                                                                       // コンストラクタ
            S_Matrix4x4(T a_11, T a_12, T a_13, T a_14,                                                                 // コンストラクタ
                        T a_21, T a_22, T a_23, T a_24,
                        T a_31, T a_32, T a_33, T a_34,
                        T a_41, T a_42, T a_43, T a_44);
            S_Matrix4x4(const T ELEMENTS[m_s_ELEMENT_COUNT]);                                                           // コンストラクタ
            S_Matrix4x4(const S_Matrix3x3<T>& r_MATRIX);                                                                // コンストラクタ
            ~S_Matrix4x4();                                                                                             // デストラクタ
            void Zero();                                                                                                // ゼロ行列化
            void Identity();                                                                                            // 単位行列化
            void Transpose();                                                                                           // 転置行列化
            void Invert();                                                                                              // 逆行列化
            S_Matrix4x4 GetTranspose() const;                                                                           // 転置行列を取得
            S_Matrix4x4 GetInvert() const;                                                                              // 逆行列を取得
            S_Vector3<T> GetTranslationComponent() const;                                                               // 平行移動成分を取得
            S_Vector3<T> GetScalingComponent() const;                                                                   // 拡縮成分を取得
            S_Vector3<T> GetLocalAxisX() const;                                                                         // ローカル座標のX軸を取得
            S_Vector3<T> GetLocalAxisY() const;                                                                         // ローカル座標のY軸を取得
            S_Vector3<T> GetLocalAxisZ() const;                                                                         // ローカル座標のZ軸を取得
            S_Vector4<T> GetRow(Int32 index = 0) const;                                                                 // 行を取得
            S_Vector4<T> GetColumn(Int32 index = 0) const;                                                              // 列を取得
            String ToString() const;                                                                                    // 行列を文字列として取得
            void SetRow(const S_Vector4<T>& r_ROM, Int32 index = 0);                                                    // 行を設定
            void SetColumn(const S_Vector4<T>& r_COLUMN, Int32 index = 0);                                              // 列を設定

            /* 静的メンバ関数 */
            static S_Matrix4x4 s_CreateRotationX(T angle);                                                              // X軸から回転行列を作成
            static S_Matrix4x4 s_CreateRotationY(T angle);                                                              // Y軸から回転行列を作成
            static S_Matrix4x4 s_CreateRotationZ(T angle);                                                              // Z軸から回転行列を作成
            static S_Matrix4x4 s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle);                               // 任意軸から回転行列を作成
            static S_Matrix4x4 s_CreateRotationYawPitchRoll(T pitch,                                                    // 3軸の回転を反映した回転行列を作成
                                                            T yaw,
                                                            T roll);
            static S_Matrix4x4 s_CreateRotationYawPitchRoll(const S_Vector3<T>& r_ROTATION);                            // 3軸の回転を反映した回転行列を作成
            static S_Matrix4x4 s_CreateScaling(T scaling_rate_x, T scaling_rate_y, T scaling_rate_z);                   // 拡縮行列を作成
            static S_Matrix4x4 s_CreateScaling(const S_Vector3<T>& r_scaling_rate);                                     // 拡縮行列を作成
            static S_Matrix4x4 s_CreateTranslation(T movement_x,                                                        // 平行移動行列を作成
                                                   T movement_y,
                                                   T movement_z);
            static S_Matrix4x4 s_CreateTranslation(const S_Vector3<T>& r_MOVEMENT);                                     // 平行移動行列を作成
            static S_Matrix4x4 s_CreateTRS(const S_Vector3<T>& r_MOVEMENT,                                              // 拡縮・回転・平行移動を掛け合わせた行列を作成 
                                           const S_Vector3<T>& r_ROTATION,
                                           const S_Vector3<T>& r_SCALING_RATE);
            static S_Matrix4x4 s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,                                          // ビュー行列を作成
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR);
            static S_Matrix4x4 s_CreatePerspectiveProjection(T field_of_view_y,                                         // 透視投影の射影行列を作成
                                                             T aspect_ratio,
                                                             T near_clipping_plane,
                                                             T far_clipping_plane);
            static S_Matrix4x4 s_CreateOrthographicProjection(T clip_space_left,                                        // 正投影の射影行列を作成
                                                              T clip_space_right,
                                                              T clip_space_bottom,
                                                              T clip_space_top,
                                                              T near_clipping_plane = m_s_ORTHOGRAPHIC_2D_NEAR,
                                                              T far_clipping_plane = m_s_ORTHOGRAPHIC_2D_FAR);
            static S_Matrix4x4 s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& r_MATRIXS);                          // 3 * 3行列から4 * 4の行列へ変換し、取得
            static S_Matrix4x4 s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& r_QUATERNION);                     // クォータニオンから4 * 4の行列へ変換し、取得
            static S_Matrix4x4 s_CreateViewport(T width, T height);                                                     // ビューポート行列を作成 
            static S_Matrix4x4 s_SlerpRotation(const S_Matrix4x4& r_START_MATRIX,                                       // 回転行列を球面線形補間
                                               const S_Matrix4x4& r_END_MATRIX,
                                               T factor);

            /* S_Matrix4x4型との演算子のオーバーロード */
            const S_Matrix4x4 operator+(const S_Matrix4x4& r_ANOTHER) const;                                            // +演算子のオーバーロード
            const S_Matrix4x4 operator-(const S_Matrix4x4& r_ANOTHER) const;                                            // -演算子のオーバーロード
            const S_Matrix4x4 operator*(const S_Matrix4x4& r_ANOTHER) const;                                            // *演算子のオーバーロード
            const S_Matrix4x4& operator+=(const S_Matrix4x4& r_ANOTHER);                                                // +=演算子のオーバーロード
            const S_Matrix4x4& operator-=(const S_Matrix4x4& r_ANOTHER);                                                // -=演算子のオーバーロード
            const S_Matrix4x4& operator*=(const S_Matrix4x4& r_ANOTHER);                                                // *=演算子のオーバーロード
            bool operator==(const S_Matrix4x4& r_ANOTHER) const;                                                        // ==演算子のオーバーロード
            bool operator!=(const S_Matrix4x4& r_ANOTHER) const;                                                        // !=演算子のオーバーロード

            /* S_Vector4との演算子のオーバーロード */
            const S_Vector4<T> operator*(const S_Vector4<T>& r_VECTOR) const;                                           // *演算子のオーバーロード

            /* キャスト演算子のオーバーロード */
            operator S_Matrix3x3<T>() const;                                                                            // S_Matrix3x3型へのキャスト
            operator String() const;                                                                                    // String型へのキャスト
        };


        /* 別名 */
        typedef S_Matrix4x4<float> Matrix4x4;                                                                           // Matrix4x4型
    }
}