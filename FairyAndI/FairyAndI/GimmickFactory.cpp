////�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "BatteryGimmick.h"
#include "Bullet.h"
#include "FireGimmick.h"
#include "GimmickFactory.h"
#include "IceGimmick.h"
#include "WoodGimmick.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateBatteryGimmick
//
//�@�\�F�C��̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateBatteryGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---����---//
	ACTORMANAGER::GameObject.emplace_back(new BATTERYGIMMICK(TEXT("FIRE"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateBulletGimmick
//
//�@�\�F�C��̒e�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateBulletGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---����---//
	ACTORMANAGER::GameObject.emplace_back(new BULLET(TEXT("ICE"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateFireGimmick
//
//�@�\�F���̕ǂ̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateFireGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new FIREGIMMICK(TEXT("FIREGIMMICK"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateGimmick
//
//�@�\�F�M�~�b�N�I�u�W�F�N�g�̐���
//
//�����F(tstring)�����I�u�W�F�N�g,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateGimmick(tstring gameobject, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    std::unordered_map<tstring, std::function< void(D3DXVECTOR3, D3DXVECTOR3) >> Function = { { TEXT("BATTERYGIMMCK"), InstantiateBatteryGimmick },{ TEXT("ICE"), InstantiateBulletGimmick },{ TEXT("FIREGIMMCK"), InstantiateFireGimmick },{ TEXT("ICEGIMMICK"), InstantiateIceGimmick },{ TEXT("WOODGIMMICK"), InstantiateWoodGimmick } };

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
//�֐����FInstantiateIceGimmick
//
//�@�\�F�X�ǂ̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateIceGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new ICEGIMMICK(TEXT("ICEGIMMICK"), TEXT("Gimmick"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateWoodGimmick
//
//�@�\�F����̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GIMMICKFACTORY::InstantiateWoodGimmick(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new FIREGIMMICK(TEXT("WOODGIMMICK"), TEXT("Gimmick"), position, rotation));
}