//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SelectMarker.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：選択マーカーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTMARKER::Draw(void)
{
    ANIMATIONSPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：選択マーカーの初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SELECTMARKER::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = ANIMATIONSPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("体力ハートの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：選択マーカーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTMARKER::Uninitialize(void)
{
    ANIMATIONSPRITE::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：選択マーカーの更新
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
            Vertex.at(nCounter).Position.x = vecPosition[nPositionNumber].x + (nCounter & 1) * Size.x;
            Vertex.at(nCounter).Position.y = vecPosition[nPositionNumber].y + ((nCounter >> 1) & 1) * Size.y;
        }
    }
}