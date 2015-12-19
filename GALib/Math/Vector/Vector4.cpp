/* ヘッダファイル */
#include "Vector4.h"


// 名前空間を省略
using namespace GALib::Math;


#pragma region 静的メンバ変数の初期化


template<class T>
const S_Vector4<T> S_Vector4<T>::m_s_ZERO;

template<class T>
const S_Vector4<T> S_Vector4<T>::m_s_ONE(static_cast<T>(1));


#pragma endregion


/* 

 @brief コンストラクタ
 @param なし

*/
template<class T>
S_Vector4<T>::S_Vector4() : 

    m_x(0),
    m_y(0),
    m_z(0),
    m_w(0)

{
}


/* 

 @brief     コンストラクタ( 指定した1つの値で各成分を初期化 )
 @param[in] value 値

*/
template<class T>
S_Vector4<T>::S_Vector4(T value) : 

    m_x(value),
    m_y(value),
    m_z(value),
    m_w(value)

{
}


/* 

 @brief     コンストラクタ( 指定した値で各成分を初期化 )
 @param[in] x X成分
 @param[in] y Y成分
 @param[in] z Z成分
 @param[in] w W成分

*/
template<class T>
S_Vector4<T>::S_Vector4(T x, T y, T z, T w) :

    m_x(x),
    m_y(y),
    m_z(z),
    m_w(w)

{
}


/* 

 @brief     コンストラクタ( 指定した配列で各成分を初期化 )
 @param[in] ELEMENTS 要素が4つの配列

*/
template<class T>
S_Vector4<T>::S_Vector4(const T ELEMENTS[4]) :

    m_x(ELEMENTS[0]),
    m_y(ELEMENTS[1]),
    m_z(ELEMENTS[2]),
    m_w(ELEMENTS[3])

{
}


/* 

 @brief     コンストラクタ( 指定した2Dベクトルと値で各成分を初期化 )
 @param[in] r_XY X・Y成分
 @param[in] z    Z成分
 @param[in] w    W成分

*/
template<class T>
S_Vector4<T>::S_Vector4(const S_Vector2<T>& r_XY, T z, T w) :

    m_x(r_XY.m_x),
    m_y(r_XY.m_y),
    m_z(z),
    m_w(w)

{
}


/* 

 @brief     コンストラクタ( 指定した3Dベクトルと値で各成分を初期化 )
 @param[in] r_XYZ X・Y・Z成分
 @param[in] w     W成分

*/
template<class T>
S_Vector4<T>::S_Vector4(const S_Vector3<T>& r_XYZ, T w) :

    m_x(r_XYZ.m_x),
    m_y(r_XYZ.m_y),
    m_z(r_XYZ.m_z),
    m_w(w)

{
}


/* 

 @brief デストラクタ
 @param なし

*/
template<class T>
S_Vector4<T>::~S_Vector4()
{
}


/* 

 @brief  ゼロベクトル化する
 @param  なし
 @return なし

*/
template<class T>
void S_Vector4<T>::Zero()
{
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
    this->m_w = 0;
}


/* 

 @brief     各成分を特定の値に変更する
 @param[in] value 値
 @return    なし

*/
template<class T>
void S_Vector4<T>::Fill(T value)
{
    this->m_x = value;
    this->m_y = value;
    this->m_z = value;
    this->m_w = value;
}


/* 

 @brief  単位ベクトル化する
 @param  なし
 @return なし

*/
template<class T>
void S_Vector4<T>::Normalize()
{
    // 大きさを取得
    T magnitude = this->GetMagnitude();
    assert(magnitude != 0);

    // 単位ベクトル化
    this->m_x /= magnitude;
    this->m_y /= magnitude;
    this->m_z /= magnitude;
    this->m_w /= magnitude;
}


/* 

 @brief  ベクトルを反転する
 @param  なし
 @return なし

*/
template<class T>
void S_Vector4<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
    this->m_z *= static_cast<T>(-1);
    this->m_w *= static_cast<T>(-1);
}


