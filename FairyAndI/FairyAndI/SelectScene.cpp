//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
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
void SELECTSCENE::ChooseStage(void)
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
		if (vecStickVector.x > 0.0F)
		{
			IntervalCnt = 0;
			++Select;
			if (Select > MAX_SELECTBUTTON - 1)
			{
				Select = MAX_SELECTBUTTON - 1;
			}
		}
		//���ɃX�e�B�b�N�����
		else if (vecStickVector.x < 0.0F)
		{
			IntervalCnt = 0;
			--Select;
			if (Select < 0)
			{
				Select = 0;
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
void SELECTSCENE::Draw(void)
{
	Back.Draw();

	for (int nConter = 0; nConter < 3; ++nConter)
	{
		if (Select == nConter)
		{
			if (dwTicks & dwMask)
			{
				Button.at(nConter).Draw();
			}
			continue;
		}
		Button.at(nConter).Draw();
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
	D3DXVECTOR2 ButtonPos;

	ButtonPos = D3DXVECTOR2(200.0F, 500.0F);
	dwTicks = 0;
	dwMask = 8;
	Select = 0;

	//�e�{�^���̍s����
	Button.at(0).SetSelectStage(SCENE_TRAINING);
	Button.at(1).SetSelectStage(SCENE_TITLE);
	Button.at(2).SetSelectStage(SCENE_GAMECLEAR);

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

	for (int nConter = 0; nConter < 3; ++nConter)
	{
		hResult = Button.at(nConter).Initialize(TEXT("BACKGROUND"), ButtonPos, D3DXVECTOR2(200.0F, 50.0F));
		if (FAILED(hResult))
		{
			return E_FAIL;
		}

		ButtonPos.x += 300.0F;
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

	for (int nConter = 0; nConter < 3; ++nConter)
	{
		Button.at(nConter).Uninitialize();
	}

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
	++dwTicks;

	//---�I�u�W�F�N�g�̍X�V---//
	Back.Update();
	for (int nConter = 0; nConter < 3; ++nConter)
	{
		if (Select == nConter)
		{
			Button.at(nConter).Update();
		}
	}

	if (FADE::CheckFadeEnd(FADE_IN))
	{
		ChooseStage();

		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
		{
			SCENEMANAGER::SetScene(SCENE_TITLE);
		}
	}
}
