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
        D3DXVECTOR3 AxisLength;                     //�e�������̒���

        std::array<D3DXVECTOR3, 3> NormalDirection; //��]�����x�N�g��

        OBB(D3DXVECTOR3, D3DXVECTOR3, tstring, tstring, GAMEOBJECT*);

        bool CheckCollision(OBB*);
        bool CheckCollision(SPHERE*);
};

#endif