/**

 @brief  �R���X�g���N�^
 @param  �Ȃ�

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::C_UniquePtr() :
    
    m_p_object(GA_NULL)

{
}



/**

 @brief  �R���X�g���N�^
 @param  �I�u�W�F�N�g�̃|�C���^

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::C_UniquePtr(T* p_object) :
    
    m_p_object(p_object)

{
}


/**

 @brief  �f�X�g���N�^
 @param  �Ȃ�

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::~C_UniquePtr()
{
    this->SafeDelete();
}


/**

 @brief  �I�u�W�F�N�g�̃|�C���^���擾
 @param  �Ȃ�
 @return �I�u�W�F�N�g�̃|�C���^

*/
template<typename T, typename Deleter>
inline T* C_UniquePtr<T, Deleter>::Get() const
{
    return this->m_p_object;
}


/**

 @brief  �I�u�W�F�N�g�̃|�C���^�̊Ǘ����O���ֈڂ�
 @param  �Ȃ�
 @return �I�u�W�F�N�g�̃|�C���^

*/
template<typename T, typename Deleter>
inline T* C_UniquePtr<T, Deleter>::Release()
{
    T* p_temp = this->m_p_object;
    this->m_p_object = GA_NULL;

    return p_temp;
}


/**

 @brief     �I�u�W�F�N�g�̃|�C���^�̊Ǘ���j������
 @param[in] p_object �V���ɊǗ�����I�u�W�F�N�g�̃|�C���^
 @return    �I�u�W�F�N�g�̃|�C���^

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::Reset(T* p_object)
{
    this->SafeDelete();
    this->m_p_object = p_object;
}


/**

 @brief           C_UniquePtr���Ǘ����Ă���|�C���^����������
 @param[in, out]  r_other �ʂ�C_UniquePtr
 @return          �Ȃ�

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::Swap(C_UniquePtr<T, Deleter>& r_other)
{
    T* p_temp = r_other->m_p_object;
    r_other->m_p_object = this->m_p_object;
    this->m_p_object = p_temp;
}


/**

 @brief           �Ǘ����Ă���|�C���^�̏��L����ʂ�C_UniquePtr�Ɉڂ�
                  C++11�ȍ~�ŕW���ɒ񋟂���Ă���std::move�Ǝg�������قȂ�̂Œ���
 @param[in, out]  �^���鑤
 @param[in, out]  �󂯎�鑤
 @return          �Ȃ�

*/
template<typename T, typename Deleter>
inline void C_UniquePtr<T, Deleter>::s_Move(C_UniquePtr<T, Deleter>& r_giver, C_UniquePtr<T, Deleter>& r_taker)
{
    r_taker.SafeDelete();
    r_taker.m_p_object = r_giver.m_p_object;
    r_giver.m_p_object = GA_NULL;
}


/**

 @brief  �����o�Q�Ɖ��Z�q�̃I�[�o�[���[�h
 @param  �Ȃ�
 @param  �I�u�W�F�N�g�̎Q��

*/
template<typename T, typename Deleter>
inline T& C_UniquePtr<T, Deleter>::operator*() const
{
    return (*this->m_p_object);
}


/**

 @brief  �A���[���Z�q�̃I�[�o�[���[�h
 @param  �Ȃ�
 @param  �I�u�W�F�N�g�̃|�C���^

*/
template<typename T, typename Deleter>
inline T* C_UniquePtr<T, Deleter>::operator->() const
{
    return this->m_p_object;
}


/**

 @brief  �Y�������Z�q�̃I�[�o�[���[�h
 @param  i �C���f�b�N�X
 @param  �I�u�W�F�N�g�̎Q��

*/
template<typename T, typename Deleter>
inline T& C_UniquePtr<T, Deleter>::operator[](Int32 i) const
{
    return this->m_p_object[i];
}


/**

 @brief  bool���Z�q�̃I�[�o�[���[�h
 @param  �Ȃ�

*/
template<typename T, typename Deleter>
inline C_UniquePtr<T, Deleter>::operator bool() const
{
    return (this->m_p_object != GA_NULL);
}


/**

 @brief  C_UniquePtr���Ǘ����Ă���|�C���^����������
 @param  �ʂ�C_UniquePtr
 @return �Ȃ�

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