/* ヘッダファイル */
#include "Quaternion.h"
#include "..\Matrix\Matrix3x3.h"
#include "..\Matrix\Matrix4x4.h"


// 名前空間を省略
using namespace GALib::Math;


/* プロトタイプ宣言 */
template<class T>
static S_Quaternion<T> m_s_LerpQuaternion(const S_Quaternion<T>& r_START_QUATERNION,
                                          const S_Quaternion<T>& r_END_QUATERNION,
                                          T factor);


#pragma region 静的メンバ変数の初期化


template<class T>
const S_Quaternion<T> S_Quaternion<T>::m_s_IDENTITY(static_cast<T>(1), 0, 0, 0);


#pragma endregion


/* 

 @brief コンストラクタ
 @param なし

*/
template<class T>
S_Quaternion<T>::S_Quaternion() : 
    
    m_t(0),
    m_x(0),
    m_y(0),
    m_z(0)

{
}


/* 

 @brief     コンストラクタ( 値で全要素を初期化 )
 @param[in] value 値

*/
template<class T>
S_Quaternion<T>::S_Quaternion(T value) :

    m_t(value),
    m_x(value),
    m_y(value),
    m_z(value)

{
}


/* 

 @brief     コンストラクタ( 各要素で初期化 )
 @param[in] t T成分
 @param[in] x X成分
 @param[in] y Y成分
 @param[in] z Z成分

*/
template<class T>
S_Quaternion<T>::S_Quaternion(T t, T x, T y, T z) :

    m_t(t),
    m_x(x),
    m_y(y),
    m_z(z)

{
}


/* 

 @brief     コンストラクタ( T成分と3Dベクトルで初期化 )
 @param[in] t     T成分
 @param[in] r_XYZ X・Y・Z成分

*/
template<class T>
S_Quaternion<T>::S_Quaternion(T t, const S_Vector3<T>& r_XYZ) :

    m_t(t),
    m_x(r_XYZ.m_x),
    m_y(r_XYZ.m_y),
    m_z(r_XYZ.m_z)

{
}


/* 

 @brief デストラクタ
 @param なし

*/
template<class T>
S_Quaternion<T>::~S_Quaternion()
{
}


/* 

 @brief     各成分を特定の値に変更する
 @param[in] value 値
 @return    なし

*/
template<class T>
void S_Quaternion<T>::Fill(T value)
{
    this->m_t = value;
    this->m_x = value;
    this->m_y = value;
    this->m_z = value;
}


/* 

 @brief  単位クォータニオン化する
 @param  なし
 @return なし

*/
template<class T>
void S_Quaternion<T>::Identity()
{
    this->m_t = static_cast<T>(1);
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
}


/* 

 @brief  正規化を行う
 @param  なし
 @return なし

*/
template<class T>
void S_Quaternion<T>::Normalize()
{
    // 大きさを取得
    T magnitude = GetMagnitude();
    assert(magnitude != 0);

    // 正規化
    this->m_t /= magnitude;
    this->m_x /= magnitude;
    this->m_y /= magnitude;
    this->m_z /= magnitude;
}


/* 

 @brief  逆クォータニオン化を行う
 @param  なし
 @return なし

*/
template<class T>
void S_Quaternion<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
    this->m_z *= static_cast<T>(-1);
}


/* 

 @brief  大きさを取得する
 @param  なし
 @return T 大きさ

*/
template<class T>
T S_Quaternion<T>::GetMagnitude() const
{
    return SquareRoot(GetMagnitudeSquare());
}


/* 

 @brief  大きさの2乗を取得する
 @param  なし
 @return T 大きさの2乗

*/
template<class T>
T S_Quaternion<T>::GetMagnitudeSquare() const
{
    return Square(this->m_t) + Square(this->m_x) + Square(this->m_y) + Square(this->m_z);
}


/* 

 @brief  正規化したクォータニオンを取得する
 @param  なし
 @return S_Quaternion<T> 正規化したクォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::GetNormalize() const
{
    S_Quaternion temp(*this);
    temp.Normalize();

    return temp;
}


/* 

 @brief  逆クォータニオンを取得する
 @param  なし
 @return S_Quaternion<T> 逆クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::GetInvert() const
{
    S_Quaternion temp(*this);
    temp.Invert();

    return temp;
}


/* 

 @brief  X軸からの角度を取得する
 @param  なし
 @return T 角度( ラジアン値 )

*/
template<class T>
T S_Quaternion<T>::GetAngleFromXAxis() const
{
    T angle = std::atan2(static_cast<T>(2) * (this->m_y * this->m_z + this->m_t * this->m_x),
                         Square(this->m_t) - Square(this->m_x) - Square(this->m_y) + Square(this->m_z));

    return angle;
}


