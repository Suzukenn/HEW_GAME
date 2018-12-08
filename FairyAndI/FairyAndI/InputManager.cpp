//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "Main.h"

//＝＝＝グローバル宣言＝＝＝//
LPDIRECTINPUT8 INPUTMANAGER::Manager;
GAMEPAD INPUTMANAGER::GamePad;
KEYBOARD INPUTMANAGER::Keyboard;
MOUSE INPUTMANAGER::Mouse;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：デバイスの初期化
//
//引数：(HINSTANCE)インスタンス,(HWND)ハンドル
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT INPUTMANAGER::Initialize(HINSTANCE instance, HWND handle)
{
	//---各種宣言---//
	HRESULT hResult;

    //DirectInputオブジェクト生成
    hResult = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Manager, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("DirectInputオブジェクト生成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //ジョイスティックの初期化
    hResult = GamePad.Initialize();
    if (FAILED(hResult))
    {
        Uninitialize();
        return hResult;
    }

	//キーボードの初期化
    hResult = Keyboard.Initialize(handle, Manager);
	if (FAILED(hResult))
	{
		Uninitialize();
		return hResult;
	}

    //マウスの初期化
    hResult = Mouse.Initialize(handle, Manager);
    if (FAILED(hResult))
    {
        Uninitialize();
        return hResult;
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
void INPUTMANAGER::Uninitialize(void)
{
    GamePad.Uninitialize();
	Keyboard.Uninitialize();
    Mouse.Uninitialize();
    SAFE_RELEASE(Manager);
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
void INPUTMANAGER::Update(void)
{
    GamePad.Update();
	Keyboard.Update();
    Mouse.Update();
}

/////////////////////////////////////////////
//関数名：GetGamePadButton
//
//機能：ゲームパッドボタン入力判定
//
//引数：(GAMEPADNUMBER)ゲームパッド番号,(DWORD)入力ボタン,(PUSHTYPE)判定タイプ
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER number, DWORD button, PUSHTYPE type)
{
    switch (type)
    {
        case HOLD:
            return GamePad.GetHold(number, button);

        case TRIGGER:
            return GamePad.GetTrigger(number, button);

        case RELEASE:
            return GamePad.GetRelease(number, button);

        default:
            return false;
    }
}

/////////////////////////////////////////////
//関数名：GetGamePadStick
//
//機能：ゲームパッドのアナログスティックの入力値取得
//
//引数：(JOYSTICKNUMBER)ゲームパッド番号,(GAMEPADDIRECTION)取得スティック
//
//戻り値：(D3DXVECTOR2)入力値
/////////////////////////////////////////////
D3DXVECTOR2 INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER number, GAMEPADDIRECTION direction)
{
    switch (direction)
    {
        case GAMEPADDIRECTION_LEFT:
            return GamePad.GetLeftStick(number);

        case GAMEPADDIRECTION_RIGHT:
            return GamePad.GetRightStick(number);

        default:
            return { 0, 0 };
    }
}

/////////////////////////////////////////////
//関数名：GetGamePadTrigger
//
//機能：ゲームパッドのトリガーの入力値取得
//
//引数：(JOYSTICKNUMBER)ゲームパッド番号,(GAMEPADDIRECTION)取得トリガー
//
//戻り値：(float)入力率
/////////////////////////////////////////////
float INPUTMANAGER::GetGamePadTrigger(GAMEPADNUMBER number, GAMEPADDIRECTION direction)
{
    switch (direction)
    {
        case GAMEPADDIRECTION_LEFT:
            return GamePad.GetLeftTrigger(number);

        case GAMEPADDIRECTION_RIGHT:
            return GamePad.GetRightTrigger(number);

        default:
            return 0.0F;
    }
}

/////////////////////////////////////////////
//関数名：GetKey
//
//機能：キーボード入力判定
//
//引数：(DWORD)入力ボタン,(PUSHTYPE)判定タイプ
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool INPUTMANAGER::GetKey(DWORD button, PUSHTYPE type)
{
	switch (type)
	{
		case HOLD:
			return Keyboard.GetHold(button);

		case TRIGGER:
			return Keyboard.GetTrigger(button);

		case RELEASE:
			return Keyboard.GetRelease(button);

		default:
			return false;
	}
}

/////////////////////////////////////////////
//関数名：GetMouseButton
//
//機能：マウスボタン入力判定
//
//引数：(MOUSEBUTTON)入力ボタン,(PUSHTYPE)判定タイプ
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool INPUTMANAGER::GetMouseButton(MOUSEBUTTON button, PUSHTYPE type)
{
    switch (type)
    {
        case HOLD:
            return Mouse.GetHold(button);

        case TRIGGER:
            return Mouse.GetTrigger(button);

        case RELEASE:
            return Mouse.GetRelease(button);

        default:
            return false;
    }
}

/////////////////////////////////////////////
//関数名：GetMousePosition
//
//機能：マウスの座標取得
//
//引数：なし
//
//戻り値：(POINT)座標
/////////////////////////////////////////////
POINT INPUTMANAGER::GetMousePosition(void)
{
    return Mouse.GetCursor();
}