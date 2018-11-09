#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>

//�������N���X�錾������//
class KEYBOARD
{
    private:
        LPDIRECTINPUTDEVICE8 Device;    //�f�o�C�X
        std::array<BYTE, 256> Current;	//���݂̏��
        std::array<BYTE, 256> Preview;	//�O��̏��
        std::array<BYTE, 256> Trigger;	//�g���K���
        std::array<BYTE, 256> Release;	//�����[�X���

    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(DWORD);
        bool GetRelease(DWORD);
        bool GetTrigger(DWORD);
};

#endif