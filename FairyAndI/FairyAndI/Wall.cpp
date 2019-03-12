//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "SquareGauge.h"
#include "Wall.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：WALL
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)モデル名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：なし
/////////////////////////////////////////////
WALL::WALL(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//関数名：~WALL
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
WALL::~WALL(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：壁の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WALL::Draw(void)
{
    BillBoard.Draw(Transform.Position);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：壁の初期化
//
//引数：(LPCTSTR)テクスチャ名,(tstirng)生成属性,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WALL::Initialize(LPCTSTR texturename, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    BornTime = 0;
    //---ビルボードの作成---//
    hResult = BillBoard.Initialize(texturename, D3DXVECTOR2(50.0F, 50.0F), Transform.Rotation.y > 0.0F);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("壁の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }


    //---当たり判定の付与---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.5F, TEXT("Wall"), this);

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
void WALL::OnCollision(COLLISION* opponent)
{

}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：壁の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WALL::Uninitialize(void)
{
    //---開放---//
    BillBoard.Uninitialize();
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：壁の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WALL::Update(void)
{
	Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }

    if (++BornTime > 60)
    {
        ACTORMANAGER::Destroy(this);
    }
    BillBoard.Update();
}