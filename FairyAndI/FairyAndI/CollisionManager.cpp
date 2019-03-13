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
    std::unordered_map<tstring, bool>conWork;

    //---初期化処理---//
    Collision.clear();
    DestroyCollision.clear();
    HitList.clear();
    HitOpponent.clear();

    //---衝突レイヤーの設定---//
    //プレイヤー
    conWork.emplace(TEXT("Player"), false);
    conWork.emplace(TEXT("Fairy"), false);
    conWork.emplace(TEXT("Skill"), false);
    conWork.emplace(TEXT("Wall"), true);
    conWork.emplace(TEXT("Enemy"), true);
    conWork.emplace(TEXT("EnemyBullet"), true);
    conWork.emplace(TEXT("Battery"), true);
    conWork.emplace(TEXT("BatteryCannon"), true);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Player"), conWork);
    conWork.clear();

    //フェアリー
    conWork.emplace(TEXT("Fairy"), false);
    conWork.emplace(TEXT("Skill"), false);
    conWork.emplace(TEXT("Wall"), false);
    conWork.emplace(TEXT("Enemy"), false);
    conWork.emplace(TEXT("EnemyBullet"), false);
    conWork.emplace(TEXT("Battery"), false);
    conWork.emplace(TEXT("BatteryCannon"), false);
    conWork.emplace(TEXT("Gimmick"), false);
    conWork.emplace(TEXT("Item"), true);
    CollsitionLayer.emplace(TEXT("Fairy"), conWork);
    conWork.clear();

    //スキル
    conWork.emplace(TEXT("Skill"), false);
    conWork.emplace(TEXT("Wall"), true);
    conWork.emplace(TEXT("Enemy"), true);
    conWork.emplace(TEXT("EnemyBullet"), false);
    conWork.emplace(TEXT("Battery"), true);
    conWork.emplace(TEXT("BatteryCannon"), false);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Skill"), conWork);
    conWork.clear();

    //スキルの壁
    conWork.emplace(TEXT("Wall"), true);
    conWork.emplace(TEXT("Enemy"), true);
    conWork.emplace(TEXT("EnemyBullet"), true);
    conWork.emplace(TEXT("Battery"), true);
    conWork.emplace(TEXT("BatteryCannon"), true);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Wall"), conWork);
    conWork.clear();

    //敵
    conWork.emplace(TEXT("Enemy"), false);
    conWork.emplace(TEXT("EnemyBullet"), false);
    conWork.emplace(TEXT("Battery"), true);
    conWork.emplace(TEXT("BatteryCannon"), false);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Enemy"), conWork);
    conWork.clear();

    //敵弾
    conWork.emplace(TEXT("EnemyBullet"), false);
    conWork.emplace(TEXT("Battery"), true);
    conWork.emplace(TEXT("BatteryCannon"), false);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("EnemyBullet"), conWork);
    conWork.clear();

    //砲台
    conWork.emplace(TEXT("Battery"), false);
    conWork.emplace(TEXT("BatteryCannon"), true);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Battery"), conWork);
    conWork.clear();

    //砲弾
    conWork.emplace(TEXT("BatteryCannon"), false);
    conWork.emplace(TEXT("Gimmick"), true);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("BatteryCannon"), conWork);
    conWork.clear();

    //ギミック
    conWork.emplace(TEXT("Gimmick"), false);
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Gimmick"), conWork);
    conWork.clear();

    //アイテム
    conWork.emplace(TEXT("Item"), false);
    CollsitionLayer.emplace(TEXT("Item"), conWork);

    return S_OK;
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
    bHit = false;
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

			//球で確認
			pSphere = dynamic_cast<SPHERE*>(*itrOpponent);
			if (pSphere)
			{
				bHit = (*itrBase)->CheckCollisionToSphere(pSphere);
			}
            else
            {
				//OBBで確認
				pObb = dynamic_cast<OBB*>(*itrOpponent);
				if (pObb)
				{
					bHit = (*itrBase)->CheckCollisionToOBB(pObb);
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