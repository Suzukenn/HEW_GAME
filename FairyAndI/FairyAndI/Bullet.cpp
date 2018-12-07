//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ModelManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：BULLET
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
BULLET::BULLET(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
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
    pMatrix = (LPD3DXMATERIAL)Model->MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < (Model)->MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //テクスチャの設定
        pDevice->SetTexture(0, *Model->Texture);

        //描画
        (Model)->Mesh->DrawSubset(nCounter);
    }

    //マテリアルをデフォルトに戻す
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：弾丸の初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BULLET::Initialize(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Position = position;
    Rotation = rotation;

    Model.reset(new MODEL);

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelname, *Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("弾丸のモデルの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    Collision = COLLISIONMANAGER::InstantiateToSphere(Position + 5, 3.5F, tag, TEXT("BULLET"), this);

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
    Model->Release();
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
    Position.x += 1.0F;

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_X, TRIGGER))
    {
        ACTORMANAGER::Destroy(this);
    }
}