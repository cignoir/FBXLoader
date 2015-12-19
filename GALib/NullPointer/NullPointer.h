/* 二重インクルード防止 */
#pragma once


/**

 @brief  GALib
 @brief  GAライブラリ関連の名前空間

*/
namespace GALib
{
    /**

     @brief  C_NullPointer
             ヌルポインタを表すクラス

    */
    class C_NullPointer
    {
    public:
        /**

         @brief     キャスト演算子のオーバーロード
                    ポインタ型にしか代入を許可しない
         @param     なし
         @return    T* 0( ヌル )

        */
        template<typename T>
        operator T*() const
        {
            return 0;
        }
    private:

        // アドレス演算子をプライベートに置くことで、アドレスの取得を許可しない
        void operator&() const;
    };

    typedef C_NullPointer NullType;
}


/* マクロ定義 */
#define GA_NULL (GALib::NullType())