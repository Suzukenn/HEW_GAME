#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>

//＝＝＝クラス宣言＝＝＝//
class KEYBOARD
{
    private:
        LPDIRECTINPUTDEVICE8 Device;    //デバイス
        std::array<BYTE, 256> Current;	//現在の状態
        std::array<BYTE, 256> Preview;	//前回の状態
        std::array<BYTE, 256> Trigger;	//トリガ状態
        std::array<BYTE, 256> Release;	//リリース状態

    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(DWORD);
        bool GetRelease(DWORD);
        bool GetTrigger(DWORD);
};

#endif