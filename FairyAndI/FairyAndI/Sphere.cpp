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
SPHERE::SPHERE(D3DXVECTOR3 position, float radius, tstring tag, tstring layer, GAMEOBJECT* owner) : COLLISION(tag, layer, owner)
{
    Position = position;
    Radius = radius;
}

/////////////////////////////////////////////
//関数名：CheckCollision
//
//機能：OBBとの当たり判定
//
//引数：(OBB)衝突相手
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool SPHERE::CheckCollision(OBB* opponent)
{
    return false;
}

/////////////////////////////////////////////
//関数名：CheckCollision
//
//機能：球との当たり判定
//
//引数：(SPHERE)衝突相手
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool SPHERE::CheckCollision(SPHERE* opponent)
{
    //---各種宣言---//
    float fRadiusDifference;
    D3DXVECTOR3 vecPositionDifference;

    //---距離の算出---//
    //vecPositionDifference.x = (opponent.Position.x - Position.x) * (opponent.Position.x - Position.x);
    //vecPositionDifference.y = (opponent.Position.y - Position.y) * (opponent.Position.y - Position.y);
    //vecPositionDifference.z = (opponent.Position.z - Position.z) * (opponent.Position.z - Position.z);

    ////---限界距離の算出---//
    //fRadiusDifference = (opponent.Radius + Radius) * (opponent.Radius + Radius);

    //---当たり判定---//
    return false; vecPositionDifference.x + vecPositionDifference.y + vecPositionDifference.z <= fRadiusDifference ? true : false;
}