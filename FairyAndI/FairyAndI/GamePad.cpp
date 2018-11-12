//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "GamePad.h"
#include "Main.h"
#include <Xinput.h>

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�f�o�C�X�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(LRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAMEPAD::Initialize(void)
{
    //---�e��錾---//
    int nCounter;

    //---����������---//
    Current.resize(GAMEPADNUMBER_MAX);

    //---�f�o�C�X�̗�---//
    for (nCounter = 0; nCounter < GAMEPADNUMBER_MAX; nCounter++)
    {
        memset(&Current.at(nCounter), 0, sizeof(XINPUT_STATE));
        if (XInputGetState(nCounter, &Current.at(nCounter)) != ERROR_SUCCESS)
        {
            break;
        }
    }
 
    //---�e��z��̍œK��---//
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
//�֐����FUninitialize
//
//�@�\�F�f�o�C�X�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEPAD::Uninitialize(void)
{
    std::vector<XINPUT_STATE>().swap(Current);
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
void GAMEPAD::Update(void)
{
    //---�e��錾---//
    int nCounter;

    //---�f�[�^�̍X�V---//
    for (nCounter = 0; nCounter < Current.size(); nCounter++)
    {
        //���O�̃f�[�^�̎擾
        Preview.at(nCounter) = Current.at(nCounter).Gamepad.wButtons;
        
        //�f�[�^�̍X�V
        if (XInputGetState(nCounter, &Current.at(nCounter)) != ERROR_SUCCESS)
        {
            MessageBox(nullptr, TEXT("�Q�[���p�b�h�̓��͂��擾�ł��܂���ł���"), TEXT("�擾�G���["), MB_ICONSTOP | MB_OK);
            continue;
        }

        //�f�b�h�]�[���̔���
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

        //�g���K�[�A�����[�X����p�f�[�^�̎擾
        Trigger.at(nCounter) = Current.at(nCounter).Gamepad.wButtons & ~Preview.at(nCounter);
        Release.at(nCounter) = ~Current.at(nCounter).Gamepad.wButtons & Preview.at(nCounter);
    }
}

/////////////////////////////////////////////
//�֐����FGetHold
//
//�@�\�F�{�^���z�[���h����
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�,(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool GAMEPAD::GetHold(DWORD number, DWORD button)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Current.size())
    {
        return false;
    }

    //---�f�[�^�擾---//
    return Current.at(number).Gamepad.wButtons & button ? true : false;
}

/////////////////////////////////////////////
//�֐����FGetLeftStick
//
//�@�\�F���X�e�B�b�N���͒l�̎擾
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�
//
//�߂�l�F(float)���͒l
/////////////////////////////////////////////
POINTS GAMEPAD::GetLeftStick(DWORD number)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Current.size())
    {
        return { 0, 0 };
    }

    return { Current.at(number).Gamepad.sThumbLX, Current.at(number).Gamepad.sThumbLY };
}

/////////////////////////////////////////////
//�֐����FGetLeftTrigger
//
//�@�\�F���g���K���͒l�̎擾
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�
//
//�߂�l�F(float)���͗�
/////////////////////////////////////////////
float GAMEPAD::GetLeftTrigger(DWORD number)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Current.size())
    {
        return 0;
    }

    return (float)(Current.at(number).Gamepad.bLeftTrigger >> 7);
}

/////////////////////////////////////////////
//�֐����FGetRelease
//
//�@�\�F�{�^�������[�X����
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�,(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool GAMEPAD::GetRelease(DWORD number, DWORD button)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Release.size())
    {
        return false;
    }

    //---�f�[�^�擾---//
    return Release.at(number) & button ? true : false;
}

/////////////////////////////////////////////
//�֐����FGetRightStick
//
//�@�\�F�E�X�e�B�b�N���͒l�̎擾
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�
//
//�߂�l�F(POINTS)���͒l
/////////////////////////////////////////////
POINTS GAMEPAD::GetRightStick(DWORD number)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Current.size())
    {
        return{ 0, 0 };
    }

    return { Current.at(number).Gamepad.sThumbRX, Current.at(number).Gamepad.sThumbRY };
}

/////////////////////////////////////////////
//�֐����FGetRightTrigger
//
//�@�\�F�E�g���K���͒l�̎擾
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�
//
//�߂�l�F(float)���͗�
/////////////////////////////////////////////
float GAMEPAD::GetRightTrigger(DWORD number)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Current.size())
    {
        return 0;
    }

    return (float)(Current.at(number).Gamepad.bRightTrigger >> 7);
}

/////////////////////////////////////////////
//�֐����FGetTrigger
//
//�@�\�F�{�^���g���K����
//
//�����F(DWORD)�Q�[���p�b�h�ԍ�,(DWORD)���̓{�^��
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool GAMEPAD::GetTrigger(DWORD number, DWORD button)
{
    //---�ڑ��`�F�b�N---//
    if (number >= Trigger.size())
    {
        return false;
    }

    //---�f�[�^�擾---//
    return Trigger.at(number) & button ? true : false;
}