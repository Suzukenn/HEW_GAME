#ifndef _ACTOR_MANAGER_H_
#define _ACTOR_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <list>
#include <vector>
#include "FileParameter.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class CHARACTERFACTORY;
class EFFECTFACTORY;
class OBJECTFACTORY;
class GIMMICKFACTORY;
class SKILLFACTORY;

//＝＝＝クラス宣言＝＝＝//
class ACTORMANAGER
{
    private:
        static std::list<GAMEOBJECT*> GameObject;
        static std::list<GAMEOBJECT*> DestroyObject;

    public:
        static void Destroy(GAMEOBJECT*);
        static void Draw(void);
        static void FindObject(std::vector<GAMEOBJECT*>&, tstring);
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        friend CHARACTERFACTORY;
        friend EFFECTFACTORY;
        friend OBJECTFACTORY;
        friend GIMMICKFACTORY;
        friend SKILLFACTORY;
};

#endif