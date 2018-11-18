//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "WordMenu.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���[�h���j���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDMENU::Draw(void)
{
    //---�e��錾---//
    int nCounter;

    Back.Draw();
    SelectMarker.Draw();

    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        SelectWord.at(nCounter).Draw();
    }

    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        List.at(nCounter).Draw();
    }
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���[�h���j���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMENU::Initialize(void)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    const D3DXVECTOR2 vecListPosition[2] = { D3DXVECTOR2(50.0F, 500.0F), D3DXVECTOR2(750.0F, 500.0F) };
    const D3DXVECTOR2 vecPanelPosition[2] = { D3DXVECTOR2(400.0F, 130.0F), D3DXVECTOR2(750.0F, 130.0F) };
    LPCTSTR strWord[2] = { TEXT("ADJECTIVELIST"), TEXT("NOUNLIST") };
    LPCTSTR strList[2][WORD_VALUE] = {{ TEXT("HOT"), TEXT("COLD"), TEXT("HARD"), TEXT("SOFT") }, { TEXT("FIRE"), TEXT("ICE"), TEXT("ROCK"), TEXT("EARTH") }};

    //---����������---//
    State = SETTING_STATE_SELECT;

    //---�I�u�W�F�N�g�̏�����---//
    //�����o��
    hResult = Back.Initialize(TEXT("BALLON"), D3DXVECTOR2(350.0F, 100.0F), D3DXVECTOR2(600.0F, 250.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h���X�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //�����o���̒�
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = SelectWord.at(nCounter).Initialize(TEXT("LOCK"), vecPanelPosition[nCounter], D3DXVECTOR2(130.0F, 130.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���[�h���X�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    //�I�𕔕��\���}�[�J�[
    hResult = SelectMarker.Initialize(TEXT("MARKER"), D3DXVECTOR2(390.0F, 120.0F), D3DXVECTOR2(150.0F, 150.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h���X�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //���[�h���X�g
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = List.at(nCounter).Initialize(strWord[nCounter], strList[nCounter], vecListPosition[nCounter], D3DXVECTOR2(500.0F, 200.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���[�h���X�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���[�h���j���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDMENU::Uninitialize(void)
{
    //---�e��錾---//
    int nCounter;

    Back.Uninitialize();
    SelectMarker.Uninitialize();
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        SelectWord.at(nCounter).Uninitialize();
    }

    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        List.at(nCounter).Uninitialize();
    }
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���[�h���j���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDMENU::Update(void)
{
    //---�e��錾---//
    static int nNextState = SETTING_STATE_ADJECTIVELIST;

    switch (State)
    {
        //���͑I�����
        case SETTING_STATE_SELECT:

            //�ݒ�i���I��
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
            {
                SelectMarker.Update();
                nNextState = !nNextState;
            }

            //�����ݒ�
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                State = nNextState;
            }
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
            {
                return;
            }

            break;

        //�`�e���ݒ�
        case SETTING_STATE_ADJECTIVELIST:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B, TRIGGER))
            {
                State = SETTING_STATE_SELECT;
            }
            List.at(0).Update();
            SelectWord.at(0).SetTexture(List.at(0).GetSelectItem());
            break;

        //�����ݒ�
        case SETTING_STATE_NOUN:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B, TRIGGER))
            {
                State = SETTING_STATE_SELECT;
            }
            List.at(1).Update();
            SelectWord.at(1).SetTexture(List.at(1).GetSelectItem());
            break;
    }

    Back.Update();
}