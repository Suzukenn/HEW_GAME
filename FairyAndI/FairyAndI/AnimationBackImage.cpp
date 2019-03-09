//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "AnimationBackImage.h"
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
void ANIMATIONBACKIMAGE::Draw(void)
{
    ANIMATIONSPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ,(POINT)UV分割値
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONBACKIMAGE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = ANIMATIONSPRITE::Initialize(texturename, position, size, uv);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アニメーション背景の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：MoveTexture
//
//機能：テクスチャの移動
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONBACKIMAGE::MoveTexture(void)
{
    //---各種宣言---//
    int nCounter;

    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).U += 0.00075F;
        if (Vertex.at(nCounter).U > 2.0F)
        {
            Vertex.at(nCounter).U = 0.0F;
        }
    }
}

/////////////////////////////////////////////
//関数名：SetAlpha
//
//機能：透明度の変更
//
//引数：(unsigned char)透明度
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONBACKIMAGE::SetAlpha(unsigned char alpha)
{
    //---各種宣言---//
    int nCounter;

    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(alpha, 255, 255, 255);
    }
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
void ANIMATIONBACKIMAGE::Uninitialize(void)
{
    ANIMATIONSPRITE::Uninitialize();
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
void ANIMATIONBACKIMAGE::Update(void)
{

}