//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameScene02.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

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
void GAME02::Draw(void)
{
    //---�I�u�W�F�N�g�̕`�揈��---//
    //Back.Draw();
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
HRESULT GAME02::Initialize(void)
{
    if (FAILED(TEXTUREMANAGER::Initialize(TEXT("Data/GameScene/TextureList.txt"))))
    {
        return E_FAIL;
    }

    //---�I�u�W�F�N�g�̏���������---//
    //if (FAILED(Back.Initialize(TEXT("BACKGROUND"))))
    //{
    //    return E_FAIL;
    //}

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
void GAME02::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();

    //---�e�N�X�`���̍폜---//
    TEXTUREMANAGER::Uninitialize();

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
void GAME02::Update(void)
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
}