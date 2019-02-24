//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <fstream>
#include <vector>
#include "Main.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "WordMenu.h"
#include "WordManager.h"

//�������O���[�o���錾������//
int WORDMENU::State;
bool WORDMENU::Control;
BACKIMAGE WORDMENU::Back;
SELECTMARKER WORDMENU::SelectMarker;

std::array<WORDPLATE, 2> WORDMENU::SelectWord;
std::array<WORDLIST, 2> WORDMENU::List;

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

    if (!Control)
    {
        return;
    }

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
    const LPCTSTR strWord[2] = { TEXT("ADJECTIVELIST"), TEXT("NOUNLIST") };
    std::vector<std::vector<tstring>> conList;

    //---����������---//
    Control = false;
    State = SETTING_STATE_SELECT;

    //�f�[�^�̃��[�h
    hResult = Load(conList);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h�y�A�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�I�u�W�F�N�g�̏�����---//
    //�����o��
    hResult = Back.Initialize(TEXT("BALLOON"), D3DXVECTOR2(350.0F, 100.0F), D3DXVECTOR2(600.0F, 250.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�����o���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //�I�𒆂̌��t�̏�����
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = SelectWord.at(nCounter).Initialize(TEXT("EMPTY"), vecPanelPosition[nCounter]);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�|�����킹�p�l���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    //�I�𕔕��\���}�[�J�[
    hResult = SelectMarker.Initialize(TEXT("MARKER"), D3DXVECTOR2(390.0F, 120.0F), D3DXVECTOR2(150.0F, 150.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�I���}�[�J�[�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //���[�h���X�g
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = List.at(nCounter).Initialize(strWord[nCounter], conList.at(nCounter), vecListPosition[nCounter], D3DXVECTOR2(500.0F, 200.0F));
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
//�֐����FLoad
//
//�@�\�F�y�A�̍쐬
//
//�����F(std::vector<std::vector<tstring>>&)�i�[���X�g
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDMENU::Load(std::vector<std::vector<tstring>>& list)
{
    //---�e��錾---//
    std::string szAdjective;
    std::string szNoun;
    std::wstring wszAdjective;
    std::wstring wszNoun;
    std::ifstream file;

    //---����������---//
    list.resize(2);

    //---�t�@�C���̓ǂݍ���---//
    file.open(TEXT("Data/GameScene/Word/WordPair.txt"));
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("���[�h�y�A���X�g���J���܂���ł���"), TEXT("Data/GameScene/Word/WordPair.txt"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---�f�[�^�̒��o---//
    while (!file.eof())
    {
        file >> szNoun >> szAdjective;

#ifdef _UNICODE
        wszNoun = std::wstring(szNoun.begin(), szNoun.end());
        wszNoun.shrink_to_fit();
        wszAdjective = std::wstring(szAdjective.begin(), szAdjective.end());
        wszAdjective.shrink_to_fit();
        list.at(0).emplace_back(wszAdjective);
        list.at(1).emplace_back(wszNoun);
#else
        list.at(0).emplace_back(szNoun);
        list.at(1).emplace_back(szAdjective);
#endif
    }

    return S_OK;
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

    //---�J��---//
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
    bool bCheck;
    static int nNextState = SETTING_STATE_ADJECTIVELIST;
    static LPCTSTR strCurrentWord;

    //---���[�h�ؑ�---//
    if (State == SETTING_STATE_SELECT && INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Control = !Control;
    }
    if (Control)
    {
        SelectWord.at(0).SetTexture(List.at(0).GetSelectWord());
        SelectWord.at(1).SetTexture(List.at(1).GetSelectWord());
    }
    else
    {
        return;
    }

    //---�e�폈��---//
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
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                strCurrentWord = List.at(nNextState).GetSelectWord();
                State = nNextState;
            }

            break;

        //�`�e���ݒ�
        case SETTING_STATE_ADJECTIVELIST:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                if (FAILED(WORDMANAGER::GetWordLock(List.at(0).GetSelectWord(), bCheck)))
                {
                    MessageBox(nullptr, TEXT("�P�ꂪ������܂���ł���"), TEXT("�G���["), MB_ICONSTOP | MB_OK);
                    Uninitialize();
                    exit(EXIT_FAILURE);
                }

                bCheck ? State = SETTING_STATE_SELECT : SOUNDMANAGER::Play(TEXT("SE_SHOT"));
            }
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
            {
                SelectWord.at(0).SetTexture(strCurrentWord);
                List.at(0).ResetWordNumber(strCurrentWord);
                State = SETTING_STATE_SELECT;
            }
            else
            {
                SelectWord.at(0).SetTexture(List.at(0).GetSelectWord());
                List.at(0).Update();
            }
            break;

        //�����ݒ�
        case SETTING_STATE_NOUN:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                if (FAILED(WORDMANAGER::GetWordLock(List.at(1).GetSelectWord(), bCheck)))
                {
                    MessageBox(nullptr, TEXT("�P�ꂪ������܂���ł���"), TEXT("�G���["), MB_ICONSTOP | MB_OK);
                    Uninitialize();
                    exit(EXIT_FAILURE);
                }

                bCheck ? State = SETTING_STATE_SELECT : SOUNDMANAGER::Play(TEXT("SE_SHOT"));
            }
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
            {
                SelectWord.at(1).SetTexture(strCurrentWord);
                List.at(1).ResetWordNumber(strCurrentWord);
                State = SETTING_STATE_SELECT;
            }
            else
            {
                SelectWord.at(1).SetTexture(List.at(1).GetSelectWord());
                List.at(1).Update();
            }
            break;
    }

    //�e���X�g�̍X�V
    List.at(0).ResetTexture();
    List.at(1).ResetTexture();

    //�w�i�̍X�V
    Back.Update();
}