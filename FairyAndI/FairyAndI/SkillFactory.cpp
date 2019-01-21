//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Bullet.h"
#include "Grenade.h"
#include "SkillFactory.h"
#include "Trap.h"
#include "Wall.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateBullet
//
//�@�\�F�e�̐���
//
//�����F(tstring)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateBullet(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---����---//
	ACTORMANAGER::GameObject.emplace_back(new BULLET(TEXT("ICE"), type, position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateGrenade
//
//�@�\�F�֒e�̐���
//
//�����F(tstring)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateGrenade(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---����---//
	ACTORMANAGER::GameObject.emplace_back(new GRENADE(TEXT("FIRE"), type, position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateTrap
//
//�@�\�F㩂̐���
//
//�����F(tstring)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateTrap(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---����---//
	ACTORMANAGER::GameObject.emplace_back(new TRAP(TEXT("RICECAKE"), type, position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateSkill
//
//�@�\�F�X�L���I�u�W�F�N�g�̐���
//
//�����F(tstring)��������,(tstring)�����I�u�W�F�N�g,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateSkill(tstring type, tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    std::unordered_map<tstring, std::function< void(tstring, D3DXVECTOR3, D3DXVECTOR3) >> Function = { {TEXT("FIRE"), InstantiateGrenade }, { TEXT("ICE"), InstantiateBullet }, {TEXT("RICECAKE"), InstantiateTrap },{ TEXT("ROCK"), InstantiateWall } };

    //---����---//
    for (auto& data : Function)
    {
        if (data.first == gameobject)
        {
            data.second(type, position, rotation);
            return;
        }
    }
}

/////////////////////////////////////////////
//�֐����FInstantiateWall
//
//�@�\�F�ǂ̐���
//
//�����F(tstring)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateWall(tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new WALL(TEXT("WALL"), type, position, rotation));
}