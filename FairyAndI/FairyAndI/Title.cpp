//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TrainingButton.h"
#include "Title.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�^�C�g���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Draw(void)
{
    //---�I�u�W�F�N�g�̕`�揈��---//
    Back.Draw();
    StartButton.Draw();
    TrainingButton.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�^�C�g���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TITLE::Initialize(void)
{
    //---�I�u�W�F�N�g�̏���������---//
    if (FAILED(Back.Initialize(TEXT("Data/Title/Title.png"))))
    {
        return E_FAIL;
    }

    if (FAILED(StartButton.Initialize(TEXT("Data/Title/UI/GameStartButton.png"), { 500.0F, 500.0F }, { 200.0F, 50.0F })))
    {
        return E_FAIL;
    }

    if (FAILED(TrainingButton.Initialize(TEXT("Data/Title/UI/Training.tga"), { 800.0F, 500.0F }, { 200.0F, 50.0F })))
    {
        return E_FAIL;
    }

    //---BGM�Đ�---//
    SOUNDMANAGER::Play(TEXT("BGM_OPENING"));

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�^�C�g���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Uninitialize(void)
{
    //---�I�u�W�F�N�g�̏I������---//
    Back.Uninitialize();
    StartButton.Uninitialize();
    TrainingButton.Uninitialize();

    //---BGM��~---//
    SOUNDMANAGER::Stop(TEXT("BGM_OPENING"));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�^�C�g���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TITLE::Update(void)
{
    //---�I�u�W�F�N�g�̍X�V����---//
    Back.Update();
    StartButton.Update();
    TrainingButton.Update();
}