//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "BackGround.h"
#include "Canvas.h"
#include "CharacterFactory.h"
#include "CollisionManager.h"
#include "DirectionalLight.h"
#include "Fade.h"
#include "GameScene01.h"
#include "GimmickFactory.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "SideViewCamera.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "WordManager.h"

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
void GAME01::Draw(void)
{
    Background_Back.Draw();
    Background_Front.Draw();
    Field.Draw();
    ACTORMANAGER::Draw();
    Canvas.Draw();
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
HRESULT GAME01::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

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

    hResult = ANIMATIONMODELMANAGER::Initialize(TEXT("Data/GameScene/Model/AnimationModelList.txt"));
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
    CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3(0.0F, 50.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));
    CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));

    //�G
    //CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3(100.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));
    //CHARACTERFACTORY::InstantiateWood(D3DXVECTOR3(100.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));
    //CHARACTERFACTORY::InstantiateWood(D3DXVECTOR3(150.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));

    //�G�������g
    OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3(100.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateIceElement(D3DXVECTOR3(-50.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateRockElement(D3DXVECTOR3(-100.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateRiceCakeElement(D3DXVECTOR3(50.0F, 0.0F, 0.0F));

    //�M�~�b�N
    GIMMICKFACTORY::InstantiateBatteryGimmick(D3DXVECTOR3(50.0F, 0.0F, 0.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateGoal(D3DXVECTOR3(150.0F, 0.0F, 0.0F));

    //---�X�^�b�t�n��̏�����---//
    //�n�`
    hResult = Field.Initialize(TEXT("Data/GameScene/Model/Field/Stage01.x"), TEXT("Field"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(200.0F, 10.0F, 1.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�w�i
    hResult = Background_Back.Initialize(TEXT("BACKGROUND_BACK"), D3DXVECTOR3(0.0F, 0.0F, 100.0F), D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
    hResult = Background_Front.Initialize(TEXT("BACKGROUND_FRONT"), D3DXVECTOR3(0.0F, 0.0F, 100.0F), D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�T�C�h�r���[�J����
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(0.0F, 20.0F, -50.0F), PLAYER::GetPlayerPosition());
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
//�@�\�F�Q�[���V�[���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GAME01::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Background_Back.Uninitialize();
    Background_Front.Uninitialize();
    Canvas.Uninitialize();
    Field.Uninitialize();

    //---�X�^�b�t�n��̏I������---//
    ACTORMANAGER::Uninitialize();
    ANIMATIONMODELMANAGER::Uninitialize();
    COLLISIONMANAGER::Uninitialize();
    DIRECTIONALLIGHT::Uninitialize();
    MODELMANAGER::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();
    SHADERMANAGER::Uninitialize();
    TEXTUREMANAGER::Uninitialize();
    WORDMANAGER::Uninitialize();

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
void GAME01::Update(void)
{
    //---�e��錾---//

    //---�I�u�W�F�N�g�̍X�V����---//
    ACTORMANAGER::Update();
    DIRECTIONALLIGHT::Update();
    COLLISIONMANAGER::Update();

    Background_Back.Update(0.0075F);
    Background_Front.Update(0.015F);
    Canvas.Update();

    //---��ʑJ��---//
    if(!PLAYER::GetPlayerHP())
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }
}