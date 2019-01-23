//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "CharacterFactory.h"
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
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(TEXT("Data/GameScene/Model/Character/Fairy.x"), position, rotation));
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
    //ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/GameScene/Model/Character/Player.x"), position, rotation));
    //ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/GameScene/Model/Character/tiny_4anim.x"), position, rotation));
    //ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/GameScene/Model/Character/Walk.x"), position, rotation));
}