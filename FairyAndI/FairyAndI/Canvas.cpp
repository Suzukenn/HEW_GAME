//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Canvas.h"
#include "InputManager.h"
#include "Player.h"

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
    //---�e��錾---//
    int nCounter;


    for (nCounter = 0; nCounter < PLAYER::GetPlayerHP(); ++nCounter)
    {
        Heart.at(nCounter).Draw();
    }

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
    int nCounter;
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

    //�n�[�g
    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        hResult = Heart.at(nCounter).Initialize(TEXT("HEART"), D3DXVECTOR2(10.0F + 60.0F * nCounter, 10.0F), D3DXVECTOR2(50.0F, 50.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�n�[�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            return hResult;
        }
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
    //---�e��錾---//
    int nCounter;

    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        Heart.at(nCounter).Uninitialize();
    }

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
    //---�e��錾---//
    int nCounter;

    //---�\�����[�h�؂�ւ�---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }

    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        Heart.at(nCounter).Update();
    }

    if (Mode)
    {
        Menu.Update();
        Item.Update();
        Item.SetTexture(WORDMENU::NotificationAdjective() + WORDMENU::NotificationNoun());
    }
    else
    {
        ItemBox.Update();
    }
}