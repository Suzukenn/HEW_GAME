#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <list>
#include <vector>
#include "Collision.h"
#include "FileParameter.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class COLLISIONMANAGER
{
    private:
        static std::list<COLLISION*> Collision;

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        static void Instantiate(tstring);
};

#endif