#ifndef _COLLISION_H_
#define _COLLISION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Base3Dobject.h"
#include "Main.h"

//�������O���錾������//
class GAMEOBJECT;
class OBB;
class SPHERE;

//�������N���X�錾������//
class COLLISION : public BASE3DOBJECT
{
    public:
        tstring Tag;                                //�^�O

        GAMEOBJECT* Parent;

        COLLISION(tstring, GAMEOBJECT*);

        virtual bool CollisionToOBB(const OBB&) = 0;
        virtual bool CollisionToSphere(const SPHERE&) = 0;
};

#endif