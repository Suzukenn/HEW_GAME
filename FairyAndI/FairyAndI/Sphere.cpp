//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Sphere.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FSPHERE
//
//�@�\�F�R���X�g���N�^
//
//�����F(D3DXVECTOR3)�ʒu,(float)���a,(tstring)�^�O��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
SPHERE::SPHERE(D3DXVECTOR3 position, float radius, tstring tag, GAMEOBJECT*const parent) : COLLISION(tag, parent)
{
    Position = position;
    Radius = radius;
}

/////////////////////////////////////////////
//�֐����FCollisionToOBB
//
//�@�\�FOBB�Ƃ̓����蔻��
//
//�����F(OBB)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool SPHERE::CollisionToOBB(const OBB& opponent)
{
    return false;
}

/////////////////////////////////////////////
//�֐����FCollisionToSphere
//
//�@�\�F���Ƃ̓����蔻��
//
//�����F(SPHERE)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool SPHERE::CollisionToSphere(const SPHERE& opponent)
{
    //---�e��錾---//
    float fRadiusDifference;
    D3DXVECTOR3 vecPositionDifference;

    //---�����̎Z�o---//
    vecPositionDifference.x = (opponent.Position.x - Position.x) * (opponent.Position.x - Position.x);
    vecPositionDifference.y = (opponent.Position.y - Position.y) * (opponent.Position.y - Position.y);
    vecPositionDifference.z = (opponent.Position.z - Position.z) * (opponent.Position.z - Position.z);

    //---���E�����̎Z�o---//
    fRadiusDifference = (opponent.Radius + Radius) * (opponent.Radius + Radius);

    //---�����蔻��---//
    return vecPositionDifference.x + vecPositionDifference.y + vecPositionDifference.z <= fRadiusDifference ? true : false;
}