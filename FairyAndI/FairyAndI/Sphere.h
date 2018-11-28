#ifndef _SPHERE_H_
#define _SPHERE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Collision.h"
#include "Main.h"

//�������N���X�錾������//
class SPHERE final : public COLLISION
{
    public:
        float Radius;

        SPHERE(D3DXVECTOR3, float, tstring, GAMEOBJECT*const);
        //~SPHERE();

        bool CollisionToOBB(const OBB&);
        bool CollisionToSphere(const SPHERE&);
};

#endif