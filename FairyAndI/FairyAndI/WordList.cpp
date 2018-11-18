//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "WordList.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���[�h���X�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDLIST::Draw(void)
{
    //---�e��錾---//
    int nCounter;

    Back.Draw();
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        WordPlate.at(nCounter).Draw();
    }
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���[�h���X�g�̏�����
//
//�����F(LPCTSTR)�w�i�e�N�X�`��,(LPCTSTR*)�������X�g,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDLIST::Initialize(LPCTSTR texturename, LPCTSTR* list, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    D3DXVECTOR2 vecPanelPosition;

    //---����������---//
    SelectNumber = 1;
    vecPanelPosition = D3DXVECTOR2(position.x + 20.0F, position.y + 30.0F);

    for (nCounter = 0; nCounter < WORD_VALUE; ++nCounter)
    {
        WordList.at(nCounter) = (*(list + nCounter));
    }

    //---�I�u�W�F�N�g�̏�����---//
    //�w�i
    hResult = Back.Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        return hResult;
    }

    //���[�h�p�l��
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        hResult = WordPlate.at(nCounter).Initialize(WordList.at(nCounter), D3DXVECTOR2(vecPanelPosition.x + 160.0F * nCounter, vecPanelPosition.y + 30.0F), D3DXVECTOR2(130.0F, 130.0F));
        if (FAILED(hResult))
        {
            return hResult;
        }
    }

    //���b�N�`�F�b�N
    for (nCounter = 0; nCounter < WORD_VALUE; ++nCounter)
    {
        UnlockCheck.at(nCounter) = false;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FResetTexture
//
//�@�\�F�p�l���̕\���e�N�X�`���̐ݒ�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDLIST::ResetTexture(void)
{
    WordPlate.at(0).SetTexture(WordList.at((SelectNumber + WORD_VALUE - 1) % WORD_VALUE));
    WordPlate.at(1).SetTexture(WordList.at(SelectNumber % WORD_VALUE));
    WordPlate.at(2).SetTexture(WordList.at((SelectNumber + 1) % WORD_VALUE));
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���[�h���X�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDLIST::Uninitialize(void)
{
    Back.Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���[�h���X�g�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDLIST::Update(void)
{
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + WORD_VALUE + 1) % WORD_VALUE;
        ResetTexture();
    }
    else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + 1) % WORD_VALUE;
        ResetTexture();
    }

    //------//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + WORD_VALUE + 1) % WORD_VALUE;
        ResetTexture();
    }
}