//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Fade.h"
#include "Goal.h"
#include "ModelManager.h"
#include "SceneManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：GOAL
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タイプ,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ
//
//戻り値：なし
/////////////////////////////////////////////
GOAL::GOAL(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//関数名：~GOAL
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
GOAL::~GOAL(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゴールの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GOAL::Draw(void)
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
//機能：ゴールの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タイプ,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GOAL::Initialize(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
	Goal = 0;
    // 位置・向きの初期設定
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Tag = TEXT("Goal");

    // Xファイルの読み込み
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ゴールのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Object"), this);
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
void GOAL::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag() == TEXT("Player"))
	{
		Goal++;
	}
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゴールの終了
//
//引数：(LPCTSTR)モデルファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
void GOAL::Uninitialize(void)
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
//機能：ゴールの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GOAL::Update(void)
{
	if (Goal == 1)
	{
		FADE::SetFade(FADE_OUT);
	}
		if (FADE::CheckFadeEnd(FADE_OUT))
		{
			SCENEMANAGER::SetScene(SCENE_GAMECLEAR);
		}
}