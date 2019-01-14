//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Element.h"
#include "ModelManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：ELEMENT
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タイプ,(D3DXVECTOR3)位置
//
//戻り値：なし
/////////////////////////////////////////////
ELEMENT::ELEMENT(LPCTSTR modelname, tstring type, D3DXVECTOR3 position)
{
    Initialize(modelname, type, position);
}

/////////////////////////////////////////////
//関数名：~ELEMENT
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
ELEMENT::~ELEMENT(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：アイテムの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ELEMENT::Draw(void)
{
    //---各種宣言---//
    DWORD nCounter;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    std::shared_ptr<MODEL> pModel;

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

    //---描画---//
    //描画対象チェック
    pModel = Model.lock();
    if (!pModel)
    {
        MessageBox(nullptr, TEXT("弾丸のモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return;
    }

    // 現在のマテリアルを取得
    pDevice->GetMaterial(&matDef);

    //ポインタを取得
    pMatrix = (LPD3DXMATERIAL)pModel->MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < pModel->MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //テクスチャの設定
        pDevice->SetTexture(0, *pModel->Texture);

        //描画
        pModel->Mesh->DrawSubset(nCounter);
    }

    //マテリアルをデフォルトに戻す
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：モデルの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タイプ,(D3DXVECTOR3)位置
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ELEMENT::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXVECTOR3 rotCamera;

    //---初期化処理---//

    // 位置・向きの初期設定
    Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = TEXT("Element");

    // Xファイルの読み込み
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("エレメントのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Position.x + 5.0F, Position.y + 5.0F, Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Element"), this);

	//初期化
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
void ELEMENT::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag().find(TEXT("Fairy")) != tstring::npos)
    {
        ACTORMANAGER::Destroy(this);
    }
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
void ELEMENT::Uninitialize(void)
{
    //SAFE_RELEASE((*Model->Texture));
    //SAFE_RELEASE(Model->Mesh);
    //SAFE_RELEASE(Model->MaterialBuffer);
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
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
void ELEMENT::Update(void)
{

}