//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "EnemyBullet.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Sphere.h"
#include "SquareGauge.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：ENEMYBULLET
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
ENEMYBULLET::ENEMYBULLET(LPCTSTR modelname,D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：~ENEMYBULLET
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
ENEMYBULLET::~ENEMYBULLET(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：敵弾の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ENEMYBULLET::Draw(void)
{
    //---各種宣言---//
    D3DXMATRIX mtxWorld;

    std::shared_ptr<MODEL> pModel;

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
        MessageBox(nullptr, TEXT("敵弾のモデル情報の取得に失敗しました"), TEXT("描画エラー"), MB_OK);
        return;
    }

    //描画
    pModel->Draw(Shader, TEXT("NonTextureModel"), (UINT)Gray, mtxWorld);

}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：敵丸の初期化
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ENEMYBULLET::Initialize(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = modelname == TEXT("SLIMEBULLET") ? D3DXVECTOR3(3.0F, 3.0F, 3.0F) : D3DXVECTOR3(10.0F, 10.0F, 10.0F);
    BornTime = 0;
    Move = D3DXVECTOR3(-sinf(Transform.Rotation.y) * 1.5F, 0.0F, 0.0F);
    Gray = false;
    Tag = TEXT("EnemyBullet");

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("敵弾のモデルの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---シェーダーの取得---//
    hResult = SHADERMANAGER::GetShader(TEXT("MODEL"), Shader);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("敵弾描画用のシェーダーの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, Transform.Scale.x, TEXT("EnemyBullet"), this);

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
void ENEMYBULLET::OnCollision(COLLISION* opponent)
{
    ACTORMANAGER::Destroy(this);
	if (Collision)
	{
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
		Collision = nullptr;
	}
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
void ENEMYBULLET::Uninitialize(void)
{
    //---開放---//
    Model.reset();
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
void ENEMYBULLET::Update(void)
{
    Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }

    ++BornTime;
    if (BornTime > 120)
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
	else
	{
		Transform.Position += Move;
		if (Collision)
		{
			Collision->Position = Transform.Position;
		}
	}
}