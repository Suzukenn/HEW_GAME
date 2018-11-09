//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameOver.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

//�������֐���`������//
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
    //---�I�u�W�F�N�g�̏���������---//
    if (FAILED(Back.Initialize(TEXT("Data/Game/GameOver.png"))))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_GAMEOVER"));

    return S_OK;
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

    //---��ʑJ��---//
    if (INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TITLE);
    }
}