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
//�����F(LPCTSTR)�w�i�e�N�X�`��,(std::vector<tstring>&*)�������X�g,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDLIST::Initialize(LPCTSTR texturename, std::vector<tstring>& list, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    D3DXVECTOR2 vecPanelPosition;

    //---����������---//
    SelectNumber = 0;
    vecPanelPosition = D3DXVECTOR2(position.x + 20.0F, position.y + 30.0F);
    WordList.clear();

    for (auto& data : list)
    {
        WordList.emplace_back(data);
    }

    //---�I�u�W�F�N�g�̏�����---//
    //�w�i
    hResult = Back.Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h���X�g�̔w�i�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //���[�h�p�l��
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        hResult = WordPlate.at(nCounter).Initialize(WordList.at(nCounter).data(), D3DXVECTOR2(vecPanelPosition.x + 160.0F * nCounter, vecPanelPosition.y + 30.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���[�h���X�g���̃��[�h�p�l���̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    //�����e�N�X�`���̐ݒ�
    ResetTexture();

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
    //---�e��錾---//
    int nListSize;

    //---����������---//
    nListSize = (int)WordList.size();

    //---�e�N�X�`���̐ݒ�---//
    WordPlate.at(0).SetTexture(WordList.at((SelectNumber + nListSize - 1) % nListSize).data());
    WordPlate.at(1).SetTexture(WordList.at(SelectNumber % nListSize).data());
    WordPlate.at(2).SetTexture(WordList.at((SelectNumber + 1) % nListSize).data());
}

/////////////////////////////////////////////
//�֐����FResetWordNumber
//
//�@�\�F�I�𒆂̌��t�̔ԍ��̕ύX
//
//�����F(tstring)���t
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDLIST::ResetWordNumber(tstring word)
{
    //---�e��錾---//
    int nCounter;

    //---�I�𒆂̌��t�̒T��---//
    for (nCounter = 0; nCounter < WordList.size(); ++nCounter)
    {
        if (WordList.at(nCounter) == word)
        {
            SelectNumber = nCounter;
            return S_OK;
        }
    }
    return E_FAIL;
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
    //---�e��錾---//
    int nCounter;

    //---�J��---//
    Back.Uninitialize();
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        WordPlate.at(nCounter).Uninitialize();
    }
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
    //---�e��錾---//
    int nListSize;

    //---����������---//
    nListSize = (int)WordList.size();

    //---�J�[�\���ړ�---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + nListSize - 1) % nListSize;
        ResetTexture();
    }
    else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + 1) % nListSize;
        ResetTexture();
    }
}