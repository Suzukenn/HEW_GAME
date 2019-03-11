//＝＝＝ヘッダファイル読み込＝＝＝//
#include "Fairy.h"
#include "InputManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "SquareGauge.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define	CAM_POS_P_X			(0.0f)					// カメラの視点初期位置(X座標)
#define	CAM_POS_P_Y			(10.0f)				// カメラの視点初期位置(Y座標)
#define	CAM_POS_P_Z			(-100.0f)				// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X			(0.0f)					// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y			(50.0f)					// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z			(0.0f)					// カメラの注視点初期位置(Z座標)
#define CAM_MAX_WID			1400.0F
#define CAM_MIN_WID			-1400.F

//＝＝＝グローバル宣言＝＝＝//
D3DXVECTOR3 SIDEVIEWCAMERA::Position;
D3DXVECTOR3 SIDEVIEWCAMERA::Rotation;
D3DXVECTOR3	SIDEVIEWCAMERA::ReversoPoint;
D3DXVECTOR3 SIDEVIEWCAMERA::UpVector;
float SIDEVIEWCAMERA::Interval;
D3DXMATRIX SIDEVIEWCAMERA::ViewMatrix;
D3DXMATRIX SIDEVIEWCAMERA::ProjectionMatrix;
bool SIDEVIEWCAMERA::PositionPlace;

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：カメラの初期化
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)注視点
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SIDEVIEWCAMERA::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 reverso)
{
    //---各種宣言---//
    float fVectorX;
    float fVectorZ;

    Position = position;
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    ReversoPoint = reverso;
    UpVector = D3DXVECTOR3(0.0F, 1.0F, 0.0F);
    PositionPlace = false;

    fVectorX = Position.x - ReversoPoint.x;
    fVectorZ = Position.z - ReversoPoint.z;
    Interval = sqrtf(fVectorX * fVectorX + fVectorZ * fVectorZ);

	return S_OK;
}

/////////////////////////////////////////////
//関数名：SetCamera
//
//機能：カメラの設定
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SIDEVIEWCAMERA::SetCamera(void)
{
    //---各種宣言---//
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---ビューマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&ViewMatrix);

    //作成
    D3DXMatrixLookAtLH(&ViewMatrix, &Position, &ReversoPoint, &UpVector);

    //設定
    hResult = pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("サイドビューカメラのビューマトリクスの設定に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---プロジェクションマトリックス設定---//
    //初期化
    D3DXMatrixIdentity(&ProjectionMatrix);

    //作成
    D3DXMatrixPerspectiveFovLH(&ProjectionMatrix, D3DXToRadian(45.0F), SCREEN_WIDTH / SCREEN_HEIGHT, 10.0F, 1000.0F);

    //設定
    hResult = pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("サイドビューカメラのプロジェクションマトリクスの設定に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    return hResult;
}
/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：カメラの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SIDEVIEWCAMERA::Uninitialize(void)
{

}

/////////////////////////////////////////////
//関数名：Update
//
//機能：カメラの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SIDEVIEWCAMERA::Update(D3DXVECTOR3 player)
{
    //---各種宣言---//
    float fStickVector;
    static bool Mode;
    D3DXVECTOR3 FairyPosition;

    FairyPosition = FAIRY::GetFairyPosition();
    Mode = SQUAREGAUGE::GetFairyTime();

    //---移動処理---//
    //カメラの向き取得
    fStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT).x;

    //端にいるかの判定判定
    if (player.x >= Position.x && Position.x >= CAM_MAX_WID || player.x <= Position.x && Position.x <= CAM_MIN_WID)
    {
        PositionPlace = true;
    }
    //原点より右にいてプレイヤーがカメラpos以下になる、または原点より左にいてプレイヤーがカメラpos以上になったら
    else if (player.x < Position.x && Position.x > 0.0F || player.x > Position.x && Position.x < 0.0F)
    {
        PositionPlace = false;
    }

    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
    Mode = !Mode;
    }
    else if (SQUAREGAUGE::GetFairyTime() == false)
    {
    Mode = false;
    }*/

    if (!PositionPlace)
    {
        //プレイヤーを真ん中にして追いかける処理
        Position = D3DXVECTOR3(player.x, 60.0F, player.z - 100.0F);
        ReversoPoint = D3DXVECTOR3(player.x, 30.0F, player.z);
    }
    else
    {
        //スクロール処理
        Position.x += VALUE_MOVE_PLAYER * fStickVector * 0.5F;
        ReversoPoint = D3DXVECTOR3(Position.x, 30.0F, player.z);
    }

    if (Mode)
    {
        Position = D3DXVECTOR3(FairyPosition.x, FairyPosition.y + 10.0F, FairyPosition.z - 50.0F);
        ReversoPoint = D3DXVECTOR3(FairyPosition.x, FairyPosition.y + 10.0F, FairyPosition.z);
    }

    //カメラの移動制限
    if (Position.x > CAM_MAX_WID)
    {
        Position.x = CAM_MAX_WID;
        ReversoPoint.x = CAM_MAX_WID;
    }
    if (Position.x < CAM_MIN_WID)
    {
        Position.x = CAM_MIN_WID;
        ReversoPoint.x = CAM_MIN_WID;
    }

    SetCamera();
}

/////////////////////////////////////////////
//関数名：GetRotation
//
//機能：カメラの回転の取得
//
//引数：なし
//
//戻り値：(D3DXVECTOR3)回転
/////////////////////////////////////////////
D3DXVECTOR3 SIDEVIEWCAMERA::GetRotation(void)
{
	return Rotation;
}

/////////////////////////////////////////////
//関数名：GetProjectionMatrix
//
//機能：カメラのプロジェクションマトリクスの取得
//
//引数：(LPD3DXMATRIX)格納マトリクス
//
//戻り値：なし
/////////////////////////////////////////////
void SIDEVIEWCAMERA::GetProjectionMatrix(LPD3DXMATRIX projectionmatrix)
{
    if (projectionmatrix)
    {
        *projectionmatrix = ProjectionMatrix;
    }
    else
    {
        projectionmatrix = nullptr;
    }
}

/////////////////////////////////////////////
//関数名：GetViewMatrix
//
//機能：カメラのビューマトリクスの取得
//
//引数：(LPD3DXMATRIX)格納マトリクス
//
//戻り値：なし
/////////////////////////////////////////////
void SIDEVIEWCAMERA::GetViewMatrix(LPD3DXMATRIX viewmatrix)
{
    if (viewmatrix)
    {
        *viewmatrix = ViewMatrix;
    }
    else
    {
        viewmatrix = nullptr;
    }
}