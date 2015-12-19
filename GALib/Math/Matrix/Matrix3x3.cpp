/* ヘッダファイル */
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "..\Vector\Vector3.h"
#include "..\Quaternion\Quaternion.h"


// 名前空間を省略
using namespace GALib::Math;


/* プロトタイプ宣言 */
template<class T>
static T s_GetDeterminant(const S_Matrix3x3<T>& r_MATRIX);

template<class T>
static void s_Swap(T* p_a, T* p_b);


#pragma region 静的メンバ変数の初期化


template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::m_s_ZERO(static_cast<T>(0));


template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::m_s_IDENTITY;


#pragma endregion


/* 

 @brief コンストラクタ
 @param なし

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3() :

    m_a_11(static_cast<T>(1)),
    m_a_12(0),
    m_a_13(0),

    m_a_21(0),
    m_a_22(static_cast<T>(1)),
    m_a_23(0),

    m_a_31(0),
    m_a_32(0),
    m_a_33(static_cast<T>(1))

{
}


/* 

 @brief     コンストラクタ( 各要素を指定した1つの値で初期化 )
 @param[in] value 値

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3(T value) :

    m_a_11(value),
    m_a_12(value),
    m_a_13(value),

    m_a_21(value),
    m_a_22(value),
    m_a_23(value),

    m_a_31(value),
    m_a_32(value),
    m_a_33(value)

{
}


/* 

 @brief     コンストラクタ( 各要素を指定した1つの値で初期化 )
 @param[in] a_11 要素1
 @param[in] a_12 要素2
 @param[in] a_13 要素3
 @param[in] a_21 要素4
 @param[in] a_22 要素5
 @param[in] a_23 要素6
 @param[in] a_31 要素7
 @param[in] a_32 要素8
 @param[in] a_33 要素9

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3(T a_11, T a_12, T a_13,
                            T a_21, T a_22, T a_23,
                            T a_31, T a_32, T a_33) :

    m_a_11(a_11),
    m_a_12(a_12),
    m_a_13(a_13),
            
    m_a_21(a_21),
    m_a_22(a_22),
    m_a_23(a_23),
            
    m_a_31(a_31),
    m_a_32(a_32),
    m_a_33(a_33)

{
}


/* 

 @brief     コンストラクタ( 各要素を指定した1つの値で初期化 )
 @param[in] ELEMENTS 要素が9個の配列

*/
template<class T>
S_Matrix3x3<T>::S_Matrix3x3(const T ELEMENTS[9])
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] = ELEMENTS[i];
}


/* 

 @brief デストラクタ
 @param なし

*/
template<class T>
S_Matrix3x3<T>::~S_Matrix3x3()
{
}


/* 

 @brief  デストラクタ
 @param  なし
 @return なし

*/
template<class T>
void S_Matrix3x3<T>::Zero()
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; i++)
    {
        this->m_elements[i] = 0;
    }
}


/* 

 @brief     各要素を特定の値に変更する
 @param[in] value 値
 @return    なし

*/
template<class T>
void S_Matrix3x3<T>::Fill(T value)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; i++)
    {
        this->m_elements[i] = value;
    }
}


/* 

 @brief  単位行列化する
 @param  なし
 @return なし

*/
template<class T>
void S_Matrix3x3<T>::Identity()
{
    this->m_a_11 = static_cast<T>(1);
    this->m_a_12 = 0;
    this->m_a_13 = 0;

    this->m_a_21 = 0;
    this->m_a_22 = static_cast<T>(1);
    this->m_a_23 = 0;

    this->m_a_31 = 0;
    this->m_a_32 = 0;
    this->m_a_33 = static_cast<T>(1);
}


/*

 @brief  転置行列化する
 @param  なし
 @return なし

*/
template<class T>
void S_Matrix3x3<T>::Transpose()
{
    ::s_Swap(&this->m_a_12, &this->m_a_21);
    ::s_Swap(&this->m_a_13, &this->m_a_31);
    ::s_Swap(&this->m_a_23, &this->m_a_32);
}


