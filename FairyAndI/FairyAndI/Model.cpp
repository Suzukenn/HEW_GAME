//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"
#include "Model.h"
#include "SideViewCamera.h"
#include "Shader.h"
#include "Texture.h"

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

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;

    //---初期化処理---//
    pDevice = GetDevice();

    //現在のマテリアルを取得
    hResult = pDevice->GetMaterial(&matDefault);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("標準マテリアルの取得に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
    }

    //ポインタを取得
    pMaterial = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        if (effect)
        {
            matEffect = pMaterial[nCounter].MatD3D;
            matEffect.Diffuse = { 0.5F, 0.5F, 0.5F, 1.0F };
            hResult = pDevice->SetMaterial(&matEffect);
        }
        else
        {
            hResult = pDevice->SetMaterial(&pMaterial[nCounter].MatD3D);
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

void MODEL::Draw(std::weak_ptr<SHADER>& shader, LPCTSTR technique, UINT passnumber, D3DXMATRIX& worldmatrix)
{
    //---各種宣言---//
    DWORD nCounter;
    HRESULT hResult;
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxProjection;
    D3DXMATRIX mtxWorldViewProjection;

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;
    LPDIRECT3DVERTEXDECLARATION9 pVertexDeclaration; //頂点シェーダの頂点定義
    std::shared_ptr<SHADER> pShader;

    //パイプラインに渡す頂点データの構造を定義
    D3DVERTEXELEMENT9 decl[] = {{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, //位置
                                { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },  //法線
                                { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //テクスチャ座標
                                D3DDECL_END() //最後に必ずD3DDECL_END()をつける
                               };

    //---初期化処理---//
    pDevice = GetDevice();
    pMaterial = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    pShader = shader.lock();
    if (!pShader)
    {
        MessageBox(nullptr, TEXT("描画に使用するシェーダーが存在しません"), TEXT("描画エラー"), MB_OK);
    }


    //---頂点定義の設定---//
    hResult = pDevice->CreateVertexDeclaration(decl, &pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("頂点情報の定義に失敗しました"), TEXT("描画エラー"), MB_OK);
    }
    hResult = pDevice->SetVertexDeclaration(pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("頂点定義の設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    //---書式設定---//
    hResult = pShader->Effect->SetTechnique(pShader->Technic.at(technique));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    SIDEVIEWCAMERA::GetViewMatrix(&mtxView);
    SIDEVIEWCAMERA::GetProjectionMatrix(&mtxProjection);
    mtxWorldViewProjection = worldmatrix * mtxView * mtxProjection;

    hResult = pShader->Effect->SetMatrix("WorldViewProjection", &mtxWorldViewProjection);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("マトリクスの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->Begin(nullptr, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの適用を開始できませんでした"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->BeginPass(passnumber);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの適用パスの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        hResult = pDevice->SetMaterial(&pMaterial[nCounter].MatD3D);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("マテリアルの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
        }

        D3DXVECTOR4 Diffuse = D3DXVECTOR4(pMaterial[nCounter].MatD3D.Diffuse.r, pMaterial[nCounter].MatD3D.Diffuse.g, pMaterial[nCounter].MatD3D.Diffuse.b, pMaterial[nCounter].MatD3D.Diffuse.a);
        hResult = pShader->Effect->SetVector("Diffuse", &Diffuse);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("ディフューズの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
        }

        //テクスチャの設定
        hResult = pShader->Effect->SetTexture("Texture", Texture.at(nCounter));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("テクスチャの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
        }

        hResult = pShader->Effect->CommitChanges();
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("設定の変更に失敗しました"), TEXT("描画エラー"), MB_OK);
        }

        //描画
        hResult = Mesh->DrawSubset(nCounter);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("メッシュの描画に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
        }
    }

    hResult = pShader->Effect->EndPass();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの適用パスの終了に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->End();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの適用の終了に失敗しました"), TEXT("描画エラー"), MB_OK);
    }
}