//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Debug.h"
#include "DirectionalLight.h"
#include "FlexibleCamera.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
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
void TRAINING::Draw(void)
{
    //---�J�����̃Z�b�g---//

    //---�I�u�W�F�N�g�̕`�揈��---//
    //Back.Draw();
    //Debugger.Draw();
    Field.Draw();
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
HRESULT TRAINING::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Training/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---�I�u�W�F�N�g�̏���������---//
    //�w�i
    hResult = Back.Initialize(TEXT("BACKGROUND"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�J����
    hResult = FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�f�o�b�K�[
    //if (FAILED(Debugger.Initialize()))
    //{
    //    return E_FAIL;
    //}

    //�n�`
    hResult = Field.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�f�B���N�V���i�����C�g
    hResult = DIRECTIONALLIGHT::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�X�v���C�g
    hResult = Sprite.Initialize(TEXT("Data/GameScene/BackGround.tga"), D3DXVECTOR2(0.0F, 0.0F), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_TRAINING"));

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
void TRAINING::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();
    FlexibleCamera.Uninitialize();
    //Debugger.Uninitialize();
    DIRECTIONALLIGHT::Uninitialize();
    Field.Uninitialize();
    Sprite.Uninitialize();

    //---�e�N�X�`���̍폜---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM��~---//
    SOUNDMANAGER::Stop(TEXT("BGM_TRAINING"));
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
void TRAINING::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V����---//
    Back.Update();
    FlexibleCamera.Update();
    //Debugger.Update();
    DIRECTIONALLIGHT::Update();
    Field.Update();
    Sprite.Update();

    //---��ʑJ��---//
    if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TITLE);
    }
}