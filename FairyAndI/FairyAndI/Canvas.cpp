//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Canvas.h"
#include "InputManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CANVAS::Draw(void)
{
    if (Mode)
    {
        Menu.Draw();
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT CANVAS::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = WORDMENU::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    Mode = false;

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：背景の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CANVAS::Uninitialize(void)
{
    Menu.Uninitialize();
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
void CANVAS::Update(void)
{
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER) || INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        Mode = !Mode;
    }

    if (Mode)
    {
        Menu.Update();
    }
}