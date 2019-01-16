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
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxScale;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //大きさを設定
    D3DXMatrixScaling(&mtxScale, 0.1F, 0.1F, 0.1F);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

    //回転を反映
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //移動を反映
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //設定
    GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

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
    Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Rotation = D3DXVECTOR3(270.0F, 270.0F, 0.0F);
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
    //Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Position.x + 5.0F, Position.y + 5.0F, Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Character"), this);

    return S_OK;// hResult;
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
    DWORD dwAnime;
    bool bMove;

    //---初期化処理---//
    Move.x = 0.0F;
    Move.z = 0.0F;
    bMove = false;

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
        Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));

        bMove = true;
    }

	//ジャンプ
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
        //ジャンプ力の付与
        Move.y += JUMP;
	}

	//---位置情報更新---//
    Position += Move;

	//移動制限
	if (Position.y < 0.0F)
	{
        Position.y = 0.0F;
		Move.y = 0.0F;
	}
	if (Position.x > 1500.0F)
	{
        Position.x = 1500.0F;
	}
	else if (Position.x < -1500.0F)
	{
        Position.x = -1500.0F;
	}

    //---アイテム生成---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        vecInstancePosition.x = Position.x - sinf(Rotation.y) * 10.0F - cosf(Rotation.y) * 8.0F;
        vecInstancePosition.y = Position.y + 21.0F;
        vecInstancePosition.z = 0.0F;

        SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationItem(), vecInstancePosition, Rotation);
    }

    pos = Position;
    rot = Rotation;

    if (Move.y != 0.0F)
    {
        dwAnime = 2;
        Model.ChangeAnimation(dwAnime);

    }
    else
    {
        if (bMove)
        {
            dwAnime = 1;
            Model.ChangeAnimation(dwAnime);

        }
        else
        {
            dwAnime = 0;
            Model.ChangeAnimation(dwAnime);
        }
    }

    if (INPUTMANAGER::GetKey(DIK_0, TRIGGER))
    {
        Model.ChangeAnimation(0);
    }
    else if (INPUTMANAGER::GetKey(DIK_1, TRIGGER))
    {
        Model.ChangeAnimation(1);
    }
    else if (INPUTMANAGER::GetKey(DIK_2, TRIGGER))
    {
        Model.ChangeAnimation(2);
    }
    else if (INPUTMANAGER::GetKey(DIK_3, TRIGGER))
    {
        Model.ChangeAnimation(3);
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