//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Sprite.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：スプライトの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SPRITE::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_2D)); //頂点書式設定
    pDevice->SetFVF(FVF_VERTEX_2D);                                   //フォーマット設定
    pDevice->SetTexture(0, *Texture);                                 //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：スプライトの初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SPRITE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    VERTEX_2D* pVertex;

    //---初期化処理---//
    Position = position;
    Size = size;
    Texture.reset(new LPDIRECT3DTEXTURE9());
    VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9());

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("スプライトのテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---頂点バッファの生成---//
    hResult = GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("スプライトの頂点バッファの生成に失敗しました"), texturename, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---頂点バッファへの値の設定---//
    //バッファのポインタを取得
    hResult = (*VertexBuffer)->Lock(0, 0, (void**)&pVertex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("スプライトの頂点バッファのポインタの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //値の設定
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        pVertex[nCounter].U = (float)(nCounter & 1);
        pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
        pVertex[nCounter].Position.x = pVertex[nCounter].U * SCREEN_WIDTH;
        pVertex[nCounter].Position.y = pVertex[nCounter].V * SCREEN_HEIGHT;
        pVertex[nCounter].Position.z = 0.0F;
        pVertex[nCounter].RHW = 1.0F;
        pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //バッファのポインタの解放
    hResult = (*VertexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("スプライトの頂点バッファのポインタの開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：スプライトの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SPRITE::Uninitialize(void)
{
    //---開放---//
    SAFE_RELEASE((*VertexBuffer));
    SAFE_RELEASE((*Texture));
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
void SPRITE::Update(void)
{

}