/* 

 @brief  Y軸からの角度を取得する
 @param  なし
 @return T 角度( ラジアン値 )

*/
template<class T>
T S_Quaternion<T>::GetAngleFromYAxis() const
{
    T angle = std::asin(static_cast<T>(-2) * (this->m_x * this->m_z - this->m_t * this->m_y));
    return angle;
}


/* 

 @brief  Z軸からの角度を取得する
 @param  なし
 @return T 角度( ラジアン値 )

*/
template<class T>
T S_Quaternion<T>::GetAngleFromZAxis() const
{
    T angle = std::atan2(static_cast<T>(2) * (this->m_x * this->m_y + this->m_t * this->m_z),
                         Square(this->m_t) + Square(this->m_x) - Square(this->m_y) - Square(this->m_z));

    return angle;
}


/* 

 @brief     軸と角度を取得する
 @param[in] p_axis  軸
 @param[in] p_angle 角度( ラジアン値 )
 @return    なし

*/
template<class T>
void S_Quaternion<T>::GetAxisAndAngle(S_Vector3<T>* p_axis, T* p_angle) const
{
    assert(p_axis && p_angle);

    // 角度の半分とサインを求める
    T half_angle = 0, sine = 0;

    half_angle = static_cast<T>(std::acos(this->m_t));

    sine = SquareRoot(Square(this->m_x) + Square(this->m_y) + Square(this->m_z));
    T absolute_sine = Absolute(sine);

    // サインから軸と角度を設定
    if (absolute_sine < GetEpsilon<T>() || Absolute(absolute_sine - Get2Pi<T>()) < GetEpsilon<T>())
    {
        *p_angle = 0;

        p_axis->m_x = 0;
        p_axis->m_y = 0;
        p_axis->m_z = static_cast<T>(1);
    }
    else
    {
        *p_angle = half_angle * static_cast<T>(2);
        
        p_axis->m_x = this->m_x / sine;
        p_axis->m_y = this->m_y / sine;
        p_axis->m_z = this->m_z / sine;
        p_axis->Normalize();
    }
}


/* 

 @brief  ベクトルを文字列として取得する
 @param  なし
 @return String 文字列に変換したベクトル

*/
template<class T>
String S_Quaternion<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( T : %f, X : %f, Y : %f, Z : %f )", this->m_t, this->m_x, this->m_y, this->m_z);
    return buffer;
}


/* 

 @brief  内積を求める
 @param  なし
 @return T 内積

*/
template<class T>
T S_Quaternion<T>::s_DotProduct(const S_Quaternion<T>& rLhs, const S_Quaternion<T>& rRhs)
{
    return (rLhs.m_t * rRhs.m_t)
         + (rLhs.m_x * rRhs.m_x)
         + (rLhs.m_y * rRhs.m_y)
         + (rLhs.m_z * rRhs.m_z);
}


