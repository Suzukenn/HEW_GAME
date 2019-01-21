#ifndef _SKILL_H_
#define _SKILL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝クラス宣言＝＝＝//
class SKILL : public GAMEOBJECT
{
    public:
        tstring Type;

        SKILL(void) {}
        ~SKILL(void) {}
        virtual void Draw(void) PURE;
        virtual void OnCollision(COLLISION*) PURE;
        virtual void Uninitialize(void) PURE;
        virtual void Update(void) PURE;

        tstring GetType(void) { return Type; }
};

#endif