//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "ItemBox.h"
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
void ITEMBOX::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX_2D);     //フォーマット設定
    pDevice->SetTexture(0, *Texture);    //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex, sizeof(VERTEX_2D));
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
HRESULT ITEMBOX::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //---初期化処理---//
    Position = position;
    Size = size;
    UV = uv;
    Texture.reset(new LPDIRECT3DTEXTURE9());

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景のテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---初期値の設定---//
    SetSpriteUV(0);
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Position.x = position.x + (nCounter & 1) * Size.x;
        Vertex.at(nCounter).Position.y = position.y + ((nCounter >> 1) & 1) * Size.y;
        Vertex.at(nCounter).Position.z = 0.0F;
        Vertex.at(nCounter).RHW = 1.0F;
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
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
void ITEMBOX::Uninitialize(void)
{
    //---開放---//

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
void ITEMBOX::Update(void)
{
    //---各種宣言---//
    static int nFrameTime = 0;

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        nFrameTime = 30;
        SetSpriteUV(1);
    }

    if (nFrameTime)
    {
        --nFrameTime;
        if (nFrameTime <= 0)
        {
            nFrameTime = 0;
            SetSpriteUV(0);
        }
    }
}