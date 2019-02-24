//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "TextureManager.h"
#include "WordPlate.h"
#include "WordManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ワードプレートの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDPLATE::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ワードプレートの初期化
//
//引数：(LPCTSTR)画像のファイル名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDPLATE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードプレートの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }
    hResult = SetTexture(TEXT("EMPTY"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードプレート初期のテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ワードプレートの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDPLATE::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ワードプレートの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDPLATE::Update(void)
{
}

/////////////////////////////////////////////
//関数名：SetTexture
//
//機能：ワードプレートの適用テクスチャの設定
//
//引数：(tstring)テクスチャ名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDPLATE::SetTexture(LPCTSTR texturename)
{
    if (FAILED(WORDMANAGER::GetWordTexture(texturename, Texture)))
    {
        MessageBox(nullptr, TEXT("ワードプレートの適用テクスチャの取得に失敗しました"), TEXT("設定エラー"), MB_OK);
        Uninitialize();
        return E_FAIL;
    }
    return S_OK;
}