#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//wb_t@CÇÝÝ//
#include <array>
#include <memory>
#include "Main.h"

//NXé¾//
class ANIMATIONSPRITE
{
    protected:
        D3DXVECTOR2 Position;            //ÊuÀW
        D3DXVECTOR2 Size;                //å«³
        POINT UV;                                       //UVª
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //eNX`ÖÌ|C^
        std::array<VERTEX_2D, 4> Vertex;                //¸_obt@

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        virtual void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif