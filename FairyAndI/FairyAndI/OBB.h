#ifndef _OBB_H_
#define _OBB_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Collision.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class OBB final : public COLLISION
{
    public:
        std::array<float, 3> AxisLength;            //各軸方向の長さ
        std::array<D3DXVECTOR3, 3> NormalDirection; //回転方向ベクトル

        OBB(D3DXVECTOR3, D3DXVECTOR3, tstring, GAMEOBJECT*);
        ~OBB();

        bool CheckCollisionToOBB(OBB*);
        bool CheckCollisionToSphere(SPHERE*);
};

#endif