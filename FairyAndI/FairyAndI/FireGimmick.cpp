//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "FireGimmick.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Skill.h"
#include "SquareGauge.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：FIREGIMMICK
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
FIREGIMMICK::FIREGIMMICK(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：~FIREGIMMICK
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
FIREGIMMICK::~FIREGIMMICK(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：炎の壁ギミックの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FIREGIMMICK::Draw(void)
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
        MessageBox(nullptr, TEXT("炎の壁ギミックのモデル情報の取得に失敗しました"), TEXT("描画エラー"), MB_OK);
        return;
    }

    //描画
    pModel->Draw(Shader, TEXT("NonTextureModel"), (UINT)Gray, mtxWorld);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：炎の壁ギミックの初期化
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FIREGIMMICK::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(700.0F, 700.0F, 700.0F);
    Gray = false;
    Small = false;
	Tag = TEXT("FireGimmick");

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("炎の壁ギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---シェーダーの取得---//
    hResult = SHADERMANAGER::GetShader(TEXT("MODEL"), Shader);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("氷壁ギミック描画用のシェーダーの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.0F, TEXT("Gimmick"), this);

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
void FIREGIMMICK::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag() == TEXT("Bullet"))
    {
        SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
        if (Skill)
        {
            if (Skill->GetType() == TEXT("HOT") || Skill->GetType() == TEXT("SOFT"))
            {
                Small = true;
            }
        }
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：炎の壁ギミックの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FIREGIMMICK::Uninitialize(void)
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
//機能：炎の壁ギミックの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FIREGIMMICK::Update(void)
{	
	Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }

    if (Small)
    {
        Transform.Scale.x -= 1.0F;
        Transform.Scale.y -= 1.0F;
        Transform.Scale.z -= 1.0F;
        if (Transform.Scale.x < 0.0F)
        {
            ACTORMANAGER::Destroy(this);
            COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        }
    }
}