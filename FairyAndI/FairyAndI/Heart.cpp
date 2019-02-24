//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Heart.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：体力ハートの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void HEART::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ハートの初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT HEART::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("体力ハートの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
    }
   
    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ハートの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void HEART::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ハートの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void HEART::Update(void)
{

}