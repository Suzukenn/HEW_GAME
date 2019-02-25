//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "SoundManager.h"
#include "TextureManager.h"

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
void SELECTSCENE::Draw(void)
{
    Back.Draw();

	switch (Select)
	{
		case SELECT_STAGE1:
			if (dwTicks & dwMask)
			{
				Button1.Draw();
			}
			Button2.Draw();
			Button3.Draw();
			break;
		case SELECT_STAGE2:
			if (dwTicks & dwMask)
			{
				Button2.Draw();
			}
			Button1.Draw();
			Button3.Draw();
			break;
		case SELECT_STAGE3:
			if (dwTicks & dwMask)
			{
				Button3.Draw();
			}
			Button1.Draw();
			Button2.Draw();
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
HRESULT SELECTSCENE::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

	dwTicks = 0;
	dwMask = 8;
	Select = SELECT_STAGE1;

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/SelectScene/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---�I�u�W�F�N�g�̏�����---//
    hResult = Back.Initialize(TEXT("BACKGROUND"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

	hResult = Button1.Initialize(TEXT("BACKGROUND"),D3DXVECTOR2(200.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
	if (FAILED(hResult))
	{
		return E_FAIL;
	}

	hResult = Button2.Initialize(TEXT("BACKGROUND"),D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
	if (FAILED(hResult))
	{
		return E_FAIL;
	}

	hResult = Button3.Initialize(TEXT("BACKGROUND"), D3DXVECTOR2(800.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
	if (FAILED(hResult))
	{
		return E_FAIL;
	}

	FADE::SetFade(FADE_IN);

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_SELECT"));

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
void SELECTSCENE::Uninitialize(void)
{
    //---���---//
    Back.Uninitialize();

	Button1.Uninitialize();
	Button2.Uninitialize();
	Button3.Uninitialize();

    TEXTUREMANAGER::Uninitialize();

    //---BGM��~---//
    SOUNDMANAGER::Stop(TEXT("BGM_SELECT"));
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
void SELECTSCENE::Update(void)
{
	//---�e��錾---//
	D3DXVECTOR2 vecStickVector;
	static int IntervalCnt;

	vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);
	dwTicks++;

    //---�I�u�W�F�N�g�̍X�V---//
    Back.Update();
	Button1.Update();
	Button2.Update();
	Button3.Update();

	IntervalCnt++;
	if (IntervalCnt > 60 / 3)
	{
		//�E�ɃX�e�B�b�N�����
		if (vecStickVector.x > 0.0F)
		{
			IntervalCnt = 0;
			Select++;
			if (Select > SELECT_MAX - 1)
			{
				Select = SELECT_MAX - 1;
			}
		}
		//���X�e�B�b�N�����
		else if (vecStickVector.x < 0.0F)
		{
			IntervalCnt = 0;
			Select--;
			if (Select < 0)
			{
				Select = 0;
			}
		}
	}

	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
		dwMask = 2;
		FADE::SetFade(FADE_OUT);
	}
	else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
	{
		SCENEMANAGER::SetScene(SCENE_TITLE);
	}

	//�t�F�[�h�A�E�g���I����Ă�����
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		switch (Select)
		{
			case SELECT_STAGE1:
				SCENEMANAGER::SetScene(SCENE_GAME);
				break;
			case SELECT_STAGE2:
				SCENEMANAGER::SetScene(SCENE_TITLE);
				break;
			case SELECT_STAGE3:
				SCENEMANAGER::SetScene(SCENE_GAMECLEAR);
				break;
			default:
				break;
		}
	}
}