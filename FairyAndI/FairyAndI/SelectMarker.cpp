//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SelectMarker.h"
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
void SELECTMARKER::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX_2D);     //フォーマット設定
    pDevice->SetTexture(0, *Texture);   //テクスチャ設定

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
HRESULT SELECTMARKER::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //---初期化処理---//
    Position = position;
    Size = size;
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
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).U = (float)(nCounter & 1);
        Vertex.at(nCounter).V = (float)((nCounter >> 1) & 1);
        Vertex.at(nCounter).Position.x = position.x + Vertex.at(nCounter).U * Size.x;
        Vertex.at(nCounter).Position.y = position.y + Vertex.at(nCounter).V * Size.y;
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
void SELECTMARKER::Uninitialize(void)
{
    //---開放---//
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
void SELECTMARKER::Update(void)
{
    //---各種宣言---//
    int nCounter;
    static int nPositionNumber = 0;

    const static D3DXVECTOR2 vecPosition[2] = { D3DXVECTOR2(390.0F, 120.0F), D3DXVECTOR2(740.0F, 120.0F) };

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
    {
        nPositionNumber = !nPositionNumber;

        for (nCounter = 0; nCounter < 4; ++nCounter)
        {
            Vertex.at(nCounter).Position.x = vecPosition[nPositionNumber].x + Vertex.at(nCounter).U * Size.x;
            Vertex.at(nCounter).Position.y = vecPosition[nPositionNumber].y + Vertex.at(nCounter).V * Size.y;
        }
    }
}