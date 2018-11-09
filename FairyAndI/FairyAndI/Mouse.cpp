//＝＝＝ヘッダファイル読み込み＝＝＝//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Main.h"
#include "Mouse.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：デバイスの初期化
//
//引数：(HWND)ハンドル,(LPDIRECTINPUT8)デバイスマネージャー
//
//戻り値：(LRESULT)処理の成否
/////////////////////////////////////////////
HRESULT MOUSE::Initialize(HWND handle, LPDIRECTINPUT8 manager)
{
    //---各種宣言---//
    HRESULT hResult;
    DIPROPDWORD diProperty;

    //---初期化処理---//
    Handle = handle;

    //---デバイス生成---//
    hResult = manager->CreateDevice(GUID_SysMouse, &Device, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("マウスのオブジェクト生成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---入力設定---//
    //データフォーマット設定
    hResult = Device->SetDataFormat(&c_dfDIMouse);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("マウスのデータフォーマット設定に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //協調レベルの設定
    hResult = Device->SetCooperativeLevel(Handle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("マウスの協調レベル設定に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //デバイス設定
    diProperty.diph.dwSize = sizeof(DIPROPDWORD);
    diProperty.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diProperty.diph.dwObj = 0;
    diProperty.diph.dwHow = DIPH_DEVICE;
    diProperty.dwData = DIPROPAXISMODE_REL;
    hResult = Device->SetProperty(DIPROP_AXISMODE, &diProperty.diph);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("マウスの軸設定に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //デバイスへの入力制御開始
    Device->Acquire();
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("マウスの入力制御開始に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //マウス座標(スクリーン座標)取得
    if (!GetCursorPos(&Position))
    {
        MessageBox(Handle, TEXT("マウス座標の初期化に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //ウィンドウローカル座標に変換
    if (!ScreenToClient(Handle, &Position))
    {
        MessageBox(Handle, TEXT("マウス座標の初期化に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：デバイスの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void MOUSE::Uninitialize(void)
{
    if (Device)
    {
        Device->Unacquire();
    }

    SAFE_RELEASE(Device);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：入力情報の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void MOUSE::Update(void)
{
    //---各種宣言---//
    int nCounter;

    //---データの更新---//
    if (Device)
    {
        Device->Acquire();
        memcpy(&Preview, &Current, sizeof(DIMOUSESTATE));
        if (Device->GetDeviceState(sizeof(DIMOUSESTATE), &Current) == DIERR_INPUTLOST)
        {
            Device->Acquire();
        }
        else
        {
            GetCursorPos(&Position);
            ScreenToClient(Handle, &Position);
            for (nCounter = 0; nCounter < 4; nCounter++)
            {
                Trigger.rgbButtons[nCounter] = Current.rgbButtons[nCounter] & ~Preview.rgbButtons[nCounter];
                Release.rgbButtons[nCounter] = ~Current.rgbButtons[nCounter] & Preview.rgbButtons[nCounter];
            }
        }
    }
}

/////////////////////////////////////////////
//関数名：GetHold
//
//機能：ボタンホールド判定
//
//引数：(MOUSEBUTTON)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool MOUSE::GetHold(MOUSEBUTTON button)
{
    if (button >= _countof(Current.rgbButtons))
    {
        return false;
    }

    return Current.rgbButtons[button] ? true : false;
}

/////////////////////////////////////////////
//関数名：GetCursor
//
//機能：マウス座標の取得
//
//引数：なし
//
//戻り値：(POINT)座標
/////////////////////////////////////////////
POINT MOUSE::GetCursor(void)
{
    return Position;
}

/////////////////////////////////////////////
//関数名：GetRelease
//
//機能：ボタンリリース判定
//
//引数：(MOUSEBUTTON)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool MOUSE::GetRelease(MOUSEBUTTON button)
{
    if (button >= _countof(Release.rgbButtons))
    {
        return false;
    }
    return Release.rgbButtons[button] ? true : false;
}

/////////////////////////////////////////////
//関数名：GetTrigger
//
//機能：ボタントリガ判定
//
//引数：(MOUSEBUTTON)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool MOUSE::GetTrigger(MOUSEBUTTON button)
{
    if (button >= _countof(Trigger.rgbButtons))
    {
        return false;
    }
    return Trigger.rgbButtons[button] ? true : false;
}