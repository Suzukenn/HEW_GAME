//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "EffectFactory.h"
#include "Field.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "SkillFactory.h"
#include "SoundManager.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "WordMenu.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define GRAVITY 0.018F
#define JUMP 2.0F

//＝＝＝グローバル宣言＝＝＝//
int hp;
D3DXVECTOR3 pos;
D3DXVECTOR3 rot;
PLAYERSTATE state;

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
    State = PLAYERSTATE_WAIT;
    Gray = false;
    Jump = false;
    IsGround = false;
    Vibration = 0;
    AnimationTime = 0;
    Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    VibrationPower = D3DXVECTOR2(0.0F, 0.0F);
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
	if (opponent->Owner->GetTag() == TEXT("Enemy") || opponent->Owner->GetTag() == TEXT("EnemyBullet") || opponent->Owner->GetTag() == TEXT("FireGimmick"))
	{
        Transform.Position.x -=5.0F;
        Model->ChangeAnimation(PLAYERSTATE_DAMAGE);
        --HP;
    }
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
        INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, VibrationPower.x, VibrationPower.y);
    }

    //---バイブレーション---//
    if (--Vibration <= 0)
    {
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        VibrationPower = D3DXVECTOR2(0.0F, 0.0F);
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
        if (State != PLAYERSTATE_JUMP)
        {
            State = PLAYERSTATE_FALL;
        }
    }

    //着地判定
    if (FIELD::CheckField(&D3DXVECTOR3(Transform.Position.x, Transform.Position.y - 11.0F, Transform.Position.z), &D3DXVECTOR3(0.0F, 1.0F, 0.0F), fAfterYPosition))
    {
        Transform.Position.y = fAfterYPosition + 11.0F;
        Move.y = 0.0F;
        Jump = false;
        IsGround = true;
        if (State != PLAYERSTATE_ATTACK)
        {
            State = PLAYERSTATE_WAIT;
        }
    }
    else
    {
        State = PLAYERSTATE_FALL;
        IsGround = false;
    }

    //---モデル操作---//
    //移動
    if (State != PLAYERSTATE_ATTACK && vecStickVector != D3DXVECTOR2(0.0F, 0.0F))
    {
        Move.x += VALUE_MOVE_PLAYER * vecStickVector.x;

        //向きに応じて回転
        Transform.Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));

        if (IsGround)
        {
            State = PLAYERSTATE_WALK;
        }
        if (!SOUNDMANAGER::CheckPlay(TEXT("SE_PLAYER_WALK")))
        {
            SOUNDMANAGER::Play(TEXT("SE_PLAYER_WALK"));
        }
    }
    
    else
    {
        SOUNDMANAGER::Stop(TEXT("SE_PLAYER_WALK"));
    }

	//ジャンプ
    if (!Jump && State != PLAYERSTATE_ATTACK)
    {
        if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
        {
            Move.y += JUMP;
            Jump = true;
            IsGround = false;
            AnimationTime = 50;
            State = PLAYERSTATE_JUMP;
        }
    }
    if (State == PLAYERSTATE_JUMP)
    {
        if (!--AnimationTime)
        {
            State = PLAYERSTATE_FALL;
        }
    }


	//---位置情報更新---//
    //移動を反映
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
	else if (Transform.Position.x < 50.0F)
	{
        Transform.Position.x = 50.0F;
	}

    //---スキル生成---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        if (IsGround)
        {
           State = PLAYERSTATE_ATTACK;
           AnimationTime = 130;
        }
    }

    //攻撃
    if (State == PLAYERSTATE_ATTACK)
    {
        Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
        --AnimationTime;

        //ラスト30フレームでスキル・エフェクト生成
        if (AnimationTime == 70)
        {
            vecInstancePosition.x = Transform.Position.x + sinf(D3DXToRadian(Transform.Rotation.y)) * 4.0F + cosf(D3DXToRadian(Transform.Rotation.y));
            vecInstancePosition.y = Transform.Position.y + 5.0F;
            vecInstancePosition.z = 0.0F;

            SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationAdjective(), WORDMENU::NotificationNoun(), vecInstancePosition, Transform.Rotation);
            EFFECTFACTORY::InstantiateSkillEffect(vecInstancePosition, D3DXVECTOR2(5.0F, 5.0F), false);
            VibrationPower = D3DXVECTOR2(0.4F, 0.4F);
            INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, VibrationPower.x, VibrationPower.y);
            Vibration = 30;

            SOUNDMANAGER::Stop(tstring(TEXT("SE_SKILL_TYPE") + WORDMENU::NotificationNoun()).data());
            SOUNDMANAGER::Play(tstring(TEXT("SE_SKILL_TYPE") + WORDMENU::NotificationNoun()).data());
        }

        //0フレームで待機に移行
        else if (!AnimationTime)
        {
            State = PLAYERSTATE_WAIT;
        }
    }

    Model->ChangeAnimation(State);

    hp = HP;
    pos = Transform.Position;
    rot = Transform.Rotation;
    state = State;
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

/////////////////////////////////////////////
//関数名：GetPlayerPosition
//
//機能：プレイヤーの位置の取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return pos;
}

/////////////////////////////////////////////
//関数名：GetPlayerRotation
//
//機能：プレイヤーの向きの取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
D3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return rot;
}

/////////////////////////////////////////////
//関数名：GetPlayerState
//
//機能：プレイヤーのステートの取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
PLAYERSTATE PLAYER::GetPlayerState(void)
{
    return state;
}
