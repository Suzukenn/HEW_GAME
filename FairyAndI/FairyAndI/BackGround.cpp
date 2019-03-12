//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "SideViewCamera.h"

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
void BACKGROUND::Draw(void)
{
    Billboard.Draw(Position);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Position = position;

    hResult = Billboard.Initialize(texturename, scale);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

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
void BACKGROUND::Uninitialize(void)
{
    Billboard.Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�̍X�V
//
//�����F(float)�ړ���
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BACKGROUND::Update(float value)
{
    //---�e��錾---//
    float Stick;

    Stick = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT).x;

    if (Stick)
    {
        Position.x += 1.0F * Stick;
        Billboard.MoveTexture(value * Stick);
    }
    else
    {
        Billboard.MoveTexture(value);
    }
    Billboard.Update();
}