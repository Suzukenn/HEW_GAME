//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "BatteryCannon.h"
#include "CollisionManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Skill.h"
#include "Sphere.h"
#include "SquareGauge.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：BATTERYCANNON
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
BATTERYCANNON::BATTERYCANNON(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：~BATTERYCANNON
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
BATTERYCANNON::~BATTERYCANNON(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：砲弾の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BATTERYCANNON::Draw(void)
{
    //---各種宣言---//
    D3DXMATRIX mtxWorld;

    std::shared_ptr<MODEL> pModel;

    //---ワールドマトリクスの設定---//
    //初期化
    D3DXMatrixIdentity(&mtxWorld);

    //設定
    Transform.MakeWorldMatrix(mtxWorld);
    GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

    //---描画---//
    //描画対象チェック
    pModel = Model.lock();
    if (!pModel)
    {
        MessageBox(nullptr, TEXT("砲弾ギミックのモデル情報の取得に失敗しました"), TEXT("描画エラー"), MB_OK);
        return;
    }

    //描画
	pModel->Draw(Shader, TEXT("NonTextureModel"), (UINT)Gray, mtxWorld);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：砲弾の初期化
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BATTERYCANNON::Initialize(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    BornTime = 0;
    Move = D3DXVECTOR3(sinf(Transform.Rotation.y) * 1.5F, 0.0F, 0.0F);
    Tag = TEXT("BatteryCannon");

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("砲弾のモデルの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

	//---シェーダーの取得---//
	hResult = SHADERMANAGER::GetShader(TEXT("MODEL"), Shader);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("大樹ギミック描画用のシェーダーの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
		Uninitialize();
		return hResult;
	}

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("BatteryCannon"), this);

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
void BATTERYCANNON::OnCollision(COLLISION* opponent)
{
    //跳ね返った動き
    if (opponent->Owner->GetTag() == TEXT("Wall"))
    {
        SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
        if (Skill)
        {
            if (Skill->GetType() == TEXT("SOFT"))
            {
                Move.x = -Move.x;
            }
        }
    }
    else
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：砲弾の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BATTERYCANNON::Uninitialize(void)
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
//機能：砲弾の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BATTERYCANNON::Update(void)
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
        Collision->Position = Transform.Position;
    }
}