//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Billboard.h"
#include "SideViewCamera.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ビルボードの描画
//
//引数：(D3DXVECTOR3)位置
//
//戻り値：なし
/////////////////////////////////////////////
void BILLBOARD::Draw(D3DXVECTOR3 position)
{
    //---各種宣言---//
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxWorld;

    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();
    D3DXMatrixIdentity(&mtxWorld);

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
    pDevice->SetFVF(FVF_VERTEX_3D);    //フォーマット設定
    pDevice->SetTexture(0, Texture);   //テクスチャ設定

    //---頂点バッファによる描画---//
    // 移動を反映
    mtxWorld._41 = position.x;
    mtxWorld._42 = position.y;
    mtxWorld._43 = position.z;

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
//引数：(LPCTSTR)テクスチャ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BILLBOARD::Initialize(LPCTSTR texturename, POINT uv)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //---初期化処理---//
    UV = uv;

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("プレイヤーのテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---ビルボードの作成---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Vertex.x = nCounter >> 1 ? 5.0F : -5.0F;
        Vertex.at(nCounter).Vertex.y = nCounter & 1 ? 5.0F : -5.0F;
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
    Texture = nullptr;
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