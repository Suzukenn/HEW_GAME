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
    ACTORMANAGER::GameObject.emplace_back(new FAIRY(TEXT("Data/GameScene/Model/Character/Fairy.x"), position, rotation));
}

/////////////////////////////////////////////
//�֐����FInstantiatePlant
//
//�@�\�F�v�����g�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void CHARACTERFACTORY::InstantiatePlant(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    ACTORMANAGER::GameObject.emplace_back(new ENEMY(TEXT("Data/GameScene/Model/Character/Wait.x"), TEXT("Plant"), position, rotation));
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
    //ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/GameScene/Model/Character/Player.x"), position, rotation));
    //ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/GameScene/Model/Character/tiny_4anim.x"), position, rotation));
    ACTORMANAGER::GameObject.emplace_back(new PLAYER(TEXT("Data/GameScene/Model/Character/Wait.x"), position, rotation));
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
    ACTORMANAGER::GameObject.emplace_back(new ENEMY(TEXT("Data/GameScene/Model/Character/Wait.x"), TEXT("Slime"), position, rotation));
}