/* 

 @brief     任意軸から回転クォータニオンを作成する
 @param[in] r_AXIS 軸
 @param[in] angle  角度( ラジアン値 )
 @return    S_Quaternion<T> 回転クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateRotationAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // 角度の半分とそのサインを求める
    T half_angle = angle * static_cast<T>(0.5);
    T sine = static_cast<T>(Sine(static_cast<T>(half_angle)));

    // 回転クォータニオンを求める
    S_Quaternion rotation_quaternion(Cosine(half_angle),
                                     r_AXIS.m_x * sine,
                                     r_AXIS.m_y * sine,
                                     r_AXIS.m_z * sine);

    rotation_quaternion.Normalize();
    return rotation_quaternion;
}


/* 

 @brief     3軸の回転を反映した回転クォータニオンを作成する
 @param[in] pitch ピッチ( X軸の角度・ラジアン値 )
 @param[in] yaw   ヨー( Y軸の角度・ラジアン値 )
 @param[in] roll  ロール( Z軸の角度・ラジアン値 )
 @return    S_Quaternion<T> 回転クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(T pitch,
                                                              T yaw,
                                                              T roll)
{
    // 各角度を調節
    pitch = AdjustRadianFrom0To2pi(pitch);
    yaw = AdjustRadianFrom0To2pi(yaw);
    roll = AdjustRadianFrom0To2pi(roll);

    // 各軸のサインとコサインを求める
    T sine_x = Sine(pitch * static_cast<T>(0.5));
    T cosine_x = Cosine(pitch * static_cast<T>(0.5));

    T sine_y = Sine(yaw * static_cast<T>(0.5));
    T cosine_y = Cosine(yaw * static_cast<T>(0.5));

    T sine_z = Sine(roll * static_cast<T>(0.5));
    T cosine_z = Cosine(roll * static_cast<T>(0.5));

    // 回転クォータニオンを求める
    S_Quaternion rotation_quaternion;

    rotation_quaternion.m_t = (cosine_y * cosine_z * cosine_x) - (sine_y   * sine_z   * sine_x);
    rotation_quaternion.m_x = (sine_y   * sine_z   * cosine_x) + (cosine_y * cosine_z * sine_x);
    rotation_quaternion.m_y = (sine_y   * cosine_z * cosine_x) + (cosine_y * sine_z   * sine_x);
    rotation_quaternion.m_z = (cosine_y * sine_z   * cosine_x) - (sine_y   * cosine_z * sine_x);

    return rotation_quaternion;
}


/* 

 @brief     3軸の回転を反映した回転クォータニオンを作成する
 @param[in] r_ROTATION 回転量
 @return    S_Quaternion<T> 回転クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(const S_Vector3<T>& r_ROTATION)
{
    return s_CreateRotationPitchYawRoll(r_ROTATION.m_x, r_ROTATION.m_y, r_ROTATION.m_z);
}


/* 

 @brief     任意の向きへ向くための回転クォータニオンを作成する
 @param[in] r_DIRECTION 向き
 @param[in] r_UP_VECTOR 上方向
 @return    S_Quaternion<T> 回転クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateLookRotation(const S_Vector3<T>& r_DIRECTION,
                                                      const S_Vector3<T>& r_UP_VECTOR)
{
    // 3 * 3行列のビュー行列を作成し、クォータニオンに変換
    S_Matrix3x3<T> view_matrix;
    view_matrix = S_Matrix3x3<T>::s_CreateLookAt(S_Vector3<T>::m_s_ZERO, r_DIRECTION, r_UP_VECTOR);

    S_Quaternion rotation_quaternion = s_ConvertMatrix3x3ToQuaternion(view_matrix);
    rotation_quaternion.Normalize();

    return rotation_quaternion;
}


/* 

 @brief     向きから向きへ回転させる回転クォータニオンを作成する
 @param[in] r_FROM_DIRECTION 回転前の向き
 @param[in] r_TO_DIRECTION   上方向
 @return    S_Quaternion<T> 回転クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_CreateFromToRotation(const S_Vector3<T>& r_FROM_DIRECTION,
                                                        const S_Vector3<T>& r_TO_DIRECTION)
{
    // 角度と軸を求める
    T angle = S_Vector3<T>::s_AngleBetweenVectors(r_FROM_DIRECTION, r_TO_DIRECTION);
    S_Vector3<T> axis = S_Vector3<T>::s_CrossProduct(r_FROM_DIRECTION, r_TO_DIRECTION);

    // 回転クォータニオンを作成
    S_Quaternion rotation_quaternion = s_CreateRotationAxis(axis, angle);
    return rotation_quaternion;
}


/* 

 @brief     3 * 3の行列からクォータニオンへ変換し、取得する
 @param[in] r_MATRIX 3 * 3の行列向き
 @return    S_Quaternion<T> クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& r_MATRIX)
{
    // 変換後のクォータニオン
    S_Quaternion<T> convertion_quaternion;

    // 転置行列を取得
    S_Matrix3x3<T> transpose_matrix(r_MATRIX.GetTranspose());

    // ( 4x4行列の場合の )対角線の合計
    T diagonal_sum = transpose_matrix.m_a_11
                   + transpose_matrix.m_a_22
                   + transpose_matrix.m_a_33
                   + static_cast<T>(1);

    // 対角線のスケール
    T diagonal_scale = 0;

    // 対角線の合計が0超過の場合
    if (diagonal_sum > GetEpsilon<T>())
    {
        // 対角線のスケールを求める
        diagonal_scale = SquareRoot(diagonal_sum) * static_cast<T>(2);

        // 各成分を求める
        convertion_quaternion.m_t = static_cast<T>(0.25) * diagonal_scale;
        convertion_quaternion.m_x = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
        convertion_quaternion.m_y = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
        convertion_quaternion.m_z = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
    }
    else
    {
        // 対角線の最大値に応じて成分を求める
        if (transpose_matrix.m_a_11 > transpose_matrix.m_a_22 && transpose_matrix.m_a_11 > transpose_matrix.m_a_33)
        {
            // 対角線のスケールを求める
            diagonal_scale = SquareRoot(static_cast<T>(1) + transpose_matrix.m_a_11 - transpose_matrix.m_a_22 - transpose_matrix.m_a_33) * static_cast<T>(2);

            // 各成分を求める
            convertion_quaternion.m_t = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
            convertion_quaternion.m_x = static_cast<T>(0.25) * diagonal_scale;
            convertion_quaternion.m_y = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
            convertion_quaternion.m_z = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
        }
        else if (transpose_matrix.m_a_22 > transpose_matrix.m_a_33)
        {
            // 対角線のスケールを求める
            diagonal_scale = SquareRoot(static_cast<T>(1) + transpose_matrix.m_a_22 - transpose_matrix.m_a_11 - transpose_matrix.m_a_33) * static_cast<T>(2);

            // 各成分を求める
            convertion_quaternion.m_t = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
            convertion_quaternion.m_x = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
            convertion_quaternion.m_y = static_cast<T>(0.25) * diagonal_scale;
            convertion_quaternion.m_z = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
        }
        else
        {
            // 対角線のスケールを求める
            diagonal_scale = SquareRoot(static_cast<T>(1) + transpose_matrix.m_a_33 - transpose_matrix.m_a_11 - transpose_matrix.m_a_22) * static_cast<T>(2);

            // 各成分を求める
            convertion_quaternion.m_t = (transpose_matrix.m_a_21 - transpose_matrix.m_a_12) / diagonal_scale;
            convertion_quaternion.m_x = (transpose_matrix.m_a_13 - transpose_matrix.m_a_31) / diagonal_scale;
            convertion_quaternion.m_y = (transpose_matrix.m_a_32 - transpose_matrix.m_a_23) / diagonal_scale;
            convertion_quaternion.m_z = static_cast<T>(0.25) * diagonal_scale;
        }
    }

    return convertion_quaternion;
}


/* 

 @brief     4 * 4の行列からクォータニオンへ変換し、取得する
 @param[in] r_MATRIX 4 * 4の行列
 @return    S_Quaternion<T> クォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& r_MATRIX)
{
    return s_ConvertMatrix3x3ToQuaternion(S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(r_MATRIX));
}


/* 

 @brief     線形補間を行う
 @param[in] r_START 開始値
 @param[in] r_END   終了値
 @param[in] factor  補間係数
 @return    S_Quaternion<T> 二つのクォータニオンを線形補間したクォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_Lerp(const S_Quaternion<T>& r_START,
                                        const S_Quaternion<T>& r_END,
                                        T factor)
{
    S_Quaternion lerp_point;

    if (s_DotProduct(r_START, r_END) > 0)
    {
        lerp_point = s_LerpQuaternion(r_START, r_END, factor);
    }
    else
    {
        lerp_point = s_LerpQuaternion(r_START, r_END * T(-1), factor);
    }

    return lerp_point;
}


/* 

 @brief     球面線形補間を行う
 @param[in] r_START 開始値
 @param[in] r_END   終了値
 @param[in] factor  補間係数
 @return    S_Quaternion<T> 二つのクォータニオンを球面線形補間したクォータニオン

*/
template<class T>
S_Quaternion<T> S_Quaternion<T>::s_Slerp(const S_Quaternion<T>& r_START,
                                         const S_Quaternion<T>& r_END,
                                         T factor)
{
    // 球面線形補間後のクォータニオン
    S_Quaternion slerp_quaternion;

    // 内積
    T dot = s_DotProduct(r_START, r_END);

    // 内積のしきい値
    const T DOT_THRESHOLD = static_cast<T>(0.9995);

    if (dot > DOT_THRESHOLD)
    {
        // もう1つのクォータニオンとの差
        S_Quaternion difference(r_END - r_START);

        // 差に補間係数を掛け、それに自身を足した値を求める
        difference *= factor;
        slerp_quaternion = r_START + difference;

        // クォータニオンを正規化
        slerp_quaternion.Normalize();
    }
    else
    {
        // 内積をクランプし、角度を求める
        dot = Clamp(dot, T(-1), static_cast<T>(1));
        T angle = T(std::acos(static_cast<double>(dot)));

        // 角度に補間係数を掛ける
        T interpolation_angle = angle * factor;

        // 自身に内積をかけた値を求め、もう1つのクォータニオンとの差分を求める
        S_Quaternion dot_quaternion(r_START * dot);
        S_Quaternion difference(r_END - dot_quaternion);

        // 差分を正規化
        difference.Normalize();

        // 自身と補間係数を掛けた角度のコサインを掛けたクォータニオン
        S_Quaternion cosine_quaternion(r_START * Cosine(interpolation_angle));

        // 差分と補間係数をかけた角度のサインを掛けたクォータニオン
        S_Quaternion sine_quaternion(difference * Sine(interpolation_angle));

        // 2つのクォータニオンを合わせる
        slerp_quaternion = cosine_quaternion + sine_quaternion;
    }

    return slerp_quaternion;
}


