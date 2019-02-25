//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Element.h"
#include "Goal.h"
#include "ObjectFactory.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：InstantiateFireElement
//
//機能：炎のエレメントの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3 position)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new ELEMENT(TEXT("FIRE"), TEXT("FIRE"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}

/////////////////////////////////////////////
//関数名：InstantiateGoal
//
//機能：ゴールの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateGoal(D3DXVECTOR3 position)
{
	//---生成---//
	ACTORMANAGER::GameObject.emplace_back(new GOAL(TEXT("GOAL"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}

/////////////////////////////////////////////
//関数名：InstantiateIceElement
//
//機能：氷のエレメントの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateIceElement(D3DXVECTOR3 position)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new ELEMENT(TEXT("ICE"), TEXT("ICE"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}

/////////////////////////////////////////////
//関数名：InstantiateRockElement
//
//機能：岩のエレメントの生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateRockElement(D3DXVECTOR3 position)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new ELEMENT(TEXT("ROCK"), TEXT("ROCK"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}