#pragma once
#include "WindowBase.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	win32apiの名前空間
	
	*/
	namespace Win32api{
		/**
		
		*	@brief	win32apiのフォントハンドルラッパークラス
		
		*/
		class C_GDIFont{
		public:
			/**
			
			*	@brief	コンストラクタ

			*	@param[in]	font_name	フォント名
			*	@param[in]	font_height	フォント高さ
			*	@param[in]	font_width	フォント幅
			*	@param[in]	font_weight	フォントの重さ（太さ）0で標準、1000で最大

			*/
			C_GDIFont(const wchar_t* font_name, int font_height, int font_width, int font_weight){
				this->m_Font = CreateFont(
					font_height,    //フォント高さ
					font_width,                    //文字幅
					0,                    //テキストの角度
					0,                    //ベースラインとｘ軸との角度
					font_weight,            //フォントの重さ（太さ）
					FALSE,                //イタリック体
					FALSE,                //アンダーライン
					FALSE,                //打ち消し線
					SHIFTJIS_CHARSET,    //文字セット
					OUT_DEFAULT_PRECIS,    //出力精度
					CLIP_DEFAULT_PRECIS,//クリッピング精度
					PROOF_QUALITY,        //出力品質
					FIXED_PITCH | FF_MODERN,//ピッチとファミリー
					font_name);    //書体名
			}
			/**
			
			*	@brief	デストラクタ

			*	@param	なし

			*/
			~C_GDIFont(){
				DeleteObject(this->m_Font);
			}

			/**
			
			*	@brief	フォントハンドルを取得する

			*	@param	なし

			*	@return	フォントハンドル
			
			*/
			HFONT GetFont(){ return this->m_Font; }

			/**
			
			*	@brief	デバイスコンテキストに自身のフォントを持たせる

			*	@param[in]	hdc	デバイスこんてきすｔ

			*	@return	なし

			*/
			void StartFont(HDC hdc){
				this->m_OldFont = (HFONT)SelectObject(hdc, this->m_Font);
			}

			/**
			
			*	@brief	デバイスコンテキストのフォントを戻す

			*	@param[in]	hdc	デバイスコンテキスト

			*	@return	なし

			*/
			void EndFont(HDC hdc){
				SelectObject(hdc, this->m_OldFont);
			}
		private:
			HFONT m_Font = NULL;
			HFONT m_OldFont = NULL;
		};
	}
}