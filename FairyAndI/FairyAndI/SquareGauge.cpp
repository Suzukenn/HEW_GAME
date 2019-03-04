//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "SquareGauge.h"
#include "Texture.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：四角ゲージの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SQUAREGAUGE::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pMemoryTexture;

    //---初期化処理---//
    pDevice = GetDevice();
    pMemoryTexture = MemoryTexture.lock();
    if (!pMemoryTexture)
    {
        MessageBox(nullptr, TEXT("ゲージメモリのテクスチャが存在しません"), TEXT("描画エラー"), MB_OK);
    }

    //---描画---//

    //メモリ
    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX_2D);                //フォーマット設定
    pDevice->SetTexture(0, pMemoryTexture->Image); //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &MemoryVertex, sizeof(VERTEX_2D));

    //背景
    Back.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：四角ゲージの初期化
//
//引数：(LPCTSTR)背景テクスチャ名,(D3DXVECTOR3)位置,(D3DXVECTOR3)向き
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SQUAREGAUGE::Initialize(LPCTSTR background, LPCTSTR gauge, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //---初期化処理---//
    Percent = 0.5F;
    Size.x = 207.0F;
    Size.y = 30.0F;
    Percent = 0.5F;

    //背景
    hResult = Back.Initialize(background, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ゲージ背景の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //ゲージメモリ
    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::GetTexture(gauge, MemoryTexture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("スプライトのテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---初期値の設定---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        MemoryVertex.at(nCounter).U = (float)(nCounter & 1);
        MemoryVertex.at(nCounter).V = (float)((nCounter >> 1) & 1);
        MemoryVertex.at(nCounter).Position.x = position.x + 25.0F + MemoryVertex.at(nCounter).U * Size.x;
        MemoryVertex.at(nCounter).Position.y = position.y + 73.0F + MemoryVertex.at(nCounter).V * Size.y;
        MemoryVertex.at(nCounter).Position.z = 0.0F;
        MemoryVertex.at(nCounter).RHW = 1.0F;
        MemoryVertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：四角ゲージの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SQUAREGAUGE::Uninitialize(void)
{
    Back.Uninitialize();
    MemoryTexture.reset();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：四角ゲージの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SQUAREGAUGE::Update(void)
{
    MemoryVertex.at(1).Position.x = MemoryVertex.at(0).Position.x + Size.x * Percent;
    MemoryVertex.at(3).Position.x = MemoryVertex.at(2).Position.x + Size.x * Percent;
}