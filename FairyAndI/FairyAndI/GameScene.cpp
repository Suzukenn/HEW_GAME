//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�Q�[���V�[���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME::Draw(void)
{
    //---�I�u�W�F�N�g�̕`�揈��---//
    Back.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�Q�[���V�[���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GAME::Initialize(void)
{
    //---�I�u�W�F�N�g�̏���������---//
    if (FAILED(Back.Initialize(TEXT("Data/Game/BackGround.tga"))))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_GAME"));

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�Q�[���V�[���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();

    //---BGM��~---//
    SOUNDMANAGER::Stop(TEXT("BGM_GAME"));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�Q�[���V�[���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V����---//
    Back.Update();

    //---��ʑJ��---//
    if (INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }

    if (INPUTMANAGER::GetGamePadTrigger(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT))
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }
}