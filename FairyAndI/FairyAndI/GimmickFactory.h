#ifndef _GIMMICK_FACTORY_H_
#define _GIMMICK_FACTORY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X��`������//
class GIMMICKFACTORY
{
    public:
		static void InstantiateBatteryGimmick(D3DXVECTOR3, D3DXVECTOR3);
		static void InstantiateBulletGimmick(D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateFireGimmick(D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateGimmick(tstring, D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateIceGimmick(D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateWoodGimmick(D3DXVECTOR3, D3DXVECTOR3);

        friend ACTORMANAGER;
};

#endif