/*

 @brief  逆行列化する
 @param  なし
 @return なし

*/
template<class T>
void S_Matrix3x3<T>::Invert()
{
    // 行列式を取得
    T determinant = ::s_GetDeterminant(*this);
    if (determinant == 0) return;

    // 行列式の逆数
    T reciprocal_determinant = static_cast<T>(1) / determinant;

    // 逆行列を求める
    S_Matrix3x3 inverse_matrix;

    inverse_matrix.m_a_11 = (this->m_a_22 * this->m_a_33 - this->m_a_23 * this->m_a_32) * reciprocal_determinant;
    inverse_matrix.m_a_12 = (this->m_a_13 * this->m_a_32 - this->m_a_12 * this->m_a_33) * reciprocal_determinant;
    inverse_matrix.m_a_13 = (this->m_a_12 * this->m_a_23 - this->m_a_13 * this->m_a_22) * reciprocal_determinant;
    inverse_matrix.m_a_21 = (this->m_a_23 * this->m_a_31 - this->m_a_21 * this->m_a_33) * reciprocal_determinant;
    inverse_matrix.m_a_22 = (this->m_a_11 * this->m_a_33 - this->m_a_13 * this->m_a_31) * reciprocal_determinant;
    inverse_matrix.m_a_23 = (this->m_a_13 * this->m_a_21 - this->m_a_11 * this->m_a_23) * reciprocal_determinant;
    inverse_matrix.m_a_31 = (this->m_a_21 * this->m_a_32 - this->m_a_22 * this->m_a_31) * reciprocal_determinant;
    inverse_matrix.m_a_32 = (this->m_a_12 * this->m_a_31 - this->m_a_11 * this->m_a_32) * reciprocal_determinant;
    inverse_matrix.m_a_33 = (this->m_a_11 * this->m_a_22 - this->m_a_12 * this->m_a_21) * reciprocal_determinant;

    // 逆行列を代入
    (*this) = inverse_matrix;
}


/*

 @brief  転置行列を取得する
 @param  なし
 @return S_Matrix3x3<T> 転置行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::GetTranspose() const
{
    S_Matrix3x3 temp(*this);
    temp.Transpose();

    return temp;
}


/*

 @brief  逆行列を取得する
 @param  なし
 @return S_Matrix3x3<T> 逆行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::GetInvert() const
{
    S_Matrix3x3 temp(*this);
    temp.Invert();

    return temp;
}


/*

 @brief     行を取得する
 @param[in] index 添え字
 @return    S_Matrix3x3<T> 行

*/
template<class T>
S_Vector3<T> S_Matrix3x3<T>::GetRow(Int32 index) const
{
    assert(index >= 0 && index < 3);
    return S_Vector3<T>(this->m_elements[index], this->m_elements[index + 3], this->m_elements[index + 6]);
}


/*

 @brief     列を取得する
 @param[in] index 添え字
 @return    S_Matrix3x3<T> 列

*/
template<class T>
S_Vector3<T> S_Matrix3x3<T>::GetColumn(Int32 index) const
{
    assert(index >= 0 && index < 3);

    index *= 3;
    return S_Vector3<T>(this->m_elements[index], this->m_elements[index + 1], this->m_elements[index + 2]);
}


/*

 @brief  行列を文字列として取得する
 @param  なし
 @return String 文字列に変換した行列

*/
template<class T>
String S_Matrix3x3<T>::ToString() const
{
    char buffer[1024];

    GALib_Sprintf(buffer, "| A11 : %10f, A21 : %10f, A31 : %10f |\n"
                          "| A12 : %10f, A22 : %10f, A32 : %10f |\n"
                          "| A13 : %10f, A23 : %10f, A33 : %10f |",
                          this->m_a_11, this->m_a_21, this->m_a_31,
                          this->m_a_12, this->m_a_22, this->m_a_32,
                          this->m_a_13, this->m_a_23, this->m_a_33);

    return buffer;
}


/*

 @brief     行を設定する
 @param[in] r_ROW 行
 @param[in] index 添え字
 @return    なし

*/
template<class T>
void S_Matrix3x3<T>::SetRow(const S_Vector3<T>& r_ROW, Int32 index)
{
    assert(index >= 0 && index < 3);
    for (Int32 i = 0; i < 3; ++i) this->m_elements[index + i * 3] = r_ROW.m_elements[i];
}


