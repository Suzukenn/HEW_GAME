//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Canvas.h"
#include "CharacterFactory.h"
#include "CollisionManager.h"
#include "DirectionalLight.h"
#include "FlexibleCamera.h"
#include "GimmickFactory.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "ObjectFactory.h"
#include "Player.h"
#include "SceneManager.h"
#include "SideViewCamera.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingScene.h"
#include "WordManager.h"

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
    //---�I�u�W�F�N�g�̕`�揈��---//
    ACTORMANAGER::Draw();
    Field.Draw();
    Ground.Draw();
    Canvas.Draw();
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

    Mode = true;

    //---�f�[�^�̓ǂݍ���---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Training/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    hResult = MODELMANAGER::Initialize(TEXT("Data/Common/Model/ModelList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    hResult = WORDMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    hResult = ACTORMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    hResult = COLLISIONMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---�I�u�W�F�N�g�̏���������---//

    //�L�����N�^�[
    CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3(-20.0F, 50.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));
    CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));

    //�G�������g
    OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3(100.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateIceElement(D3DXVECTOR3(-50.0F, 0.0F, 0.0F));

	//�M�~�b�N
	GIMMICKFACTORY::InstantiateBatteryGimmick(D3DXVECTOR3(50.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));

    //�n�`
    //hResult = Field.Initialize(TEXT("Data/Common/Model/Field/Field.x"), TEXT("Field"), D3DXVECTOR3(0.0F, -10.0F, 0.0F), D3DXVECTOR3(20.0F, 20.0F, 20.0F));
    hResult = Field.Initialize(TEXT("Data/Common/Model/Field/Field.x"), TEXT("Field"), D3DXVECTOR3(0.0F, -10.0F, 0.0F), D3DXVECTOR3(1.0F, 20.0F, 1.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    hResult = Ground.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�t���L�V�u���J����
    hResult = FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�T�C�h�r���[�J����
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(0.0F, 20.0F, -150.0F), PLAYER::GetPlayerPosition());
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

    //UI�L�����o�X
    hResult = Canvas.Initialize();
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
    Canvas.Uninitialize();
    FlexibleCamera.Uninitialize();
    Field.Uninitialize();

    DIRECTIONALLIGHT::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();
    ACTORMANAGER::Uninitialize();
    COLLISIONMANAGER::Uninitialize();

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
    //---�e��錾---//
    static bool bCameraMode = false;

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }

    //---�I�u�W�F�N�g�̍X�V����---//
    if (Mode)
    {
        if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_START, TRIGGER)) bCameraMode = !bCameraMode;
        bCameraMode ? FlexibleCamera.Update() : SIDEVIEWCAMERA::Update(PLAYER::GetPlayerPosition());

        ACTORMANAGER::Update();

        Field.Update();

        DIRECTIONALLIGHT::Update();

        COLLISIONMANAGER::Update();

        //---��ʑJ��---//
        if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
        {
            SCENEMANAGER::SetScene(SCENE_TITLE);
        }
    }
    if (INPUTMANAGER::GetKey(DIK_Z, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("FIRE"));
    }
    if (INPUTMANAGER::GetKey(DIK_X, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("ICE"));
    }
    if (INPUTMANAGER::GetKey(DIK_C, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("ROCK"));
    }
    if (INPUTMANAGER::GetKey(DIK_V, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("RICECAKE"));
    }

    Canvas.Update();
}