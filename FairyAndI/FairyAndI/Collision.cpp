//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Collision.h"

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マネージャーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
COLLISION::COLLISION(tstring tag, GAMEOBJECT* parent)
{
    Tag = tag;
    Parent = parent;
}