//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "IceGimmick.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "SquareGauge.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：ICEGIMMICK
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
ICEGIMMICK::ICEGIMMICK(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：~ICEGIMMICK
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
ICEGIMMICK::~ICEGIMMICK(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：氷の壁ギミックの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ICEGIMMICK::Draw(void)
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
        MessageBox(nullptr, TEXT("氷の壁のギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return;
    }

    //描画
    pModel->Draw(Gray);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：氷の壁ギミックの初期化
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ICEGIMMICK::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Gray = false;
    Tag = TEXT("Gimmick");

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("氷壁ギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(Transform.Position, D3DXVECTOR3(3.0F, 3.0F, 3.0F), TEXT("Gimmick"), this);

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
void ICEGIMMICK::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag().find(TEXT("Hot")) != tstring::npos)
	{
		ACTORMANAGER::Destroy(this);
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：氷の壁ギミックの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ICEGIMMICK::Uninitialize(void)
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
//機能：氷の壁ギミックの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ICEGIMMICK::Update(void)
{	
   /* if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/
	Gray = SQUAREGAUGE::GetFairyTime();
}