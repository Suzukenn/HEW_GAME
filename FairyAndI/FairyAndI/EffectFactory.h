#ifndef _EFFECT_FACTORY_H_
#define _EFFECT_FACTORY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X��`������//
class EFFECTFACTORY
{
    public:
        static void InstantiateSkillEffect(D3DXVECTOR3, D3DXVECTOR2, bool);

        friend ACTORMANAGER;
};

#endif