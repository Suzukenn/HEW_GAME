//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "ItemMenu.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TrainingScene.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�g���[�j���O�V�[���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ITEMMENU::Draw(void)
{
    //---�J�����̃Z�b�g---//

    //---�I�u�W�F�N�g�̕`�揈��---//
    //Back.Draw();
    //Debugger.Draw();
    //Field.Draw();
    //Sprite.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�g���[�j���O�V�[���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ITEMMENU::Initialize(void)
{
    //---�I�u�W�F�N�g�̏���������---//
    //�w�i
    //if (FAILED(Back.Initialize(D3DXVECTOR2(100.0F, 500.0F), D3DXVECTOR2(0.0F, 0.0F), TEXT("Data/GameScene/BackGround.tga"))))
    //{
    //    return E_FAIL;
    //}

    ////�J����
    //if (FAILED(FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F))))
    //{
    //    return E_FAIL;
    //}

    //�f�o�b�K�[
    //if (FAILED(Debugger.Initialize()))
    //{
    //    return E_FAIL;
    //}

    //�n�`
    //if (FAILED(Field.Initialize(TEXT("Data/Training/Texture/Field.jpg"), 40, 40, 8.0F, 8.0F)))
    //{
    //    return E_FAIL;
    //}

    ////�f�B���N�V���i�����C�g
    //if (FAILED(DIRECTIONALLIGHT::Initialize()))
    //{
    //    return E_FAIL;
    //}

    ////�X�v���C�g
    //if (FAILED(Sprite.Initialize({ 0.0F,0.0F }, { SCREEN_WIDTH,SCREEN_HEIGHT }, TEXT("Data/GameScene/BackGround.tga"))))
    //{
    //    return E_FAIL;
    //}

    //---BGM�Đ�---//
    //SOUNDMANAGER::Play(TEXT("BGM_TRAINING"));

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�g���[�j���O�V�[���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ITEMMENU::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    //Back.Uninitialize();
    //FlexibleCamera.Uninitialize();
    //Debugger.Uninitialize();
    //DIRECTIONALLIGHT::Uninitialize();
    //Field.Uninitialize();
    //Sprite.Uninitialize();

    //---BGM��~---//
    //SOUNDMANAGER::Stop(TEXT("BGM_TRAINING"));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�g���[�j���O�V�[���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ITEMMENU::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V����---//
    //Back.Update();
    //FlexibleCamera.Update();
    //Debugger.Update();
    //DIRECTIONALLIGHT::Update();
    //Field.Update();
    //Sprite.Update();

    ////---��ʑJ��---//
    //if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
    //{
    //    SCENEMANAGER::SetScene(SCENE_TITLE);
    //}
}