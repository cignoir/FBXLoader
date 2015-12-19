/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Vector/Vector3.h"


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
        struct S_Matrix3x3;

        template<class T>
        struct S_Matrix4x4;


        /*

         @brief S_Quaternion
                クォータニオンを表す構造体

        */
        template<class T>
        struct S_Quaternion
        {
            /* 定数 */
            static const S_Quaternion m_s_IDENTITY;                                                             ///< @brief 単位クォータニオン

            /* メンバ変数 */
            union
            {
                struct
                {
                    T m_elements[4];                                                                            ///< brief 4つの要素を持つ配列
                };

                struct
                {
                    T m_t;                                                                                      ///< @brief T成分
                    T m_x;                                                                                      ///< @brief X成分
                    T m_y;                                                                                      ///< @brief Y成分
                    T m_z;                                                                                      ///< @brief Z成分
                };
            };

            /* メンバ関数 */
            S_Quaternion();                                                                                     // コンストラクタ
            S_Quaternion(T value);                                                                              // コンストラクタ
            S_Quaternion(T t, T x, T y, T z);                                                                   // コンストラクタ
            S_Quaternion(T t, const S_Vector3<T>& r_XYZ);                                                       // コンストラクタ
            ~S_Quaternion();                                                                                    // デストラクタ
            void Fill(T value);                                                                                 // 各成分を特定の値に変更
            void Identity();                                                                                    // 単位クォータニオン化
            void Normalize();                                                                                   // 正規化
            void Invert();                                                                                      // 逆クォータニオン化
            T GetMagnitude() const;                                                                             // 大きさを取得
            T GetMagnitudeSquare() const;                                                                       // 大きさの2乗を取得
            S_Quaternion GetNormalize() const;                                                                  // 正規化したクォータニオンを取得
            S_Quaternion GetInvert() const;                                                                     // 逆クォータニオンを取得
            T GetAngleFromXAxis() const;                                                                        // X軸からの角度を取得
            T GetAngleFromYAxis() const;                                                                        // Y軸からの角度を取得
            T GetAngleFromZAxis() const;                                                                        // Z軸からの角度を取得
            void GetAxisAndAngle(S_Vector3<T>* p_axis, T* p_angle) const;                                       // 軸と角度を取得
            String ToString() const;                                                                            // クォータニオンを文字列として取得

            /* 静的メンバ関数 */
            static T s_DotProduct(const S_Quaternion<T>& r_LHS, const S_Quaternion<T>& r_RHS);                  // 内積
            static S_Quaternion s_CreateRotationAxis(const S_Vector3<T>& r_AXIS,                                // 任意軸からクォータニオンを作成
                                                     T angle);
            static S_Quaternion s_CreateRotationPitchYawRoll(T pitch,                                           // 3軸の回転を反映したクォータニオンを作成
                                                             T yaw,
                                                             T roll);
            static S_Quaternion s_CreateRotationPitchYawRoll(const S_Vector3<T>& r_ROTATION);                   // 3軸の回転を反映したクォータニオンを作成
            static S_Quaternion s_CreateLookRotation(const S_Vector3<T>& r_DIRECTION,                           // 任意の向きへ向くためのクォータニオンを作成
                                                     const S_Vector3<T>& r_UP_VECTOR);
            static S_Quaternion s_CreateFromToRotation(const S_Vector3<T>& r_FROM_DIRECTION,                    // 向きから向きへ回転させるクォータニオンを作成 
                                                       const S_Vector3<T>& r_TO_DIRECTION);
            static S_Quaternion s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& r_MATRIX);                 // 3 * 3の行列からクォータニオンへ変換して取得
            static S_Quaternion s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& r_MATRIX);                 // 4 * 4の行列からクォータニオンへ変換して取得
            static S_Quaternion s_Lerp(const S_Quaternion& r_START,                                             // 線形補間
                                       const S_Quaternion& r_END,
                                       T factor);
            static S_Quaternion s_Slerp(const S_Quaternion& r_START,                                            // 球面線形補間
                                        const S_Quaternion& r_END,
                                        T factor);

            /* S_Quaternion型との演算子のオーバーロード */
            const S_Quaternion operator+(const S_Quaternion& r_ANOTHER) const;                                  // +演算子のオーバーロード
            const S_Quaternion operator-(const S_Quaternion& r_ANOTHER) const;                                  // -演算子のオーバーロード
            const S_Quaternion operator*(const S_Quaternion& r_ANOTHER) const;                                  // *演算子のオーバーロード
            const S_Quaternion& operator+=(const S_Quaternion& r_ANOTHER);                                      // +=演算子のオーバーロード
            const S_Quaternion& operator-=(const S_Quaternion& r_ANOTHER);                                      // -=演算子のオーバーロード
            const S_Quaternion& operator*=(const S_Quaternion& r_ANOTHER);                                      // *=演算子のオーバーロード
            bool operator==(const S_Quaternion& r_ANOTHER) const;                                               // ==演算子のオーバーロード
            bool operator!=(const S_Quaternion& r_ANOTHER) const;                                               // !=演算子のオーバーロード

            /* T型との演算子のオーバーロード */
            const S_Quaternion operator*(T value) const;                                                        // *演算子のオーバーロード
            const S_Quaternion& operator*=(T value);                                                            // *=演算子のオーバーロード

            /* キャスト演算子のオーバーロード */
            operator S_Vector3<T>() const;                                                                      // S_Vector3型へのキャスト
            operator String() const;                                                                            // String型へのキャスト

#pragma region T型との演算子のオーバーロード


            /* 

             @brief  乗算演算子のオーバーロード
             @param[in] value        値
             @param[in] r_QUATERNION クォータニオン 
             @return const S_Quaternion<T> 乗算したクォータニオン
            
            */
            friend const S_Quaternion operator*(T value, const S_Quaternion& r_QUATERNION)
            {
                return S_Quaternion(r_QUATERNION.m_t * value,
                                    r_QUATERNION.m_x * value,
                                    r_QUATERNION.m_y * value,
                                    r_QUATERNION.m_z * value);
            }


#pragma endregion
 
       };

       /* 別名 */
        typedef S_Quaternion<float> Quaternion;                                                             // Vector2型
    }
}