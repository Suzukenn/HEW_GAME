//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingButton.h"
#include "Title.h"

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
void TITLE::ChooseStage(void)
{
	//---�e��錾---//
	D3DXVECTOR2 vecStickVector;
	static int IntervalCnt;

	vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	++IntervalCnt;
	if (IntervalCnt > 60 / 3)
	{
		IntervalCnt = 60 / 3;
		//��ɃX�e�B�b�N�����
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
				CursorPos.y = 450.0F;
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
			if (Select > TITLE_BUTTON - 1)
			{
				Select = TITLE_BUTTON - 1;
				CursorPos.y = 550.0F;
			}
		}
	}
}
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
	int nConter;

    //---�I�u�W�F�N�g�̕`�揈��---//
    AnimationBack.Draw();
    Back.Draw();
    Logo.Draw();

	switch (Mode)
	{
		case MODE_FIRST:
			if (dwTicks & dwMask)
			{
				FirstButton.Draw();
			}
			break;

		case MODE_SELECT:
			for (nConter = 0; nConter < TITLE_BUTTON; ++nConter)
			{
				SelectButton.at(nConter).Draw();
			}
			Cursor.Draw();
			break;

		case MODE_MANUAL:
			break;

		default:
			break;
	}
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

	//---�e�평����---//
	dwTicks = 0;
	dwMask = 8;
	Select = 0;
	CursorPos = D3DXVECTOR2(350.0F, 450.0F);
	Mode = MODE_FIRST;
	LogoAlpha = 0;

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Title/TextureList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---�I�u�W�F�N�g�̏���������---//
    //�_
    hResult = AnimationBack.Initialize((TEXT("TITLE_BACK")));
    if (FAILED(hResult))
    {
        return hResult;
    }
    
    //�r���Q
    hResult = Back.Initialize((TEXT("TITLE_FRONT")));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�^�C�g�����S
    hResult = Logo.Initialize((TEXT("TITLE_LOGO")), D3DXVECTOR2(300.0F, 100.0F), D3DXVECTOR2(700.0F, 350.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//�ŏ��̃{�^��
	hResult = FirstButton.Initialize(TEXT("PUSHBUTTON"), D3DXVECTOR2(450.0F, 500.0F), D3DXVECTOR2(400.0F, 200.0F));
	if (FAILED(hResult))
	{
		return hResult;
	}

    //�X�^�[�g
    hResult = SelectButton.at(0).Initialize(TEXT("GAMESTART"), D3DXVECTOR2(450.0F, 400.0F), D3DXVECTOR2(400.0F, 200.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
	//�}�j���A��
	hResult = SelectButton.at(1).Initialize(TEXT("MANUAL"), D3DXVECTOR2(450.0F, 500.0F), D3DXVECTOR2(400.0F, 200.0F));
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
    SOUNDMANAGER::Play(TEXT("BGM_TITLE"));

	//�t�F�[�h�J�n
	FADE::SetFade(FADE_IN);

    return hResult;
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
	int nConter;

    //---�I�u�W�F�N�g�̏I������---//
    AnimationBack.Uninitialize();
    Back.Uninitialize();
    Logo.Uninitialize();
	FirstButton.Uninitialize();
	for (nConter = 0; nConter < TITLE_BUTTON; ++nConter)
	{
		SelectButton.at(nConter).Uninitialize();
	}
	Cursor.Uninitialize();

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
	//---�I�u�W�F�N�g�̍X�V����---//
    AnimationBack.MoveTexture();
    Back.Update();
    Logo.Update();
	FirstButton.Update();
	Logo.SetAlpha((unsigned char)LogoAlpha);

	//�t�F�[�h�C�����I����Ă�����
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		++LogoAlpha;
		if (LogoAlpha >= 255)
		{
			LogoAlpha = 255;
			++dwTicks;
		}

		switch (Mode)
		{
			case MODE_FIRST:
				if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, 0xFFFF, TRIGGER))
				{
                    SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
                    SOUNDMANAGER::Play(TEXT("SE_ENTER"));

					if (LogoAlpha == 255)
					{
						Mode = MODE_SELECT;
					}
					else
					{
						LogoAlpha = 255;
					}
				}
				break;

			case MODE_SELECT:
				ChooseStage();
				Cursor.SetPosition(CursorPos);
				if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
				{
                    SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
                    SOUNDMANAGER::Play(TEXT("SE_ENTER"));

					if (!Select)
					{
						FADE::SetFade(FADE_OUT);
					}
					else
					{
						Mode = MODE_MANUAL;
					}
				}
				else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
				{
                    SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
                    SOUNDMANAGER::Play(TEXT("SE_ENTER"));

					Mode = MODE_FIRST;
				}
				break;

			case MODE_MANUAL:
                SCENEMANAGER::SetScene(SCENE_TRAINING);
                break;

			default:
				break;
		}
	}
	//�t�F�[�h�A�E�g���I����Ă�����
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		SCENEMANAGER::SetScene(SCENE_SELECT);
	}
}