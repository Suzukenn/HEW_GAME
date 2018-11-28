//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <list>
#include "Main.h"
#include "ActorManager.h"

//�������O���[�o���ϐ�������//
std::list<GAMEOBJECT*> ACTORMANAGER::GameObject;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�}�l�[�W���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ACTORMANAGER::Draw(void)
{
    for (auto& data : GameObject)
    {
        data->Draw();
    }
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�}�l�[�W���[�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ACTORMANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    GameObject.clear();
    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//�֐����FInstantiate
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ACTORMANAGER::Instantiate(tstring gameobject)
{
    //GameObject.emplace_back();
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�}�l�[�W���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ACTORMANAGER::Uninitialize(void)
{
    //---���---//
    for (auto& data : GameObject)
    {
        data->Uninitialize();
    }
    GameObject.clear();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�e�N�X�`���̎擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ACTORMANAGER::Update(void)
{
    for (auto& data : GameObject)
    {
        data->Update();
    }
}

