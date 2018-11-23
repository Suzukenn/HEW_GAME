//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Canvas.h"
#include "DirectionalLight.h"
#include "FlexibleCamera.h"
#include "InputManager.h"
#include "ModelManager.h"
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
    Field.Draw();
    
    //for (int i = 0; i < MAX_ITEM; i++)
    //{
    //    Item[i].Draw();
    //}

    Fairy.Draw();

    Player.Draw();

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

    //hResult = MODELMANAGER::Initialize(TEXT("Data/Model/ModelList.txt"));
    //if (FAILED(hResult))
    //{
    //    return E_FAIL;
    //}

    hResult = WORDMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }


    //---�I�u�W�F�N�g�̏���������---//
    //�n�`
    hResult = Field.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //�t�F�A���[
    if (FAILED(Fairy.Initialize()))
    {
        return E_FAIL;
    }

    //�A�C�e��
    //for (int i = 0; i < MAX_ITEM; i++)
    //{
    //    if (FAILED(Item[i].Initialize()))
    //    {
    //        return E_FAIL;
    //    }
    //}
    //Item[0].CreateItem(D3DXVECTOR3(0.0f, 10.0f, 0.0f), ITEM_ICE);
    //Item[1].CreateItem(D3DXVECTOR3(100.0f, 10.0f, 0.0f), ITEM_FIRE);

    //�v���C���[
    hResult = Player.Initialize(TEXT("Data/Model/car000.x"));
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
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(0.0F, 20.0F, -150.0F), Player.GetPlayerPosition());
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
    Fairy.Uninitialize();
    Player.Uninitialize();

    DIRECTIONALLIGHT::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();

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
        bCameraMode ? FlexibleCamera.Update() : SIDEVIEWCAMERA::Update(Player.GetPlayerPosition());

        Field.Update();

        Player.Update();
        Fairy.Update(SIDEVIEWCAMERA::GetRotation(), Player.GetPlayerPosition(), *Player.GetPlayerRotation(), Item);

        //for (int i = 0; i < MAX_ITEM; i++)
        //{
        //    Item[i].Update(Item);
        //}


        DIRECTIONALLIGHT::Update();

        //---��ʑJ��---//
        if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
        {
            SCENEMANAGER::SetScene(SCENE_TITLE);
        }
    }
    Canvas.Update();
}