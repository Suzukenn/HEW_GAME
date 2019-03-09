//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "TextureManager.h"
#include "SideViewCamera.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKGROUND::Draw(void)
{
    Billboard.Draw(Position);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR3)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Position = position;

    hResult = Billboard.Initialize(texturename, scale);
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
void BACKGROUND::Uninitialize(void)
{
    Billboard.Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：背景の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKGROUND::Update(void)
{
    Billboard.Update();
}