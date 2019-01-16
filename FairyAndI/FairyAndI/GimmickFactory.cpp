////＝＝＝ヘッダファイル読み込み＝＝＝//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "BatteryGimmick.h"
#include "Bullet.h"
#include "FireGimmick.h"
#include "GimmickFactory.h"
#include "IceGimmick.h"
#include "WoodGimmick.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：InstantiateBatteryGimmick
//
//機能：砲台の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateBatteryGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---生成---//
	ACTORMANAGER::GameObject.emplace_back(new BATTERYGIMMICK(TEXT("FIRE"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateBulletGimmick
//
//機能：砲台の弾の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateBulletGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---生成---//
	ACTORMANAGER::GameObject.emplace_back(new BULLET(TEXT("ICE"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateFireGimmick
//
//機能：炎の壁の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateFireGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new FIREGIMMICK(TEXT("FIREGIMMICK"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateGimmick
//
//機能：ギミックオブジェクトの生成
//
//引数：(tstring)生成オブジェクト,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateGimmick(tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    std::unordered_map<tstring, std::function< void(D3DXVECTOR3, D3DXVECTOR3) >> Function = { { TEXT("BATTERYGIMMCK"), InstantiateBatteryGimmick },{ TEXT("ICE"), InstantiateBulletGimmick },{ TEXT("FIREGIMMCK"), InstantiateFireGimmick },{ TEXT("ICEGIMMICK"), InstantiateIceGimmick },{ TEXT("WOODGIMMICK"), InstantiateWoodGimmick } };

    //---生成---//
    for (auto& data : Function)
    {
        if (gameobject.find(data.first) != tstring::npos)
        {
            data.second(position, rotation);
        }
    }
}

/////////////////////////////////////////////
//関数名：InstantiateIceGimmick
//
//機能：氷壁の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateIceGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new ICEGIMMICK(TEXT("ICEGIMMICK"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateWoodGimmick
//
//機能：大樹の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateWoodGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new FIREGIMMICK(TEXT("WOODGIMMICK"), TEXT("Gimmick"), position, rotation));
}