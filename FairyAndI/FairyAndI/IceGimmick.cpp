//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "IceGimmick.h"
#include "ModelManager.h"

//＝＝＝定数・マクロ定義＝＝＝//

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：ICEGIMMICK
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
ICEGIMMICK::ICEGIMMICK(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
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
ICEGIMMICK::~ICEGIMMICK()
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
        MessageBox(nullptr, TEXT("氷の壁のギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
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
//機能：氷の壁ギミックの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ICEGIMMICK::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	//初期設定
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Tag = tag;

    //Xファイルの読み込み
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("氷壁ギミックのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(Transform.Position, D3DXVECTOR3(3.0F, 3.0F, 3.0F), TEXT("Object"), this);

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

}

/////////////////////////////////////////////
//関数名：GetPos
//
//機能：氷の壁ギミックの位置情報取得
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
D3DXVECTOR3 ICEGIMMICK::GetPos(void)
{
	return Transform.Position;
}