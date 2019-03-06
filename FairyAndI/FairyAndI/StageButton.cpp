//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Fade.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "StageButton.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBehavior
//
//�@�\�F�X�e�[�W�{�^���̋���
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void STAGEBUTTON::Behavior(void)
{
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
		{
			FADE::SetFade(FADE_OUT);
		}
	}
	//�t�F�[�h�A�E�g���I����Ă�����
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		SCENEMANAGER::SetScene(Stage);
	}
}

/////////////////////////////////////////////
//�֐����FSetSelectStage
//
//�@�\�F�X�e�[�W�̍s����Z�b�g
//
//�����F(SCENE)�X�e�[�W�̍s����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void STAGEBUTTON::SetSelectStage(SCENE stage)
{
	Stage = stage;
}
