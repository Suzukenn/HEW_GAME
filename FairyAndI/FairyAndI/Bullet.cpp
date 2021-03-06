//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "Texture.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：BULLET
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
BULLET::BULLET(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//関数名：~BULLET
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
BULLET::~BULLET(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：弾丸の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BULLET::Draw(void)
{
    BillBoard.Draw(Transform.Position);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：弾丸の初期化
//
//引数：(LPCTSTR)テクスチャ名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BULLET::Initialize(LPCTSTR texturename, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Move = D3DXVECTOR3(sinf(Transform.Rotation.y) * 1.5F, 0.0F, 0.0F);
	Tag = TEXT("Bullet");
	Type = type;

    //---ビルボードの作成---//
    hResult = BillBoard.Initialize(texturename, D3DXVECTOR2(5.0F, 5.0F), Transform.Rotation.y > 0.0F);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("弾の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.5F, TEXT("Skill"), this);

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
void BULLET::OnCollision(COLLISION* opponent)
{
	ACTORMANAGER::Destroy(this);
	COLLISIONMANAGER::Destroy((COLLISION*)Collision);
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：弾丸の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BULLET::Uninitialize(void)
{
    //---開放---//
    BillBoard.Uninitialize();
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：弾丸の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BULLET::Update(void)
{
    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/

	Gray = SQUAREGAUGE::GetFairyTime();
    BillBoard.Update();

    if (Gray)
    {
        return;
    }

    ++BornTime;
    if (BornTime > 120)
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
    else
    {
        Transform.Position += Move;
        Collision->Position = Transform.Position;
    }
}