/*

 @brief     列を設定する
 @param[in] r_COLUMN 列
 @param[in] index    添え字
 @return    なし

*/
template<class T>
void S_Matrix3x3<T>::SetColumn(const S_Vector3<T>& r_COLUMN, Int32 index)
{
    assert(index >= 0 && index < 3);
    for (Int32 i = 0; i < 3; ++i) this->m_elements[index + i] = r_COLUMN.m_elements[i];
}


/*

 @brief     回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Matrix3x3<T> 回転行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotation(T angle)
{
    // 回転行列
    S_Matrix3x3 rotation_matrix;

    // サインとコサインを求める
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // 回転行列を求める
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_12 = sine;
    rotation_matrix.m_a_21 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_22 = cosine;

    return rotation_matrix;
}


/*

 @brief     X軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Matrix3x3<T> 回転行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationX(T angle)
{
    return s_CreateRotationZ(angle);
}


/*

 @brief     Y軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Matrix3x3<T> 回転行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationY(T angle)
{
    // 回転行列
    S_Matrix3x3 rotation_matrix;

    // サインとコサインを求める
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // 回転行列を求める
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_13 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_31 = sine;
    rotation_matrix.m_a_33 = cosine;

    return rotation_matrix;
}


/*

 @brief     Z軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Matrix3x3<T> 回転行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationZ(T angle)
{
    // 回転行列
    S_Matrix3x3 rotation_matrix;

    // サインとコサインを求める
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // 回転行列を求める
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_12 = sine;
    rotation_matrix.m_a_21 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_22 = cosine;

    return rotation_matrix;
}


/*

 @brief     任意軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Matrix3x3<T> 回転行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // 回転行列
    S_Matrix3x3 rotation_matrix;

    // サインとコサインを求める
    T sine = Sine(angle);
    T cosine = Cosine(angle);

    // 1 - cosine の値を求める
    T one_minus_cosine = static_cast<T>(1) - cosine;

    // 軸の各値のサインを求める
    T axis_x_sine = r_AXIS.m_x * sine;
    T axis_y_sine = r_AXIS.m_y * sine;
    T axis_z_sine = r_AXIS.m_z * sine;

    // 軸の成分と 1 - cosine をかけた値を求める
    T one_minus_cosine_x = r_AXIS.m_x * one_minus_cosine;
    T one_minus_cosine_y = r_AXIS.m_y * one_minus_cosine;
    T one_minus_cosine_z = r_AXIS.m_z * one_minus_cosine;

    // 回転行列を求める
    rotation_matrix.m_a_11 = (r_AXIS.m_x * one_minus_cosine_x) + cosine;
    rotation_matrix.m_a_21 = (r_AXIS.m_x * one_minus_cosine_y) - axis_z_sine;
    rotation_matrix.m_a_31 = (r_AXIS.m_x * one_minus_cosine_z) + axis_y_sine;

    rotation_matrix.m_a_12 = (r_AXIS.m_y * one_minus_cosine_x) + axis_z_sine;
    rotation_matrix.m_a_22 = (r_AXIS.m_y * one_minus_cosine_y) + cosine;
    rotation_matrix.m_a_32 = (r_AXIS.m_y * one_minus_cosine_z) - axis_x_sine;

    rotation_matrix.m_a_13 = (r_AXIS.m_z * one_minus_cosine_x) - axis_y_sine;
    rotation_matrix.m_a_23 = (r_AXIS.m_z * one_minus_cosine_y) + axis_x_sine;
    rotation_matrix.m_a_33 = (r_AXIS.m_z * one_minus_cosine_z) + cosine;

    return rotation_matrix;
}


/*

 @brief     拡縮行列を作成する
 @param[in] rate_x X方向の拡大率
 @param[in] rate_y Y方向の拡大率
 @return    S_Matrix3x3<T> 拡縮行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateScaling(T scaling_rate_x, T scaling_rate_y)
{
    S_Matrix3x3 scaling_matrix;

    scaling_matrix.m_a_11 = scaling_rate_x;
    scaling_matrix.m_a_22 = scaling_rate_y;

    return scaling_matrix;
}


/*

 @brief     拡縮行列を作成する
 @param[in] r_SCALING_RATE 拡大率
 @return    S_Matrix3x3<T> 拡縮行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateScaling(const S_Vector2<T>& r_SCALING_RATE)
{
    S_Matrix3x3 scaling_matrix;

    scaling_matrix.m_a_11 = r_SCALING_RATE.m_x;
    scaling_matrix.m_a_22 = r_SCALING_RATE.m_y;

    return scaling_matrix;
}


/*

 @brief     平行移動行列を作成する
 @param[in] movement_x X方向の移動量
 @param[in] movement_y Y方向の移動量
 @return    S_Matrix3x3<T> 平行移動行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTranslation(T movement_x, T movement_y)
{
    S_Matrix3x3 translation_matrix;

    translation_matrix.m_a_31 = movement_x;
    translation_matrix.m_a_32 = movement_y;

    return translation_matrix;
}


/*

 @brief     平行移動行列を作成する
 @param[in] r_MOVEMENT 移動量
 @return    S_Matrix3x3<T> 平行移動行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTranslation(const S_Vector2<T>& r_MOVEMENT)
{
    S_Matrix3x3 translation_matrix;

    translation_matrix.m_a_31 = r_MOVEMENT.m_x;
    translation_matrix.m_a_32 = r_MOVEMENT.m_y;

    return translation_matrix;
}


/*

 @brief     拡縮・回転・平行移動を掛け合わせた行列を作成する
 @param[in] r_MOVEMENT 移動量
 @return    S_Matrix3x3<T> 平行移動行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTRS(const S_Vector2<T>& r_MOVEMENT,
                                           T angle,
                                           const S_Vector2<T>& r_SCALING_RATE)
{
    S_Matrix3x3 trs_matrix = s_CreateRotation(angle);

    trs_matrix.m_a_11 *= r_SCALING_RATE.m_x;
    trs_matrix.m_a_12 *= r_SCALING_RATE.m_x;

    trs_matrix.m_a_21 *= r_SCALING_RATE.m_y;
    trs_matrix.m_a_22 *= r_SCALING_RATE.m_y;

    trs_matrix.m_a_31 = r_MOVEMENT.m_x;
    trs_matrix.m_a_32 = r_MOVEMENT.m_y;

    return trs_matrix;
}


/*

 @brief     4 * 4の行列を3 * 3の行列に変換し、取得する
 @param[in] r_MATRIX_4x4 4 * 4の行列
 @return    S_Matrix3x3<T> 3 * 3の行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& r_MATRIX_4x4)
{
    // 変換後の行列
    S_Matrix3x3 convertion_matrix;

    // 4 * 4行列を3 * 3に変換
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        Uint32 shift_index = i / 3;
        convertion_matrix.m_elements[i] = r_MATRIX_4x4.m_elements[i + shift_index];
    }

    return convertion_matrix;
}


/*

 @brief     クォータニオンを3 * 3の行列に変換し、取得する
 @param[in] r_QUATERNION クォータニオン
 @return    S_Matrix3x3<T> 3 * 3の行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& r_QUATERNION)
{
    // 変換後の行列
    S_Matrix3x3 convertion_matrix;

    // 各成分の掛け合わせた値を求める
    T xx = Square(r_QUATERNION.m_x);
    T xy = r_QUATERNION.m_x * r_QUATERNION.m_y;
    T xz = r_QUATERNION.m_x * r_QUATERNION.m_z;
    T xt = r_QUATERNION.m_x * r_QUATERNION.m_t;

    T yy = Square(r_QUATERNION.m_y);
    T yz = r_QUATERNION.m_y * r_QUATERNION.m_z;
    T yt = r_QUATERNION.m_y * r_QUATERNION.m_t;

    T zz = Square(r_QUATERNION.m_z);
    T zt = r_QUATERNION.m_z * r_QUATERNION.m_t;

    // クォータニオンを3 * 3の行列へ変換
    convertion_matrix.m_a_11 = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
    convertion_matrix.m_a_12 = static_cast<T>(2) * (xy + zt);
    convertion_matrix.m_a_13 = static_cast<T>(2) * (xz - yt);

    convertion_matrix.m_a_21 = static_cast<T>(2) * (xy - zt);
    convertion_matrix.m_a_22 = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
    convertion_matrix.m_a_23 = static_cast<T>(2) * (yt + xt);

    convertion_matrix.m_a_31 = static_cast<T>(2) * (xz + yt);
    convertion_matrix.m_a_32 = static_cast<T>(2) * (yz - xt);
    convertion_matrix.m_a_33 = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);

    return convertion_matrix;
}


/*

 @brief     法線行列を作成する
 @param[in] r_MATRIX 4 * 4の行列
 @return    S_Matrix3x3<T> 法線行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateNormal(const S_Matrix4x4<T>& r_MATRIX)
{
    S_Matrix3x3 normal_matrix(s_ConvertMatrix4x4ToMatrix3x3(r_MATRIX));

    normal_matrix.Invert();
    normal_matrix.Transpose();

    return normal_matrix;
}


/*

 @brief     ビュー行列を作成する
 @param[in] r_EYE_POINT    視点
 @param[in] r_TARGET_POINT 注視点
 @param[in] r_UP_VECTOR    上方向
 @return    S_Matrix3x3<T> ビュー行列

*/
template<class T>
S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR)
{
    // ビュー行列
    S_Matrix3x3 view_matrix;

    // Z軸を求める
    S_Vector3<T> z_axis = r_TARGET_POINT - r_EYE_POINT;
    z_axis.Normalize();

    // X軸を求める
    S_Vector3<T> x_axis = S_Vector3<T>::s_CrossProduct(z_axis, r_UP_VECTOR);
    x_axis.Normalize();

    // Y軸を求める
    S_Vector3<T> y_axis = S_Vector3<T>::s_CrossProduct(x_axis, z_axis);
    y_axis.Normalize();

    // Z軸を反転する
    z_axis.Invert();

    // ビュー行列を求める
    view_matrix.m_a_11 = x_axis.m_x;
    view_matrix.m_a_21 = x_axis.m_y;
    view_matrix.m_a_31 = x_axis.m_z;

    view_matrix.m_a_12 = y_axis.m_x;
    view_matrix.m_a_22 = y_axis.m_y;
    view_matrix.m_a_32 = y_axis.m_z;

    view_matrix.m_a_13 = z_axis.m_x;
    view_matrix.m_a_23 = z_axis.m_y;
    view_matrix.m_a_33 = z_axis.m_z;

    return view_matrix;
}


