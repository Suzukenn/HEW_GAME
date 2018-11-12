#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//wb_t@CÇÝÝ//
#include <array>
#include "Main.h"
#include "Sprite.h"

//NXé¾//
class ANIMATIONSPRITE : private SPRITE
{
    private:
        POINT UV;                        //UVª

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(D3DXVECTOR2, D3DXVECTOR2, POINT, LPCTSTR);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif