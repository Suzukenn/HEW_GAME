//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "OBB.h"
#include "Sphere.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：SPHERE
//
//機能：コンストラクタ
//
//引数：(D3DXVECTOR3)位置,(float)半径,(tstring)タグ名
//
//戻り値：なし
/////////////////////////////////////////////
SPHERE::SPHERE(D3DXVECTOR3 position, float radius, tstring layer, GAMEOBJECT* owner) : COLLISION(layer, owner)
{
    Position = position;
    Radius = radius;
}

/////////////////////////////////////////////
//関数名：~SPHERE
//
//機能：デストラクタ
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
SPHERE::~SPHERE()
{

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
bool SPHERE::CheckCollisionToOBB(OBB* opponent)
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
        fLength = opponent->AxisLength.at(nCounter);
        if (fLength <= 0.0F)
        {
            continue;
        }
        fSeparation = D3DXVec3Dot(&(opponent->Position - Position), &opponent->NormalDirection.at(nCounter)) / fLength;

        //fSeparationの値から、はみ出した部分があればそのベクトルを加算
        fSeparation = fabs(fSeparation);
        if (fSeparation > 1.0F)
        {
            vecLength += (1.0F - fSeparation) * fLength * opponent->NormalDirection.at(nCounter);   // はみ出した部分のベクトル算出
        }
    }

    return D3DXVec3Length(&vecLength) < Radius;
}

/////////////////////////////////////////////
//関数名：CheckCollisionSphere
//
//機能：球との当たり判定
//
//引数：(SPHERE)衝突相手
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool SPHERE::CheckCollisionToSphere(SPHERE* opponent)
{
    //---各種宣言---//
    float fRadiusDifference;
    D3DXVECTOR3 vecPositionDifference;

    //---距離の算出---//
    vecPositionDifference.x = (opponent->Position.x - Position.x) * (opponent->Position.x - Position.x);
    vecPositionDifference.y = (opponent->Position.y - Position.y) * (opponent->Position.y - Position.y);
    vecPositionDifference.z = (opponent->Position.z - Position.z) * (opponent->Position.z - Position.z);

    //---限界距離の算出---//
    fRadiusDifference = (opponent->Radius + Radius) * (opponent->Radius + Radius);

    //---当たり判定---//
    return vecPositionDifference.x + vecPositionDifference.y + vecPositionDifference.z <= fRadiusDifference;
}