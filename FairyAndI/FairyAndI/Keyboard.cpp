//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Keyboard.h"
#include "Main.h"

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
HRESULT KEYBOARD::Initialize(HWND handle ,LPDIRECTINPUT8 manager)
{
    //---各種宣言---//
    HRESULT hResult;

    //---デバイス生成---//
    hResult = manager->CreateDevice(GUID_SysKeyboard, &Device, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("キーボードのオブジェクト生成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---入力設定---//
    //データフォーマット設定
    hResult = Device->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("キーボードのデータフォーマット設定に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //協調レベルの設定
    hResult = Device->SetCooperativeLevel(handle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("キーボードの協調レベル設定に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //デバイスへの入力制御開始
    Device->Acquire();
    
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
void KEYBOARD::Uninitialize(void)
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
void KEYBOARD::Update(void)
{
    //---各種宣言---//
    int nCounter;

    //---データの更新---//
    if (Device)
    {
        Device->Acquire();
        Preview = Current;
        if (Device->GetDeviceState(256, (void*)&Current) == DIERR_INPUTLOST)
        {
            Device->Acquire();
        }
        else
        {
            for (nCounter = 0; nCounter < 256; ++nCounter)
            {
                Trigger.at(nCounter) = Current.at(nCounter) & ~Preview.at(nCounter);
                Release.at(nCounter) = ~Current.at(nCounter) & Preview.at(nCounter);
            }
        }
    }
}

/////////////////////////////////////////////
//関数名：GetHold
//
//機能：ボタンホールド判定
//
//引数：(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool KEYBOARD::GetHold(DWORD button)
{
    return Current.at(button & 0xFF) ? true : false;
}

/////////////////////////////////////////////
//関数名：GetRelease
//
//機能：ボタンリリース判定
//
//引数：(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool KEYBOARD::GetRelease(DWORD button)
{
    return Release.at(button & 0xFF) ? true : false;
}

/////////////////////////////////////////////
//関数名：GetTrigger
//
//機能：ボタントリガ判定
//
//引数：(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool KEYBOARD::GetTrigger(DWORD button)
{
    return Trigger.at(button & 0xFF) ? true : false;
}