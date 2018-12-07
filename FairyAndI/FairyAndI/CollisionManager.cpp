//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <list>
#include "Collision.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Main.h"
#include "OBB.h"
#include "Sphere.h"

//＝＝＝グローバル変数＝＝＝//
std::list<COLLISION*> COLLISIONMANAGER::Collision;
std::list<COLLISION*> COLLISIONMANAGER::HitList;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：マネージャーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT COLLISIONMANAGER::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Collision.clear();
    HitList.clear();
    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//関数名：InstantiateToOBB
//
//機能：OBBコリジョンの登録
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
COLLISION* COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3 position, D3DXVECTOR3 rotation, tstring tag, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new OBB(position, rotation, tag, layer, owner));
    return Collision.back();
}

/////////////////////////////////////////////
//関数名：Instantiate
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
COLLISION* COLLISIONMANAGER::InstantiateToSphere(D3DXVECTOR3 position, float radius, tstring tag, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new SPHERE(position, radius, tag, layer, owner));
    return Collision.back();
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISIONMANAGER::Uninitialize(void)
{
    //---解放---//
    Collision.clear();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：マネージャの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISIONMANAGER::Update(void)
{
    //---当たり判定の処理---//
    for (auto& itrBase = Collision.begin(); itrBase != Collision.end(); ++itrBase)
    {
        for (auto& itrOpponent = std::next(itrBase) ; itrOpponent != Collision.end(); ++itrOpponent)
        {
            //if ((*itrBase)->CheckCollision(nullptr))
            //{
            //    HitList.emplace_back(itrBase);
            //    HitList.emplace_back(itrOpponent);
            //}
        }
    }

    //---当たった時の処理の実行---//
    for (auto& data : HitList)
    {
        data->Owner->OnCollision(nullptr);
    }
}