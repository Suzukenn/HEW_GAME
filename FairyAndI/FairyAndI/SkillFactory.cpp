//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Bullet.h"
#include "Grenade.h"
#include "SkillFactory.h"
#include "Trap.h"
#include "Wall.h"
#include "WordManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：InstantiateBullet
//
//機能：弾の生成
//
//引数：(tstring)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateBullet(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---生成---//
	ACTORMANAGER::GameObject.emplace_back(new BULLET(tstring(TEXT("SKILL_") + type + TEXT("ICE")).data(), type, position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateGrenade
//
//機能：榴弾の生成
//
//引数：(tstring)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateGrenade(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---生成---//
	ACTORMANAGER::GameObject.emplace_back(new GRENADE(tstring(TEXT("SKILL_") + type + TEXT("FIRE")).data(), type, position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateTrap
//
//機能：罠の生成
//
//引数：(tstring)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateTrap(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---生成---//
	ACTORMANAGER::GameObject.emplace_back(new TRAP(tstring(TEXT("SKILL_") + type + TEXT("RICECAKE")).data(), type, position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateSkill
//
//機能：スキルオブジェクトの生成
//
//引数：(tstring)生成属性,(tstring)生成オブジェクト,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateSkill(tstring type, tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    bool bLock;
    const std::unordered_map<tstring, std::function< void(tstring, D3DXVECTOR3, D3DXVECTOR3) >> Function = { {TEXT("FIRE"), InstantiateGrenade }, { TEXT("ICE"), InstantiateBullet }, {TEXT("RICECAKE"), InstantiateTrap },{ TEXT("ROCK"), InstantiateWall } };

    //---生成---//
    if (FAILED(WORDMANAGER::GetWordLock(gameobject.data(), bLock)))
    {
        MessageBox(nullptr, TEXT("指定ワードのロック情報の取得に失敗しました"), gameobject.data(), MB_OK);
        return;
    }

    if (bLock)
    {
        Function.at(gameobject)(type, position, rotation);
    }
}

/////////////////////////////////////////////
//関数名：InstantiateWall
//
//機能：壁の生成
//
//引数：(tstring)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateWall(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new WALL(tstring(TEXT("SKILL_") + type + TEXT("ROCK")).data(), type, position, rotation));
}