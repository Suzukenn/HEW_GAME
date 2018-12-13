#ifndef _OBB_H_
#define _OBB_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Collision.h"
#include "Main.h"

//�������N���X�錾������//
class OBB final : public COLLISION
{
    public:
        std::array<float, 3> AxisLength;            //�e�������̒���
        std::array<D3DXVECTOR3, 3> NormalDirection; //��]�����x�N�g��

        OBB(D3DXVECTOR3, D3DXVECTOR3, tstring, GAMEOBJECT*);
        ~OBB();

        bool CheckCollisionToOBB(OBB*);
        bool CheckCollisionToSphere(SPHERE*);
};

#endif