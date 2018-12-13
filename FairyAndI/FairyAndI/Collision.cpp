//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Collision.h"

/////////////////////////////////////////////
//関数名：COLLISION
//
//機能：コリジョンの初期化
//
//引数：(tstring)判定タグ,(tstring)所属レイヤー,(GAMEOBJECT*)持ち主
//
//戻り値：なし
/////////////////////////////////////////////
COLLISION::COLLISION(tstring layer, GAMEOBJECT* owner)
{
    Layer = layer;
    Owner = owner;
}