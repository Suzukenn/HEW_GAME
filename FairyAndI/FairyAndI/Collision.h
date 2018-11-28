#ifndef _COLLISION_H_
#define _COLLISION_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Base3Dobject.h"
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class GAMEOBJECT;
class OBB;
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class COLLISION : public BASE3DOBJECT
{
    public:
        tstring Tag;                                //タグ

        GAMEOBJECT* Parent;

        COLLISION(tstring, GAMEOBJECT*);

        virtual bool CollisionToOBB(const OBB&) = 0;
        virtual bool CollisionToSphere(const SPHERE&) = 0;
};

#endif