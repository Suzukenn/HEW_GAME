//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Fade.h"
#include "GameClear.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

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
void GAMECLEAR::ChooseButton(void)
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
			if (Select > GAMECLEAR_BUTTON - 1)
			{
				Select = GAMECLEAR_BUTTON - 1;
				CursorPos.y = 500.0F;
			}
		}
	}
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�Q�[���N���A�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMECLEAR::Draw(void)
{
    //---�I�u�W�F�N�g�̕`�揈��---//
    Back.Draw();
	for (int nConter = 0; nConter < GAMECLEAR_BUTTON; ++nConter)
	{
		SelectButton.at(nConter).Draw();
	}
	Cursor.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�Q�[���N���A�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAMECLEAR::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

	//---�e�평��---//
	CursorPos = D3DXVECTOR2(350.0F, 400.0F);
	Select = 0;

    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/GameClear/TextureList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---�I�u�W�F�N�g�̏���������---//
    hResult = Back.Initialize(TEXT("BACKGROUND"));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//�Z���N�g�V�[���s���̃{�^��
    hResult = SelectButton.at(0).Initialize((TEXT("SELECT_STAGE")), D3DXVECTOR2(500.0F, 400.0F), D3DXVECTOR2(300.0F, 100.0F));
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

	FADE::SetFade(FADE_IN);

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_GAMEOVER"));

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�Q�[���N���A�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMECLEAR::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();
	for (int nConter = 0; nConter < GAMECLEAR_BUTTON; ++nConter)
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
//�@�\�F�Q�[���N���A�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAMECLEAR::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V����---//
    Back.Update();

	if (FADE::CheckFadeEnd(FADE_IN))
	{
		ChooseButton();
		Cursor.SetPosition(CursorPos);

		//---��ʑJ��---//
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
		{
            SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
            SOUNDMANAGER::Play(TEXT("SE_ENTER"));

			FADE::SetFade(FADE_OUT);
		}

	}
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		if (Select == 0)
		{
			SCENEMANAGER::SetScene(SCENE_SELECT);
		}
		else
		{
			SCENEMANAGER::SetScene(SCENE_TITLE);
		}
	}
}