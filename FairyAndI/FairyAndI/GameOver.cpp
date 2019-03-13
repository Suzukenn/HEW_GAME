//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameOver.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

SCENE GAMEOVER::RetryScene;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FChooseStage
//
//�@�\�F�X�e�[�W�̑I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::ChooseButton(void)
{
	//---�e��錾---//
	D3DXVECTOR2 vecStickVector;
	static int IntervalCnt;

	vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	++IntervalCnt;
	if (IntervalCnt > 60 / 3)
	{
		IntervalCnt = 60 / 3;
		//�E�ɃX�e�B�b�N�����
		if (vecStickVector.y > 0.0F)
		{
            SOUNDMANAGER::Stop(TEXT("SE_CURSOR"));
            SOUNDMANAGER::Play(TEXT("SE_CURSOR"));

			IntervalCnt = 0;
			--Select;
			CursorPos.y -= 100.0F;
			if (Select < 0)
			{
				Select = 0;
				CursorPos.y = 400.0F;
			}
		}
		//���ɃX�e�B�b�N�����
		else if (vecStickVector.y < 0.0F)
		{
            SOUNDMANAGER::Stop(TEXT("SE_CURSOR"));
            SOUNDMANAGER::Play(TEXT("SE_CURSOR"));

			IntervalCnt = 0;
			++Select;
			CursorPos.y += 100.0F;
			if (Select > GAMEOVER_BUTTON - 1)
			{
				Select = GAMEOVER_BUTTON - 1;
				CursorPos.y = 500.0F;
			}
		}
	}
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�Q�[���I�[�o�[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Draw(void)
{
    //---�I�u�W�F�N�g�̕`�揈��---//
    Back.Draw();
	Logo.Draw();
	if (LogoAlpha == 255)
	{
		for (int nConter = 0; nConter < GAMEOVER_BUTTON; ++nConter)
		{
			SelectButton.at(nConter).Draw();
		}
		Cursor.Draw();
	}
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�Q�[���I�[�o�[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAMEOVER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

	//---����������---//
	LogoAlpha = 0;
	CursorPos = D3DXVECTOR2(350.0F, 400.0F);
	Select = 0;
	RetryScene = SCENE_GAMECLEAR;			//��������ŏ�������

    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/GameOver/TextureList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = Back.Initialize(TEXT("BACKGROUND"));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//���S
    hResult = Logo.Initialize((TEXT("GAMEOVER")), D3DXVECTOR2(300.0F, 100.0F), D3DXVECTOR2(700.0F, 350.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
    
    //�Z���N�g�V�[���s���̃{�^��
    hResult = SelectButton.at(0).Initialize((TEXT("RETRY")), D3DXVECTOR2(500.0F, 400.0F), D3DXVECTOR2(300.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//�^�C�g���s���̃{�^��
    hResult = SelectButton.at(1).Initialize((TEXT("RETURN_TITLE")), D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(300.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//�J�[�\��
    hResult = Cursor.Initialize(TEXT("CURSOR"), CursorPos, D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_GAMEOVER"));

	//�t�F�[�h�J�n
	FADE::SetFade(FADE_IN);

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�Q�[���I�[�o�[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();
	Logo.Uninitialize();
	for (int nConter = 0; nConter < GAMEOVER_BUTTON; ++nConter)
	{
		SelectButton.at(nConter).Uninitialize();
	}
	Cursor.Uninitialize();

    //---�e�N�X�`���̍폜---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM��~---//
    SOUNDMANAGER::Stop(TEXT("BGM_GAMEOVER"));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�Q�[���I�[�o�[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V����---//
    Back.Update();
	Logo.Update();
	Logo.SetAlpha((unsigned char)LogoAlpha);

	//�t�F�[�h�C�����I����Ă�����
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		if (++LogoAlpha >= 255)
		{
			LogoAlpha = 255;
		}

		ChooseButton();
		Cursor.SetPosition(CursorPos);

		//---��ʑJ��---//
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, 0xFFFF, TRIGGER))
		{
            SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
            SOUNDMANAGER::Play(TEXT("SE_ENTER"));

			if (LogoAlpha == 255)
			{
				FADE::SetFade(FADE_OUT);
			}
			else
			{
				LogoAlpha = 255;
			}
		}
	}
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		if (Select == 0)
		{
			SCENEMANAGER::SetScene(RetryScene);
		}
		else
		{
			SCENEMANAGER::SetScene(SCENE_TITLE);
		}
	}
}

/////////////////////////////////////////////
//�֐����FSetRetryScene
//
//�@�\�F���g���C��̃Z�b�g
//
//�����F(SCENE)���g���C����V�[��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMEOVER::SetRetryScene(SCENE retryScene)
{
	RetryScene = retryScene;
}