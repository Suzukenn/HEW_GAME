#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <list>
#include <vector>
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class COLLISION;
class GAMEOBJECT;

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    COLLISIONTYPE_OBB,
    COLLISIONTYPE_SPHERE,
    COLLISIONTYPE_MAX
} COLLISIONTYPE;

//＝＝＝クラス宣言＝＝＝//
class COLLISIONMANAGER
{
    private:
        static std::list<COLLISION*> Collision;
        static std::list<COLLISION*> HitList;

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        static COLLISION* InstantiateToOBB(D3DXVECTOR3, D3DXVECTOR3, tstring, tstring, GAMEOBJECT*);
        static COLLISION* InstantiateToSphere(D3DXVECTOR3, float, tstring, tstring, GAMEOBJECT*);
};

#endif