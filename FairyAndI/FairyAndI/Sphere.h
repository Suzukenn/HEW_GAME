#ifndef _SPHERE_H_
#define _SPHERE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Collision.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SPHERE final : public COLLISION
{
    public:
        float Radius;

        SPHERE(D3DXVECTOR3, float, tstring, GAMEOBJECT*const);
        //~SPHERE();

        bool CollisionToOBB(const OBB&);
        bool CollisionToSphere(const SPHERE&);
};

#endif