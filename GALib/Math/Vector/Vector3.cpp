/* ヘッダファイル */
#include "Vector3.h"
#include "../Quaternion/Quaternion.h"


// 名前空間を省略
using namespace GALib::Math;


#pragma region 静的メンバ変数の初期化
    
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_RIGHT_DIRECTION(static_cast<T>(1), 0, 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_LEFT_DIRECTION(static_cast<T>(-1), 0, 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_UP_DIRECTION(0, static_cast<T>(1), 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_DOWN_DIRECTION(0, static_cast<T>(-1), 0);
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_FRONT_DIRECTION(0, 0, static_cast<T>(-1));
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_BACK_DIRECTION(0, 0, static_cast<T>(1));
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_ZERO;
    
template<class T>
const S_Vector3<T> S_Vector3<T>::m_s_ONE(static_cast<T>(1));
    
    
#pragma endregion
    

/* 

 @brief コンストラクタ
 @param なし

*/
template<class T>
S_Vector3<T>::S_Vector3() :

    m_x(0),
    m_y(0),
    m_z(0)

{
}
    

/* 

 @brief     コンストラクタ( 指定した1つの値で各成分の初期化 )
 @param[in] value 値

*/
template<class T>
S_Vector3<T>::S_Vector3(T value) :

    m_x(value),
    m_y(value),
    m_z(value)

{
}
    

/* 

 @brief     コンストラクタ( 指定した値で各成分の初期化 )
 @param[in] x X成分
 @param[in] y Y成分
 @param[in] z Z成分

*/
template<class T>
S_Vector3<T>::S_Vector3(T x, T y, T z) : 
    
    m_x(x),
    m_y(y),
    m_z(z)
    
{
}
    
 
/* 

 @brief     コンストラクタ( 指定した配列で各成分の初期化 )
 @param[in] ELEMENTS 要素が3つの配列

*/
template<class T>
S_Vector3<T>::S_Vector3(const T ELEMENTS[3]) :

    m_x(ELEMENTS[0]),
    m_y(ELEMENTS[1]),
    m_z(ELEMENTS[2])

{
}
    
    
/* 

 @brief     コンストラクタ( 2DベクトルとZ成分で初期化初期化 )
 @param[in] r_XY X・Y成分
 @param[in] z    Z成分

*/
template<class T>
S_Vector3<T>::S_Vector3(const S_Vector2<T>& r_XY, T z) : 
    
    m_x(r_XY.m_x),
    m_y(r_XY.m_y),
    m_z(z)
    
{
}
    
    
    
/* 

 @brief デストラクタ
 @param なし

*/
template<class T>
S_Vector3<T>::~S_Vector3()
{
}
    

/* 

 @brief  ゼロベクトル化する
 @param  なし
 @return なし

*/
template<class T>
void S_Vector3<T>::Zero()
{
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
}
    

/* 

 @brief     各成分を特定の値に変更する
 @param[in] value 値
 @return    なし

*/
template<class T>
void S_Vector3<T>::Fill(T value)
{
    this->m_x = value;
    this->m_y = value;
    this->m_z = value;
}
    

/* 

 @brief  単位ベクトル化する
 @param  なし
 @return なし

*/
template<class T>
void S_Vector3<T>::Normalize()
{
    // 大きさを取得
    T magnitude = this->GetMagnitude();
    assert(magnitude != 0);
    
    // 単位ベクトル化
    this->m_x /= magnitude;
    this->m_y /= magnitude;
    this->m_z /= magnitude;
}
    

/* 

 @brief  ベクトルを反転する
 @param  なし
 @return なし

*/
template<class T>
void S_Vector3<T>::Invert()
{
    this->m_x *= static_cast<T>(-1);
    this->m_y *= static_cast<T>(-1);
    this->m_z *= static_cast<T>(-1);
}
    
    
/* 

 @brief     X軸からベクトルを回転する
 @param[in] angle 角度( ラジアン値 )
 @return    なし

*/
template<class T>
void S_Vector3<T>::RotateX(T angle)
{
    T temp_z = this->m_z;
    this->m_z = temp_z * Cosine(angle) - this->m_y * Sine(angle);
    this->m_y = temp_z * Sine(angle) + this->m_y * Cosine(angle);
}
    

/* 

 @brief     Y軸からベクトルを回転する
 @param[in] angle 角度( ラジアン値 )
 @return    なし

*/
template<class T>
void S_Vector3<T>::RotateY(T angle)
{
    T temp_x = this->m_x;
    this->m_x = temp_x * Cosine(angle) - this->m_z * Sine(angle);
    this->m_z = temp_x * Sine(angle) + this->m_z * Cosine(angle);
}
    
    
/* 

 @brief     Z軸からベクトルを回転する
 @param[in] angle 角度( ラジアン値 )
 @return    なし

*/
template<class T>
void S_Vector3<T>::RotateZ(T angle)
{
    T temp_x = this->m_x;
    this->m_x = temp_x * Cosine(angle) - this->m_y * Sine(angle);
    this->m_y = temp_x * Sine(angle) + this->m_y * Cosine(angle);
}
    
    
/* 

 @brief     任意軸からベクトルを回転する
 @param[in] r_AXIS 軸
 @param[in] angle  角度( ラジアン値 )
 @return    なし

*/
template<class T>
void S_Vector3<T>::RotateAxis(const S_Vector3<T>& r_AXIS, T angle)
{
    // 回転するベクトル
    S_Quaternion<T> rotation_vector(0, *this);
    
    // 回転クォータニオンを作成
    S_Quaternion<T> rotation_quaternion = S_Quaternion<T>::s_CreateRotationAxis(r_AXIS, angle);
    S_Quaternion<T> inverse_rotation_quaternion = S_Quaternion<T>::s_CreateRotationAxis(r_AXIS.GetInvert(), angle);
    
    // ベクトルを回転し、自身に代入
    rotation_vector =  inverse_rotation_quaternion * rotation_vector * rotation_quaternion;

    this->m_x = rotation_vector.m_x;
    this->m_y = rotation_vector.m_y;
    this->m_z = rotation_vector.m_z;
}
    
    
/* 

 @brief     大きさでベクトルをクランプする
 @param[in] min 最小の大きさ
 @param[in] max 最大の大きさ
 @return    なし

*/
template<class T>
void S_Vector3<T>::ClampMagnitude(T min, T max)
{
    // 大きさを取得し、その大きさをクランプ
    T magnitude = GetMagnitude();
    magnitude = Clamp(magnitude, min, max);
    
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
T S_Vector3<T>::GetMagnitude() const
{
    return SquareRoot(GetMagnitudeSquare());
}
    
    
/* 

 @brief  大きさの2乗を取得する
 @param  なし
 @return T 大きさの2乗

*/
template<class T>
T S_Vector3<T>::GetMagnitudeSquare() const
{
    return Square(this->m_x) + Square(this->m_y) + Square(this->m_z);
}
    
  
/* 

 @brief  単位ベクトルを取得する
 @param  なし
 @return S_Vector3<T> 単位ベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetNormalize() const
{
    S_Vector3 temp(*this);
    temp.Normalize();
    
    return temp;
}
    
   
/* 

 @brief  反転したベクトルを取得する
 @param  なし
 @return S_Vector3<T> 反転したベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetInvert() const
{
    return S_Vector3(-this->m_x, -this->m_y, -this->m_z);
}

    
/* 

 @brief     X軸から回転したベクトルを取得する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Vector3<T> 回転したベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateX(T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateX(angle);
    return temp;
}
    
    
/* 

 @brief     Y軸から回転したベクトルを取得する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Vector3<T> 回転したベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateY(T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateY(angle);
    return temp;
}
    
   
/* 

 @brief     Z軸から回転したベクトルを取得する
 @param[in] angle 角度( ラジアン値 )
 @return    S_Vector3<T> 回転したベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateZ(T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateZ(angle);
    return temp;
}
    

/* 

 @brief     任意軸から回転したベクトルを取得する
 @param[in] r_AXIS 軸
 @param[in] angle  角度( ラジアン値 )
 @return    S_Vector3<T> 回転したベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetRotateAxis(const S_Vector3<T>& r_AXIS, T angle) const
{
    S_Vector3 temp(*this);
    temp.RotateAxis(r_AXIS, angle);
    return temp;
}
    
    
/* 

 @brief     大きさでクランプしたベクトルを取得する
 @param[in] min 最小の大きさ
 @param[in] max 最大の大きさ
 @return    S_Vector3<T> クランプしたベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::GetClampMagnitude(T min, T max) const
{
    S_Vector3 temp = (*this);
    temp.ClampMagnitude(min, max);
    return temp;
}
    

/* 

 @brief  ベクトルを文字列として取得する
 @param  なし
 @return String 文字列に変換したベクトル

*/
template<class T>
String S_Vector3<T>::ToString() const
{
    char buffer[256];
    GALib_Sprintf(buffer, "( X : %f, Y : %f, Z : %f )", this->m_x, this->m_y, this->m_z);
    return buffer;
}
    
    
/* 

 @brief     内積を求める
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    T 内積

*/
template<class T>
T S_Vector3<T>::s_DotProduct(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    return (r_LHS.m_x * r_RHS.m_x) + (r_LHS.m_y * r_RHS.m_y) + (r_LHS.m_z * r_RHS.m_z);
}
    
    
/* 

 @brief     外積を求める
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    S_Vector3<T> 外積

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_CrossProduct(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 cross_vector;
    
    cross_vector.m_x = (r_LHS.m_y * r_RHS.m_z) - (r_LHS.m_z * r_RHS.m_y);
    cross_vector.m_y = (r_LHS.m_z * r_RHS.m_x) - (r_LHS.m_x * r_RHS.m_z);
    cross_vector.m_z = (r_LHS.m_x * r_RHS.m_y) - (r_LHS.m_y * r_RHS.m_x);
        
    return cross_vector;
}
    
   
/* 

 @brief     スカラー三重積を求める
 @param[in] r_A 1つ目のベクトル
 @param[in] r_B 2つ目のベクトル
 @param[in] r_C 3つ目のベクトル
 @return    T スカラー三重積

*/
template<class T>
T S_Vector3<T>::s_ScalarTripleProduct(const S_Vector3<T>& r_A,
                                      const S_Vector3<T>& r_B,
                                      const S_Vector3<T>& r_C)
{
    return s_DotProduct(r_A, s_CrossProduct(r_B, r_C));
}
    
    
/* 

 @brief     ベクトル三重積を求める
 @param[in] r_A 1つ目のベクトル
 @param[in] r_B 2つ目のベクトル
 @param[in] r_C 3つ目のベクトル
 @return    T ベクトル三重積

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_VectorTripleProduct(const S_Vector3<T>& r_A,
                                                 const S_Vector3<T>& r_B,
                                                 const S_Vector3<T>& r_C)
{
    return s_CrossProduct(r_A, s_CrossProduct(r_B, r_C));
}
    
    
/* 

 @brief     線形補間を行う
 @param[in] r_START_POINT 始点
 @param[in] r_END_POINT   終点
 @param[in] factor        補間係数( 0 ～ 1 )
 @return    S_Vector3<T> 二つの点を線形補間した点

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Lerp(const S_Vector3<T>& r_START_POINT,
                                  const S_Vector3<T>& r_END_POINT,
                                  T factor)
{
    S_Vector3 lerp_point;
    
    lerp_point.m_x = (r_END_POINT.m_x - r_START_POINT.m_x) * factor + r_START_POINT.m_x;
    lerp_point.m_y = (r_END_POINT.m_y - r_START_POINT.m_y) * factor + r_START_POINT.m_y;
    lerp_point.m_z = (r_END_POINT.m_z - r_START_POINT.m_z) * factor + r_START_POINT.m_z;
    
    return lerp_point;
}
    
    
/* 

 @brief     球面線形補間を行う
 @param[in] r_START_POINT 始点
 @param[in] r_END_POINT   終点
 @param[in] factor        補間係数( 0 ～ 1 )
 @return    S_Vector3<T> 二つの点を球面線形補間した点

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Slerp(const S_Vector3<T>& r_START_POINT,
                                   const S_Vector3<T>& r_END_POINT,
                                   T factor)
{
    // 角度とサインを求める
    T angle = s_AngleBetweenVectors(r_START_POINT, r_END_POINT);
    T sine = Sine(angle);
    
    // 各補間係数を求める
    T start_factor = Sine(angle * (static_cast<T>(1) - factor));
    T end_factor = Sine(angle * factor);
    
    // 球面線形補間した点を求める
    S_Vector3 slerp_point = r_START_POINT * start_factor + r_END_POINT * end_factor;
    
    return slerp_point;
}
    
    
/* 

 @brief     エルミート補間を行う
 @param[in] r_START_POINT   始点
 @param[in] r_START_TANGENT 始点の接線
 @param[in] r_END_POINT     終点
 @param[in] r_END_TANGENT   終点の接線
 @param[in] factor          補間係数( 0 ～ 1 )
 @return    S_Vector3<T> 二つの点をエルミート補間した点

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Hermite(const S_Vector3<T>& r_START_POINT,
                                     const S_Vector3<T>& r_START_TANGENT,
                                     const S_Vector3<T>& r_END_POINT,
                                     const S_Vector3<T>& r_END_TANGENT,
                                     T factor)
{
    // 各点と各接点の係数を求める
    T u_1 = factor;
    T u_2 = Square(factor);
    T u_3 = u_2 * factor;
    
    T p_0 = (static_cast<T>(2) * u_3) - (static_cast<T>(3) * u_2) + static_cast<T>(1);
    T t_0 = u_3 - (static_cast<T>(2) * u_2) + u_1;
    T p_1 = (static_cast<T>(-2) * u_3) + static_cast<T>(3) * u_2;
    T t_1 = u_3 - u_2;
    
    // エルミート補間する
    S_Vector3 hermite_point;
    
    hermite_point.m_x = r_START_POINT.m_x   * p_0 
                      + r_START_TANGENT.m_x * t_0 
                      + r_END_POINT.m_x     * p_1 
                      + r_END_TANGENT.m_x   * t_1;

    hermite_point.m_y = r_START_POINT.m_y   * p_0 
                      + r_START_TANGENT.m_y * t_0
                      + r_END_POINT.m_y     * p_1
                      + r_END_TANGENT.m_y   * t_1;

    hermite_point.m_z = r_START_POINT.m_z   * p_0 
                      + r_START_TANGENT.m_z * t_0 
                      + r_END_POINT.m_z     * p_1 
                      + r_END_TANGENT.m_z   * t_1;
    
    return hermite_point;
}
    

/* 

 @brief     Catmull-Romスプライン補間を行う
 @param[in] r_PREVIOUS_START_POINT 始点の前の点
 @param[in] r_START_POINT          始点
 @param[in] r_END_POINT            終点
 @param[in] r_NEXT_END_POINT       終点の次の点
 @param[in] factor                 補間係数( 0 ～ 1 )
 @return    S_Vector3<T> 二つの点をCatmull-Romスプライン補間した点

*/    
template<class T>
S_Vector3<T> S_Vector3<T>::s_CatmullRomSpline(const S_Vector3<T>& r_PREVIOUS_START_POINT,
                                              const S_Vector3<T>& r_START_POINT,
                                              const S_Vector3<T>& r_END_POINT,
                                              const S_Vector3<T>& r_NEXT_END_POINT,
                                              T factor)
{
    // 両サイドの点から接線を求める
    S_Vector3 start_tangent = (r_END_POINT - r_PREVIOUS_START_POINT) * static_cast<T>(0.5);
    S_Vector3 end_tangent = (r_NEXT_END_POINT - r_START_POINT) * static_cast<T>(0.5);
    
    // 接線を利用して、エルミート補間
    S_Vector3 catmull_rom_spline_point = s_Hermite(r_START_POINT, start_tangent, r_END_POINT, end_tangent, factor);
    return catmull_rom_spline_point;
}
    
    
/* 

 @brief     ベジェ補間を行う
 @param[in] r_START_POINT     始点
 @param[in] r_END_POINT       終点
 @param[in] r_CONTROL_POINT_1 制御点1
 @param[in] r_CONTROL_POINT_2 制御点2
 @param[in] factor            補間係数( 0 ～ 1 )
 @return    S_Vector3<T> 二つの点をベジェ補間した点

*/    
template<class T>
S_Vector3<T> S_Vector3<T>::s_Bezier(const S_Vector3<T>& r_START_POINT,
                                    const S_Vector3<T>& r_END_POINT,
                                    const S_Vector3<T>& r_CONTROL_POINT_1,
                                    const S_Vector3<T>& r_CONTROL_POINT_2,
                                    T factor)
{
    // 各点の係数を求める
    T one_minus_factor = static_cast<T>(1) - factor;
        
    T p_0 = Cubic(one_minus_factor);
    T p_1 = Cubic(factor);
    T c_0 = static_cast<T>(3) * factor * Square(one_minus_factor);
    T c_1 = static_cast<T>(3) * Square(factor) * one_minus_factor;
    
    // ベジェ補間する
    S_Vector3 bezier_point;
    
    bezier_point.m_x = r_START_POINT.m_x           * p_0 
                           + r_END_POINT.m_x       * p_1
                           + r_CONTROL_POINT_1.m_x * c_0 
                           + r_CONTROL_POINT_2.m_x * c_1;

    bezier_point.m_y = r_START_POINT.m_y           * p_0
                           + r_END_POINT.m_y       * p_1 
                           + r_CONTROL_POINT_1.m_y * c_0 
                           + r_CONTROL_POINT_2.m_y * c_1;

    bezier_point.m_z = r_START_POINT.m_z           * p_0
                           + r_END_POINT.m_z       * p_1
                           + r_CONTROL_POINT_1.m_z * c_0
                           + r_CONTROL_POINT_2.m_z * c_1;

    return bezier_point;
}
    
    
/* 

 @brief     迎撃ポイント( 交差位置 )を求める
 @param[in] r_POSITION         座標
 @param[in] r_VELOCITY         速度
 @param[in] r_ANOTHER_POSITION もう1つの座標
 @param[in] r_ANOTHER_VELOCITY もう1つの速度
 @return    S_Vector3<T> 迎撃ポイント

*/  
template<class T>
S_Vector3<T> S_Vector3<T>::s_InterceptPoint(const S_Vector3<T>& r_POSITION,
                                            const S_Vector3<T>& r_VELOCITY,
                                            const S_Vector3<T>& r_ANOTHER_POSITION,
                                            const S_Vector3<T>& r_ANOTHER_VELOCITY)
{
    // 距離と速度の差を求める
    S_Vector3 distance = r_POSITION - r_ANOTHER_POSITION;
    S_Vector3 velocity_difference = r_VELOCITY - r_ANOTHER_VELOCITY;
    
    // 距離から速度を割り、時間をだす
    T time = distance.GetMagnitude() / velocity_difference.GetMagnitude();
    
    // 迎撃ポイントを求める
    S_Vector3 intercept_point = r_POSITION + (r_VELOCITY * time);
    return intercept_point;
}
    

/* 

 @brief     ベクトル間の角度を求める
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    T 角度( ラジアン値 )

*/  
template<class T>
T S_Vector3<T>::s_AngleBetweenVectors(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    T cosine = s_DotProduct(r_LHS.GetNormalize(), r_RHS.GetNormalize());
    T angle = static_cast<T>(std::acos(static_cast<double>(cosine)));
        
    return angle;
}
    
    
/* 

 @brief     ベクトル間の距離を求める
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    T 距離

*/  
template<class T>
T S_Vector3<T>::s_DistanceBetweenVectors(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 distance = r_LHS - r_RHS;
    return distance.GetMagnitude();
}
    

/* 

 @brief     各成分の最小値を成分にしたベクトルを取得する
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    T 最小値を成分にしたベクトル

*/  
template<class T>
S_Vector3<T> S_Vector3<T>::s_Minimize(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 min_vector;

    min_vector.m_x = (r_LHS.m_x < r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    min_vector.m_y = (r_LHS.m_y < r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    min_vector.m_z = (r_LHS.m_z < r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;

    return min_vector;
}
    
    
/* 

 @brief     各成分の最大値を成分にしたベクトルを取得する
 @param[in] r_LHS 1つ目のベクトル
 @param[in] r_RHS 2つ目のベクトル
 @return    T 最大値を成分にしたベクトル

*/ 
template<class T>
S_Vector3<T> S_Vector3<T>::s_Maximize(const S_Vector3<T>& r_LHS, const S_Vector3<T>& r_RHS)
{
    S_Vector3 max_vector;

    max_vector.m_x = (r_LHS.m_x > r_RHS.m_x) ? r_LHS.m_x : r_RHS.m_x;
    max_vector.m_y = (r_LHS.m_y > r_RHS.m_y) ? r_LHS.m_y : r_RHS.m_y;
    max_vector.m_z = (r_LHS.m_z > r_RHS.m_z) ? r_LHS.m_z : r_RHS.m_z;

    return max_vector;
}
    
    
/* 

 @brief     2点間からの距離分だけ進んだ点を取得する
 @param[in] r_START_POINT 始点
 @param[in] r_END_POINT   終点
 @param[in] distance      距離
 @return    S_Vector3<T> 始点から距離分だけ進んだ点

*/ 
template<class T>
S_Vector3<T> S_Vector3<T>::s_MoveTowards(const S_Vector3<T>& r_START_POINT, 
                                         const S_Vector3<T>& r_END_POINT,
                                         T distance)
{
    if (distance < 0) return r_START_POINT;
    
    S_Vector3 difference = r_START_POINT - r_END_POINT;
    S_Vector3 movement = difference.GetNormalize() * distance;
    
    if (movement.GetMagnitudeSquare() >= difference.GetMagnitudeSquare()) return r_END_POINT;
    return r_START_POINT + movement;
}
    
   
/* 

 @brief     投影ベクトルを取得する
 @param[in] r_VECTOR ベクトル
 @param[in] r_NORMAL 法線ベクトル
 @return    S_Vector3<T> 投影ベクトル

*/ 
template<class T>
S_Vector3<T> S_Vector3<T>::s_Project(const S_Vector3<T>& r_VECTOR, 
                                     const S_Vector3<T>& r_NORMAL)
{
    // 単位ベクトル化した法線と投影の大きさを取得
    S_Vector3 unit_normal = r_NORMAL.GetNormalize();
    T project_length = s_DotProduct(r_VECTOR, unit_normal);
    
    return unit_normal * project_length;
}
    

/* 

 @brief     反射ベクトルを取得する
 @param[in] r_VECTOR ベクトル
 @param[in] r_NORMAL 法線ベクトル
 @return    S_Vector3<T> 反射ベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Reflect(const S_Vector3<T>& r_VECTOR, 
                                     const S_Vector3<T>& r_NORMAL)
{
    // 単位ベクトル化した法線を取得
    S_Vector3 unit_normal = r_NORMAL.GetNormalize();
    
    // 反射ベクトルを求める
    S_Vector3 reflection_vector = r_VECTOR - static_cast<T>(2) * s_DotProduct(r_VECTOR, unit_normal) * unit_normal;
    return reflection_vector;
}
    

/* 

 @brief     屈折ベクトルを取得する
 @param[in] r_VECTOR         ベクトル
 @param[in] r_NORMAL         法線ベクトル
 @param[in] refractive_index 屈折率
 @return    S_Vector3<T> 屈折ベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Refract(const S_Vector3<T>& r_INCIDENT_VECTOR, 
                                     const S_Vector3<T>& r_NORMAL,
                                     T refractive_index)
{
    // 各ベクトルを単位ベクトル化
    S_Vector3 unit_incident_vector = r_INCIDENT_VECTOR.GetNormalize();
    S_Vector3 unit_normal = r_NORMAL.GetNormalize();
    
    // 入射ベクトルと法線ベクトルの内積を求める
    T dot = s_DotProduct(unit_incident_vector, unit_normal);
    
    // 屈折の角度
    T refract_angle = static_cast<T>(1) - Square(refractive_index) * (static_cast<T>(1) - Square(dot));
    
    // 屈折ベクトルを求める
    S_Vector3 refract_vector;
    if (refract_angle < 0) return refract_vector;
    
    refract_vector = refractive_index * unit_incident_vector 
                   - (refractive_index * dot * SquareRoot(refract_angle)) * unit_normal;
    
    return refract_vector;
}
    

/* 

 @brief     滑りしたベクトルを取得する
 @param[in] r_VECTOR ベクトル
 @param[in] r_NORMAL 法線ベクトル
 @return    S_Vector3<T> 滑りしたベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_Slide(const S_Vector3<T>& rVector, 
                                const S_Vector3<T>& rNormal)
{
    // 単位ベクトル化した法線を取得
    S_Vector3 unit_normal = rNormal.GetNormalize();
    
    // 滑りベクトルを求める
    S_Vector3 slider_vector = rVector - s_DotProduct(rVector, unit_normal) * unit_normal;
    return slider_vector;
}
    

/* 

 @brief     法線ベクトルを作成
 @param[in] r_POSITION_A 1つ目の座標
 @param[in] r_POSITION_B 2つ目の座標
 @param[in] r_POSITION_C 3つ目の座標
 @return    S_Vector3<T> 法線ベクトル

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_CreateNormal(const S_Vector3<T>& r_POSITION_A, 
                                          const S_Vector3<T>& r_POSITION_B,
                                          const S_Vector3<T>& r_POSITION_C)
{
    // 各座標からベクトルを求める
    S_Vector3 vector_ab = r_POSITION_B - r_POSITION_A;
    S_Vector3 vector_bc = r_POSITION_C - r_POSITION_B;
    
    // 法線ベクトルを求める
    S_Vector3 normal = s_CrossProduct(vector_ab, vector_bc);
    normal.Normalize();
    return normal;
}
    

/* 

 @brief      接線ベクトルと従法線を作成
 @param[in]  r_POSITION_A      1つ目の座標
 @param[in]  r_TEXTURE_COORD_A 1つ目のテクスチャ座標
 @param[in]  r_POSITION_B      2つ目の座標
 @param[in]  r_TEXTURE_COORD_B 2つ目のテクスチャ座標
 @param[in]  r_POSITION_C      3つ目の座標
 @param[in]  r_TEXTURE_COORD_C 3つ目のテクスチャ座標
 @param[out] p_tangent         接ベクトル
 @param[out] p_binormal        従法線
 @return     なし

*/
template<class T>
void S_Vector3<T>::s_CreateTangentAndBinormal(const S_Vector3<T>& r_POSITION_A,   
                                              const S_Vector2<T>& r_TEXTURE_COORD_A,
                                              const S_Vector3<T>& r_POSITION_B,
                                              const S_Vector2<T>& r_TEXTURE_COORD_B,
                                              const S_Vector3<T>& r_POSITION_C,
                                              const S_Vector2<T>& r_TEXTURE_COORD_C,
                                              S_Vector3* p_tangent,
                                              S_Vector3* p_binormal)
{
    assert(p_tangent || p_binormal);

    // 頂点Aに対する相対的なベクトルを求める
    S_Vector3 vector_position_ab = r_POSITION_B - r_POSITION_A;
    S_Vector3 vector_position_ac = r_POSITION_C - r_POSITION_A;
    
    S_Vector2<T> vector_texture_coord_ab = r_TEXTURE_COORD_B - r_TEXTURE_COORD_A;
    S_Vector2<T> vector_texture_coord_ac = r_TEXTURE_COORD_C - r_TEXTURE_COORD_A;
    
    // 接線ベクトルと従法線ベクトルを求める
    T denominator = vector_texture_coord_ab.m_x * vector_texture_coord_ac.m_y 
                  - vector_texture_coord_ab.m_y * vector_texture_coord_ac.m_x;
    assert(denominator != 0);
        
    T part_of_inverse_matrix = static_cast<T>(1) / denominator;
    
    if (p_tangent)
    {
        S_Vector3 tangent((vector_texture_coord_ac.m_y * vector_position_ab.m_x - vector_texture_coord_ab.m_y * vector_position_ac.m_x) * part_of_inverse_matrix,
                          (vector_texture_coord_ac.m_y * vector_position_ab.m_y - vector_texture_coord_ab.m_y * vector_position_ac.m_y) * part_of_inverse_matrix,
                          (vector_texture_coord_ac.m_y * vector_position_ab.m_z - vector_texture_coord_ab.m_y * vector_position_ac.m_z) * part_of_inverse_matrix);

        *p_tangent = tangent;
    }

    if (p_binormal)
    {
        S_Vector3 binormal((vector_texture_coord_ab.m_x * vector_position_ac.m_x - vector_texture_coord_ac.m_x * vector_position_ab.m_x) * part_of_inverse_matrix,
                           (vector_texture_coord_ab.m_x * vector_position_ac.m_y - vector_texture_coord_ac.m_x * vector_position_ab.m_y) * part_of_inverse_matrix,
                           (vector_texture_coord_ab.m_x * vector_position_ac.m_z - vector_texture_coord_ac.m_x * vector_position_ab.m_z) * part_of_inverse_matrix);
    
        *p_binormal = binormal;
    }
}
    
    
/* 

 @brief     3点から重心を取得する
 @param[in] r_A 1つ目の座標
 @param[in] r_B 2つ目の座標
 @param[in] r_C 3つ目の座標
 @return    S_Vector3<T> 重心

*/
template<class T>
S_Vector3<T> S_Vector3<T>::s_CenterOfGravityWith3Points(const S_Vector3<T>& r_A,
                                                        const S_Vector3<T>& r_B,
                                                        const S_Vector3<T>& r_C)
{
    S_Vector3 center_of_gravity(r_A + r_B + r_C);
    center_of_gravity /= static_cast<T>(3);
    return center_of_gravity;
}
    
    
#pragma region S_Vector3型との演算子のオーバーロード
    
    
/* 

 @brief     加算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T> 加算したベクトル

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator+(const S_Vector3<T>& r_ANOTHER) const
{
return S_Vector3(this->m_x + r_ANOTHER.m_x, 
                 this->m_y + r_ANOTHER.m_y,
                 this->m_z + r_ANOTHER.m_z);
}
    
    
/* 

 @brief     減算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T> 減算したベクトル

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator-(const S_Vector3<T>& r_ANOTHER) const
{
return S_Vector3(this->m_x - r_ANOTHER.m_x,
                 this->m_y - r_ANOTHER.m_y,
                 this->m_z - r_ANOTHER.m_z);
}
    
    
/* 

 @brief     乗算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T> 乗算したベクトル

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator*(const S_Vector3<T>& r_ANOTHER) const
{
return S_Vector3(this->m_x * r_ANOTHER.m_x,
                 this->m_y * r_ANOTHER.m_y,
                 this->m_z * r_ANOTHER.m_z);
}
    
    
/* 

 @brief     除算演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T> 除算したベクトル

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator/(const S_Vector3<T>& r_ANOTHER) const
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    
    return S_Vector3(this->m_x / r_ANOTHER.m_x,
                     this->m_y / r_ANOTHER.m_y,
                     this->m_z / r_ANOTHER.m_z);
}
    
    
/* 

 @brief     加算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T>& 加算したベクトル

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator+=(const S_Vector3<T>& r_ANOTHER)
{
    this->m_x += r_ANOTHER.m_x;
    this->m_y += r_ANOTHER.m_y;
    this->m_z += r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     減算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T>& 減算したベクトル

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator-=(const S_Vector3<T>& r_ANOTHER)
{
    this->m_x -= r_ANOTHER.m_x;
    this->m_y -= r_ANOTHER.m_y;
    this->m_z -= r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     乗算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T>& 乗算したベクトル

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator*=(const S_Vector3<T>& r_ANOTHER)
{
    this->m_x *= r_ANOTHER.m_x;
    this->m_y *= r_ANOTHER.m_y;
    this->m_z *= r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     除算代入演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    const S_Vector3<T>& 除算したベクトル

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator/=(const S_Vector3<T>& r_ANOTHER)
{
    assert(r_ANOTHER.m_x != 0);
    assert(r_ANOTHER.m_y != 0);
    assert(r_ANOTHER.m_z != 0);
    
    this->m_x /= r_ANOTHER.m_x;
    this->m_y /= r_ANOTHER.m_y;
    this->m_z /= r_ANOTHER.m_z;
    
    return (*this);
}
    
    
/* 

 @brief     等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    bool  比較した結果
 @retval    true  同じベクトルの場合
 @retval    false 違うじベクトルの場合

*/
template<class T>
bool S_Vector3<T>::operator==(const S_Vector3<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) < GetEpsilon<T>()
        && Absolute(this->m_y - r_ANOTHER.m_y) < GetEpsilon<T>()
        && Absolute(this->m_z - r_ANOTHER.m_z) < GetEpsilon<T>();
}
    
   
/* 

 @brief     非等値演算子のオーバーロード
 @param[in] r_ANOTHER もう1つのベクトル
 @return    bool  比較した結果
 @retval    true  違うベクトルの場合
 @retval    false 同じベクトルの場合

*/
template<class T>
bool S_Vector3<T>::operator!=(const S_Vector3<T>& r_ANOTHER) const
{
    return Absolute(this->m_x - r_ANOTHER.m_x) > GetEpsilon<T>()
        || Absolute(this->m_y - r_ANOTHER.m_y) > GetEpsilon<T>()
        || Absolute(this->m_z - r_ANOTHER.m_z) > GetEpsilon<T>();
}
    
    
#pragma endregion


#pragma region T型との演算子のオーバーロード
    
    
/* 

 @brief     T型の値を各成分に乗算したベクトルを求める
 @param[in] value T型の値
 @return    const S_Vector3<T> 乗算したベクトル

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator*(T value) const
{
    return S_Vector3(this->m_x * value, this->m_y * value, this->m_z * value);
}
    
    
/* 

 @brief     T型の値で各成分を除算したベクトルを求める
 @param[in] value T型の値
 @return    const S_Vector3<T> 除算したベクトル

*/
template<class T>
const S_Vector3<T> S_Vector3<T>::operator/(T value) const
{
    assert(value != 0);
    return S_Vector3(this->m_x / value, this->m_y / value, this->m_z / value);
}
    
    
/* 

 @brief     T型の値を各成分に乗算する
 @param[in] value T型の値
 @return    const S_Vector3<T>& 乗算したベクトル

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator*=(T value)
{
    this->m_x *= value;
    this->m_y *= value;
    this->m_z *= value;
    
    return (*this);
}
    
    
/* 

 @brief     T型の値で各成分を除算する
 @param[in] value T型の値
 @return    const S_Vector3<T>& 除算したベクトル

*/
template<class T>
const S_Vector3<T>& S_Vector3<T>::operator/=(T value)
{
    assert(value != 0);
    
    this->m_x /= value;
    this->m_y /= value;
    this->m_z /= value;
    
    return (*this);
}
    
    
#pragma endregion
    
    
#pragma region キャスト
    
    
/* 

 @brief  S_Vector2型へのキャストする
 @param  なし
 @return S_Vector2<T> 2Dベクトル

*/
template<class T>
S_Vector3<T>::operator S_Vector2<T>() const
{
    return S_Vector2<T>(this->m_x, this->m_y);
}
    
    
/* 

 @brief  String型へキャストする
 @param  なし
 @return String 文字列に変換したベクトル

*/
template<class T>
S_Vector3<T>::operator String() const
{
    return this->ToString();
}
    
    
#pragma endregion


/* 明示的インスタンス化 */
template struct S_Vector3<float>;
template struct S_Vector3<double>;

