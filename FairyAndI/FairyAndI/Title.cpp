//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingButton.h"
#include "Title.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�^�C�g���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Draw(void)
{
    //---�I�u�W�F�N�g�̕`�揈��---//
    Back.Draw();
    StartButton.Draw();
    TrainingButton.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�^�C�g���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TITLE::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Title/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---�I�u�W�F�N�g�̏���������---//
    //�w�i
    hResult = Back.Initialize((TEXT("BACKGROUND")));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�X�^�[�g�{�^��
    hResult = StartButton.Initialize(TEXT("START_BUTTON"), D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�g���[�j���O�{�^��
    hResult = FAILED(TrainingButton.Initialize(TEXT("TRAINING_BUTTON"), D3DXVECTOR2(800.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F)));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_TITLE"));

	//�t�F�[�h�J�n
	FADE::SetFade(FADE_IN);

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�^�C�g���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();
    StartButton.Uninitialize();
    TrainingButton.Uninitialize();

    //---�e�N�X�`���̍폜---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM��~---//
    SOUNDMANAGER::Stop(TEXT("BGM_TITLE"));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�^�C�g���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Update(void)
{
	static int Mood;

    //---�I�u�W�F�N�g�̍X�V����---//
    Back.Update();
    StartButton.Update();
    TrainingButton.Update();

	//�t�F�[�h�C�����I����Ă�����
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
		{
			FADE::SetFade(FADE_OUT);
			//SCENEMANAGER::SetScene(SCENE_SELECT);
			Mood = 1;
		}
		else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_START, TRIGGER))
		{
			FADE::SetFade(FADE_OUT);
			//SCENEMANAGER::SetScene(SCENE_TRAINING);
			Mood = 2;
		}
	}
	//�t�F�[�h�A�E�g���I����Ă�����
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		if (Mood == 1)
		{
			SCENEMANAGER::SetScene(SCENE_SELECT);
		}
		else if(Mood == 2)
		{
			SCENEMANAGER::SetScene(SCENE_TRAINING);
		}
	}
}