/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../NullPointer/NullPointer.h"

// TODO ： S_DefaultDeleterを定義するヘッダを別途用意すること( SharedPtr.hに依存させるのは変なので )
#include "SharedPtr.h"


/**

 @brief GALib
        GAライブラリ関連の名前空間

*/
namespace GALib
{
    /**

     @brief Utility
            実用的なプログラム関連の名前空間

    */
    namespace Utility
    {
        /* 別名 */
        typedef int Int32;
        
        
        /**

         @brief S_ArrayDeleter
                配列で確保したオブジェクトのデリータを表す構造体

        */
        template<typename T>
        struct S_ArrayDeleter
        {
            void operator()(T* p_object)
            {
                // TODO ： deleteの配列版が出来次第置き換えること
                delete[] p_object;
            }
        };


        /**

         @brief C_UniquePtr
                コピーを許さない唯一のポインタを表すクラス
                基本的な使用方法はC++11以降で標準に提供されているstd::unique_ptrと同じになっている
                new[]でオブジェクトを確保している場合はDeleterを上記のS_ArrayDeleterに変更すること

        */
        template<typename T, typename Deleter = S_DefaultDeleter<T> >
        class C_UniquePtr
        {
        public:
            // コンストラクタ・デストラクタ
            C_UniquePtr();
            C_UniquePtr(T* p_object);
            virtual ~C_UniquePtr();

            // メンバ関数
            T* Get() const;
            T* Release();
            void Reset(T* p_object = GA_NULL);
            void Swap(C_UniquePtr& r_other);

            // 静的メンバ関数

            // std::moveと使い方が異なるので注意
            static void s_Move(C_UniquePtr& r_giver, C_UniquePtr& r_taker);

            // 演算子のオーバーロード
            T& operator*() const;
            T* operator->() const;
            T& operator[](Int32 i) const;
            operator bool() const;
        private:
            T* m_p_object;

            // コピーコンストラクタと代入演算子をプライベートに宣言し、コピーを禁止させる
            C_UniquePtr(const C_UniquePtr& r_other);
            C_UniquePtr& operator=(const C_UniquePtr& r_other);

            void SafeDelete();
        };

        /* 実装 */
        #include "UniquePointerImpl.h"
    }
}
