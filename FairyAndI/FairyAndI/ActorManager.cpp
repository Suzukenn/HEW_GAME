//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <algorithm>
#include <list>
#include "Main.h"
#include "ActorManager.h"
#include "Bullet.h"
#include "Player.h"
#include "Fairy.h"
#include "Wall.h"

//�������O���[�o���ϐ�������//
std::list<GAMEOBJECT*> ACTORMANAGER::GameObject;
std::list<GAMEOBJECT*> ACTORMANAGER::DestroyObject;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDestroy
//
//�@�\�F�I�u�W�F�N�g�̍폜
//
//�����F(GAMEOBJECT*)�폜�I�u�W�F�N�g
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ACTORMANAGER::Destroy(GAMEOBJECT* object)
{
    //---�p�����X�g�֓o�^---//
    DestroyObject.emplace_back(object);
}

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

    GameObject.emplace_back(new PLAYER(TEXT("PLAYER"), TEXT("PLAYER"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, -D3DX_PI * 0.5F, 0.0F)));
    GameObject.emplace_back(new FAIRY(TEXT("FAIRY"), TEXT("FAIRY"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, -D3DX_PI * 0.5F, 0.0F)));

    hResult = S_OK;

    return hResult;
}

/////////////////////////////////////////////
//�֐����FInstantiate
//
//�@�\�F�A�C�e���̐���
//
//�����F(tstring)�I�u�W�F�N�g��,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ACTORMANAGER::Instantiate(tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    tstring strInstance;
    std::vector<tstring> conObjectName = {TEXT("BULLET"), TEXT("WALL")};
    
    //for (auto& data : conObjectName)
    //{
    //    if (gameobject.find(data))
    //    {
    //        strInstance = data;
    //        break;
    //    }
    //}

    if (gameobject.find(TEXT("ICE")))
    {
        GameObject.emplace_back(new BULLET(TEXT("ICE"), TEXT("BULLET"), position, rotation));
    }
    else if (gameobject.find(TEXT("WALL")))
    {
        GameObject.emplace_back(new WALL(gameobject.data(), TEXT("WALL"), position, rotation));
    }
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
    for (auto& data : DestroyObject)
    {
        data->Uninitialize();
    }

    GameObject.clear();
    DestroyObject.clear();
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
    //---�����I�u�W�F�N�g�̍X�V
    for (auto& data : GameObject)
    {
        data->Update();
    }

    //---�p���̎��s---//
    for (auto& data : DestroyObject)
    {
        GameObject.remove(data);
    }
}