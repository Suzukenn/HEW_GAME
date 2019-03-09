//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "BackGround.h"
#include "Canvas.h"
#include "CharacterFactory.h"
#include "CollisionManager.h"
#include "DirectionalLight.h"
#include "Fade.h"
#include "FlexibleCamera.h"
#include "GimmickFactory.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
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
    Field.Draw();
    Ground.Draw();
    Back.Draw();
    ACTORMANAGER::Draw();
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
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/GameScene/TextureList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = MODELMANAGER::Initialize(TEXT("Data/GameScene/Model/ModelList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = SHADERMANAGER::Initialize(TEXT("Data/GameScene/ShaderList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = WORDMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = ACTORMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = COLLISIONMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---�I�u�W�F�N�g�̏���������---//

    //�L�����N�^�[
    CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3(-20.0F, 50.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));
    CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));

    //�G�������g
    OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3(100.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateIceElement(D3DXVECTOR3(-50.0F, 0.0F, 0.0F));

    //�M�~�b�N
    GIMMICKFACTORY::InstantiateBatteryGimmick(D3DXVECTOR3(50.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));
	OBJECTFACTORY::InstantiateGoal(D3DXVECTOR3(150.0F, 10.0F, 0.0F));

    //�n�`
    //hResult = Field.Initialize(TEXT("Data/Common/Model/Field/Field.x"), TEXT("Field"), D3DXVECTOR3(0.0F, -10.0F, 0.0F), D3DXVECTOR3(20.0F, 20.0F, 20.0F));
    hResult = Field.Initialize(TEXT("Data/GameScene/Model/Field/Field.x"), TEXT("Field"), D3DXVECTOR3(0.0F, -10.0F, 0.0F), D3DXVECTOR3(1.0F, 20.0F, 1.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = Ground.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return hResult;
    }
    hResult = Back.Initialize(TEXT("SKILL_HOTFIRE"), D3DXVECTOR3(0.0F, 0.0F, 100.0F), D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
    //�t���L�V�u���J����
    hResult = FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�T�C�h�r���[�J����
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(0.0F, 20.0F, -150.0F), PLAYER::GetPlayerPosition());
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�f�B���N�V���i�����C�g
    hResult = DIRECTIONALLIGHT::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    //UI�L�����o�X
    hResult = Canvas.Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    FADE::SetFade(FADE_IN);

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_TRAINING"));

    return hResult;
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
    Canvas.Uninitialize();
    FlexibleCamera.Uninitialize();
    Field.Uninitialize();

    DIRECTIONALLIGHT::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();
    ACTORMANAGER::Uninitialize();
    COLLISIONMANAGER::Uninitialize();
    WORDMANAGER::Uninitialize();
    SHADERMANAGER::Uninitialize();

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

    //---�I�u�W�F�N�g�̍X�V����---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_START, TRIGGER))
    {
        bCameraMode = !bCameraMode;
    }
    bCameraMode ? FlexibleCamera.Update() : SIDEVIEWCAMERA::Update(PLAYER::GetPlayerPosition());

    ACTORMANAGER::Update();

    Field.Update();

    DIRECTIONALLIGHT::Update();

    COLLISIONMANAGER::Update();

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
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
    Back.Update();

    //---��ʑJ��---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_BACK, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TITLE);
    }
}