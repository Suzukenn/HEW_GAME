#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

//＝＝＝ヘッダファイル読み込み＝＝＝//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Main.h"
#include "GamePad.h"
#include "Keyboard.h"
#include "Mouse.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    HOLD,
    RELEASE,
    TRIGGER,
    PUSHTYPE_MAX
}PUSHTYPE;

//＝＝＝クラス宣言＝＝＝//
class INPUTMANAGER
{
    private:
        static LPDIRECTINPUT8 Manager;
        static GAMEPAD GamePad;
        static KEYBOARD Keyboard;
        static MOUSE Mouse;

    public:
        static HRESULT Initialize(HINSTANCE, HWND);
        static void Uninitialize(void);
        static void Update(void);

        static bool GetGamePadButton(GAMEPADNUMBER, DWORD, PUSHTYPE);
        static POINTS GetGamePadStick(GAMEPADNUMBER, GAMEPADDIRECTION);
        static BYTE GetGamePadTrigger(GAMEPADNUMBER, GAMEPADDIRECTION);
        static bool GetKey(DWORD, PUSHTYPE);
        static bool GetMouseButton(MOUSEBUTTON, PUSHTYPE);
        static POINT GetMousePosition(void);
};

#endif