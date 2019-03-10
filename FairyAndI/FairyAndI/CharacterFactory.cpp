//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "CharacterFactory.h"
#include "Fairy.h"
#include "Player.h"
#include "Slime.h"
#include "Wood.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：InstantiateFairy
//
//機能：フェアリーの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiatePlayer
//
//機能：プレイヤーの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateSlime
//
//機能：スライムの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new SLIME(TEXT("Slime"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateWood
//
//機能：木のオバケの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateWood(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new WOOD(TEXT("Wood"), position, rotation));
}