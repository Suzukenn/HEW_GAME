//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "StartButton.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBehavior
//
//�@�\�F�X�^�[�g�{�^���̋���
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void STARTBUTTON::Behavior(void)
{
    if (INPUTMANAGER::GetMouseButton(MOUSEBUTTON_LEFT, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAME);
    }
}