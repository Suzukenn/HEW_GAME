//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SkillBox.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：スキルボックスの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLBOX::Draw(void)
{
    ANIMATIONSPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：スキルボックスの初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SKILLBOX::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = ANIMATIONSPRITE::Initialize(texturename, position, size, uv);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("体力ハートの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：スキルボックスの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLBOX::Uninitialize(void)
{
    //---開放---//
    ANIMATIONSPRITE::Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：スキルボックスの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SKILLBOX::Update(void)
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