#pragma region S_Quaternion型との演算子のオーバーロード


/* 

 @brief     加算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T> 加算したクォータニオン

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator+(const S_Quaternion<T>& r_ANOTHER) const
{
    S_Quaternion temp;

    temp.m_t = this->m_t + r_ANOTHER.m_t;
    temp.m_x = this->m_x + r_ANOTHER.m_x;
    temp.m_y = this->m_y + r_ANOTHER.m_y;
    temp.m_z = this->m_z + r_ANOTHER.m_z;

    return temp;
}


/* 

 @brief     減算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T> 減算したクォータニオン

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator-(const S_Quaternion<T>& r_ANOTHER) const
{
    S_Quaternion temp;

    temp.m_t = this->m_t - r_ANOTHER.m_t;
    temp.m_x = this->m_x - r_ANOTHER.m_x;
    temp.m_y = this->m_y - r_ANOTHER.m_y;
    temp.m_z = this->m_z - r_ANOTHER.m_z;

    return temp;
}


/* 

 @brief     乗算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T> 乗算したクォータニオン

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator*(const S_Quaternion<T>& r_ANOTHER) const
{
    S_Vector3<T> xyz(this->m_x, this->m_y, this->m_z);
    S_Vector3<T> another_xyz(r_ANOTHER.m_x, r_ANOTHER.m_y, r_ANOTHER.m_z);

    // 実部を求める
    T temp_t = (this->m_t * r_ANOTHER.m_t)
             - S_Vector3<T>::s_DotProduct(xyz, another_xyz);

    // 虚部を求める
    S_Vector3<T> temp_xyz = (this->m_t * another_xyz)
                          + (r_ANOTHER.m_t * xyz)
                          + S_Vector3<T>::s_CrossProduct(xyz, another_xyz);

    return S_Quaternion(temp_t, temp_xyz);
}


/* 

 @brief     加算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T>& 加算したクォータニオン

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator+=(const S_Quaternion<T>& r_ANOTHER)
{
    this->m_t += r_ANOTHER.m_t;
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;
    this->m_z += r_ANOTHER.m_z;

    return (*this);
}


/* 

 @brief     減算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T>& 減算したクォータニオン

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator-=(const S_Quaternion<T>& r_ANOTHER)
{
    this->m_t -= r_ANOTHER.m_t;
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;
    this->m_z -= r_ANOTHER.m_z;

    return (*this);
}


/* 

 @brief     乗算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T>& 乗算したクォータニオン

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator*=(const S_Quaternion<T>& r_ANOTHER)
{
    S_Quaternion temp;

    S_Vector3<T> xyz(this->m_x, this->m_y, this->m_z);
    S_Vector3<T> another_xyz(r_ANOTHER.m_x, r_ANOTHER.m_y, r_ANOTHER.m_z);

    // 実部を求める
    T temp_t = (this->m_t * r_ANOTHER.m_t)
             - S_Vector3<T>::s_DotProduct(xyz, another_xyz);

    // 虚部を求める
    S_Vector3<T> temp_xyz = (this->m_t * another_xyz)
                          + (r_ANOTHER.m_t * xyz)
                          + S_Vector3<T>::s_CrossProduct(xyz, another_xyz);

    this->m_t = temp_t;
    this->m_x = temp_xyz.m_x;
    this->m_y = temp_xyz.m_y;
    this->m_z = temp_xyz.m_z;

    (*this) = temp;

    return (*this);
}


/* 

 @brief     等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    bool  比較した結果
 @retval    true  同じクォータニオンの場合
 @retval    false 違うクォータニオンの場合

*/
template<class T>
bool S_Quaternion<T>::operator==(const S_Quaternion<T>& r_ANOTHER) const
{
    return Absolute(this->m_t - r_ANOTHER.m_t) < GetEpsilon<T>()
        && Absolute(this->m_x - r_ANOTHER.m_x) < GetEpsilon<T>()
        && Absolute(this->m_y - r_ANOTHER.m_y) < GetEpsilon<T>()
        && Absolute(this->m_z - r_ANOTHER.m_z) < GetEpsilon<T>();
}


