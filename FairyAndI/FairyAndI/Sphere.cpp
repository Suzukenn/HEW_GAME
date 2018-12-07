//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "OBB.h"
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
SPHERE::SPHERE(D3DXVECTOR3 position, float radius, tstring tag, tstring layer, GAMEOBJECT* owner) : COLLISION(tag, layer, owner)
{
    Position = position;
    Radius = radius;
}

/////////////////////////////////////////////
//�֐����FCheckCollision
//
//�@�\�FOBB�Ƃ̓����蔻��
//
//�����F(OBB)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool SPHERE::CheckCollision(OBB* opponent)
{
    return false;
}

/////////////////////////////////////////////
//�֐����FCheckCollision
//
//�@�\�F���Ƃ̓����蔻��
//
//�����F(SPHERE)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool SPHERE::CheckCollision(SPHERE* opponent)
{
    //---�e��錾---//
    float fRadiusDifference;
    D3DXVECTOR3 vecPositionDifference;

    //---�����̎Z�o---//
    //vecPositionDifference.x = (opponent.Position.x - Position.x) * (opponent.Position.x - Position.x);
    //vecPositionDifference.y = (opponent.Position.y - Position.y) * (opponent.Position.y - Position.y);
    //vecPositionDifference.z = (opponent.Position.z - Position.z) * (opponent.Position.z - Position.z);

    ////---���E�����̎Z�o---//
    //fRadiusDifference = (opponent.Radius + Radius) * (opponent.Radius + Radius);

    //---�����蔻��---//
    return false; vecPositionDifference.x + vecPositionDifference.y + vecPositionDifference.z <= fRadiusDifference ? true : false;
}