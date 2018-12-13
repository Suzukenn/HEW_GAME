//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "OBB.h"
#include "Sphere.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CollisionToOBB
//
//機能：OBBとの当たり判定
//
//引数：(OBB)衝突相手
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
OBB::OBB(D3DXVECTOR3 position, D3DXVECTOR3 axislength, tstring layer, GAMEOBJECT* owner) : COLLISION(layer, owner)
{
    Position = position;
    AxisLength.at(0) = axislength.x;
    AxisLength.at(1) = axislength.y;
    AxisLength.at(2) = axislength.z;
}

/////////////////////////////////////////////
//関数名：~OBB
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
OBB::~OBB()
{

}

/////////////////////////////////////////////
//関数名：CalculationToSeparateAxis
//
//機能：投影線分長の算出
//
//引数：(LPD3DXVECTOR3)分離軸,(LPD3DXVECTOR3)成分,(LPD3DXVECTOR3)成分,(LPD3DXVECTOR3)成分
//
//戻り値：(float)投影線分長
/////////////////////////////////////////////
float CalculationToSeparateAxis(LPD3DXVECTOR3 axis, LPD3DXVECTOR3 element1, LPD3DXVECTOR3 element2, LPD3DXVECTOR3 element3 = nullptr)
{
    //---各種宣言---//
    float fRadius1;
    float fRadius2;
    float fRadius3;

    //3つの内積の絶対値の和で投影線分長を計算 (分離軸は標準化されていること)
    fRadius1 = fabs(D3DXVec3Dot(axis, element1));
    fRadius2 = fabs(D3DXVec3Dot(axis, element2));
    fRadius3 = element3 ? fabs(D3DXVec3Dot(axis, element3)) : 0;

    return fRadius1 + fRadius2 + fRadius3;
}

/////////////////////////////////////////////
//関数名：CheckCollisionToOBB
//
//機能：OBBとの当たり判定
//
//引数：(OBB)衝突相手
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool OBB::CheckCollisionToOBB(OBB* opponent)
{
    //---各種宣言---//
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

    //---各方向ベクトルの算出---//
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

    //---衝突検証---//
    //分離軸 : Ae1
    fRadiusA = D3DXVec3Length(&vecAe1);
    fRadiusB = CalculationToSeparateAxis(&vecNormalAe1, &vecBe1, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalAe1));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }
    
    //分離軸 : Ae2
    fRadiusA = D3DXVec3Length(&vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecNormalAe2, &vecBe1, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalAe2));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //// 分離軸 : Ae3
    fRadiusA = D3DXVec3Length(&vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecNormalAe3, &vecBe1, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalAe3));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : Be1
    fRadiusA = CalculationToSeparateAxis(&vecNormalBe1, &vecAe1, &vecAe2, &vecAe3);
    fRadiusB = D3DXVec3Length(&vecBe1);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalBe1));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : Be2
    fRadiusA = CalculationToSeparateAxis(&vecNormalBe2, &vecAe1, &vecAe2, &vecAe3);
    fRadiusB = D3DXVec3Length(&vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalBe2));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : Be3
    fRadiusA = CalculationToSeparateAxis(&vecNormalBe3, &vecAe1, &vecAe2, &vecAe3);
    fRadiusB = D3DXVec3Length(&vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecNormalBe3));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C11
    D3DXVec3Cross(&vecCross, &vecNormalAe1, &vecNormalBe1);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe2, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C12
    D3DXVec3Cross(&vecCross, &vecNormalAe1, &vecNormalBe2);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe2, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C13
    D3DXVec3Cross(&vecCross, &vecNormalAe1, &vecNormalBe3);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe2, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C21
    D3DXVec3Cross(&vecCross, &vecNormalAe2, &vecNormalBe1);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C22
    D3DXVec3Cross(&vecCross, &vecNormalAe2, &vecNormalBe2);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C23
    D3DXVec3Cross(&vecCross, &vecNormalAe2, &vecNormalBe3);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe3);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C31
    D3DXVec3Cross(&vecCross, &vecNormalAe3, &vecNormalBe1);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe2, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C32
    D3DXVec3Cross(&vecCross, &vecNormalAe3, &vecNormalBe2);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe3);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離軸 : C33
    D3DXVec3Cross(&vecCross, &vecNormalAe3, &vecNormalBe3);
    fRadiusA = CalculationToSeparateAxis(&vecCross, &vecAe1, &vecAe2);
    fRadiusB = CalculationToSeparateAxis(&vecCross, &vecBe1, &vecBe2);
    fLength = fabs(D3DXVec3Dot(&vecInterval, &vecCross));
    if (fLength > fRadiusA + fRadiusB)
    {
        return false;
    }

    //分離平面が存在しないので「衝突している」
    return true;
}

/////////////////////////////////////////////
//関数名：CheckCollisionToSphere
//
//機能：球との当たり判定
//
//引数：(SPHERE)衝突相手
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool OBB::CheckCollisionToSphere(SPHERE* opponent)
{
    //---各種宣言---//
    int nCounter;
    float fLength;
    float fSeparation;
    D3DXVECTOR3 vecLength;

    //---初期化処理---//
    vecLength = D3DXVECTOR3(0.0F, 0.0F, 0.0F);

    //各軸についてはみ出た部分のベクトルを算出
    for (nCounter = 0; nCounter < 3; ++nCounter)
    {
        fLength = AxisLength.at(nCounter);
        if (fLength <= 0.0F)
        {
            continue;
        }
        fSeparation = D3DXVec3Dot(&(opponent->Position - Position), &NormalDirection.at(nCounter)) / fLength;

        //fSeparationの値から、はみ出した部分があればそのベクトルを加算
        fSeparation = fabs(fSeparation);
        if (fSeparation > 1.0F)
        {
            vecLength += (1.0F - fSeparation) * fLength * NormalDirection.at(nCounter);   // はみ出した部分のベクトル算出
        }
    }

    return D3DXVec3Length(&vecLength) < opponent->Radius;
}
