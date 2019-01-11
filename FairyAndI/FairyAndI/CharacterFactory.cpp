//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CharacterFactory.h"
#include "Fairy.h"
#include "Player.h"

//�������O���錾������//

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateFairy
//
//�@�\�F�v���C���[�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(TEXT("Data/Common/Model/Character/car001.x"), TEXT("Fairy"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiatePlayer
//
//�@�\�F�v���C���[�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/Common/Model/Character/tiny_4anim.x"), TEXT("Player"), position, rotation));
}