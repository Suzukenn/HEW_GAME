//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Canvas.h"
#include "InputManager.h"
#include "Player.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�L�����o�X�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CANVAS::Draw(void)
{
    //---�e��錾---//
    int nCounter;

    //---�`��---//
    for (nCounter = 0; nCounter < PLAYER::GetPlayerHP(); ++nCounter)
    {
        Heart.at(nCounter).Draw();
    }

    SkillBox.Draw();
    Skill.Draw();
    Menu.Draw();
    TimeGauge.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�L�����o�X�̏�����
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

    //�X�L���{�b�N�X
    hResult = SkillBox.Initialize(TEXT("SKILLBOX"), D3DXVECTOR2(1050.0F, 10.0F), D3DXVECTOR2(150.0F, 150.0F), { 2, 1 });
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�A�C�e���{�b�N�X�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //�X�L��
    hResult = Skill.Initialize(TEXT("EMPTY"), D3DXVECTOR2(1076.0F, 35.0F), D3DXVECTOR2(100.0F, 100.0F));
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

    //�^�C���Q�[�W
    hResult = TimeGauge.Initialize(TEXT("GAUGEBACK"), TEXT("GAUGEMEMORY"), D3DXVECTOR2(400.0F, 10.0F), D3DXVECTOR2(200.0F, 50.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�^�C���Q�[�W�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    Mode = false;

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�L�����o�X�̏I��
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

    SkillBox.Uninitialize();
    Skill.Uninitialize();
    Menu.Uninitialize();
    TimeGauge.Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�L�����o�X�̍X�V
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

    Menu.Update();
    SkillBox.Update();
    if (Mode)Skill.SetTexture(WORDMENU::NotificationAdjective() + WORDMENU::NotificationNoun());
    TimeGauge.Update();
}