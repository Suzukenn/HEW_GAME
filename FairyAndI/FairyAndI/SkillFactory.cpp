//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Bullet.h"
#include "Grenade.h"
#include "SkillFactory.h"
#include "Trap.h"
#include "Wall.h"

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
	ACTORMANAGER::GameObject.emplace_back(new BULLET(TEXT("ICE"), type, position, rotation));
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
	ACTORMANAGER::GameObject.emplace_back(new GRENADE(TEXT("FIRE"), type, position, rotation));
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
	ACTORMANAGER::GameObject.emplace_back(new TRAP(TEXT("RICECAKE"), type, position, rotation));
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
    std::unordered_map<tstring, std::function< void(tstring, D3DXVECTOR3, D3DXVECTOR3) >> Function = { {TEXT("FIRE"), InstantiateGrenade }, { TEXT("ICE"), InstantiateBullet }, {TEXT("RICECAKE"), InstantiateTrap },{ TEXT("ROCK"), InstantiateWall } };

    //---生成---//
    for (auto& data : Function)
    {
        if (data.first == gameobject)
        {
            data.second(type, position, rotation);
            return;
        }
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
    ACTORMANAGER::GameObject.emplace_back(new WALL(TEXT("WALL"), type, position, rotation));
}