//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CharacterFactory.h"
#include "Fairy.h"
#include "Player.h"
#include "Slime.h"
#include "Wood.h"

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
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(position, rotation));
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
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateSlime
//
//�@�\�F�X���C���̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new SLIME(TEXT("Slime"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiateWood
//
//�@�\�F�؂̃I�o�P�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiateWood(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new WOOD(TEXT("Wood"), position, rotation));
}