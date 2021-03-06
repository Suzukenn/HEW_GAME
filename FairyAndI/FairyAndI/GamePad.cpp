//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "GamePad.h"
#include "Main.h"
#include <Xinput.h>

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：デバイスの初期化
//
//引数：なし
//
//戻り値：(LRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAMEPAD::Initialize(void)
{
    //---各種宣言---//
    int nCounter;

    //---初期化処理---//
    Current.resize(GAMEPADNUMBER_MAX);

    //---デバイスの列挙---//
    for (nCounter = 0; nCounter < GAMEPADNUMBER_MAX; ++nCounter)
    {
        memset(&Current.at(nCounter), 0, sizeof(XINPUT_STATE));
        if (XInputGetState(nCounter, &Current.at(nCounter)) != ERROR_SUCCESS)
        {
            break;
        }
    }
 
    //---各種配列の最適化---//
    Current.resize(nCounter);
    Preview.resize(nCounter);
    Trigger.resize(nCounter);
    Release.resize(nCounter);
    Current.shrink_to_fit();
    Preview.shrink_to_fit();
    Trigger.shrink_to_fit();
    Release.shrink_to_fit();

    return S_OK;
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
void GAMEPAD::Uninitialize(void)
{
    std::vector<XINPUT_STATE>().swap(Current);
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
void GAMEPAD::Update(void)
{
    //---各種宣言---//
    int nCounter;

    //---データの更新---//
    for (nCounter = 0; nCounter < Current.size(); ++nCounter)
    {
        //直前のデータの取得
        Preview.at(nCounter) = Current.at(nCounter).Gamepad.wButtons;
        
        //データの更新
        if (XInputGetState(nCounter, &Current.at(nCounter)) != ERROR_SUCCESS)
        {
            MessageBox(nullptr, TEXT("ゲームパッドの入力を取得できませんでした"), TEXT("取得エラー"), MB_ICONSTOP | MB_OK);
            continue;
        }

        //デッドゾーンの判定
        if ((Current.at(nCounter).Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && Current.at(nCounter).Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
        {
            if (Current.at(nCounter).Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && Current.at(nCounter).Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                Current.at(nCounter).Gamepad.sThumbLX = 0;
                Current.at(nCounter).Gamepad.sThumbLY = 0;
            }
        }
        if ((Current.at(nCounter).Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && Current.at(nCounter).Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
        {
            if (Current.at(nCounter).Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && Current.at(nCounter).Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                Current.at(nCounter).Gamepad.sThumbRX = 0;
                Current.at(nCounter).Gamepad.sThumbRY = 0;
            }
        }

        //トリガー、リリース判定用データの取得
        Trigger.at(nCounter) = Current.at(nCounter).Gamepad.wButtons & ~Preview.at(nCounter);
        Release.at(nCounter) = ~Current.at(nCounter).Gamepad.wButtons & Preview.at(nCounter);
    }
}

/////////////////////////////////////////////
//関数名：GetHold
//
//機能：ボタンホールド判定
//
//引数：(DWORD)ゲームパッド番号,(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool GAMEPAD::GetHold(DWORD number, DWORD button)
{
    //---接続チェック---//
    if (number >= Current.size())
    {
        return false;
    }

    //---データ取得---//
    return Current.at(number).Gamepad.wButtons & button ? true : false;
}

/////////////////////////////////////////////
//関数名：GetLeftStick
//
//機能：左スティック入力値の取得
//
//引数：(DWORD)ゲームパッド番号
//
//戻り値：(D3DXVECTOR2)入力値
/////////////////////////////////////////////
D3DXVECTOR2 GAMEPAD::GetLeftStick(DWORD number)
{
    //---接続チェック---//
    if (number >= Current.size())
    {
        return D3DXVECTOR2(0.0F, 0.0F);
    }

    return D3DXVECTOR2(Current.at(number).Gamepad.sThumbLX / 32768.0F, Current.at(number).Gamepad.sThumbLY / 32768.0F);
}

/////////////////////////////////////////////
//関数名：GetLeftTrigger
//
//機能：左トリガ入力値の取得
//
//引数：(DWORD)ゲームパッド番号
//
//戻り値：(float)入力率
/////////////////////////////////////////////
float GAMEPAD::GetLeftTrigger(DWORD number)
{
    //---接続チェック---//
    if (number >= Current.size())
    {
        return 0;
    }

    return (float)(Current.at(number).Gamepad.bLeftTrigger / 256.0F);
}

/////////////////////////////////////////////
//関数名：GetRelease
//
//機能：ボタンリリース判定
//
//引数：(DWORD)ゲームパッド番号,(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool GAMEPAD::GetRelease(DWORD number, DWORD button)
{
    //---接続チェック---//
    if (number >= Release.size())
    {
        return false;
    }

    //---データ取得---//
    return Release.at(number) & button ? true : false;
}

/////////////////////////////////////////////
//関数名：GetRightStick
//
//機能：右スティック入力値の取得
//
//引数：(DWORD)ゲームパッド番号
//
//戻り値：(D3DXVECTOR2)入力値
/////////////////////////////////////////////
D3DXVECTOR2 GAMEPAD::GetRightStick(DWORD number)
{
    //---接続チェック---//
    if (number >= Current.size())
    {
        return D3DXVECTOR2(0.0F, 0.0F);
    }

    return D3DXVECTOR2(Current.at(number).Gamepad.sThumbRX / 32768.0F, Current.at(number).Gamepad.sThumbRY / 32768.0F);
}

/////////////////////////////////////////////
//関数名：GetRightTrigger
//
//機能：右トリガ入力値の取得
//
//引数：(DWORD)ゲームパッド番号
//
//戻り値：(float)入力率
/////////////////////////////////////////////
float GAMEPAD::GetRightTrigger(DWORD number)
{
    //---接続チェック---//
    if (number >= Current.size())
    {
        return 0;
    }

    return (float)(Current.at(number).Gamepad.bRightTrigger / 256.0F);
}

/////////////////////////////////////////////
//関数名：GetTrigger
//
//機能：ボタントリガ判定
//
//引数：(DWORD)ゲームパッド番号,(DWORD)入力ボタン
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool GAMEPAD::GetTrigger(DWORD number, DWORD button)
{
    //---接続チェック---//
    if (number >= Trigger.size())
    {
        return false;
    }

    //---データ取得---//
    return Trigger.at(number) & button ? true : false;
}

/////////////////////////////////////////////
//関数名：PlayVibration
//
//機能：ゲームパッドの振動
//
//引数：(DWORD)ゲームパッド番号,(float)左の振動スピード,(float)右の振動スピード
//
//戻り値：なし
/////////////////////////////////////////////
void GAMEPAD::PlayVibration(DWORD number, float LMotorSpeed, float RMotorSpeed)
{
	//---接続チェック---//
	if (number >= Current.size())
	{
		return;
	}

    //---振動量の設定---//
	Vibration.wLeftMotorSpeed = (WORD)(65535.0F * LMotorSpeed);
	Vibration.wRightMotorSpeed = (WORD)(65535.0F * RMotorSpeed);
	XInputSetState(number, &Vibration);
}

/////////////////////////////////////////////
//関数名：StopVibration
//
//機能：ゲームパッドの振動を止める
//
//引数：(DWORD)ゲームパッド番号
//
//戻り値：なし
/////////////////////////////////////////////
void GAMEPAD::StopVibration(DWORD number)
{
	//---接続チェック---//
	if (number >= Current.size())
	{
		return;
	}

    //---振動量の設定---//
	Vibration.wLeftMotorSpeed = 0;
	Vibration.wRightMotorSpeed = 0;
	XInputSetState(number, &Vibration);
}