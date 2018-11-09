#ifndef _MOUSE_H_
#define _MOUSE_H_

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    MOUSEBUTTON_LEFT,
    MOUSEBUTTON_RIGHT,
    MOUSEBUTTON_CENTER,
    MOUSEBUTTON_MAX
}MOUSEBUTTON;

//＝＝＝クラス宣言＝＝＝//
class MOUSE
{
    private:
        LPDIRECTINPUTDEVICE8 Device; //デバイス
        POINT Position;              //カーソル座標
        DIMOUSESTATE Current;	     //現在の状態
        DIMOUSESTATE Preview;	     //前回の状態
        DIMOUSESTATE Trigger;	     //トリガ状態
        DIMOUSESTATE Release;	     //リリース状態
        HWND Handle;                 //ウィンドウハンドル

    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(MOUSEBUTTON);
        POINT GetCursor(void);
        bool GetRelease(MOUSEBUTTON);
        bool GetTrigger(MOUSEBUTTON);
};

#endif