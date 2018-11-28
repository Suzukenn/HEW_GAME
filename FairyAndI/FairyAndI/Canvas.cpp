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
    ItemBox.Draw();
    Item.Draw();
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

    //�A�C�e���{�b�N�X
    hResult = ItemBox.Initialize(TEXT("ITEMBOX"), D3DXVECTOR2(1050.0F, 10.0F), D3DXVECTOR2(150.0F, 150.0F), { 2, 1 });
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�A�C�e���{�b�N�X�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }
    //�A�C�e��
    hResult = Item.Initialize(TEXT("UNKNOWN"), D3DXVECTOR2(1060.0F, 15.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�A�C�e���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
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
    ItemBox.Uninitialize();
    Item.Uninitialize();
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
    //---�\�����[�h�؂�ւ�---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER) || INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        Mode = !Mode;
    }


    if (Mode)
    {
        Menu.Update();
        Item.Update();
        Item.SetTexture(WORDMENU::NotificationItem());
    }
    else
    {
        ItemBox.Update();
    }
}