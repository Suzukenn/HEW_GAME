//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Keyboard.h"
#include "Main.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�f�o�C�X�̏�����
//
//�����F(HWND)�n���h��,(LPDIRECTINPUT8)�f�o�C�X�}�l�[�W���[
//
//�߂�l�F(LRESULT)�����̐���
/////////////////////////////////////////////
HRESULT KEYBOARD::Initialize(HWND handle ,LPDIRECTINPUT8 manager)
{
    //---�e��錾---//
    HRESULT hResult;

    //---�f�o�C�X����---//
    hResult = manager->CreateDevice(GUID_SysKeyboard, &Device, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("�L�[�{�[�h�̃I�u�W�F�N�g�����Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---���͐ݒ�---//
    //�f�[�^�t�H�[�}�b�g�ݒ�
    hResult = Device->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g�ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�������x���̐ݒ�
    hResult = Device->SetCooperativeLevel(handle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("�L�[�{�[�h�̋������x���ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�f�o�C�X�ւ̓��͐���J�n
    Device->Acquire();
    
    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�f�o�C�X�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
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
//�֐����FUpdate
//
//�@�\�F���͏��̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void KEYBOARD::Update(void)
{
    //---�e��錾---//
    int nCounter;

    //---�f�[�^�̍X�V---//
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
//�֐����FGetHold
//
//�@�\�F�{�^���z�[���h����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool KEYBOARD::GetHold(DWORD button)
{
    return Current.at(button & 0xFF) ? true : false;
}

/////////////////////////////////////////////
//�֐����FGetRelease
//
//�@�\�F�{�^�������[�X����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool KEYBOARD::GetRelease(DWORD button)
{
    return Release.at(button & 0xFF) ? true : false;
}

/////////////////////////////////////////////
//�֐����FGetTrigger
//
//�@�\�F�{�^���g���K����
//
//�����F(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool KEYBOARD::GetTrigger(DWORD button)
{
    return Trigger.at(button & 0xFF) ? true : false;
}