#ifndef _SKILL_FACTORY_H_
#define _SKILL_FACTORY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X��`������//
class SKILLFACTORY
{
    public:
		static void InstantiateBullet(tstring, D3DXVECTOR3, D3DXVECTOR3);
		static void InstantiateGrenade(tstring, D3DXVECTOR3, D3DXVECTOR3);
		static void InstantiateSkill(tstring, tstring, D3DXVECTOR3, D3DXVECTOR3);
		static void InstantiateTrap(tstring, D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateWall(tstring, D3DXVECTOR3, D3DXVECTOR3);

        friend ACTORMANAGER;
};

#endif