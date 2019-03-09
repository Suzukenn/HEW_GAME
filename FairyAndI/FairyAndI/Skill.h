#ifndef _SKILL_H_
#define _SKILL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Billboard.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SKILL : public GAMEOBJECT
{
    protected:
        bool Gray;
        BILLBOARD BillBoard;
        tstring Type;

    public:
        virtual void Draw(void) PURE;
        virtual void OnCollision(COLLISION*) PURE;
        virtual void Uninitialize(void) PURE;
        virtual void Update(void) PURE;

        tstring GetType(void) { return Type; }
};

#endif