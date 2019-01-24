//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CharacterFactory.h"
#include "Enemy.h"
#include "Fairy.h"
#include "Player.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateFairy
//
//�@�\�F�t�F�A���[�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(TEXT("Data/Common/Model/Character/Fairy.x"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiatePlant
//
//�@�\�F�G(�U�R�A��)�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiatePlant(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	ACTORMANAGER::GameObject.emplace_back(new ENEMY(TEXT("FIRE"), TEXT("Plant"), position, rotation));
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
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/Common/Model/Character/tiny_4anim.x"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateSlime
//
//�@�\�F�G(�U�R��)�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	ACTORMANAGER::GameObject.emplace_back(new ENEMY(TEXT("ICE"), TEXT("Slime"), position, rotation));
}