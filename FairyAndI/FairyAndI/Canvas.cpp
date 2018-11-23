//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Canvas.h"
#include "InputManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CANVAS::Draw(void)
{
    if (Mode)
    {
        Menu.Draw();
    }
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT CANVAS::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = WORDMENU::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    Mode = false;

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�w�i�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CANVAS::Uninitialize(void)
{
    Menu.Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CANVAS::Update(void)
{
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER) || INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        Mode = !Mode;
    }

    if (Mode)
    {
        Menu.Update();
    }
}