/* 

 @brief     非等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    bool  比較した結果
 @retval    true  違うクォータニオンの場合
 @retval    false 同じクォータニオンの場合

*/
template<class T>
bool S_Quaternion<T>::operator!=(const S_Quaternion<T>& r_ANOTHER) const
{
    return Absolute(this->m_t - r_ANOTHER.m_t) > GetEpsilon<T>()
        || Absolute(this->m_x - r_ANOTHER.m_x) > GetEpsilon<T>()
        || Absolute(this->m_y - r_ANOTHER.m_y) > GetEpsilon<T>()
        || Absolute(this->m_z - r_ANOTHER.m_z) > GetEpsilon<T>();
}



#pragma endregion


#pragma region T型との演算子のオーバーロード


/* 

 @brief     乗算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T>  乗算したクォータニオン

*/
template<class T>
const S_Quaternion<T> S_Quaternion<T>::operator*(T value) const
{
    return S_Quaternion(this->m_t * value, this->m_x * value, this->m_y * value, this->m_z * value);
}


/* 

 @brief   乗算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのクォータニオン
 @return    const S_Quaternion<T>&  乗算したクォータニオン

*/
template<class T>
const S_Quaternion<T>& S_Quaternion<T>::operator*=(T value)
{
    this->m_t *= value;
    this->m_x *= value;
    this->m_y *= value;
    this->m_z *= value;

    return (*this);
}


