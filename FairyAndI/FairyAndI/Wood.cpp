//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Skill.h"
#include "Sphere.h"
#include "Wood.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define VISIBILITY 50.0F

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：WOOD
//
//機能：コンストラクタ
//
//引数：(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
WOOD::WOOD(tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(tag, position, rotation);
}

/////////////////////////////////////////////
//関数名：~WOOD
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
WOOD::~WOOD(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：木のオバケの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WOOD::Draw(void)
{
    ENEMY::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：木のオバケの初期化
//
//引数：(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WOOD::Initialize(tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = ENEMY::Initialize(TEXT("WOOD"), tag, position, rotation, D3DXVECTOR3(300.0F, 300.0F, 300.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("木のオバケの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    State = WOODSTATE_WAIT;

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Character"), this);

    return hResult;
}

/////////////////////////////////////////////
//関数名：OnCollision
//
//機能：当たり判定反応時の挙動
//
//引数：(COLLISITON)相手
//
//戻り値：なし
/////////////////////////////////////////////
void WOOD::OnCollision(COLLISION* opponent)
{
    SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
    if (Skill)
    {
        if (Skill->GetType() == TEXT("HOT") || Skill->GetType() == TEXT("COLD"))
        {
            ACTORMANAGER::Destroy(this);
            COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        }
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：木のオバケの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WOOD::Uninitialize(void)
{
    //---開放---//
    ENEMY::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：木のオバケの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WOOD::Update(void)
{
    //---各種宣言---//
    D3DXVECTOR3 PlayerPosition;
    static int nAttackCount;

    //---初期化処理---//
    PlayerPosition = PLAYER::GetPlayerPosition();

    switch (State)
    {
        case WOODSTATE_WAIT:

            if (AttackCool)
            {
                --AttackCool;
            }

            //---敵の索敵---//
            if (ENEMY::SearchTarget(PlayerPosition, VISIBILITY))
            {
                if (!AttackCool)
                {
                    State = WOODSTATE_ATTACK;
                }
            }
            break;

        case WOODSTATE_ATTACK:
            Model->ChangeAnimation(WOODSTATE_ATTACK);
            if (++nAttackCount > 60)
            {
                //攻撃
            
                Model->ChangeAnimation(WOODSTATE_WAIT);
                AttackCool = 120;
                State = WOODSTATE_WAIT;
            }
            break;

        default:
            break;
    }

    ENEMY::Update();
}