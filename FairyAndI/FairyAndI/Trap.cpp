//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Player.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "Trap.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：TRAP
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
TRAP::TRAP(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//関数名：~TRAP
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
TRAP::~TRAP(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：罠の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TRAP::Draw(void)
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
		MessageBox(nullptr, TEXT("罠のモデル情報の取得に失敗しました"), TEXT("描画エラー"), MB_OK);
		return;
	}

    //描画
    pModel->Draw(Gray);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：罠の初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TRAP::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---各種宣言---//
	HRESULT hResult;

	//---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Gray = false;
	Tag = TEXT("Trap");
    Type = type;

	//---モデルの読み込み---//
	hResult = MODELMANAGER::GetModel(modelname, Model);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("罠のモデルの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
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
void TRAP::OnCollision(COLLISION* opponent)
{
	//ACTORMANAGER::Destroy(this);
	//COLLISIONMANAGER::Destroy((COLLISION*)Collision);
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：罠の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TRAP::Uninitialize(void)
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
//機能：罠の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TRAP::Update(void)
{
    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/

	Gray = SQUAREGAUGE::GetFairyTime();
}