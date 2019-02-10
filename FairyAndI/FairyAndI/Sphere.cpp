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
SPHERE::SPHERE(D3DXVECTOR3 position, float radius, tstring layer, GAMEOBJECT* owner) : COLLISION(layer, owner)
{
    Position = position;
    Radius = radius;
}

/////////////////////////////////////////////
//�֐����F~SPHERE
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
SPHERE::~SPHERE()
{

}

/////////////////////////////////////////////
//�֐����FCheckCollisionToOBB
//
//�@�\�FOBB�Ƃ̓����蔻��
//
//�����F(OBB)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool SPHERE::CheckCollisionToOBB(OBB* opponent)
{
    //---�e��錾---//
    int nCounter;
    float fLength;
    float fSeparation;
    D3DXVECTOR3 vecLength;
    
    //---����������---//
    vecLength = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    
    //�e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
    for (nCounter = 0; nCounter < 3; ++nCounter)
    {
        fLength = opponent->AxisLength.at(nCounter);
        if (fLength <= 0.0F)
        {
            continue;
        }
        fSeparation = D3DXVec3Dot(&(opponent->Position - Position), &opponent->NormalDirection.at(nCounter)) / fLength;

        //fSeparation�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
        fSeparation = fabs(fSeparation);
        if (fSeparation > 1.0F)
        {
            vecLength += (1.0F - fSeparation) * fLength * opponent->NormalDirection.at(nCounter);   // �͂ݏo���������̃x�N�g���Z�o
        }
    }

    return D3DXVec3Length(&vecLength) < Radius;
}

/////////////////////////////////////////////
//�֐����FCheckCollisionSphere
//
//�@�\�F���Ƃ̓����蔻��
//
//�����F(SPHERE)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool SPHERE::CheckCollisionToSphere(SPHERE* opponent)
{
    //---�e��錾---//
    float fRadiusDifference;
    D3DXVECTOR3 vecPositionDifference;

    //---�����̎Z�o---//
    vecPositionDifference.x = (opponent->Position.x - Position.x) * (opponent->Position.x - Position.x);
    vecPositionDifference.y = (opponent->Position.y - Position.y) * (opponent->Position.y - Position.y);
    vecPositionDifference.z = (opponent->Position.z - Position.z) * (opponent->Position.z - Position.z);

    //---���E�����̎Z�o---//
    fRadiusDifference = (opponent->Radius + Radius) * (opponent->Radius + Radius);

    //---�����蔻��---//
    return vecPositionDifference.x + vecPositionDifference.y + vecPositionDifference.z <= fRadiusDifference;
}