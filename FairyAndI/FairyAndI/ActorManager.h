#ifndef _ACTOR_MANAGER_H_
#define _ACTOR_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <list>
#include <vector>
#include "FileParameter.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ACTORMANAGER
{
    private:
        static std::list<GAMEOBJECT*> GameObject;

    public:
        static void Draw(void);
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        static void Instantiate(tstring);
};

#endif