#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//wb_t@CÇÝÝ//
#include <array>
#include <memory>
#include "Main.h"

//Oûé¾//
class TEXTURE;

//NXé¾//
class ANIMATIONSPRITE
{
    protected:
        D3DXVECTOR2 Position;            //ÊuÀW
        D3DXVECTOR2 Size;                //å«³
        POINT UV;                                       //UVª
        
        std::array<VERTEX_2D, 4> Vertex;                //¸_obt@

        std::weak_ptr<TEXTURE> Texture;    //eNX`ÖÌ|C^

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT uv = { 1, 1 });
		void SetPosition(D3DXVECTOR2);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
};

#endif