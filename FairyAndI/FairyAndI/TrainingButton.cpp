//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "TrainingButton.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBehavior
//
//�@�\�F�g���[�j���O�{�^���̋���
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TRAININGBUTTON::Behavior(void)
{
    if (INPUTMANAGER::GetMouseButton(MOUSEBUTTON_LEFT, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TRAINING);
    }
}