#pragma region S_Matrix3x3型との演算子のオーバーロード


/*

 @brief     加算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    const S_Matrix3x3<T> 加算した行列

*/
template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::operator+(const S_Matrix3x3<T>& r_ANOTHER) const
{
    S_Matrix3x3 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] + r_ANOTHER.m_elements[i];

    return temp;
}


/*

 @brief     減算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    const S_Matrix3x3<T> 減算した行列

*/
template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::operator-(const S_Matrix3x3<T>& r_ANOTHER) const
{
    S_Matrix3x3 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] - r_ANOTHER.m_elements[i];

    return temp;
}


/*

 @brief     乗算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    const S_Matrix3x3<T> 乗算した行列

*/
template<class T>
const S_Matrix3x3<T> S_Matrix3x3<T>::operator*(const S_Matrix3x3<T>& r_ANOTHER) const
{
    // 仮の行列
    S_Matrix3x3 temp;

    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // 各行列の添え字を求める
        Uint32 index = i % 3;
        Uint32 another_index = (i / 3) * 3;

        // 行列同士の乗算
        temp.m_elements[i] = this->m_elements[index]     * r_ANOTHER.m_elements[another_index]
                           + this->m_elements[index + 3] * r_ANOTHER.m_elements[another_index + 1]
                           + this->m_elements[index + 6] * r_ANOTHER.m_elements[another_index + 2];
    }

    return temp;
}


