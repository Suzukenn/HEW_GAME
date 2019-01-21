//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Sphere.h"
#include "Player.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：BULLET
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
BULLET::BULLET(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//関数名：~BULLET
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
BULLET::~BULLET(void)
{
    Uninitialize();
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
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    std::shared_ptr<MODEL> pModel;

    //---初期化処理---//
    pDevice = GetDevice();

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);

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
//機能：弾丸の初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BULLET::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    BornTime = 0;
    Move = D3DXVECTOR3(-sinf(Transform.Rotation.y) * 1.5F, 0.0F, -cosf(Transform.Rotation.y) * 1.5F);
    Tag = TEXT("Bullet");
    Type = type;

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("弾丸のモデルの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.5F, TEXT("Skill"), this);

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
    ACTORMANAGER::Destroy(this);
    COLLISIONMANAGER::Destroy((COLLISION*)Collision);
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
    if (Model._Get())
    {
        Model.reset();
    }
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
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
    ++BornTime;
    if (BornTime > 120)
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
    else
    {
        Transform.Position += Move;
        Collision->Position = Transform.Position;
    }
}