#ifndef _COLLISION_H_
#define _COLLISION_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������O���錾������//
class GAMEOBJECT;
class OBB;
class SPHERE;

//�������N���X�錾������//
class COLLISION
{
    public:
        D3DXVECTOR3 Position;               //�ʒu
        D3DXVECTOR3 Rotation;               //����
        tstring Tag;                        //�^�O
        tstring Layer;                      //�������C���[

        GAMEOBJECT* Owner;                  //������

        COLLISION(tstring, tstring, GAMEOBJECT*);

        virtual bool CheckCollision(OBB*) = 0;
        virtual bool CheckCollision(SPHERE*) = 0;
};

#endif