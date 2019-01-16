#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Transform.h"

//＝＝＝前方宣言＝＝＝//
class COLLISION;

//＝＝＝クラス宣言＝＝＝//
class GAMEOBJECT
{
    protected:
        TRANSFORM Transform;
        tstring Tag;

    public:
        GAMEOBJECT() {}
        ~GAMEOBJECT() {}
        virtual void Draw(void) = 0;
        virtual HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3) = 0;
        virtual void Uninitialize(void) = 0;
        virtual void Update(void) = 0;

        virtual void OnCollision(COLLISION*) = 0;

        D3DXVECTOR3 GetPosition(void) { return Transform.Position; }
        tstring GetTag(void) { return Tag; }
};

#endif