/* 

 @brief     大きさでベクトルをクランプする
 @param[in] min 最小の大きさ
 @param[in] max 最小の大きさ
 @return    なし

*/
template<class T>
void S_Vector4<T>::ClampMagnitude(T min, T max)
{
    // 大きさを取得し、その大きさをクランプ
    T magnitude = this->GetMagnitude();
    Clamp(magnitude, min, max);

    // 単位ベクトル化して、大きさ分スケール
    this->Normalize();
    (*this) = (*this) * magnitude;
}


/* 

 @brief  大きさを取得する
 @param  なし
 @return T 大きさ

*/
template<class T>
T S_Vector4<T>::GetMagnitude() const
{
    return SquareRoot(GetMagnitudeSquare());
}


/* 

 @brief  大きさの2乗を取得する
 @param  なし
 @return T 大きさの2乗

*/
template<class T>
T S_Vector4<T>::GetMagnitudeSquare() const
{
    return Square(this->m_x) + Square(this->m_y) + Square(this->m_z) + Square(this->m_w);
}


/* 

 @brief  単位ベクトルを取得する
 @param  なし
 @return S_Vector4<T> 単位ベクトル

*/
template<class T>
S_Vector4<T> S_Vector4<T>::GetNormalize() const
{
    S_Vector4 temp(*this);
    temp.Normalize();

    return temp;
}


/* 

 @brief  反転したベクトルを取得する
 @param  なし
 @return S_Vector4<T> 反転したベクトル

*/
template<class T>
S_Vector4<T> S_Vector4<T>::GetInvert() const
{
    return S_Vector4(-this->m_x, -this->m_y, -this->m_z, -this->m_w);
}


/* 

 @brief     大きさでクランプしたベクトルを取得する
 @param[in] min 最小の大きさ
 @param[in] max 最大の大きさ
 @return    S_Vector4<T> クランプしたベクトル

*/
template<class T>
S_Vector4<T> S_Vector4<T>::GetClampMagnitude(T min, T max) const
{
    S_Vector4 temp = (*this);
    temp.ClampMagnitude(min, max);

    return temp;
}


/* 

 @brief  ベクトルを文字列として取得する
 @param  なし
 @return String 文字列に変換したベクトル

*/
template<class T>
String S_Vector4<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( X : %f, Y : %f, Z : %f, W : %f )", this->m_x, this->m_y, this->m_z, this->m_w);
    return buffer;
}


/* 

 @brief     内積を求める
 @param[in] r_VECTOR
 @param[in] r_ANOTHER_VECTOR
 @return    T 内積

*/
template<class T>
T S_Vector4<T>::s_DotProduct(const S_Vector4<T>& r_VECTOR, const S_Vector4<T>& r_ANOTHER_VECTOR)
{
    return (r_VECTOR.m_x * r_ANOTHER_VECTOR.m_x)
         + (r_VECTOR.m_y * r_ANOTHER_VECTOR.m_y)
         + (r_VECTOR.m_z * r_ANOTHER_VECTOR.m_z)
         + (r_VECTOR.m_w * r_ANOTHER_VECTOR.m_w);
}


/* 

 @brief     線形補間を行う
 @param[in] r_START_POINT 始点
 @param[in] r_END_POINT   終点
 @param[in] factor        補間係数( 0 ～ 1 )
 @return    S_Vector4<T> 二つの点を線形補間した点

*/
template<class T>
S_Vector4<T> S_Vector4<T>::s_Lerp(const S_Vector4<T>& r_START_POINT,
                                  const S_Vector4<T>& r_END_POINT,
                                  T factor)
{
    S_Vector4 lerp_point;

    lerp_point.m_x = (r_END_POINT.m_x - r_START_POINT.m_x) * factor + r_START_POINT.m_x;
    lerp_point.m_y = (r_END_POINT.m_y - r_START_POINT.m_y) * factor + r_START_POINT.m_y;
    lerp_point.m_z = (r_END_POINT.m_z - r_START_POINT.m_z) * factor + r_START_POINT.m_z;
    lerp_point.m_w = (r_END_POINT.m_w - r_START_POINT.m_w) * factor + r_START_POINT.m_w;

    return lerp_point;
}


/* 

 @brief     各成分の最小値を成分にしたベクトルを取得する
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    S_Vector4<T> 最小値を成分にしたベクトル

*/
template<class T>
S_Vector4<T> S_Vector4<T>::s_Minimize(const S_Vector4<T>& r_LHS, const S_Vector4<T>& r_RHS)
{
    S_Vector4 min_vector;

    min_vector.m_x = (r_LHS.m_x < r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    min_vector.m_y = (r_LHS.m_y < r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    min_vector.m_z = (r_LHS.m_z < r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;
    min_vector.m_w = (r_LHS.m_w < r_RHS.m_w) ? r_LHS.m_w : r_RHS.m_w;

    return min_vector;
}


/* 

 @brief     各成分の最大値を成分にしたベクトルを取得する
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    S_Vector4<T> 最大値を成分にしたベクトル

*/
template<class T>
S_Vector4<T> S_Vector4<T>::s_Maximize(const S_Vector4<T>& r_LHS, const S_Vector4<T>& r_RHS)
{
    S_Vector4 max_vector;

    max_vector.m_x = (r_LHS.m_x > r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    max_vector.m_y = (r_LHS.m_y > r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    max_vector.m_z = (r_LHS.m_z > r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;
    max_vector.m_w = (r_LHS.m_w > r_RHS.m_w) ? r_LHS.m_w : r_RHS.m_w;

    return max_vector;
}


#pragma region S_Vector4型との演算子のオーバーロード


/* 

 @brief     加算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 加算したベクトル

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator+(const S_Vector4<T>& r_ANOTHER) const
{
    return S_Vector4(this->m_x + r_ANOTHER.m_x,
                     this->m_y + r_ANOTHER.m_y,
                     this->m_z + r_ANOTHER.m_z,
                     this->m_w + r_ANOTHER.m_w);
}


/* 

 @brief     減算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 減算したベクトル

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator-(const S_Vector4<T>& r_ANOTHER) const
{
    return S_Vector4(this->m_x - r_ANOTHER.m_x,
                     this->m_y - r_ANOTHER.m_y,
                     this->m_z - r_ANOTHER.m_z,
                     this->m_w - r_ANOTHER.m_w);
}


/* 

 @brief     乗算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 乗算したベクトル

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator*(const S_Vector4<T>& r_ANOTHER) const
{
    return S_Vector4(this->m_x * r_ANOTHER.m_x,
                     this->m_y * r_ANOTHER.m_y,
                     this->m_z * r_ANOTHER.m_z,
                     this->m_w * r_ANOTHER.m_w);
}


/* 

 @brief     除算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 除算したベクトル

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator/(const S_Vector4<T>& r_ANOTHER) const
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    assert(r_ANOTHER.m_w != 0);

    return S_Vector4(this->m_x / r_ANOTHER.m_x,
                     this->m_y / r_ANOTHER.m_y,
                     this->m_z / r_ANOTHER.m_z,
                     this->m_w / r_ANOTHER.m_w);
}


/* 

 @brief     加算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 加算したベクトル

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator+=(const S_Vector4<T>& r_ANOTHER)
{
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;
    this->m_z += r_ANOTHER.m_z;
    this->m_w += r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     減算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 減算したベクトル

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator-=(const S_Vector4<T>& r_ANOTHER)
{
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;
    this->m_z -= r_ANOTHER.m_z;
    this->m_w -= r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     乗算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 乗算したベクトル

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator*=(const S_Vector4<T>& r_ANOTHER)
{
    this->m_x *= r_ANOTHER.m_x;
    this->m_y *= r_ANOTHER.m_y;
    this->m_z *= r_ANOTHER.m_z;
    this->m_w *= r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     除算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    S_Vector4<T> 除算したベクトル

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator/=(const S_Vector4<T>& r_ANOTHER)
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    assert(r_ANOTHER.m_w != 0);

    this->m_x /= r_ANOTHER.m_x;
    this->m_y /= r_ANOTHER.m_y;
    this->m_z /= r_ANOTHER.m_z;
    this->m_w /= r_ANOTHER.m_w;

    return (*this);
}


/* 

 @brief     等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    bool  比較した結果
 @retval    true  同じベクトルの場合
 @retval    false 違うベクトルの場合

*/
template<class T>
bool S_Vector4<T>::operator==(const S_Vector4<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) < GetEpsilon<T>()
        && Absolute(this->m_y - r_ANOTHER.m_y) < GetEpsilon<T>()
        && Absolute(this->m_z - r_ANOTHER.m_z) < GetEpsilon<T>()
        && Absolute(this->m_w - r_ANOTHER.m_w) < GetEpsilon<T>();
}


/* 

 @brief     非等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    bool  比較した結果
 @retval    true  違うベクトルの場合
 @retval    false 同じベクトルの場合

*/
template<class T>
bool S_Vector4<T>::operator!=(const S_Vector4<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) > GetEpsilon<T>()
        || Absolute(this->m_y - r_ANOTHER.m_y) > GetEpsilon<T>()
        || Absolute(this->m_z - r_ANOTHER.m_z) > GetEpsilon<T>()
        || Absolute(this->m_w - r_ANOTHER.m_w) > GetEpsilon<T>();
}


#pragma endregion


#pragma region T型との演算子のオーバーロード


/* 

 @brief     乗算演算子のオーバーロード
 @param[in] value 値
 @return    const S_Vector4<T> 乗算したベクトル

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator*(T value) const
{
    return S_Vector4(this->m_x * value,
                     this->m_y * value,
                     this->m_z * value,
                     this->m_w * value);
}


/* 

 @brief     除算演算子のオーバーロード
 @param[in] value 値
 @return    const S_Vector4<T> 除算したベクトル

*/
template<class T>
const S_Vector4<T> S_Vector4<T>::operator/(T value) const
{
    assert(value != 0);

    return S_Vector4(this->m_x / value,
                        this->m_y / value,
                        this->m_z / value,
                        this->m_w / value);
}


/* 

 @brief     乗算代入演算子のオーバーロード
 @param[in] value 値
 @return    const S_Vector4<T> 乗算したベクトル

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator*=(T value)
{
    this->m_x *= value;
    this->m_y *= value;
    this->m_z *= value;
    this->m_w *= value;

    return (*this);
}


/* 

 @brief     除算代入演算子のオーバーロード
 @param[in] value 値
 @return    const S_Vector4<T> 除算したベクトル

*/
template<class T>
const S_Vector4<T>& S_Vector4<T>::operator/=(T value)
{
    assert(value != 0);

    this->m_x /= value;
    this->m_y /= value;
    this->m_z /= value;
    this->m_w /= value;

    return (*this);
}


#pragma endregion


#pragma region キャスト


/* 

 @brief  S_Vector2型へのキャスト
 @param  なし
 @return S_Vector2<T> 2Dベクトル

*/
template<class T>
S_Vector4<T>::operator S_Vector2<T>() const
{
    return S_Vector2<T>(this->m_x, this->m_y);
}


/* 

 @brief  S_Vector3型へのキャスト
 @param  なし
 @return S_Vector3<T> 3Dベクトル

*/
template<class T>
S_Vector4<T>::operator S_Vector3<T>() const
{
    return S_Vector3<T>(this->m_x, this->m_y, this->m_z);
}


/* 

 @brief  String型へのキャスト
 @param  なし
 @return String 文字列

*/
template<class T>
S_Vector4<T>::operator String() const
{
    return this->ToString();
}


#pragma endregion


/* 明示的インスタンス化 */
template struct S_Vector4<float>;
template struct S_Vector4<double>;

