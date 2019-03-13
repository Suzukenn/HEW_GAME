//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "Player.h"
#include "Skill.h"
#include "Slime.h"
#include "Sphere.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define VISIBILITY 50.0F

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：SLIME
//
//機能：コンストラクタ
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
SLIME::SLIME(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(position, rotation);
}

/////////////////////////////////////////////
//関数名：~SLIME
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
SLIME::~SLIME(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：敵の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SLIME::Draw(void)
{
    //---各種宣言---//
    D3DXMATRIX mtxWorld;

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);

    //---描画---//
    Model->Draw(mtxWorld, false);

    //ENEMY::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：敵の初期化
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SLIME::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    //初期設定
    hResult = ENEMY::Initialize(TEXT("SLIME"), TEXT("Slime"), position, rotation, D3DXVECTOR3(450.0F, 450.0F, 450.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("スライムの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    InitialPosition = position;
    Move = D3DXVECTOR3(-0.1F, 0.0F, 0.0F);

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Enemy"), this);

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
void SLIME::OnCollision(COLLISION* opponent)
{
    SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
    if (Skill)
    {
        if (Skill->GetType() == TEXT("COLD"))
        {
            ACTORMANAGER::Destroy(this);
            COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        }
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：敵の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SLIME::Uninitialize(void)
{
    //---開放---//
    ENEMY::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：敵の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SLIME::Update(void)
{
    //---各種宣言---//
    D3DXVECTOR3 PlayerPosition;
    static int nStopCount;	//端で少し止まる用
    static int nAttackCount;

    //---初期化処理---//
    PlayerPosition = PLAYER::GetPlayerPosition();

    switch (State)
    {
        case SLIMESTATE_MOVE:
            //---徘徊---//
            if (fabsf(Transform.Position.x - InitialPosition.x) >= 100.0F)
            {
                //2秒止まる
                if (++nStopCount > 120)
                {
                    Transform.Rotation.y = -Transform.Rotation.y;
                    Move.x = -Move.x;
                    nStopCount = 0;
                }
            }
            else
            {
                Transform.Position += Move;
                Collision->Position = Transform.Position;
            }

            //---敵の索敵---//
            if (ENEMY::SearchTarget(PlayerPosition, VISIBILITY))
            {
                if (AttackCool)
                {
                    --AttackCool;
                }
                else
                {
                    State = SLIMESTATE_ATTACK;
                }
            }
            break;

        case SLIMESTATE_ATTACK:

            //---視程内なら攻撃、そうでなければ徘徊を再開する---//
            Model->ChangeAnimation(SLIMESTATE_ATTACK);
            if (++nAttackCount > 60)
            {
                //攻撃
                OBJECTFACTORY::InstantiateSlimeBullet(Transform.Position, Transform.Rotation);
                Model->ChangeAnimation(SLIMESTATE_MOVE);
                AttackCool = 120;
                nAttackCount = 0;
                State = SLIMESTATE_MOVE;
            }
            break;

            default:
                break;
    }

    ENEMY::Update();
}