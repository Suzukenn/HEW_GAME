//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Debug.h"
#include "FlexibleCamera.h"
#include "InputManager.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define MOVE_VALUE 2.0F
#define ROTATE_VALUE (D3DX_PI * 0.01F)

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：カメラの初期化
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)注視点
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FLEXIBLECAMERA::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 reverso)
{
    //---各種宣言---//
    float fVectorX;
    float fVectorZ;

    //---初期化処理---//
    Position = position;
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    ReversoPoint = reverso;
    UpVector = D3DXVECTOR3(0.0F, 1.0F, 0.0F);

    fVectorX = Position.x - ReversoPoint.x;
    fVectorZ = Position.z - ReversoPoint.z;
    Interval = sqrtf(fVectorX * fVectorX + fVectorZ * fVectorZ);

    return S_OK;
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
void FLEXIBLECAMERA::Uninitialize(void)
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
void FLEXIBLECAMERA::Update(void)
{
    //---操作---//
    //左移動   
    if (INPUTMANAGER::GetKey(DIK_A, HOLD))
    {
        if (INPUTMANAGER::GetKey(DIK_W, HOLD))
        {
            Position.x -= cosf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z += sinf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else if (INPUTMANAGER::GetKey(DIK_S, HOLD))
        {
            Position.x -= cosf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z += sinf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else
        {
            Position.x -= cosf(Rotation.y) * MOVE_VALUE;
            Position.z += sinf(Rotation.y) * MOVE_VALUE;
        }

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //右移動
    else if (INPUTMANAGER::GetKey(DIK_D, HOLD))
    {
        if (INPUTMANAGER::GetKey(DIK_W, HOLD))
        {
            Position.x += cosf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z -= sinf(Rotation.y - D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else if (INPUTMANAGER::GetKey(DIK_S, HOLD))
        {
            Position.x += cosf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
            Position.z -= sinf(Rotation.y + D3DX_PI * 0.25F) * MOVE_VALUE;
        }
        else
        {
            Position.x += cosf(Rotation.y) * MOVE_VALUE;
            Position.z -= sinf(Rotation.y) * MOVE_VALUE;
        }

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //前移動
    if (INPUTMANAGER::GetKey(DIK_W, HOLD))
    {
        Position.x += sinf(Rotation.y) * MOVE_VALUE;
        Position.z += cosf(Rotation.y) * MOVE_VALUE;

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //後移動
    else if (INPUTMANAGER::GetKey(DIK_S, HOLD))
    {
        Position.x -= sinf(Rotation.y) * MOVE_VALUE;
        Position.z -= cosf(Rotation.y) * MOVE_VALUE;

        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //左旋回
    if (INPUTMANAGER::GetKey(DIK_Z, HOLD))
    {
        Rotation.y += ROTATE_VALUE;
        if (Rotation.y > D3DX_PI)
        {
            Rotation.y -= D3DX_PI * 2.0F;
        }
        Position.x = ReversoPoint.x - sinf(Rotation.y) * Interval;
        Position.z = ReversoPoint.z - cosf(Rotation.y) * Interval;
    }

    //右旋回
    else if (INPUTMANAGER::GetKey(DIK_C, HOLD))
    {
        Rotation.y -= ROTATE_VALUE;
        if (Rotation.y < -D3DX_PI)
        {
            Rotation.y += D3DX_PI * 2.0F;
        }
        Position.x = ReversoPoint.x - sinf(Rotation.y) * Interval;
        Position.z = ReversoPoint.z - cosf(Rotation.y) * Interval;
    }

    //視点上昇
    if (INPUTMANAGER::GetKey(DIK_Y, HOLD))
    {
        Position.y += MOVE_VALUE;
    }

    //視点下降
    else if (INPUTMANAGER::GetKey(DIK_N, HOLD))
    {
        Position.y -= MOVE_VALUE;
    }

    //注視点左旋回
    if (INPUTMANAGER::GetKey(DIK_Q, HOLD))
    {
        Rotation.y -= ROTATE_VALUE;
        if (Rotation.y < -D3DX_PI)
        {
            Rotation.y += D3DX_PI * 2.0F;
        }
        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //注視点右旋回
    else if (INPUTMANAGER::GetKey(DIK_E, HOLD))
    {
        Rotation.y += ROTATE_VALUE;
        if (Rotation.y > D3DX_PI)
        {
            Rotation.y -= D3DX_PI * 2.0F;
        }
        ReversoPoint.x = Position.x + sinf(Rotation.y) * Interval;
        ReversoPoint.z = Position.z + cosf(Rotation.y) * Interval;
    }

    //注視点上昇
    if (INPUTMANAGER::GetKey(DIK_T, HOLD))
    {
        ReversoPoint.y += MOVE_VALUE;
    }

    //注視点下降
    else if (INPUTMANAGER::GetKey(DIK_B, HOLD))
    {
        ReversoPoint.y -= MOVE_VALUE;
    }

    //リセット
    if (INPUTMANAGER::GetKey(DIK_L, TRIGGER))
    {
        Position = D3DXVECTOR3(0.0F, 100.0F, -200.0F);
        ReversoPoint = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
        Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    }

    SetCamera();

#ifdef _DEBUG
    //---デバッグ表示---//
    //DEBUG::PrintDebugData(TEXT("[カメラの視点　：(%f：%f：%f)]\n"), Position.x, Position.y, Position.z);
    //DEBUG::PrintDebugData(TEXT("[カメラの注視点：(%f：%f：%f)]\n"), ReversoPoint.x, ReversoPoint.y, ReversoPoint.z);
    //DEBUG::PrintDebugData(TEXT("[カメラの向き　：(%f)]\n"), Rotation.y);
    //DEBUG::PrintDebugData(TEXT("\n"));
    //DEBUG::PrintDebugData(TEXT("***視点操作***\n"));
    //DEBUG::PrintDebugData(TEXT("前移動：W\n"));
    //DEBUG::PrintDebugData(TEXT("後移動：S\n"));
    //DEBUG::PrintDebugData(TEXT("左移動：A\n"));
    //DEBUG::PrintDebugData(TEXT("右移動：D\n"));
    //DEBUG::PrintDebugData(TEXT("***位置操作***\n"));
    //DEBUG::PrintDebugData(TEXT("上移動：Y\n"));
    //DEBUG::PrintDebugData(TEXT("下移動：N\n"));
    //DEBUG::PrintDebugData(TEXT("左旋回：Z\n"));
    //DEBUG::PrintDebugData(TEXT("右旋回：C\n"));
    //DEBUG::PrintDebugData(TEXT("***注視点操作***\n"));
    //DEBUG::PrintDebugData(TEXT("上移動：T\n"));
    //DEBUG::PrintDebugData(TEXT("下移動：B\n"));
    //DEBUG::PrintDebugData(TEXT("左旋回：Q\n"));
    //DEBUG::PrintDebugData(TEXT("右旋回：E\n"));
#endif
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
HRESULT FLEXIBLECAMERA::SetCamera(void)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXMATRIX mtxView;					// ビューマトリックス
    D3DXMATRIX mtxProjection;			// プロジェクションマトリックス
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---ビューマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxView);

    //作成
    D3DXMatrixLookAtLH(&mtxView, &Position, &ReversoPoint, &UpVector);

    //設定
    hResult = pDevice->SetTransform(D3DTS_VIEW, &mtxView);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("カメラのビューマトリクスの設定に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---プロジェクションマトリックス設定---//
    //初期化
    D3DXMatrixIdentity(&mtxProjection);

    //作成
    D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45.0F), SCREEN_WIDTH / SCREEN_HEIGHT, 10.0F, 1000.0F);

    //設定
    hResult = pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("カメラのプロジェクションマトリクスの設定に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    return hResult;
}