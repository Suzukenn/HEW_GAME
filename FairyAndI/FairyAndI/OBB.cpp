//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "OBB.h"

//�������萔�E�}�N����`������//

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
OBB::OBB(D3DXVECTOR3 position, D3DXVECTOR3 axislength, tstring tag, GAMEOBJECT*const parent) : COLLISION(tag, parent)
{
    Position = position;
    AxisLength = axislength;
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
bool OBB::CollisionToOBB(const OBB& opponent)
{
    //// �e�����x�N�g���̊m��
    //// �iN***:�W���������x�N�g���j
    //D3DXVECTOR3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen_W(0);
    //D3DXVECTOR3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen_W(1);
    //D3DXVECTOR3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen_W(2);
    //D3DXVECTOR3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen_W(0);
    //D3DXVECTOR3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen_W(1);
    //D3DXVECTOR3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen_W(2);
    //D3DXVECTOR3 Interval = obb1.GetPos_W() - obb2.GetPos_W();

    //// ������ : Ae1
    //FLOAT rA = D3DXVec3Length(&Ae1);
    //FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    //FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));
    //if (L > rA + rB)
    //    return false; // �Փ˂��Ă��Ȃ�

    //                  // ������ : Ae2
    //rA = D3DXVec3Length(&Ae2);
    //rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &NAe2));
    //if (L > rA + rB)
    //    return false;

    //// ������ : Ae3
    //rA = D3DXVec3Length(&Ae3);
    //rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &NAe3));
    //if (L > rA + rB)
    //    return false;

    //// ������ : Be1
    //rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    //rB = D3DXVec3Length(&Be1);
    //L = fabs(D3DXVec3Dot(&Interval, &NBe1));
    //if (L > rA + rB)
    //    return false;

    //// ������ : Be2
    //rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    //rB = D3DXVec3Length(&Be2);
    //L = fabs(D3DXVec3Dot(&Interval, &NBe2));
    //if (L > rA + rB)
    //    return false;

    //// ������ : Be3
    //rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    //rB = D3DXVec3Length(&Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &NBe3));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C11
    //D3DXVECTOR3 Cross;
    //D3DXVec3Cross(&Cross, &NAe1, &NBe1);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    //rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C12
    //D3DXVec3Cross(&Cross, &NAe1, &NBe2);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    //rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C13
    //D3DXVec3Cross(&Cross, &NAe1, &NBe3);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    //rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C21
    //D3DXVec3Cross(&Cross, &NAe2, &NBe1);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    //rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C22
    //D3DXVec3Cross(&Cross, &NAe2, &NBe2);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    //rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C23
    //D3DXVec3Cross(&Cross, &NAe2, &NBe3);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    //rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C31
    //D3DXVec3Cross(&Cross, &NAe3, &NBe1);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    //rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C32
    //D3DXVec3Cross(&Cross, &NAe3, &NBe2);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    //rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// ������ : C33
    //D3DXVec3Cross(&Cross, &NAe3, &NBe3);
    //rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    //rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    //L = fabs(D3DXVec3Dot(&Interval, &Cross));
    //if (L > rA + rB)
    //    return false;

    //// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
    //return true;
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
bool OBB::CollisionToSphere(const SPHERE& opponent)
{
    return false;
}
