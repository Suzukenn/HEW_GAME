//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "SkillFactory.h"
#include "WordMenu.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define GRAVITY 0.18F
#define JUMP 5.0F

static D3DXVECTOR3 pos;
static D3DXVECTOR3 rot;

/////////////////////////////////////////////
//関数名：PLAYER
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
PLAYER::PLAYER(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
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
    Model.Draw(mtxWorld);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：プレイヤーの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT PLAYER::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    //位置・向きの初期設定
    Transform.Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Transform.Rotation = D3DXVECTOR3(270.0F, 270.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(0.1F, 0.1F, 0.1F);
    Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = tag;

    //---モデルの読み込み---//
    hResult = Model.Initialize(TEXT("Data/Common/Model/Character/tiny_4anim.x"));
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("プレイヤーのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }
    else
    {
        Model.ChangeAnimation(0);
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Transform.Position.x + 5.0F, Transform.Position.y + 5.0F, Transform.Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Character"), this);

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
    SAFE_RELEASE(Texture);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(MaterialBuffer);

    Model.Uninitialize();

    ACTORMANAGER::Destroy(this);
    COLLISIONMANAGER::Destroy((COLLISION*)Collision);
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
    D3DXVECTOR3 vecInstancePosition;
    D3DXVECTOR2 vecStickVector;
    D3DXVECTOR3 vecCameraRotation;

    //---初期化処理---//
    Move.x = 0.0F;

    //---移動処理---//
	//カメラの向き取得
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	//重力加算
	Move.y -= GRAVITY;

    //モデル操作
    if (vecStickVector != D3DXVECTOR2(0.0F, 0.0F))
    {
        //移動
        Move.x += VALUE_MOVE_PLAYER * vecStickVector.x;

        //回転
        Transform.Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));
    }

	//ジャンプ
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
        //ジャンプ力の付与
        Move.y += JUMP;
	}

	//---位置情報更新---//
    Transform.Position += Move;

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
        vecInstancePosition.x = Transform.Position.x + sinf(D3DXToRadian(Transform.Rotation.y)) * 10.0F + cosf(D3DXToRadian(Transform.Rotation.y)) * 8.0F;
        vecInstancePosition.y = Transform.Position.y + 21.0F;
        vecInstancePosition.z = 0.0F;

        SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationItem(), vecInstancePosition, Transform.Rotation);
    }

    pos = Transform.Position;
    rot = Transform.Rotation;

    if (Move.x)
    {
        Model.ChangeAnimation(1);
    }
    else
    {
        Model.ChangeAnimation(0);
    }

    if (Move.y != 0.0F)
    {
        Model.ChangeAnimation(2);
    }

}

// モデル位置の取得
const D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return pos;
}

// モデル向きの取得
const D3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return rot;
}