/**

 @brief  コンストラクタ
 @param  なし

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::C_UniquePtr() :
    
    m_p_object(GA_NULL)

{
}



/**

 @brief  コンストラクタ
 @param  オブジェクトのポインタ

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::C_UniquePtr(T* p_object) :
    
    m_p_object(p_object)

{
}


/**

 @brief  デストラクタ
 @param  なし

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::~C_UniquePtr()
{
    this->SafeDelete();
}


/**

 @brief  オブジェクトのポインタを取得
 @param  なし
 @return オブジェクトのポインタ

*/
template<typename T, typename Deleter>
inline T* C_UniquePtr<T, Deleter>::Get() const
{
    return this->m_p_object;
}


/**

 @brief  オブジェクトのポインタの管理を外部へ移す
 @param  なし
 @return オブジェクトのポインタ

*/
template<typename T, typename Deleter>
inline T* C_UniquePtr<T, Deleter>::Release()
{
    T* p_temp = this->m_p_object;
    this->m_p_object = GA_NULL;

    return p_temp;
}


/**

 @brief     オブジェクトのポインタの管理を破棄する
 @param[in] p_object 新たに管理するオブジェクトのポインタ
 @return    オブジェクトのポインタ

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::Reset(T* p_object)
{
    this->SafeDelete();
    this->m_p_object = p_object;
}


/**

 @brief           C_UniquePtrが管理しているポインタを交換する
 @param[in, out]  r_other 別のC_UniquePtr
 @return          なし

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::Swap(C_UniquePtr<T, Deleter>& r_other)
{
    T* p_temp = r_other->m_p_object;
    r_other->m_p_object = this->m_p_object;
    this->m_p_object = p_temp;
}


/**

 @brief           管理しているポインタの所有権を別のC_UniquePtrに移す
                  C++11以降で標準に提供されているstd::moveと使い方が異なるので注意
 @param[in, out]  与える側
 @param[in, out]  受け取る側
 @return          なし

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::s_Move(C_UniquePtr<T, Deleter>& r_giver, C_UniquePtr<T, Deleter>& r_taker)
{
    r_taker.SafeDelete();
    r_taker.m_p_object = r_giver.m_p_object;
    r_giver.m_p_object = GA_NULL;
}


/**

 @brief  メンバ参照演算子のオーバーロード
 @param  なし
 @param  オブジェクトの参照

*/
template<typename T, typename Deleter>
inline T& C_UniquePtr<T, Deleter>::operator*() const
{
    return (*this->m_p_object);
}


/**

 @brief  アロー演算子のオーバーロード
 @param  なし
 @param  オブジェクトのポインタ

*/
template<typename T, typename Deleter>
inline T* C_UniquePtr<T, Deleter>::operator->() const
{
    return this->m_p_object;
}


/**

 @brief  添え字演算子のオーバーロード
 @param  i インデックス
 @param  オブジェクトの参照

*/
template<typename T, typename Deleter>
inline T& C_UniquePtr<T, Deleter>::operator[](Int32 i) const
{
    return this->m_p_object[i];
}


/**

 @brief  bool演算子のオーバーロード
 @param  なし

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::operator bool() const
{
    return (this->m_p_object != GA_NULL);
}


/**

 @brief  C_UniquePtrが管理しているポインタを交換する
 @param  別のC_UniquePtr
 @return なし

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::SafeDelete()
{
    if (this->m_p_object)
    {
        Deleter()(this->m_p_object);
        this->m_p_object = GA_NULL;
    }
}