#ifndef _COLLISION_H_
#define _COLLISION_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class GAMEOBJECT;
class OBB;
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class COLLISION
{
    public:
        D3DXVECTOR3 Position;               //位置
        D3DXVECTOR3 Rotation;               //向き
        tstring Layer;                      //所属レイヤー

        GAMEOBJECT* Owner;                  //持ち主

        COLLISION(tstring, GAMEOBJECT*);

        virtual bool CheckCollisionToOBB(OBB*) = 0;
        virtual bool CheckCollisionToSphere(SPHERE*) = 0;
};

#endif