/*

 @brief     加算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    const S_Matrix3x3<T>& 加算した行列

*/
template<class T>
const S_Matrix3x3<T>& S_Matrix3x3<T>::operator+=(const S_Matrix3x3<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] += r_ANOTHER.m_elements[i];

    return (*this);
}


/*

 @brief     減算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    const S_Matrix3x3<T>& 減算した行列

*/
template<class T>
const S_Matrix3x3<T>& S_Matrix3x3<T>::operator-=(const S_Matrix3x3<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] -= r_ANOTHER.m_elements[i];

    return (*this);
}


/*

 @brief     乗算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    const S_Matrix3x3<T>& 乗算した行列

*/
template<class T>
const S_Matrix3x3<T>& S_Matrix3x3<T>::operator*=(const S_Matrix3x3<T>& r_ANOTHER)
{
    // 仮の行列
    S_Matrix3x3 temp;

    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // 各行列の添え字を求める
        Uint32 index = i % 3;
        Uint32 another_index = (i / 3) * 3;

        // 行列同士の乗算
        temp.m_elements[i] = this->m_elements[index]     * r_ANOTHER.m_elements[another_index]
                           + this->m_elements[index + 3] * r_ANOTHER.m_elements[another_index + 1]
                           + this->m_elements[index + 6] * r_ANOTHER.m_elements[another_index + 2];
    }

    // 仮の行列を代入
    (*this) = temp;

    return (*this);
}


