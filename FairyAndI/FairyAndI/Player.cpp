//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
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
    DWORD nCounter;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    //---初期化処理---//
    pDevice = GetDevice();

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //回転を反映
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //移動を反映
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //設定
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // 現在のマテリアルを取得
    pDevice->GetMaterial(&matDef);

    //---描画---//
    //ポインタを取得
    pMatrix = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //テクスチャの設定
        pDevice->SetTexture(0, Texture);

        //描画
        Mesh->DrawSubset(nCounter);
    }

    //マテリアルをデフォルトに戻す
    pDevice->SetMaterial(&matDef);
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
	Rotation = D3DXVECTOR3(0.0F, SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F, 0.0F);
	Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);

    //Xファイルの読み込み
    hResult = D3DXLoadMeshFromX(TEXT("Data/Common/Model/Character/car000.x"), D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("プレイヤーのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}
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
    D3DXVECTOR3 vecCameraRotation;
    D3DXVECTOR2 StickPoints;

    //---移動処理---//
	//カメラの向き取得
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    StickPoints = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	//重力加算
	Move.y -= GRAVITY;

	//移動
	Position.x += sinf(vecCameraRotation.y + D3DX_PI * 0.5F) * VALUE_MOVE_PLAYER * StickPoints.x;
    Position.z += cosf(vecCameraRotation.y + D3DX_PI * 0.5F) * VALUE_MOVE_PLAYER * StickPoints.y;

    //回転
    Rotation.y = vecCameraRotation.y - D3DX_PI * 0.5F * StickPoints.x;

	//ジャンプ
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
        Move.y += JUMP;
	}

	//---位置情報更新---//
    Position.y += Move.y;

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
        ACTORMANAGER::Instantiate(WORDMENU::NotificationItem(), Position, Rotation);
    }
    pos = Position;
    rot = Rotation;
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