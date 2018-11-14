#ifndef _SOUND_PARAMETER_H_
#define _SOUND_PARAMETER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝構造体宣言＝＝＝//
typedef struct
{
    tstring FileName;	//ファイル名
    UINT32 LoopCount;	//ループカウント
    tstring CallKey;    //呼び出しキー
} SOUNDPARAMETER;

#endif