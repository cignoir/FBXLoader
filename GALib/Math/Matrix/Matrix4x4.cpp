/* ヘッダファイル */
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "..\Vector\Vector3.h"
#include "..\Vector\Vector4.h"
#include "..\Quaternion\Quaternion.h"


// 名前空間を省略
using namespace GALib::Math;


/* プロトタイプ宣言 */
template<class T>
static T s_GetDeterminant(const S_Matrix4x4<T>& r_MATRIX);

template<class T>
static void s_Swap(T* p_a, T* p_b);
    
    
#pragma region 静的メンバ変数の初期化
    
    
template<class T>
const T S_Matrix4x4<T>::m_s_ORTHOGRAPHIC_2D_NEAR = static_cast<T>(-1);
    
    
template<class T>
const T S_Matrix4x4<T>::m_s_ORTHOGRAPHIC_2D_FAR = static_cast<T>(1);
    
    
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::m_s_ZERO(static_cast<T>(0));
    
    
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::m_s_IDENTITY;
    
    
#pragma endregion
    
    
/* 

 @brief コンストラクタ
 @param なし

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4() : 
    
    m_a_11(static_cast<T>(1)),
    m_a_12(0),
    m_a_13(0),
    m_a_14(0),
    
    m_a_21(0),
    m_a_22(static_cast<T>(1)),
    m_a_23(0),
    m_a_24(0),
    
    m_a_31(0),
    m_a_32(0),
    m_a_33(static_cast<T>(1)),
    m_a_34(0),
    
    m_a_41(0),
    m_a_42(0),
    m_a_43(0),
    m_a_44(static_cast<T>(1))
    
{
}
    
    
/* 

 @brief     コンストラクタ( 各要素を指定した1つの値で初期化 )
 @param[in] value 値

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(T value) :

    m_a_11(value),
    m_a_12(value),
    m_a_13(value),
    m_a_14(value),
    
    m_a_21(value),
    m_a_22(value),
    m_a_23(value),
    m_a_24(value),
    
    m_a_31(value),
    m_a_32(value),
    m_a_33(value),
    m_a_34(value),
    
    m_a_41(value),
    m_a_42(value),
    m_a_43(value),
    m_a_44(value)


{
}
    
    
/* 

 @brief     コンストラクタ( 各要素を指定した1つの値で初期化 )
 @param[in] 要素1
 @param[in] 要素2
 @param[in] 要素3
 @param[in] 要素4
 @param[in] 要素5
 @param[in] 要素6
 @param[in] 要素7
 @param[in] 要素8
 @param[in] 要素9
 @param[in] 要素10
 @param[in] 要素11
 @param[in] 要素12
 @param[in] 要素13
 @param[in] 要素14
 @param[in] 要素15
 @param[in] 要素16

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(T a_11, T a_12, T a_13, T a_14,
                            T a_21, T a_22, T a_23, T a_24,
                            T a_31, T a_32, T a_33, T a_34,
                            T a_41, T a_42, T a_43, T a_44) :
    
    m_a_11(a_11),
    m_a_12(a_12),
    m_a_13(a_13),
    m_a_14(a_14),
    
    m_a_21(a_21),
    m_a_22(a_22),
    m_a_23(a_23),
    m_a_24(a_24),
    
    m_a_31(a_31),
    m_a_32(a_32),
    m_a_33(a_33),
    m_a_34(a_34),
    
    m_a_41(a_41),
    m_a_42(a_42),
    m_a_43(a_43),
    m_a_44(a_44)
    
{
}
    
   
/* 

 @brief     コンストラクタ( 各要素を指定した1つの値で初期化 )
 @param[in] ELEMENTS 要素が16個の配列

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(const T ELEMENTS[m_s_ELEMENT_COUNT])
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) m_elements[i] = ELEMENTS[i];
}
    
   
/* 

 @brief     コンストラクタ( 3 * 3行列で要素の初期化 )
 @param[in] r_MATRIX 3 * 3行列

*/
template<class T>
S_Matrix4x4<T>::S_Matrix4x4(const S_Matrix3x3<T>& r_MATRIX)
{
    *this = s_ConvertMatrix3x3ToMatrix4x4(r_MATRIX);
}
    
    
/* 

 @brief     デストラクタ
 @param[in] なし

*/
template<class T>
S_Matrix4x4<T>::~S_Matrix4x4()
{
}
    
    
/* 

 @brief  ゼロ行列化する
 @param  なし
 @reutrn なし

*/
template<class T>
void S_Matrix4x4<T>::Zero()
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; i++) m_elements[i] = 0;
}
    
    
/* 

 @brief  単位行列化する
 @param  なし
 @reutrn なし

*/
template<class T>
void S_Matrix4x4<T>::Identity()
{
    this->m_a_11 = static_cast<T>(1);
    this->m_a_12 = 0;
    this->m_a_13 = 0;
    this->m_a_14 = 0;
    
    this->m_a_21 = 0;
    this->m_a_22 = static_cast<T>(1);
    this->m_a_23 = 0;
    this->m_a_24 = 0;
    
    this->m_a_31 = 0;
    this->m_a_32 = 0;
    this->m_a_33 = static_cast<T>(1);
    this->m_a_34 = 0;
    
    this->m_a_41 = 0;
    this->m_a_42 = 0;
    this->m_a_43 = 0;
    this->m_a_44 = static_cast<T>(1);
}
    
 
/* 

 @brief  転置行列化する
 @param  なし
 @reutrn なし

*/
template<class T>
void S_Matrix4x4<T>::Transpose()
{
    s_Swap(&this->m_a_12, &this->m_a_21);
    s_Swap(&this->m_a_13, &this->m_a_31);
    s_Swap(&this->m_a_14, &this->m_a_41);
    s_Swap(&this->m_a_23, &this->m_a_32);
    s_Swap(&this->m_a_24, &this->m_a_42);
    s_Swap(&this->m_a_34, &this->m_a_43);
}
    
    
/* 

 @brief  逆行列化する
 @param  なし
 @reutrn なし

*/
template<class T>
void S_Matrix4x4<T>::Invert()
{
    // 行列式を取得
    T determinant = s_GetDeterminant(*this);
    if (determinant == 0) return;
    
    // 行列式の逆数
    T reciprocal_determinant = static_cast<T>(1) / determinant;
    
    // 逆行列を求める
    S_Matrix4x4 inverse_matrix;

    inverse_matrix.m_a_11 = ((this->m_a_22 * this->m_a_33 * this->m_a_44) + (this->m_a_23 * this->m_a_34 * this->m_a_42) + (this->m_a_24 * this->m_a_32 * this->m_a_43)
                          -  (this->m_a_22 * this->m_a_34 * this->m_a_43) - (this->m_a_23 * this->m_a_32 * this->m_a_44) - (this->m_a_24 * this->m_a_33 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_12 = ((this->m_a_12 * this->m_a_34 * this->m_a_43) + (this->m_a_13 * this->m_a_32 * this->m_a_44) + (this->m_a_14 * this->m_a_33 * this->m_a_42)
                          -  (this->m_a_12 * this->m_a_33 * this->m_a_44) - (this->m_a_13 * this->m_a_34 * this->m_a_42) - (this->m_a_14 * this->m_a_32 * this->m_a_43)) * reciprocal_determinant;
    
    inverse_matrix.m_a_13 = ((this->m_a_12 * this->m_a_23 * this->m_a_44) + (this->m_a_13 * this->m_a_24 * this->m_a_42) + (this->m_a_14 * this->m_a_22 * this->m_a_43)
                          -  (this->m_a_12 * this->m_a_24 * this->m_a_43) - (this->m_a_13 * this->m_a_22 * this->m_a_44) - (this->m_a_14 * this->m_a_23 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_14 = ((this->m_a_12 * this->m_a_24 * this->m_a_33) + (this->m_a_13 * this->m_a_22 * this->m_a_34) + (this->m_a_14 * this->m_a_23 * this->m_a_32)
                          -  (this->m_a_12 * this->m_a_23 * this->m_a_34) - (this->m_a_13 * this->m_a_24 * this->m_a_32) - (this->m_a_14 * this->m_a_22 * this->m_a_33)) * reciprocal_determinant;
    
    inverse_matrix.m_a_21 = ((this->m_a_21 * this->m_a_34 * this->m_a_43) + (this->m_a_23 * this->m_a_31 * this->m_a_44) + (this->m_a_24 * this->m_a_33 * this->m_a_41)
                          -  (this->m_a_21 * this->m_a_33 * this->m_a_44) - (this->m_a_23 * this->m_a_34 * this->m_a_41) - (this->m_a_24 * this->m_a_31 * this->m_a_43)) * reciprocal_determinant;
    
    inverse_matrix.m_a_22 = ((this->m_a_11 * this->m_a_33 * this->m_a_44) + (this->m_a_13 * this->m_a_34 * this->m_a_41) + (this->m_a_14 * this->m_a_31 * this->m_a_43)
                          -  (this->m_a_11 * this->m_a_34 * this->m_a_43) - (this->m_a_13 * this->m_a_31 * this->m_a_44) - (this->m_a_14 * this->m_a_33 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_23 = ((this->m_a_11 * this->m_a_24 * this->m_a_43) + (this->m_a_13 * this->m_a_21 * this->m_a_44) + (this->m_a_14 * this->m_a_23 * this->m_a_41)
                          -  (this->m_a_11 * this->m_a_23 * this->m_a_44) - (this->m_a_13 * this->m_a_24 * this->m_a_41) - (this->m_a_14 * this->m_a_21 * this->m_a_43)) * reciprocal_determinant;
    
    inverse_matrix.m_a_24 = ((this->m_a_11 * this->m_a_23 * this->m_a_34) + (this->m_a_13 * this->m_a_24 * this->m_a_31) + (this->m_a_14 * this->m_a_21 * this->m_a_33)
                          -  (this->m_a_11 * this->m_a_24 * this->m_a_33) - (this->m_a_13 * this->m_a_21 * this->m_a_34) - (this->m_a_14 * this->m_a_23 * this->m_a_31)) * reciprocal_determinant;
    
    inverse_matrix.m_a_31 = ((this->m_a_21 * this->m_a_32 * this->m_a_44) + (this->m_a_22 * this->m_a_34 * this->m_a_41) + (this->m_a_24 * this->m_a_31 * this->m_a_42)
                          -  (this->m_a_21 * this->m_a_34 * this->m_a_42) - (this->m_a_22 * this->m_a_31 * this->m_a_44) - (this->m_a_24 * this->m_a_32 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_32 = ((this->m_a_11 * this->m_a_34 * this->m_a_42) + (this->m_a_12 * this->m_a_31 * this->m_a_44) + (this->m_a_14 * this->m_a_32 * this->m_a_41)
                          -  (this->m_a_11 * this->m_a_32 * this->m_a_44) - (this->m_a_12 * this->m_a_34 * this->m_a_41) - (this->m_a_14 * this->m_a_31 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_33 = ((this->m_a_11 * this->m_a_22 * this->m_a_44) + (this->m_a_12 * this->m_a_24 * this->m_a_41) + (this->m_a_14 * this->m_a_21 * this->m_a_42)
                          -  (this->m_a_11 * this->m_a_24 * this->m_a_42) - (this->m_a_12 * this->m_a_21 * this->m_a_44) - (this->m_a_14 * this->m_a_22 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_34 = ((this->m_a_11 * this->m_a_24 * this->m_a_32) + (this->m_a_12 * this->m_a_21 * this->m_a_34) + (this->m_a_14 * this->m_a_22 * this->m_a_31)
                          -  (this->m_a_11 * this->m_a_22 * this->m_a_34) - (this->m_a_12 * this->m_a_24 * this->m_a_31) - (this->m_a_14 * this->m_a_21 * this->m_a_32)) * reciprocal_determinant;
    
    inverse_matrix.m_a_41 = ((this->m_a_21 * this->m_a_33 * this->m_a_42) + (this->m_a_22 * this->m_a_31 * this->m_a_43) + (this->m_a_23 * this->m_a_32 * this->m_a_41)
                          -  (this->m_a_21 * this->m_a_32 * this->m_a_43) - (this->m_a_22 * this->m_a_33 * this->m_a_41) - (this->m_a_23 * this->m_a_31 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_42 = ((this->m_a_11 * this->m_a_32 * this->m_a_43) + (this->m_a_12 * this->m_a_33 * this->m_a_41) + (this->m_a_13 * this->m_a_31 * this->m_a_42)
                          -  (this->m_a_11 * this->m_a_33 * this->m_a_42) - (this->m_a_12 * this->m_a_31 * this->m_a_43) - (this->m_a_13 * this->m_a_32 * this->m_a_41)) * reciprocal_determinant;
    
    inverse_matrix.m_a_43 = ((this->m_a_11 * this->m_a_23 * this->m_a_42) + (this->m_a_12 * this->m_a_21 * this->m_a_43) + (this->m_a_13 * this->m_a_22 * this->m_a_41)
                          -  (this->m_a_11 * this->m_a_22 * this->m_a_43) - (this->m_a_12 * this->m_a_23 * this->m_a_41) - (this->m_a_13 * this->m_a_21 * this->m_a_42)) * reciprocal_determinant;
    
    inverse_matrix.m_a_44 = ((this->m_a_11 * this->m_a_22 * this->m_a_33) + (this->m_a_12 * this->m_a_23 * this->m_a_31) + (this->m_a_13 * this->m_a_21 * this->m_a_32)
                          -  (this->m_a_11 * this->m_a_23 * this->m_a_32) - (this->m_a_12 * this->m_a_21 * this->m_a_33) - (this->m_a_13 * this->m_a_22 * this->m_a_31)) * reciprocal_determinant;
       
    // 逆行列を代入
    (*this) = inverse_matrix;
}
    
    
/* 

 @brief  転置行列を取得する
 @param  なし
 @reutrn S_Matrix4x4<T> 転置行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::GetTranspose() const
{
    S_Matrix4x4 temp(*this);
    temp.Transpose();
    
    return temp;
}


/* 

 @brief  逆行列を取得する
 @param  なし
 @reutrn S_Matrix4x4<T> 逆行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::GetInvert() const
{
    S_Matrix4x4 temp(*this);
    temp.Invert();
    
    return temp;
}


/* 

 @brief  移動量( 平行移動成分 )を取得する
 @param  なし
 @reutrn S_Vector3<T> 移動量

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetTranslationComponent() const
{
    return S_Vector3<T>(this->m_a_41, this->m_a_42, this->m_a_43);
}


/* 

 @brief  拡縮率( 拡縮成分 )を取得する
 @param  なし
 @reutrn S_Vector3<T> 拡縮率量

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetScalingComponent() const
{
    S_Vector3<T> scaling_component;

    scaling_component.m_x = S_Vector3<T>(this->m_a_11, this->m_a_12, this->m_a_13).GetMagnitude();
    scaling_component.m_y = S_Vector3<T>(this->m_a_21, this->m_a_22, this->m_a_23).GetMagnitude();
    scaling_component.m_z = S_Vector3<T>(this->m_a_31, this->m_a_32, this->m_a_33).GetMagnitude();

    return scaling_component;
}


/* 

 @brief  ローカル座標のX軸を取得する
 @param  なし
 @reutrn S_Vector3<T> ローカル座標のX軸

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisX() const
{
    return S_Vector3<T>(this->m_a_11, this->m_a_12, this->m_a_13).GetNormalize();
}


/* 

 @brief  ローカル座標のY軸を取得する
 @param  なし
 @reutrn S_Vector3<T> ローカル座標のY軸

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisY() const
{
    return S_Vector3<T>(this->m_a_21, this->m_a_22, this->m_a_23).GetNormalize();
}


/* 

 @brief  ローカル座標のZ軸を取得する
 @param  なし
 @reutrn S_Vector3<T> ローカル座標のZ軸

*/
template<class T>
S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisZ() const
{
    return S_Vector3<T>(this->m_a_31, this->m_a_32, this->m_a_33).GetNormalize();
}
    
    
/* 

 @brief     行を取得する
 @param[in] index 添え字
 @reutrn    S_Vector3<T> 行

*/
template<class T>
S_Vector4<T> S_Matrix4x4<T>::GetRow(Int32 index) const
{
    assert(index >= 0 && index < 4);
    return S_Vector4<T>(this->m_elements[index], this->m_elements[index + 4], this->m_elements[index + 8], this->m_elements[index + 12]);
}
    
    
    
/* 

 @brief     列を取得する
 @param[in] index 添え字
 @reutrn    S_Vector3<T> 列

*/
template<class T>
S_Vector4<T> S_Matrix4x4<T>::GetColumn(Int32 index) const
{
    assert(index >= 0 && index < 4);
    index *= 4;
    return S_Vector4<T>(this->m_elements[index], this->m_elements[index + 1], this->m_elements[index + 2], this->m_elements[index + 3]);
}
    
    
/* 

 @brief  行列を文字列に変換して取得する
 @param  なし
 @reutrn String 列

*/
template<class T>
String S_Matrix4x4<T>::ToString() const
{
    char buffer[1024];
    
    GALib_Sprintf(buffer, "| A11 : %10f, A21 : %10f, A31 : %10f, A41 : %10f |\n"
                          "| A12 : %10f, A22 : %10f, A32 : %10f, A42 : %10f |\n"
                          "| A13 : %10f, A23 : %10f, A33 : %10f, A43 : %10f |\n"
                          "| A14 : %10f, A24 : %10f, A34 : %10f, A44 : %10f |",
                          this->m_a_11, this->m_a_21, this->m_a_31, this->m_a_41,
                          this->m_a_12, this->m_a_22, this->m_a_32, this->m_a_42,
                          this->m_a_13, this->m_a_23, this->m_a_33, this->m_a_43,
                          this->m_a_14, this->m_a_24, this->m_a_34, this->m_a_44);

    return buffer;
}
    
    
/* 

 @brief     行を設定する
 @param[in] r_ROW 行
 @param[in] index 添え字
 @reutrn    なし

*/
template<class T>
void S_Matrix4x4<T>::SetRow(const S_Vector4<T>& r_ROW, Int32 index)
{
    assert(index >= 0 && index < 4);
    for (Int32 i = 0; i < 4; ++i) this->m_elements[index + i * 4] = r_ROW.m_elements[i];
}
    
    
/* 

 @brief     列を設定する
 @param[in] r_ROW 列
 @param[in] index 添え字
 @reutrn    なし

*/
template<class T>
void S_Matrix4x4<T>::SetColumn(const S_Vector4<T>& r_COLUMN, Int32 index)
{
    assert(index >= 0 && index < 4);
    for (Int32 i = 0; i < 4; ++i) this->m_elements[index + i] = r_COLUMN.m_elements[i];
}
    
    
/* 

 @brief     X軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @reutrn    S_Matrix4x4<T> 回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationX(T angle)
{
    S_Matrix4x4 rotation_matrix;
    
    T sine = Sine(angle);
    T cosine = Cosine(angle);
    
    rotation_matrix.m_a_22 = cosine;
    rotation_matrix.m_a_23 = sine;
    rotation_matrix.m_a_32 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_33 = cosine;
    
    return rotation_matrix;
}
    
    
/* 

 @brief     Y軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @reutrn    S_Matrix4x4<T> 回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationY(T angle)
{
    S_Matrix4x4 rotation_matrix;
    
    T sine = Sine(angle);
    T cosine = Cosine(angle);
    
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_13 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_31 = sine;
    rotation_matrix.m_a_33 = cosine;
    
    return rotation_matrix;
}
    
    
/* 

 @brief     Z軸から回転行列を作成する
 @param[in] angle 角度( ラジアン値 )
 @reutrn    S_Matrix4x4<T> 回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationZ(T angle)
{
    S_Matrix4x4 rotation_matrix;
    
    T sine = Sine(angle);
    T cosine = Cosine(angle);
    
    rotation_matrix.m_a_11 = cosine;
    rotation_matrix.m_a_12 = sine;
    rotation_matrix.m_a_21 = sine * static_cast<T>(-1);
    rotation_matrix.m_a_22 = cosine;
    
    return rotation_matrix;
}
    
    
/* 

 @brief     任意軸から回転行列を作成する
 @param[in] r_AXIS 軸
 @param[in] angle  角度( ラジアン値 )
 @reutrn    S_Matrix4x4<T> 回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // 回転行列
    S_Matrix4x4 rotation_matrix;
    
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

 @brief     3軸の回転行列を掛け合わせた行列を作成する
 @param[in] pitch ピッチ( X軸の角度・ラジアン値 )
 @param[in] yaw   ヨー( Y軸の角度・ラジアン値 )
 @param[in] roll  ロール( Z軸の角度・ラジアン値 
 @reutrn    S_Matrix4x4<T> 回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationYawPitchRoll(T pitch,
                                                            T yaw,
                                                            T roll)
{
    S_Quaternion<T> rotation_quaternion = S_Quaternion<T>::s_CreateRotationPitchYawRoll(pitch, yaw, roll);
    return s_ConvertQuaternionToMatrix4x4(rotation_quaternion);
}
    
    
/* 

 @brief     3軸の回転行列を掛け合わせた行列を作成する
 @param[in] r_ROTATION 3方向の回転量
 @reutrn    S_Matrix4x4<T> 回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationYawPitchRoll(const S_Vector3<T>& r_ROTATION)
{
    S_Quaternion<T> rotationQuaternion = S_Quaternion<T>::s_CreateRotationPitchYawRoll(r_ROTATION);
    return s_ConvertQuaternionToMatrix4x4(rotationQuaternion);
}
    
    
/* 

 @brief     拡縮行列を作成する
 @param[in] scaling_rate_x X方向の拡縮率
 @param[in] scaling_rate_y Y方向の拡縮率
 @param[in] scaling_rate_z Z方向の拡縮率
 @reutrn    S_Matrix4x4<T> 拡縮行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateScaling(T scaling_rate_x, T scaling_rate_y, T scaling_rate_z)
{
    S_Matrix4x4 scaling_matrix;
    
    scaling_matrix.m_a_11 = scaling_rate_x;
    scaling_matrix.m_a_22 = scaling_rate_y;
    scaling_matrix.m_a_33 = scaling_rate_z;
    
    return scaling_matrix;
}
    
    
/* 

 @brief     拡縮行列を作成する
 @param[in] r_SCALING_RATE 3方向の拡縮率
 @reutrn    S_Matrix4x4<T> 拡縮行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateScaling(const S_Vector3<T>& r_SCALING_RATE)
{
    return s_CreateScaling(r_SCALING_RATE.m_x, r_SCALING_RATE.m_y, r_SCALING_RATE.m_z);
}
    
    
/* 

 @brief     平行移動行列を作成する
 @param[in] movement_x X方向の移動量
 @param[in] movement_y Y方向の移動量
 @param[in] movement_z Z方向の移動量
 @reutrn    S_Matrix4x4<T> 平行移動行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTranslation(T movement_x, T movement_y, T movement_z)
{
    S_Matrix4x4 translation_matrix;
    
    translation_matrix.m_a_41 = movement_x;
    translation_matrix.m_a_42 = movement_y;
    translation_matrix.m_a_43 = movement_z;
    
    return translation_matrix;
}
    
    
/* 

 @brief     平行移動行列を作成する
 @param[in] r_MOVEMENT 3方向の移動量
 @reutrn    S_Matrix4x4<T> 平行移動行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTranslation(const S_Vector3<T>& r_MOVEMENT)
{
    return s_CreateTranslation(r_MOVEMENT.m_x, r_MOVEMENT.m_y, r_MOVEMENT.m_z);
}
    
    
/* 

 @brief     拡縮・回転・平行移動を掛け合わせた行列を作成
 @param[in] r_MOVEMENT     3方向の移動量
 @param[in] r_ROTATION     3方向の回転量
 @param[in] r_SCALING_RATE 3方向の拡縮率
 @reutrn    S_Matrix4x4<T> アフィン変換行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTRS(const S_Vector3<T>& r_MOVEMENT, 
                                           const S_Vector3<T>& r_ROTATION, 
                                           const S_Vector3<T>& r_SCALING_RATE)
{
    S_Matrix4x4 trs_matrix = s_CreateRotationYawPitchRoll(r_ROTATION);

    trs_matrix.m_a_11 *= r_SCALING_RATE.m_x;
    trs_matrix.m_a_12 *= r_SCALING_RATE.m_x;
    trs_matrix.m_a_13 *= r_SCALING_RATE.m_x;

    trs_matrix.m_a_21 *= r_SCALING_RATE.m_y;
    trs_matrix.m_a_22 *= r_SCALING_RATE.m_y;
    trs_matrix.m_a_23 *= r_SCALING_RATE.m_y;

    trs_matrix.m_a_31 *= r_SCALING_RATE.m_z;
    trs_matrix.m_a_32 *= r_SCALING_RATE.m_z;
    trs_matrix.m_a_33 *= r_SCALING_RATE.m_z;
    
    trs_matrix.m_a_41 = r_MOVEMENT.m_x;
    trs_matrix.m_a_42 = r_MOVEMENT.m_y;
    trs_matrix.m_a_43 = r_MOVEMENT.m_z;
    
    return trs_matrix;
}
    
    
/* 

 @brief     ビュー行列を作成する
 @param[in] r_EYE_POINT    視点
 @param[in] r_TARGET_POINT 注視点
 @param[in] r_UP_VECTOR    上方向を示すベクトル
 @reutrn    S_Matrix4x4<T> ビュー行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateLookAt(const S_Vector3<T>& r_EYE_POINT,
                                              const S_Vector3<T>& r_TARGET_POINT,
                                              const S_Vector3<T>& r_UP_VECTOR)
{
    // ビュー行列
    S_Matrix4x4 view_matrix;
    
    // Z軸を求める
    S_Vector3<T> z_axis = r_TARGET_POINT - r_EYE_POINT;
    z_axis.Normalize();
    
    // X軸を求める
    S_Vector3<T> x_axis = S_Vector3<T>::s_CrossProduct(z_axis, r_UP_VECTOR);
    x_axis.Normalize();
    
    // Y軸を求める
    S_Vector3<T> y_axis = S_Vector3<T>::s_CrossProduct(x_axis, z_axis);
    y_axis.Normalize();
    
    // 視点を反転したベクトル
    S_Vector3<T> inversion_eye_vector(r_EYE_POINT.GetInvert());
    
    // Z軸を反転する
    z_axis.Invert();
    
    // ビュー行列を求める
    view_matrix.m_a_11 = x_axis.m_x;
    view_matrix.m_a_21 = x_axis.m_y;
    view_matrix.m_a_31 = x_axis.m_z;
    view_matrix.m_a_41 = S_Vector3<T>::s_DotProduct(x_axis, inversion_eye_vector);
    
    view_matrix.m_a_12 = y_axis.m_x;
    view_matrix.m_a_22 = y_axis.m_y;
    view_matrix.m_a_32 = y_axis.m_z;
    view_matrix.m_a_42 = S_Vector3<T>::s_DotProduct(y_axis, inversion_eye_vector);
      
    view_matrix.m_a_13 = z_axis.m_x;
    view_matrix.m_a_23 = z_axis.m_y;
    view_matrix.m_a_33 = z_axis.m_z;
    view_matrix.m_a_43 = S_Vector3<T>::s_DotProduct(z_axis, inversion_eye_vector);
    
    return view_matrix;
}
    
    
/* 

 @brief     透視投影の射影行列を作成する
 @param[in] field_of_view_y     視野の垂直方向の画角( ラジアン値 )
 @param[in] aspect_ratio        アスペクト比
 @param[in] near_clipping_plane 視点から最も近いクリップ面( 距離 )
 @param[in] far_clipping_plane  視点から最も遠いクリップ面( 距離 )
 @reutrn    S_Matrix4x4<T> 透視投影の射影行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreatePerspectiveProjection(T field_of_view_y,
                                                             T aspect_ratio,
                                                             T near_clipping_plane,
                                                             T far_clipping_plane)
{
    assert(field_of_view_y != 0);
    assert(aspect_ratio > 0);
    assert(far_clipping_plane != near_clipping_plane);
    
    // 透視投影の射影行列
    S_Matrix4x4 perspective_projection_matrix;
    
    // 視野の垂直方向の画角の半分を求める
    T half_field_of_view_y = field_of_view_y * static_cast<T>(0.5);
    
    // ファークリッピングプレーンとニアクリッピングプレーンの差分を求める
    T plane_difference = near_clipping_plane - far_clipping_plane;
    
    // 視野の垂直方向の画角の半分の余弦を求める
    T cot_half_fov_y = Cotangent(half_field_of_view_y);
    
    // 透視投影の射影行列を求める
    perspective_projection_matrix.m_a_11 = cot_half_fov_y / aspect_ratio;
    perspective_projection_matrix.m_a_22 = cot_half_fov_y;
    perspective_projection_matrix.m_a_33 = (far_clipping_plane + near_clipping_plane) / plane_difference;
    perspective_projection_matrix.m_a_34 = static_cast<T>(-1);
    perspective_projection_matrix.m_a_43 = static_cast<T>(2) * near_clipping_plane * far_clipping_plane / plane_difference;
    
    return perspective_projection_matrix;
}
    
    
/* 

 @brief     正投影の射影行列を作成する
 @param[in] clip_space_left     クリップ空間の左側
 @param[in] clip_space_right    クリップ空間の右側
 @param[in] clip_space_bottom   クリップ空間の下側
 @param[in] clip_space_top      クリップ空間の上側
 @param[in] near_clipping_plane 視点から最も近いクリップ面( 距離 )
 @param[in] far_clipping_plane  視点から最も遠いクリップ面( 距離 )
 @reutrn    S_Matrix4x4<T> 正投影の射影行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateOrthographicProjection(T clip_space_left,             
                                                              T clip_space_right,
                                                              T clip_space_bottom,
                                                              T clip_space_top,
                                                              T near_clipping_plane,
                                                              T far_clipping_plane)
{                                                                            
    assert(clip_space_right != clip_space_left);
    assert(clip_space_top != clip_space_bottom);
    assert(near_clipping_plane != far_clipping_plane);
    
    // 正投影の射影行列
    S_Matrix4x4 orthographic_projection_matrix;
    
    // クリップ空間の幅と高さと奥行を求める
    T clip_space_width = clip_space_right - clip_space_left;
    T clip_space_height = clip_space_top - clip_space_bottom;
    T clip_space_depth = far_clipping_plane - near_clipping_plane;
    
    // 正投影の射影行列を求める
    orthographic_projection_matrix.m_a_11 = static_cast<T>(2) / clip_space_width;
    orthographic_projection_matrix.m_a_22 = static_cast<T>(2) / clip_space_height;
    orthographic_projection_matrix.m_a_33 = T(-2) / clip_space_depth;
    
    orthographic_projection_matrix.m_a_41 = -((clip_space_right + clip_space_left) / clip_space_width);
    orthographic_projection_matrix.m_a_42 = -((clip_space_top + clip_space_bottom) / clip_space_height);
    orthographic_projection_matrix.m_a_43 = -((far_clipping_plane + near_clipping_plane) / clip_space_depth);
    
    return orthographic_projection_matrix;
}
    
    
/* 

 @brief     3 * 3行列を4 * 4の行列に変換し、取得する
 @param[in] r_MATRIX 3 * 3行列
 @reutrn    S_Matrix4x4<T> 4 * 4行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& r_MATRIX)
{
    S_Matrix4x4 convertion_matrix;
    
    convertion_matrix.m_a_11 = r_MATRIX.m_a_11;
    convertion_matrix.m_a_12 = r_MATRIX.m_a_12;
    convertion_matrix.m_a_13 = r_MATRIX.m_a_13;
    
    convertion_matrix.m_a_21 = r_MATRIX.m_a_21;
    convertion_matrix.m_a_22 = r_MATRIX.m_a_22;
    convertion_matrix.m_a_23 = r_MATRIX.m_a_23;
    
    convertion_matrix.m_a_31 = r_MATRIX.m_a_31;
    convertion_matrix.m_a_32 = r_MATRIX.m_a_32;
    convertion_matrix.m_a_33 = r_MATRIX.m_a_33;

    return convertion_matrix;
}
    
    
/* 

 @brief     クォータニオンを4 * 4の行列に変換し、取得する
 @param[in] r_MATRIX クォータニオン
 @reutrn    S_Matrix4x4<T> 4 * 4行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& r_QUATERNION)
{
    // 変換後の行列
    S_Matrix4x4 convertion_matrix;
    
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
    
    // クォータニオンを4 * 4の行列へ変換
    convertion_matrix.m_a_11 = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
    convertion_matrix.m_a_12 = static_cast<T>(2) * (xy + zt);
    convertion_matrix.m_a_13 = static_cast<T>(2) * (xz - yt);
    
    convertion_matrix.m_a_21 = static_cast<T>(2) * (xy - zt);
    convertion_matrix.m_a_22 = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
    convertion_matrix.m_a_23 = static_cast<T>(2) * (yz + xt);
    
    convertion_matrix.m_a_31 = static_cast<T>(2) * (xz + yt);
    convertion_matrix.m_a_32 = static_cast<T>(2) * (yz - xt);
    convertion_matrix.m_a_33 = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);
    
    return convertion_matrix;
}
    
    
/* 

 @brief     ビューポート行列を作成する
 @param[in] window_width  ウィンドウの幅
 @param[in] window_height ウィンドウの高さ
 @reutrn    S_Matrix4x4<T> ビューポート行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateViewport(T window_width, T window_height)
{
    // ウィンドウの幅と高さの半分
    T half_width = window_width * static_cast<T>(0.5);
    T half_height = window_height * static_cast<T>(0.5);
    
    // ビューポート行列
    S_Matrix4x4 viewport_matrix(half_width,           0,                 0,                0,
                                         0, half_height,                 0,                0,
                                         0,           0, static_cast<T>(1),                0,
                                half_width, half_height,                 0, static_cast<T>(1));
    
    return viewport_matrix;
}
    
    
/* 

 @brief     回転行列を球面線形補間する
 @param[in] r_START 開始時の回転行列
 @param[in] r_END   終了時の回転行列
 @param[in] factor  補間係数
 @reutrn    S_Matrix4x4<T> 球面線形補間した回転行列

*/
template<class T>
S_Matrix4x4<T> S_Matrix4x4<T>::s_SlerpRotation(const S_Matrix4x4& r_START,
                                               const S_Matrix4x4& r_END,
                                               T factor)
{
    // 回転行列からクォータニオンを作成
    S_Quaternion<T> start_quaternion = S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(r_START);
    S_Quaternion<T> end_quaternion = S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(r_END);
    
    // クォータニオンを球面線形補間する
    S_Quaternion<T> slerp_quaternion = S_Quaternion<T>::s_Slerp(start_quaternion, end_quaternion, factor);
    
    // クォータニオンを行列へ変換
    S_Matrix4x4 slerp_matrix = s_ConvertQuaternionToMatrix4x4(slerp_quaternion);
    
    return slerp_matrix;
}
    
    
#pragma region S_Matrix4x4型との演算子のオーバーロード
    
    
/* 

 @brief     加算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    const S_Matrix4x4<T> 加算した行列

*/
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::operator+(const S_Matrix4x4<T>& r_ANOTHER) const
{
    S_Matrix4x4 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] + r_ANOTHER.m_elements[i];
    
    return temp;
}
    
    
/* 

 @brief     減算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    const S_Matrix4x4<T> 減算した行列

*/
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::operator-(const S_Matrix4x4<T>& r_ANOTHER) const
{
    S_Matrix4x4 temp;
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) temp.m_elements[i] = this->m_elements[i] - r_ANOTHER.m_elements[i];
    
    return temp;
}
    
    
/* 

 @brief     乗算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    const S_Matrix4x4<T> 乗算した行列

*/
template<class T>
const S_Matrix4x4<T> S_Matrix4x4<T>::operator*(const S_Matrix4x4<T>& r_ANOTHER) const
{
    S_Matrix4x4 temp;
    
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // 各行列の添え字を求める
        Uint32 index = i % 4;
        Uint32 another_index = (i / 4) * 4;
    
        // 行列同士の乗算
        temp.m_elements[i] =  this->m_elements[index]      * r_ANOTHER.m_elements[another_index]
                            + this->m_elements[index + 4]  * r_ANOTHER.m_elements[another_index + 1]
                            + this->m_elements[index + 8]  * r_ANOTHER.m_elements[another_index + 2]
                            + this->m_elements[index + 12] * r_ANOTHER.m_elements[another_index + 3];
    }
    
    return temp;
}
    
    
/* 

 @brief     加算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    const S_Matrix4x4<T> 加算した行列

*/
template<class T>
const S_Matrix4x4<T>& S_Matrix4x4<T>::operator+=(const S_Matrix4x4<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] += r_ANOTHER.m_elements[i];
    return (*this);
}
    
    
/* 

 @brief     減算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    const S_Matrix4x4<T> 減算した行列

*/
template<class T>
const S_Matrix4x4<T>& S_Matrix4x4<T>::operator-=(const S_Matrix4x4<T>& r_ANOTHER)
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i) this->m_elements[i] -= r_ANOTHER.m_elements[i];
    return (*this);
}
    
    
/* 

 @brief     乗算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    const S_Matrix4x4<T> 乗算した行列

*/
template<class T>
const S_Matrix4x4<T>& S_Matrix4x4<T>::operator*=(const S_Matrix4x4<T>& r_ANOTHER)
{
    S_Matrix4x4 temp;
    
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        // 各行列の添え字を求める
        Uint32 index = i % 4;
        Uint32 another_index = (i / 4) * 4;
    
        // 行列同士の乗算
        temp.m_elements[i] =  this->m_elements[index]      * r_ANOTHER.m_elements[another_index]
                            + this->m_elements[index +  4] * r_ANOTHER.m_elements[another_index + 1]
                            + this->m_elements[index +  8] * r_ANOTHER.m_elements[another_index + 2]
                            + this->m_elements[index + 12] * r_ANOTHER.m_elements[another_index + 3];
    }
    
    // 仮の行列を代入
    (*this) = temp;
    
    return (*this);
}
    
    
/* 

 @brief     等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つの行列
 @reutrn    bool  比較した結果
 @retval    true  同じ行列の場合
 @retval    false 違う行列の場合

*/
template<class T>
bool S_Matrix4x4<T>::operator==(const S_Matrix4x4<T>& r_ANOTHER) const
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
 @reutrn    bool  比較した結果
 @retval    true  違う行列の場合
 @retval    false 同じ行列の場合

*/
template<class T>
bool S_Matrix4x4<T>::operator!=(const S_Matrix4x4<T>& r_ANOTHER) const
{
    for (Uint32 i = 0; i < m_s_ELEMENT_COUNT; ++i)
    {
        if (Absolute(this->m_elements[i] - r_ANOTHER.m_elements[i]) > GetEpsilon<T>()) return true;
    }
    
    return false;
}
    
    
    
#pragma endregion
    
    
#pragma region S_Vector4演算子とのオーバーロード
    
    
/* 

 @brief     乗算演算子のオーバーロード
 @param[in] r_VECTOR 4Dベクトル
 @reutrn    const S_Vector4<T> 乗算したベクトル

*/
template<class T>
const S_Vector4<T> S_Matrix4x4<T>::operator*(const S_Vector4<T>& r_VECTOR) const
{
    S_Vector4<T> temp_vector;
        
    temp_vector.m_x = this->m_a_11 * r_VECTOR.m_x
                    + this->m_a_21 * r_VECTOR.m_y
                    + this->m_a_31 * r_VECTOR.m_z
                    + this->m_a_41 * r_VECTOR.m_w;
    
    temp_vector.m_y = this->m_a_12 * r_VECTOR.m_x
                    + this->m_a_22 * r_VECTOR.m_y
                    + this->m_a_32 * r_VECTOR.m_z
                    + this->m_a_42 * r_VECTOR.m_w;
    
    temp_vector.m_z = this->m_a_13 * r_VECTOR.m_x
                    + this->m_a_23 * r_VECTOR.m_y
                    + this->m_a_33 * r_VECTOR.m_z
                    + this->m_a_43 * r_VECTOR.m_w;
    
    temp_vector.m_w = this->m_a_14 * r_VECTOR.m_x
                    + this->m_a_24 * r_VECTOR.m_y
                    + this->m_a_34 * r_VECTOR.m_z
                    + this->m_a_44 * r_VECTOR.m_w;
    
    return temp_vector;
}
    
    
#pragma endregion
    
    
#pragma region キャスト
    
    
/* 

 @brief  S_Matrix3x3<T>型へのキャスト
 @param  なし
 @reutrn S_Matrix3x3<T> 3 * 3行列

*/
template<class T>
S_Matrix4x4<T>::operator S_Matrix3x3<T>() const
{
    return S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(*this);
}
    
    
/* 

 @brief  String型へのキャスト
 @param  なし
 @reutrn String 文字列に変換した行列

*/
template<class T>
S_Matrix4x4<T>::operator String() const
{
    return this->ToString();
}
    
    
#pragma endregion 


/* 

 @brief     行列式を取得する
 @param[in] r_MATRIX 4 * 4行列
 @reutrn    T 行列式

*/    
template<class T>
static T s_GetDeterminant(const S_Matrix4x4<T>& r_MATRIX)
{
    return (r_MATRIX.m_a_11 * r_MATRIX.m_a_22 * r_MATRIX.m_a_33 * r_MATRIX.m_a_44) 
         + (r_MATRIX.m_a_11 * r_MATRIX.m_a_23 * r_MATRIX.m_a_34 * r_MATRIX.m_a_42)
         + (r_MATRIX.m_a_11 * r_MATRIX.m_a_24 * r_MATRIX.m_a_32 * r_MATRIX.m_a_43)
       
         + (r_MATRIX.m_a_12 * r_MATRIX.m_a_21 * r_MATRIX.m_a_34 * r_MATRIX.m_a_43)
         + (r_MATRIX.m_a_12 * r_MATRIX.m_a_23 * r_MATRIX.m_a_31 * r_MATRIX.m_a_44)
         + (r_MATRIX.m_a_12 * r_MATRIX.m_a_24 * r_MATRIX.m_a_33 * r_MATRIX.m_a_41)
       
         + (r_MATRIX.m_a_13 * r_MATRIX.m_a_21 * r_MATRIX.m_a_32 * r_MATRIX.m_a_44)
         + (r_MATRIX.m_a_13 * r_MATRIX.m_a_22 * r_MATRIX.m_a_34 * r_MATRIX.m_a_41)
         + (r_MATRIX.m_a_13 * r_MATRIX.m_a_24 * r_MATRIX.m_a_31 * r_MATRIX.m_a_42)
          
         + (r_MATRIX.m_a_14 * r_MATRIX.m_a_21 * r_MATRIX.m_a_33 * r_MATRIX.m_a_42)
         + (r_MATRIX.m_a_14 * r_MATRIX.m_a_22 * r_MATRIX.m_a_31 * r_MATRIX.m_a_43)
         + (r_MATRIX.m_a_14 * r_MATRIX.m_a_23 * r_MATRIX.m_a_32 * r_MATRIX.m_a_41)
       
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_22 * r_MATRIX.m_a_34 * r_MATRIX.m_a_43)
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_23 * r_MATRIX.m_a_32 * r_MATRIX.m_a_44)
         - (r_MATRIX.m_a_11 * r_MATRIX.m_a_24 * r_MATRIX.m_a_33 * r_MATRIX.m_a_42)
       
         - (r_MATRIX.m_a_12 * r_MATRIX.m_a_21 * r_MATRIX.m_a_33 * r_MATRIX.m_a_44)
         - (r_MATRIX.m_a_12 * r_MATRIX.m_a_23 * r_MATRIX.m_a_34 * r_MATRIX.m_a_41)
         - (r_MATRIX.m_a_12 * r_MATRIX.m_a_24 * r_MATRIX.m_a_31 * r_MATRIX.m_a_43)
       
         - (r_MATRIX.m_a_13 * r_MATRIX.m_a_21 * r_MATRIX.m_a_34 * r_MATRIX.m_a_42)
         - (r_MATRIX.m_a_13 * r_MATRIX.m_a_22 * r_MATRIX.m_a_31 * r_MATRIX.m_a_44)
         - (r_MATRIX.m_a_13 * r_MATRIX.m_a_24 * r_MATRIX.m_a_32 * r_MATRIX.m_a_41)
       
         - (r_MATRIX.m_a_14 * r_MATRIX.m_a_21 * r_MATRIX.m_a_32 * r_MATRIX.m_a_43)
         - (r_MATRIX.m_a_14 * r_MATRIX.m_a_22 * r_MATRIX.m_a_33 * r_MATRIX.m_a_41)
         - (r_MATRIX.m_a_14 * r_MATRIX.m_a_23 * r_MATRIX.m_a_31 * r_MATRIX.m_a_42);
}


/* 

 @brief     値の交換を行う
 @param[in] p_a 値のポインタ
 @param[in] p_b もう一つの値のポインタ
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
template struct S_Matrix4x4<float>;
template struct S_Matrix4x4<double>;