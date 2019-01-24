//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "CharacterFactory.h"
#include "Enemy.h"
#include "Fairy.h"
#include "Player.h"

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
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(TEXT("Data/Common/Model/Character/Fairy.x"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiatePlant
//
//機能：敵(ザコ植物)の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiatePlant(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	ACTORMANAGER::GameObject.emplace_back(new ENEMY(TEXT("FIRE"), TEXT("Plant"), position, rotation));
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
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/Common/Model/Character/tiny_4anim.x"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateSlime
//
//機能：敵(ザコ水)の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	ACTORMANAGER::GameObject.emplace_back(new ENEMY(TEXT("ICE"), TEXT("Slime"), position, rotation));
}