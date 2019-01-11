//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Bullet.h"
#include "SkillFactory.h"
#include "Wall.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：InstantiateBullet
//
//機能：弾の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateBullet(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new BULLET(TEXT("ICE"), TEXT("Bullet"), position, rotation));
}

/////////////////////////////////////////////
//関数名：InstantiateSkill
//
//機能：スキルオブジェクトの生成
//
//引数：(tstring)生成オブジェクト,(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateSkill(tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    std::unordered_map<tstring, std::function< void(D3DXVECTOR3, D3DXVECTOR3) >> Function = { {TEXT("FIRE "), InstantiateBullet }, {TEXT("WALL"), InstantiateWall } };

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
//関数名：InstantiateWall
//
//機能：壁の生成
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)回転
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateWall(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---生成---//
    ACTORMANAGER::GameObject.emplace_back(new WALL(TEXT("WALL"), TEXT("Wall"), position, rotation));
}
