#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "Main.h" 
#include <XInput.h>

//�������񋓌^��`������//
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

//�������N���X�錾������//
class GAMEPAD
{
    private:
        std::vector<XINPUT_STATE> Current; //���݂̏��
        std::vector<WORD> Preview;	       //�O��̏��
        std::vector<WORD> Trigger;	       //�g���K���
        std::vector<WORD> Release;	       //�����[�X���
		XINPUT_VIBRATION Vibration;		   //�U��

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