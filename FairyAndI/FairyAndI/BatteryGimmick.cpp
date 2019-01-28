//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "BatteryGimmick.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "Skill.h"
#include "SkillFactory.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：BATTERYGIMMICK
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
BATTERYGIMMICK::BATTERYGIMMICK(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：~WOODGIMMICK
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
BATTERYGIMMICK::~BATTERYGIMMICK(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：砲台ギミックの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BATTERYGIMMICK::Draw(void)
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
		MessageBox(nullptr, TEXT("砲台ギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
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
//機能：砲台ギミックの初期化
//
//引数：(LPCTSTR)モデル名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BATTERYGIMMICK::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Tag = TEXT("Battery");

    //Xファイルの読み込み
	hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("砲台ギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---当たり判定の付与---//
	//Collision = COLLISIONMANAGER::InstantiateToOBB(Position, Rotation, TEXT("Object"), this);
	Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Object"), this);

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
void BATTERYGIMMICK::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag() == TEXT("Bullet"))
    {
        SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
        if (Skill)
        {
            if (Skill->GetType() == TEXT("RETURN"))
            {
                ACTORMANAGER::Destroy(this);
                COLLISIONMANAGER::Destroy((COLLISION*)Collision);
            }
        }
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：砲台ギミックの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BATTERYGIMMICK::Uninitialize(void)
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
//機能：砲台ギミックの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BATTERYGIMMICK::Update(void)
{	
	static int Count;	//弾を出す間隔秒数
	D3DXVECTOR3 BulletPosition = D3DXVECTOR3(0.0F, 10.0F, 0.0F);

	//2秒経ったら
	if (++Count > 120)
	{
		if (PLAYER::GetPlayerPosition().x < Transform.Position.x)
		{
            Transform.Rotation.y = -(D3DX_PI * 0.50F);
			BulletPosition.x = Transform.Position.x - 10.0F;
		}
		else if (PLAYER::GetPlayerPosition().x > Transform.Position.x)
		{
            Transform.Rotation.y = D3DX_PI * 0.50F;
			BulletPosition.x = Transform.Position.x + 10.0F;
		}

		//弾発射
		SKILLFACTORY::InstantiateSkill(TEXT("BATTERY"), TEXT("ICE"), BulletPosition, Transform.Rotation);
		//リセット
		Count = 0;
	}
}

/////////////////////////////////////////////
//関数名：GetPos
//
//機能：砲台ギミックの位置情報取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
D3DXVECTOR3 BATTERYGIMMICK::GetPos(void)
{
	return Transform.Position;
}