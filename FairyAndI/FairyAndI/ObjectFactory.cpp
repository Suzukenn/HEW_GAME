//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <functional>
#include <unordered_map>
#include "ActorManager.h"
#include "Element.h"
#include "ObjectFactory.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInstantiateFireElement
//
//�@�\�F���̃G�������g�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3 position)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new ELEMENT(TEXT("FIRE"), TEXT("FIRE"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}

/////////////////////////////////////////////
//�֐����FInstantiateIceElement
//
//�@�\�F�e�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateIceElement(D3DXVECTOR3 position)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new ELEMENT(TEXT("ICE"), TEXT("ICE"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}

/////////////////////////////////////////////
//�֐����FInstantiateRockElement
//
//�@�\�F�e�̐���
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)��]
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void OBJECTFACTORY::InstantiateRockElement(D3DXVECTOR3 position)
{
    //---����---//
    ACTORMANAGER::GameObject.emplace_back(new ELEMENT(TEXT("ROCK"), TEXT("ROCK"), position, D3DXVECTOR3(0.0F, 0.0F, 0.0F)));
}