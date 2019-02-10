//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "OBB.h"
#include "Sphere.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FCollisionToOBB
//
//�@�\�FOBB�Ƃ̓����蔻��
//
//�����F(OBB)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
OBB::OBB(D3DXVECTOR3 position, D3DXVECTOR3 axislength, tstring layer, GAMEOBJECT* owner) : COLLISION(layer, owner)
{
    Position = position;
    AxisLength.at(0) = axislength.x;
    AxisLength.at(1) = axislength.y;
    AxisLength.at(2) = axislength.z;
}

/////////////////////////////////////////////
//�֐����F~OBB
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
OBB::~OBB()
{

}

/////////////////////////////////////////////
//�֐����FCalculationToSeparateAxis
//
//�@�\�F���e�������̎Z�o
//
//�����F(LPD3DXVECTOR3)������,(LPD3DXVECTOR3)����,(LPD3DXVECTOR3)����,(LPD3DXVECTOR3)����
//
//�߂�l�F(float)���e������
/////////////////////////////////////////////
float CalculationToSeparateAxis(LPD3DXVECTOR3 axis, LPD3DXVECTOR3 element1, LPD3DXVECTOR3 element2, LPD3DXVECTOR3 element3 = nullptr)
{
    //---�e��錾---//
    float fRadius1;
    float fRadius2;
    float fRadius3;

    //3�̓��ς̐�Βl�̘a�œ��e���������v�Z (�������͕W��������Ă��邱��)
    fRadius1 = fabs(D3DXVec3Dot(axis, element1));
    fRadius2 = fabs(D3DXVec3Dot(axis, element2));
    fRadius3 = element3 ? fabs(D3DXVec3Dot(axis, element3)) : 0;

    return fRadius1 + fRadius2 + fRadius3;
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
bool OBB::CheckCollisionToOBB(OBB* opponent)
{
    //---�e��錾---//
    float fLength;
    float fRadiusA;
    float fRadiusB;
    D3DXVECTOR3 vecAe1;
    D3DXVECTOR3 vecAe2;
    D3DXVECTOR3 vecAe3;
    D3DXVECTOR3 vecBe1;
    D3DXVECTOR3 vecBe2;
    D3DXVECTOR3 vecBe3;
    D3DXVECTOR3 vecCross;
    D3DXVECTOR3 vecInterval;
    D3DXVECTOR3 vecNormalAe1;
    D3DXVECTOR3 vecNormalAe2;
    D3DXVECTOR3 vecNormalAe3;
    D3DXVECTOR3 vecNormalBe1;
    D3DXVECTOR3 vecNormalBe2;
    D3DXVECTOR3 vecNormalBe3;

    //---�e�����x�N�g���̎Z�o---//
    vecNormalAe1 = NormalDirection.at(0);
    vecAe1 = vecNormalAe1 * AxisLength.at(0);
    vecNormalAe2 = NormalDirection.at(1);
    vecAe2 = vecNormalAe2 * AxisLength.at(1);
    vecNormalAe3 = NormalDirection.at(2);
    vecAe3 = vecNormalAe3 * AxisLength.at(2);

    vecNormalBe1 = opponent->NormalDirection.at(0);
    vecBe1 = vecNormalBe1 * opponent->AxisLength.at(0);
    vecNormalBe2 = opponent->NormalDirection.at(1);
    vecBe2 = vecNormalBe2 * opponent->AxisLength.at(1);
    vecNormalBe3 = opponent->NormalDirection.at(2);
    vecBe3 = vecNormalBe3 * opponent->AxisLength.at(2);

    vecInterval = Position - opponent->Position;

    //---�Փˌ���---//
    //������ : Ae1
    fRadiusA = D3DXVec3Length(&vecAe1);
    fRadiusB = CalculationToSeparateAxis(&vecNormalAe1, &vecBe1, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalAe1));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }
    
    //������ : Ae2
    fRadiusA = D3DXVec3Length(&vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecNormalAe2, &vecBe1, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalAe2));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //// ������ : Ae3
    fRadiusA = D3DXVec3Length(&vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecNormalAe3, &vecBe1, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalAe3));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : Be1
    fRadiusA = CalculationToSeparateAxis(&vecNormalBe1, &vecAe1, &vecAe2, &vecAe3);
    fRadiusB = D3DXVec3Length(&vecBe1);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalBe1));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : Be2
    fRadiusA = CalculationToSeparateAxis(&vecNormalBe2, &vecAe1, &vecAe2, &vecAe3);
    fRadiusB = D3DXVec3Length(&vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalBe2));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : Be3
    fRadiusA = CalculationToSeparateAxis(&vecNormalBe3, &vecAe1, &vecAe2, &vecAe3);
    fRadiusB = D3DXVec3Length(&vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalBe3));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C11
    D3DXVec3Cross(&vecCross, &vecNormalAe1, &vecNormalBe1);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe2, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C12
    D3DXVec3Cross(&vecCross, &vecNormalAe1, &vecNormalBe2);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe2, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C13
    D3DXVec3Cross(&vecCross, &vecNormalAe1, &vecNormalBe3);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe2, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C21
    D3DXVec3Cross(&vecCross, &vecNormalAe2, &vecNormalBe1);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C22
    D3DXVec3Cross(&vecCross, &vecNormalAe2, &vecNormalBe2);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C23
    D3DXVec3Cross(&vecCross, &vecNormalAe2, &vecNormalBe3);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C31
    D3DXVec3Cross(&vecCross, &vecNormalAe3, &vecNormalBe1);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C32
    D3DXVec3Cross(&vecCross, &vecNormalAe3, &vecNormalBe2);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //������ : C33
    D3DXVec3Cross(&vecCross, &vecNormalAe3, &vecNormalBe3);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //�������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
    return true;
}

/////////////////////////////////////////////
//�֐����FCheckCollisionToSphere
//
//�@�\�F���Ƃ̓����蔻��
//
//�����F(SPHERE)�Փˑ���
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool OBB::CheckCollisionToSphere(SPHERE* opponent)
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
        fLength = AxisLength.at(nCounter);
        if (fLength <= 0.0F)
        {
            continue;
        }
        fSeparation = D3DXVec3Dot(&(opponent->Position - Position), &NormalDirection.at(nCounter)) / fLength;

        //fSeparation�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
        fSeparation = fabs(fSeparation);
        if (fSeparation > 1.0F)
        {
            vecLength += (1.0F - fSeparation) * fLength * NormalDirection.at(nCounter);   // �͂ݏo���������̃x�N�g���Z�o
        }
    }

    return D3DXVec3Length(&vecLength) < opponent->Radius;
}
