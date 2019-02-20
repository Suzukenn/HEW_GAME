//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Model.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：モデルの描画
//
//引数：(bool)エフェクトの有効状態
//
//戻り値：なし
/////////////////////////////////////////////
void MODEL::Draw(bool effect)
{
    //---各種宣言---//
    DWORD nCounter;
    HRESULT hResult;
    D3DMATERIAL9 matDefault;
    D3DMATERIAL9 matEffect;

    const D3DCOLORVALUE GrayScale = { 0.2126F, 0.7152F, 0.0722F , 1.0F };

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMatrix;

    //---初期化処理---//
    pDevice = GetDevice();

    //現在のマテリアルを取得
    hResult = pDevice->GetMaterial(&matDefault);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("標準マテリアルの取得に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
    }

    //ポインタを取得
    pMatrix = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        if (effect)
        {
            matEffect = pMatrix[nCounter].MatD3D;
            matEffect.Diffuse = { 0.5F, 0.5F, 0.5F, 1.0F };
            hResult = pDevice->SetMaterial(&matEffect);
        }
        else
        {
            hResult = pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);
        }
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("マテリアルの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
        }

        //テクスチャの設定
        hResult = pDevice->SetTexture(0, Texture.at(nCounter));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("テクスチャの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
        }

        //描画
        hResult = Mesh->DrawSubset(nCounter);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("メッシュの描画に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
        }

    }

    //マテリアルをデフォルトに戻す
    hResult = pDevice->SetMaterial(&matDefault);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("標準マテリアルの復元に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
    }
}