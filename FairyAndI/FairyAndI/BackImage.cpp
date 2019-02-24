//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackImage.h"
#include "Texture.h"
#include "TextureManager.h"

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
void BACKIMAGE::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BACKIMAGE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{	
	//---各種宣言---//
	HRESULT hResult;

    //---初期化処理---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
    }

	return hResult;
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKIMAGE::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKIMAGE::Update(void)
{

}
