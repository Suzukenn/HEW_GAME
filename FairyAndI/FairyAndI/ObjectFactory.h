#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X��`������//
class OBJECTFACTORY
{
    public:
        static void InstantiateFireElement(D3DXVECTOR3);
        static void InstantiateIceElement(D3DXVECTOR3);
        static void InstantiateRockElement(D3DXVECTOR3);

        friend ACTORMANAGER;
};

#endif