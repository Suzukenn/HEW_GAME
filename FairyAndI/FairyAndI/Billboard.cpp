//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Billboard.h"
#include "SideViewCamera.h"
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
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxWorld;

    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pTexture;

    //---初期化処理---//
    pDevice = GetDevice();
    D3DXMatrixIdentity(&mtxWorld);
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("描画対象のテクスチャが存在しません"), TEXT("描画エラー"), MB_OK);
    }

    //---方向設定---//
    SIDEVIEWCAMERA::GetViewMtx(&mtxView);
    mtxWorld._11 = mtxView._11;
    mtxWorld._12 = mtxView._21;
    mtxWorld._13 = mtxView._31;
    mtxWorld._21 = mtxView._12;
    mtxWorld._22 = mtxView._22;
    mtxWorld._23 = mtxView._32;
    mtxWorld._31 = mtxView._13;
    mtxWorld._32 = mtxView._23;
    mtxWorld._33 = mtxView._33;

    //---書式設定---//
    // 頂点バッファをレンダリングパイプラインに設定
    pDevice->SetFVF(FVF_VERTEX_3D);            //フォーマット設定
    pDevice->SetTexture(0, pTexture->Image);   //テクスチャ設定

    //---頂点バッファによる描画---//
    // 移動を反映
    mtxWorld._41 = Transform.Position.x;
    mtxWorld._42 = Transform.Position.y;
    mtxWorld._43 = Transform.Position.z;

    // ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // ポリゴンの描画
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex, sizeof(VERTEX_3D));
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
        Vertex.at(nCounter).Vertex.x = Transform.Position.x + Transform.Scale.x * (nCounter >> 1);
        Vertex.at(nCounter).Vertex.y = Transform.Position.y + Transform.Scale.y * (nCounter & 1);
        Vertex.at(nCounter).Vertex.z = 0.0F;
        Vertex.at(nCounter).Normal = D3DXVECTOR3(0.0F, 0.0F, -1.0F);
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
        Vertex.at(nCounter).Texture.x = (float)(nCounter & 1);
        Vertex.at(nCounter).Texture.y = (float)((nCounter >> 1) & 1);
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
void BILLBOARD::Update(DWORD number)
{
    //---各種宣言---//
    int nCounter;       //カウンター
    float fU;           //U値
    float fV;           //V値

    //---値算出---//
    fU = (number % UV.x) * (1.0F / UV.x);
    fV = (number / UV.x) * (1.0F / UV.y);

    //---値更新---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Texture.x = fU + (nCounter % 2) * (1.0F / UV.x);
        Vertex.at(nCounter).Texture.y = fV + (nCounter / 2) * (1.0F / UV.y);
    }
}