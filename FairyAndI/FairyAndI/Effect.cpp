//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "Effect.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "SideViewCamera.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：FAIRY
//
//機能：コンストラクタ
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR3)位置,(D3DXVECTOR2)大きさ,(bool)反転,(POINT)UV分割値
//
//戻り値：なし
/////////////////////////////////////////////
EFFECT::EFFECT(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted, POINT uv)
{
    Initialize(texturename, position, scale, inverted, uv);
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void EFFECT::Draw(void)
{
    Billboard.Draw(Transform.Position);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR3)位置,(D3DXVECTOR2)大きさ,(bool)反転,(POINT)UV分割値
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT EFFECT::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted, POINT uv)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(scale.x, scale.y, 1.0F);
    EffectNumber = 0;
    FrameCounter = 0;
    UV = uv;

    hResult = Billboard.Initialize(texturename, scale, inverted, uv);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：背景の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void EFFECT::Uninitialize(void)
{
    Billboard.Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：背景の更新
//
//引数：(float)移動量
//
//戻り値：なし
/////////////////////////////////////////////
void EFFECT::Update(void)
{
    if (++FrameCounter >= 4)
    {
        FrameCounter = 0;
        if (++EffectNumber >= UV.x * UV.y)
        {
            ACTORMANAGER::Destroy(this);
        }
        else
        {
            Billboard.SetUV(EffectNumber);
        }
    }

    Billboard.Update();
}