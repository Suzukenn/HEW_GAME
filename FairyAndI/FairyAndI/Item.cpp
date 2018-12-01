//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Item.h"
#include "SideViewCamera.h"
#include "Collision.h"
#include "ModelManager.h"

//＝＝＝定数・マクロ定義＝＝＝//

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：アイテムの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ITEM::Draw(void)
{
    //---各種宣言---//
    int nCounter;
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

    for (nCounter = 0; nCounter < (int)Model->MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //テクスチャの設定
        pDevice->SetTexture(0, *Model->Texture);

        //描画
        Model->Mesh->DrawSubset(nCounter);
    }

    //マテリアルをデフォルトに戻す
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：モデルの初期化
//
//引数：(LPCTSTR)モデルファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ITEM::Initialize(LPCTSTR modelname)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXVECTOR3 rotCamera;

    //---初期化処理---//
    Model.reset(new MODEL);

    // 位置・向きの初期設定
    Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Rotation = D3DXVECTOR3(0.0F, SIDEVIEWCAMERA::GetRotation().y - D3DX_PI * 0.5F, 0.0F);

    // Xファイルの読み込み
    hResult = MODELMANAGER::GetModel(modelname, *Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アイテムのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

	// 初期化
    Name = modelname;
    return hResult;
}

/////////////////////////////////////////////
//関数名：OnCollision
//
//機能：当たり判定時の挙動
//
//引数：(LPCTSTR)モデルファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
void ITEM::OnCollision(COLLISION* opponent)
{

}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：モデルの終了
//
//引数：(LPCTSTR)モデルファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
void ITEM::Uninitialize(void)
{
    //SAFE_RELEASE((*Model->Texture));
    //SAFE_RELEASE(Model->Mesh);
    //SAFE_RELEASE(Model->MaterialBuffer);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：モデルの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ITEM::Update(void)
{

}