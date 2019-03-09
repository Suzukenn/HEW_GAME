#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "Main.h" 
#include <XInput.h>

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    GAMEPADNUMBER_1P,
    GAMEPADNUMBER_2P,
    GAMEPADNUMBER_3P,
    GAMEPADNUMBER_4P,
    GAMEPADNUMBER_MAX
}GAMEPADNUMBER;

typedef enum
{
    GAMEPADDIRECTION_LEFT,
    GAMEPADDIRECTION_RIGHT,
    GAMEPADDIRECTION_MAX,
}GAMEPADDIRECTION;

//＝＝＝クラス宣言＝＝＝//
class GAMEPAD
{
    private:
        std::vector<XINPUT_STATE> Current; //現在の状態
        std::vector<WORD> Preview;	       //前回の状態
        std::vector<WORD> Trigger;	       //トリガ状態
        std::vector<WORD> Release;	       //リリース状態
		XINPUT_VIBRATION Vibration;		   //振動

    public:
        HRESULT Initialize(void);
        void Uninitialize(void);
        void Update(void);

		
        D3DXVECTOR2 GetLeftStick(DWORD);
        float GetLeftTrigger(DWORD);
        bool GetHold(DWORD, DWORD);
        bool GetRelease(DWORD, DWORD);
        D3DXVECTOR2 GetRightStick(DWORD);
        float GetRightTrigger(DWORD);
        bool GetTrigger(DWORD, DWORD);

		void PlayVibration(DWORD, float, float);
		void StopVibration(DWORD);
};

#endif