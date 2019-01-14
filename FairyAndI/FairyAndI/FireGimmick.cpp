//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "FireGimmick.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"

//＝＝＝定数・マクロ定義＝＝＝//

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：FIREGIMMICK
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
FIREGIMMICK::FIREGIMMICK(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
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
FIREGIMMICK::~FIREGIMMICK()
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

    for (nCounter = 0; nCounter < Model->MaterialValue; ++nCounter)
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
//機能：炎の壁ギミックの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FIREGIMMICK::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
	Position = position;
	Rotation = rotation;
	Tag = tag;

	Model.reset(new MODEL);

    //Xファイルの読み込み
	hResult = MODELMANAGER::GetModel(modelfile, *Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("炎の壁ギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---当たり判定の付与---//
	Collision = COLLISIONMANAGER::InstantiateToOBB(Position, Rotation, TEXT("Object"), this);

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
	if (opponent->Owner->GetTag().find(TEXT("HotIce")) != tstring::npos ||
		opponent->Owner->GetTag().find(TEXT("SoftIce")) != tstring::npos)
	{
		ACTORMANAGER::Destroy(this);
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
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
	if (Model)
	{
		Model->Release();
		Model = nullptr;
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

}

/////////////////////////////////////////////
//関数名：GetPos
//
//機能：炎の壁ギミックの位置情報取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
D3DXVECTOR3 FIREGIMMICK::GetPos(void)
{
	return Position;
}