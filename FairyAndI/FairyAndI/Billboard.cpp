//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Billboard.h"
#include "InputManager.h"
#include "SideViewCamera.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "SquareGauge.h"
#include "Texture.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ビルボードの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BILLBOARD::Draw(void)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXMATRIX mtxProjection;
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxWorld;
    D3DXMATRIX mtxWVP;

    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<SHADER> pShader;
    std::shared_ptr<TEXTURE> pTexture;

    LPDIRECT3DVERTEXDECLARATION9 pVertexDeclaration; //頂点シェーダの頂点定義

    //パイプラインに渡す頂点データの構造を定義
    D3DVERTEXELEMENT9 decl[] = {{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, //位置
                                { 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //テクスチャ座標
                                D3DDECL_END() //最後に必ずD3DDECL_END()をつける
                               };

    //---初期化処理---//
    pDevice = GetDevice();
    D3DXMatrixIdentity(&mtxWorld);
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("描画対象のテクスチャが存在しません"), TEXT("描画エラー"), MB_OK);
    }

    pShader = Shader.lock();
    if (!pShader)
    {
        MessageBox(nullptr, TEXT("描画に使用するシェーダーが存在しません"), TEXT("描画エラー"), MB_OK);
    }

    //---方向設定---//
    SIDEVIEWCAMERA::GetViewMatrix(&mtxView);
    D3DXMatrixInverse(&mtxWorld, nullptr, &mtxView);

    //移動を反映
    mtxWorld._41 = Transform.Position.x;
    mtxWorld._42 = Transform.Position.y;
    mtxWorld._43 = Transform.Position.z;

    SIDEVIEWCAMERA::GetProjectionMatrix(&mtxProjection);
    mtxWVP = mtxWorld * mtxView * mtxProjection;

    //---書式設定---//
    //頂点の定義オブジェクトを作成する
    hResult = pDevice->CreateVertexDeclaration(decl, &pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("頂点情報の定義に失敗しました"), TEXT("描画エラー"), MB_OK);
    }
    //頂点定義をセット
    hResult = pDevice->SetVertexDeclaration(pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("頂点情報の設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    //---エフェクトの適用---//
    hResult = pShader->Effect->SetTechnique("Gray");
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->SetMatrix("WorldViewProjection", &mtxWVP);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("マトリクスの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->SetTexture("Texture", pTexture->Image);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクスチャの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->Begin(nullptr, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの適用を開始できませんでした"), TEXT("描画エラー"), MB_OK);
    }

    hResult = pShader->Effect->BeginPass(UINT(Gray));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクニックの適用パスの設定に失敗しました"), TEXT("描画エラー"), MB_OK);
    }

    //---描画---//
    hResult = pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, &Vertex, sizeof(CUSTOMVERTEX));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ポリゴンの描画に失敗しました"), TEXT("描画エラー"), MB_OK);
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

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ビルボードの初期化
//
//引数：(LPCTSTR)テクスチャ,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ,(POINT)UV分割値
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BILLBOARD::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR3 scale, POINT uv)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //---初期化処理---//
    Transform.Position = position;
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = scale;
    UV = uv;
    Gray = false;

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ビルボードのテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---ビルボードの作成---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Position.x = Transform.Position.x + Transform.Scale.x * (nCounter >> 1);
        Vertex.at(nCounter).Position.y = Transform.Position.y + Transform.Scale.y * (nCounter & 1);
        Vertex.at(nCounter).Position.z = 0.0F;
        Vertex.at(nCounter).Texture.x = (float)(nCounter >> 1);
        Vertex.at(nCounter).Texture.y = (float)!(nCounter & 1);
    }

    //---エフェクトの作成---//
    hResult = SHADERMANAGER::GetShader(TEXT("GRAY"), Shader);
    //hResult = D3DXCreateEffectFromFile(GetDevice(), TEXT("Data/GameScene/Gray.fx"), nullptr, nullptr, 0, nullptr, &Effect, &pErrMessage);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ビルボードのシェーダーの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ビルボードの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BILLBOARD::Uninitialize(void)
{
    Texture.reset();
    Shader.reset();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ビルボードの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BILLBOARD::Update(void)
{
    ////---各種宣言---//
    //int nCounter;       //カウンター
    //float fU;           //U値
    //float fV;           //V値

    ////---値算出---//
    //fU = (number % UV.x) * (1.0F / UV.x);
    //fV = (number / UV.x) * (1.0F / UV.y);

    ////---値更新---//
    //for (nCounter = 0; nCounter < 4; ++nCounter)
    //{
    //    Vertex.at(nCounter).Texture.x = fU + (nCounter % 2) * (1.0F / UV.x);
    //    Vertex.at(nCounter).Texture.y = fV + (nCounter / 2) * (1.0F / UV.y);
    //}

   /* if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = Gray ? false : true;
    }*/
	Gray = SQUAREGAUGE::GetFairyTime();
}