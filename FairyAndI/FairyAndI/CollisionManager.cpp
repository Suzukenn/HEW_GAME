//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <list>
#include <vector>
#include "Collision.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Main.h"
#include "OBB.h"
#include "Sphere.h"

//＝＝＝グローバル変数＝＝＝//
std::list<COLLISION*> COLLISIONMANAGER::Collision;
std::list<COLLISION*> COLLISIONMANAGER::DestroyCollision;
std::vector<COLLISION*> COLLISIONMANAGER::HitList;
std::vector<COLLISION*> COLLISIONMANAGER::HitOpponent;
std::unordered_map<tstring, std::unordered_map<tstring, bool>> COLLISIONMANAGER::CollsitionLayer;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Destroy
//
//機能：コリジョンの削除
//
//引数：(COLLISION*)削除コリジョン
//
//戻り値：なし
/////////////////////////////////////////////
void COLLISIONMANAGER::Destroy(COLLISION* collision)
{
    //---廃棄リストへ登録---//
    DestroyCollision.emplace_back(collision);
}

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

    std::unordered_map<tstring, bool>conWork;

    //---初期化処理---//
    Collision.clear();
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();
    hResult = S_OK;

    //---衝突レイヤーの設定---//
    conWork.emplace(TEXT("Character"), true);
    conWork.emplace(TEXT("Skill"), true);
    conWork.emplace(TEXT("Field"), true);
    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Character"), conWork);

    conWork.clear();

    conWork.emplace(TEXT("Skill"), true);
    conWork.emplace(TEXT("Field"), true);
    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Skill"), conWork);

    conWork.clear();

    conWork.emplace(TEXT("Field"), true);
    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Field"), conWork);

    conWork.clear();

    conWork.emplace(TEXT("Object"), true);
    CollsitionLayer.emplace(TEXT("Object"), conWork);

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
OBB* COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3 position, D3DXVECTOR3 axislength, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new OBB(position, axislength, layer, owner));
    return dynamic_cast<OBB*>(Collision.back());
}

/////////////////////////////////////////////
//関数名：InstantiateToSphere
//
//機能：球コリジョンの登録
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
SPHERE* COLLISIONMANAGER::InstantiateToSphere(D3DXVECTOR3 position, float radius, tstring layer, GAMEOBJECT* owner)
{
    Collision.emplace_back(new SPHERE(position, radius, layer, owner));
    return dynamic_cast<SPHERE*>(Collision.back());
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
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();
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
    //---各種宣言---//
    int nCounter;
    bool bCheck;
    bool bDestroy;
    bool bHit;

    OBB* pObb;
    SPHERE* pSphere;

    std::list<COLLISION*>::iterator itrCollision;

    //---初期化処理---//
    bDestroy = false;
    itrCollision = Collision.begin();

    //---衝突判定---//
    for (auto& itrBase = Collision.begin(); itrBase != Collision.end(); ++itrBase)
    {
        for (auto& itrOpponent = std::next(itrBase) ; itrOpponent != Collision.end(); ++itrOpponent)
        {
            //衝突レイヤー判定
            try
            {
                bCheck = CollsitionLayer.at((*itrBase)->Layer).at((*itrOpponent)->Layer);
            }
            catch(std::out_of_range&)
            {
                bCheck = CollsitionLayer.at((*itrOpponent)->Layer).at((*itrBase)->Layer);
            }
            if (!bCheck)
            {
                continue;
            }

            //OBBで確認
            pObb = dynamic_cast<OBB*>(*itrOpponent);
            if (pObb)
            {
                bHit = (*itrBase)->CheckCollisionToOBB(pObb);
            }
            else
            {
                //球で確認
                pSphere = dynamic_cast<SPHERE*>(*itrOpponent);
                if (pSphere)
                {
                    bHit = (*itrBase)->CheckCollisionToSphere(pSphere);
                }
            }
            
            //衝突リストに登録
            if (bHit)
            {
                HitList.emplace_back(*itrBase);
                HitOpponent.emplace_back(*itrOpponent);
                HitList.emplace_back(*itrOpponent);
                HitOpponent.emplace_back(*itrBase);
            }
        }
    }

    //---当たった時の処理の実行---//
    for (nCounter = 0; nCounter < HitList.size(); ++nCounter)
    {
        HitList.at(nCounter)->Owner->OnCollision(HitOpponent.at(nCounter));
    }

    //---廃棄の実行---//
    while (itrCollision != Collision.end())
    {
        for (auto& itrDestroy = DestroyCollision.begin(); itrDestroy != DestroyCollision.end(); ++itrDestroy)
        {
            //廃棄リストと照合
            if (*itrCollision == *itrDestroy)
            {
                (*itrCollision)->Owner = nullptr;
                itrCollision = Collision.erase(itrCollision);
                DestroyCollision.remove(*itrDestroy);
                bDestroy = true;
                break;
            }
        }

        //廃棄しなかったときのみインクリメント
        if (bDestroy)
        {
            bDestroy = false;
        }
        else
        {
            ++itrCollision;
        }
    }

    //---リストのクリア---//
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();
}