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
    CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3(50.0F, 50.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));
    CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3(50.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));

    //�G
    CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3(700.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));

    //�G�������g
    OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3(300.0F, 10.0F, 0.0F));

    //�M�~�b�N
    GIMMICKFACTORY::InstantiateWoodGimmick(D3DXVECTOR3(500.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));
    OBJECTFACTORY::InstantiateGoal(D3DXVECTOR3(1000.0F, 10.0F, 0.0F));

    //�n�`
    hResult = Field.Initialize(TEXT("Data/GameScene/Model/Field/Stage01.x"), TEXT("Field"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(1.0F, 1.0F, 1.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�w�i
    hResult = Background_Back.Initialize(TEXT("BACKGROUND_BACK"), D3DXVECTOR3(0.0F, -12.0F, 80.0F), D3DXVECTOR2(321.0F, 120.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
    hResult = Background_Front.Initialize(TEXT("BACKGROUND_FRONT"), D3DXVECTOR3(0.0F, -12.0F, 80.0F), D3DXVECTOR2(320.0F, 120.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //�T�C�h�r���[�J����
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(50.0F, 20.0F, -50.0F), PLAYER::GetPlayerPosition());
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
    SOUNDMANAGER::Play(TEXT("BGM_GAME"));

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
    SIDEVIEWCAMERA::Update(PLAYER::GetPlayerPosition());
    ACTORMANAGER::Update();
    DIRECTIONALLIGHT::Update();
    COLLISIONMANAGER::Update();

    Background_Back.Update(0.00075F, true);
    Background_Front.Update(0.0015F);
    Canvas.Update();

    //---��ʑJ��---//
    if(!PLAYER::GetPlayerHP())
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }
}