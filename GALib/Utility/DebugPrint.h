#pragma once
#include <Windows.h>
#include <stdio.h>

// ---------------------------------------------------------
//デバッグウィンドウに文字列出力
// ---------------------------------------------------------
//可変長引数
static void DebugPrint(const char *str, ...){
	const int DEBUG_BUFFER_SIZE = 512;
	char debug_buf[DEBUG_BUFFER_SIZE];

	//引数リストの変数を宣言
	//va_startでリストの取得
	va_list ap;
	va_start(ap, str);

	//引数リストへのポインタを利用して、書式付出力を書き込む
	if (!vsprintf_s(debug_buf, DEBUG_BUFFER_SIZE, str, ap)){
		//エラーが返ってきたのでエラー出力
		OutputDebugStringA("error");
	}
	va_end(ap);
	OutputDebugStringA(debug_buf);

}
