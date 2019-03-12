//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "EffectFactory.h"
#include "Fade.h"
#include "Field.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "SideViewCamera.h"
#include "SkillFactory.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "WordMenu.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define GRAVITY 0.18F
#define JUMP 3.0F

//＝＝＝列挙型定義＝＝＝//
enum
{
    STATE_WAIT,
    STATE_WALK,
    STATE_RUN,
    STATE_JUMP,
    STATE_FALL,
    STATE_ATTACK,
    STATE_DAMAGE
};

//＝＝＝グローバル宣言＝＝＝//
int hp;
D3DXVECTOR3 pos;
D3DXVECTOR3 rot;

/////////////////////////////////////////////
//関数名：PLAYER
//
//機能：コンストラクタ
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
PLAYER::PLAYER(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(position, rotation);
}

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：プレイヤーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void PLAYER::Draw(void)
{
    //---各種宣言---//
    D3DXMATRIX mtxWorld;

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);

    //---描画---//
    Model->Draw(mtxWorld, Gray);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：プレイヤーの初期化
//
//引数：((D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT PLAYER::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(100.0F, 100.0F, 100.0F);
    HP = MAX_PLAYER_HP;
    State = STATE_WAIT;
    Gray = false;
    Jump = false;
    IsGround = true;
    Vibration = 0;
    Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = TEXT("Player");

    //---モデルの読み込み---//
    hResult = ANIMATIONMODELMANAGER::GetModel(TEXT("PLAYER"), Model);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("プレイヤーのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }
    else
    {
        Model->ChangeAnimation(State);
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Player"), this);

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
void PLAYER::OnCollision(COLLISION* opponent)
{
	/*if (opponent->Owner->GetTag() == TEXT("Goal"))
	{
		FADE::SetFade(FADE_OUT);
		Goal = true;
	}*/
    //Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：プレイヤーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void PLAYER::Uninitialize(void)
{
    Model->Uninitialize();

    ACTORMANAGER::Destroy(this);

    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：プレイヤーの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void PLAYER::Update(void)
{
    //---各種宣言---//
    float fAfterYPosition;
    D3DXVECTOR3 vecInstancePosition;
    D3DXVECTOR2 vecStickVector;
    D3DXVECTOR3 vecCameraRotation;
    static D3DXVECTOR2 vecVibration;

    //---初期化処理---//
    Move.x = 0.0F;

    //---フリーズ判定---//
	Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        Model->SetSpeed(0.0);
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        return;
    }
    else
    {
        Model->SetSpeed(1.0);
        INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, vecVibration.x, vecVibration.y);
    }

    //---バイブレーション---//
    if (--Vibration <= 0)
    {
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        vecVibration = D3DXVECTOR2(0.0F, 0.0F);
        Vibration = 0;
    }

    //---移動処理---//
	//カメラの向き取得
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	//重力加算
    if (!IsGround)
    {
        Move.y -= GRAVITY;
    }

    //着地判定
    if (FIELD::CheckField(&D3DXVECTOR3(Transform.Position.x, Transform.Position.y - 10.8F, Transform.Position.z), &D3DXVECTOR3(0.0F, 1.0F, 0.0F), fAfterYPosition))
    {
        Transform.Position.y = fAfterYPosition + 10.8F;
        Move.y = 0.0F;
        Jump = false;
        IsGround = true;
    }
    else
    {
        IsGround = false;
    }



    //モデル操作
    if (vecStickVector != D3DXVECTOR2(0.0F, 0.0F))
    {
        //移動
        Move.x += VALUE_MOVE_PLAYER * vecStickVector.x;

        //回転
        Transform.Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));
    }

	//ジャンプ
    if (!Jump)
    {
        if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
        {
            //ジャンプ力の付与
            Move.y += JUMP;
            Jump = true;
            IsGround = false;
        }
    }

	//---位置情報更新---//
    Transform.Position += Move;
	Collision->Position = Transform.Position;

	//移動制限
	if (Transform.Position.y < 0.0F)
	{
        Transform.Position.y = 0.0F;
		Move.y = 0.0F;
	}
	if (Transform.Position.x > 1500.0F)
	{
        Transform.Position.x = 1500.0F;
	}
	else if (Transform.Position.x < -1500.0F)
	{
        Transform.Position.x = -1500.0F;
	}

    //---アイテム生成---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        vecInstancePosition.x = Transform.Position.x + sinf(D3DXToRadian(Transform.Rotation.y)) + cosf(D3DXToRadian(Transform.Rotation.y));
        vecInstancePosition.y = Transform.Position.y + 10.0F;
        vecInstancePosition.z = 0.0F;

        SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationAdjective(), WORDMENU::NotificationNoun(), vecInstancePosition, Transform.Rotation);
        EFFECTFACTORY::InstantiateSkillEffect(vecInstancePosition, D3DXVECTOR2(10.0F, 10.0F), false);
        vecVibration = D3DXVECTOR2(0.5F, 0.5F);
        INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, vecVibration.x, vecVibration.y);
        Vibration = 100;
    }

    hp = HP;
    pos = Transform.Position;
    rot = Transform.Rotation;

    if (Move.x)
    {
        State = STATE_WALK;
    }
    else
    {
        State = STATE_WAIT;
    }

    if (Move.y != 0.0F)
    {
        State = STATE_WAIT;
    }
    Model->ChangeAnimation(State);

}

/////////////////////////////////////////////
//関数名：GetPlayerHP
//
//機能：プレイヤーの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
int PLAYER::GetPlayerHP(void)
{
    return hp;
}

// モデル位置の取得
D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return pos;
}

// モデル向きの取得
D3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return rot;
}