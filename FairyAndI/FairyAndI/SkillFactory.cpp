//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Bullet.h"
#include "SkillFactory.h"
#include "Wall.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateBullet
//
//�@�\�F�e�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateBullet(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new BULLET(TEXT("ICE"), TEXT("Bullet"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateSkill
//
//�@�\�F�X�L���I�u�W�F�N�g�̐���
//
//�����F(tstring)�����I�u�W�F�N�g,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateSkill(tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    std::unordered_map<tstring, std::function< void(D3DXVECTOR3, D3DXVECTOR3) >> Function = { {TEXT("FIRE "), InstantiateBullet }, {TEXT("WALL"), InstantiateWall } };

    //---����---//
    for (auto& data : Function)
    {
        if (gameobject.find(data.first) != tstring::npos)
        {
            data.second(position, rotation);
        }
    }
}

/////////////////////////////////////////////
//�֐����FInstantiateWall
//
//�@�\�F�ǂ̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLFACTORY::InstantiateWall(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new WALL(TEXT("WALL"), TEXT("Wall"), position, rotation));
}
