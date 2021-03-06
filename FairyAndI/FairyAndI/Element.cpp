//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Element.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SquareGauge.h"
#include "WordManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：ELEMENT
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)タイプ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き(D3DXVECTOR3)大きさ
//
//戻り値：なし
/////////////////////////////////////////////
ELEMENT::ELEMENT(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
    Initialize(modelname, type, position, rotation, scale);
}

/////////////////////////////////////////////
//関数名：~ELEMENT
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
ELEMENT::~ELEMENT(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：エレメントの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ELEMENT::Draw(void)
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
        MessageBox(nullptr, TEXT("エレメントのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return;
    }

    //描画
    //pModel->Draw(Gray);
    pModel->Draw(Shader, Name == TEXT("Fire") ? TEXT("TextureModel") : TEXT("NonTextureModel"), (UINT)Gray, mtxWorld);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：エレメントの初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タイプ,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き,(D3DXVECTOR3)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ELEMENT::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXVECTOR3 rotCamera;

    //---初期化処理---//

    // 位置・向きの初期設定
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = scale;
    Gray = false;
    Type = type;
    Tag = TEXT("Element");

    //---モデルの読み込み---//
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("エレメントのモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---シェーダーの取得---//
    hResult = SHADERMANAGER::GetShader(TEXT("MODEL"), Shader);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("エレメント描画用のシェーダーの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Item"), this);

	//初期化
    Name = modelname;
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
void ELEMENT::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag() == TEXT("Fairy"))
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        WORDMANAGER::UnLockWord(Type.data());
    }
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：エレメントの終了
//
//引数：(LPCTSTR)モデルファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
void ELEMENT::Uninitialize(void)
{
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：エレメントの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ELEMENT::Update(void)
{
	Gray = SQUAREGAUGE::GetFairyTime();
}