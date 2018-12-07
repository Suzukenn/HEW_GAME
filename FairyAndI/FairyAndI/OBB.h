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
        D3DXVECTOR3 AxisLength;                     //各軸方向の長さ

        std::array<D3DXVECTOR3, 3> NormalDirection; //回転方向ベクトル

        OBB(D3DXVECTOR3, D3DXVECTOR3, tstring, tstring, GAMEOBJECT*);

        bool CheckCollision(OBB*);
        bool CheckCollision(SPHERE*);
};

#endif