/*

 @brief     等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    bool  比較した結果
 @retval    true  同じ行列の場合
 @retval    false 違う行列の場合

*/
template<class T>
bool S_Matrix3x3<T>::operator==(const S_Matrix3x3<T>& r_ANOTHER) const
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        if (Absolute(this->m_elements[i] - r_ANOTHER.m_elements[i]) > GetEpsilon<T>()) return false;
    }

    return true;
}


/*

 @brief     非等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @return    bool  比較した結果
 @retval    true  違う行列の場合
 @retval    false 同じ行列の場合

*/
template<class T>
bool S_Matrix3x3<T>::operator!=(const S_Matrix3x3<T>& r_ANOTHER) const
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        if (Absolute(this->m_elements[i] - r_ANOTHER.m_elements[i]) > GetEpsilon<T>()) return true;
    }

    return false;
}


#pragma endregion


#pragma region S_Vector3型との演算子のオーバーロード


/*

 @brief     乗算演算子のオーバーロード
 @param[in] r_VACTOR 3Dベクトル
 @return    const S_Vector3<T> 乗算したベクトル

*/
template<class T>
const S_Vector3<T> S_Matrix3x3<T>::operator*(const S_Vector3<T>& r_VACTOR) const
{
    S_Vector3<T> temp_vactor;

    temp_vactor.m_x = this->m_a_11 * r_VACTOR.m_x
                   + this->m_a_21 * r_VACTOR.m_y
                   + this->m_a_31 * r_VACTOR.m_z;

    temp_vactor.m_y = this->m_a_12 * r_VACTOR.m_x
                   + this->m_a_22 * r_VACTOR.m_y
                   + this->m_a_32 * r_VACTOR.m_z;

    temp_vactor.m_z = this->m_a_13 * r_VACTOR.m_x
                   + this->m_a_23 * r_VACTOR.m_y
                   + this->m_a_33 * r_VACTOR.m_z;

    return temp_vactor;
}


#pragma endregion


#pragma region キャスト

/*

 @brief  String型へのキャスト
 @param  なし
 @return String 文字列に変換した行列

*/
template<class T>
S_Matrix3x3<T>::operator String() const
{
    return ToString();
}


#pragma endregion


/*

 @brief     行列式を取得する
 @param[in] r_MATRIX 3 * 3行列
 @return    T 行列式

*/
template<class T>
static T s_GetDeterminant(const S_Matrix3x3<T>& r_MATRIX)
{
    return (r_MATRIX.m_a_11 * r_MATRIX.m_a_22 * r_MATRIX.m_a_33)
         + (r_MATRIX.m_a_21 * r_MATRIX.m_a_32 * r_MATRIX.m_a_13)
         + (r_MATRIX.m_a_31 * r_MATRIX.m_a_12 * r_MATRIX.m_a_23)
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_32 * r_MATRIX.m_a_23)
         - (r_MATRIX.m_a_31 * r_MATRIX.m_a_22 * r_MATRIX.m_a_13)
         - (r_MATRIX.m_a_21 * r_MATRIX.m_a_12 * r_MATRIX.m_a_33);
}


/* 

 @brief     値の交換を行う
 @param[in] p_a 値のポインタ
 @param[in] p_b もう1つの値のポインタ
 @reutrn    なし

*/ 
template<class T>
void s_Swap(T* p_a, T* p_b)
{
    T temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}


/* 明示的インスタンス化 */
template struct S_Matrix3x3<float>;
template struct S_Matrix3x3<double>;