#pragma endregion


#pragma region キャスト


/* 

 @brief  S_Vector3<T>型へのキャスト
 @param  なし
 @return S_Vector3<T> 3Dベクトル

*/
template<class T>
S_Quaternion<T>::operator S_Vector3<T>() const
{
    return S_Vector3<T>(this->m_x, this->m_y, this->m_z);
}


/* 

 @brief  String型へのキャスト
 @param  なし
 @return String 文字列に変換したクォータニオン

*/
template<class T>
S_Quaternion<T>::operator String() const
{
    return ToString();
}


#pragma endregion


/* 

 @brief  クォータニオンの線形補間を行う
 @param[in] r_START 開始時のクォータニオン
 @param[in] r_END   終了時のクォータニオン
 @param[in] factor  補間係数
 @return S_Quaternion<T> 線形補間したクォータニオン

*/
template<class T>
S_Quaternion<T> s_LerpQuaternion(const S_Quaternion<T>& r_START,
                                 const S_Quaternion<T>& r_END,
                                 T factor)
{
    S_Quaternion<T> lerp_point;

    lerp_point.m_t = (r_END.m_t - r_START.m_t) * factor + r_START.m_t;
    lerp_point.m_x = (r_END.m_x - r_START.m_x) * factor + r_START.m_x;
    lerp_point.m_y = (r_END.m_y - r_START.m_y) * factor + r_START.m_y;
    lerp_point.m_z = (r_END.m_z - r_START.m_z) * factor + r_START.m_z;

    return lerp_point;
}


/* 明示的インスタンス化 */
template struct S_Quaternion<float>;
template struct S_Quaternion<double>;