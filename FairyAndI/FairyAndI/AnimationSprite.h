#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONSPRITE : private SPRITE
{
    private:
        POINT UV;                        //UV分割数

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(D3DXVECTOR2, D3DXVECTOR2, POINT, LPCTSTR);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif