//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "Main.h"

//�������O���[�o���錾������//
LPDIRECTINPUT8 INPUTMANAGER::Manager;
GAMEPAD INPUTMANAGER::GamePad;
KEYBOARD INPUTMANAGER::Keyboard;
MOUSE INPUTMANAGER::Mouse;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�f�o�C�X�̏�����
//
//�����F(HINSTANCE)�C���X�^���X,(HWND)�n���h��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT INPUTMANAGER::Initialize(HINSTANCE instance, HWND handle)
{
	//---�e��錾---//
	HRESULT hResult;

    //DirectInput�I�u�W�F�N�g����
    hResult = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Manager, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(handle, TEXT("DirectInput�I�u�W�F�N�g�����Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //�W���C�X�e�B�b�N�̏�����
    hResult = GamePad.Initialize();
    if (FAILED(hResult))
    {
        Uninitialize();
        return hResult;
    }

	//�L�[�{�[�h�̏�����
    hResult = Keyboard.Initialize(handle, Manager);
	if (FAILED(hResult))
	{
		Uninitialize();
		return hResult;
	}

    //�}�E�X�̏�����
    hResult = Mouse.Initialize(handle, Manager);
    if (FAILED(hResult))
    {
        Uninitialize();
        return hResult;
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
void INPUTMANAGER::Uninitialize(void)
{
    GamePad.Uninitialize();
	Keyboard.Uninitialize();
    Mouse.Uninitialize();
    SAFE_RELEASE(Manager);
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
void INPUTMANAGER::Update(void)
{
    GamePad.Update();
	Keyboard.Update();
    Mouse.Update();
}

/////////////////////////////////////////////
//�֐����FGetGamePadButton
//
//�@�\�F�Q�[���p�b�h�{�^�����͔���
//
//�����F(GAMEPADNUMBER)�Q�[���p�b�h�ԍ�,(DWORD)���̓{�^��,(PUSHTYPE)����^�C�v
//
//�߂�l�F(bool)���茋��
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
//�֐����FGetGamePadStick
//
//�@�\�F�Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓��͒l�擾
//
//�����F(JOYSTICKNUMBER)�Q�[���p�b�h�ԍ�,(GAMEPADDIRECTION)�擾�X�e�B�b�N
//
//�߂�l�F(D3DXVECTOR2)���͒l
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
//�֐����FGetGamePadTrigger
//
//�@�\�F�Q�[���p�b�h�̃g���K�[�̓��͒l�擾
//
//�����F(JOYSTICKNUMBER)�Q�[���p�b�h�ԍ�,(GAMEPADDIRECTION)�擾�g���K�[
//
//�߂�l�F(float)���͗�
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
//�֐����FGetKey
//
//�@�\�F�L�[�{�[�h���͔���
//
//�����F(DWORD)���̓{�^��,(PUSHTYPE)����^�C�v
//
//�߂�l�F(bool)���茋��
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
//�֐����FGetMouseButton
//
//�@�\�F�}�E�X�{�^�����͔���
//
//�����F(MOUSEBUTTON)���̓{�^��,(PUSHTYPE)����^�C�v
//
//�߂�l�F(bool)���茋��
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
//�֐����FGetMousePosition
//
//�@�\�F�}�E�X�̍��W�擾
//
//�����F�Ȃ�
//
//�߂�l�F(POINT)���W
/////////////////////////////////////////////
POINT INPUTMANAGER::GetMousePosition(void)
{
    return Mouse.GetCursor();
}