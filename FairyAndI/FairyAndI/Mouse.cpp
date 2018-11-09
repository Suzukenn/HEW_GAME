//�������w�b�_�t�@�C���ǂݍ��݁�����//
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include "Main.h"
#include "Mouse.h"

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
HRESULT MOUSE::Initialize(HWND handle, LPDIRECTINPUT8 manager)
{
    //---�e��錾---//
    HRESULT hResult;
    DIPROPDWORD diProperty;

    //---����������---//
    Handle = handle;

    //---�f�o�C�X����---//
    hResult = manager->CreateDevice(GUID_SysMouse, &Device, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("�}�E�X�̃I�u�W�F�N�g�����Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //---���͐ݒ�---//
    //�f�[�^�t�H�[�}�b�g�ݒ�
    hResult = Device->SetDataFormat(&c_dfDIMouse);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("�}�E�X�̃f�[�^�t�H�[�}�b�g�ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�������x���̐ݒ�
    hResult = Device->SetCooperativeLevel(Handle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("�}�E�X�̋������x���ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�f�o�C�X�ݒ�
    diProperty.diph.dwSize = sizeof(DIPROPDWORD);
    diProperty.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diProperty.diph.dwObj = 0;
    diProperty.diph.dwHow = DIPH_DEVICE;
    diProperty.dwData = DIPROPAXISMODE_REL;
    hResult = Device->SetProperty(DIPROP_AXISMODE, &diProperty.diph);
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("�}�E�X�̎��ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�f�o�C�X�ւ̓��͐���J�n
    Device->Acquire();
    if (FAILED(hResult))
    {
        MessageBox(Handle, TEXT("�}�E�X�̓��͐���J�n�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return hResult;
    }

    //�}�E�X���W(�X�N���[�����W)�擾
    if (!GetCursorPos(&Position))
    {
        MessageBox(Handle, TEXT("�}�E�X���W�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //�E�B���h�E���[�J�����W�ɕϊ�
    if (!ScreenToClient(Handle, &Position))
    {
        MessageBox(Handle, TEXT("�}�E�X���W�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

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
void MOUSE::Uninitialize(void)
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
void MOUSE::Update(void)
{
    //---�e��錾---//
    int nCounter;

    //---�f�[�^�̍X�V---//
    if (Device)
    {
        Device->Acquire();
        memcpy(&Preview, &Current, sizeof(DIMOUSESTATE));
        if (Device->GetDeviceState(sizeof(DIMOUSESTATE), &Current) == DIERR_INPUTLOST)
        {
            Device->Acquire();
        }
        else
        {
            GetCursorPos(&Position);
            ScreenToClient(Handle, &Position);
            for (nCounter = 0; nCounter < 4; nCounter++)
            {
                Trigger.rgbButtons[nCounter] = Current.rgbButtons[nCounter] & ~Preview.rgbButtons[nCounter];
                Release.rgbButtons[nCounter] = ~Current.rgbButtons[nCounter] & Preview.rgbButtons[nCounter];
            }
        }
    }
}

/////////////////////////////////////////////
//�֐����FGetHold
//
//�@�\�F�{�^���z�[���h����
//
//�����F(MOUSEBUTTON)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool MOUSE::GetHold(MOUSEBUTTON button)
{
    if (button >= _countof(Current.rgbButtons))
    {
        return false;
    }

    return Current.rgbButtons[button] ? true : false;
}

/////////////////////////////////////////////
//�֐����FGetCursor
//
//�@�\�F�}�E�X���W�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(POINT)���W
/////////////////////////////////////////////
POINT MOUSE::GetCursor(void)
{
    return Position;
}

/////////////////////////////////////////////
//�֐����FGetRelease
//
//�@�\�F�{�^�������[�X����
//
//�����F(MOUSEBUTTON)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool MOUSE::GetRelease(MOUSEBUTTON button)
{
    if (button >= _countof(Release.rgbButtons))
    {
        return false;
    }
    return Release.rgbButtons[button] ? true : false;
}

/////////////////////////////////////////////
//�֐����FGetTrigger
//
//�@�\�F�{�^���g���K����
//
//�����F(MOUSEBUTTON)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool MOUSE::GetTrigger(MOUSEBUTTON button)
{
    if (button >= _countof(Trigger.rgbButtons))
    {
        return false;
    }
    return Trigger.rgbButtons[button] ? true : false;
}