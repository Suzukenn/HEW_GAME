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

	Timer.Draw();

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
        hResult = Heart.at(nCounter).Initialize(TEXT("HEART"), D3DXVECTOR2(10.0F + 60.0F * nCounter, 10.0F), D3DXVECTOR2(90.0F, 70.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�n�[�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            return hResult;
        }
    }

    //�^�C���Q�[�W
    hResult = TimeGauge.Initialize(TEXT("GAUGEBACK"), TEXT("GAUGEMEMORY"), D3DXVECTOR2(720.0F, -10.0F), D3DXVECTOR2(300.0F, 120.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�^�C���Q�[�W�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //�^�C�}�[
	hResult = Timer.Initialize(TEXT("TIMER"), D3DXVECTOR2(580.0F, 30.0F), D3DXVECTOR2(30.0F, 60.0F), 10);
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

	Timer.Uninitialize();

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
  /*  if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }*/
	Mode = SQUAREGAUGE::GetFairyTime();

    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        Heart.at(nCounter).Update();
    }

	Timer.Update();

    Menu.Update();
    SkillBox.Update();
    if (Mode)Skill.SetTexture(tstring(WORDMENU::NotificationAdjective() + WORDMENU::NotificationNoun()).data());
    TimeGauge.Update();
}