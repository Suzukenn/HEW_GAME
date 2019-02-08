#ifndef _SKILLBOX_BOX_H_
#define _SKILLBOX_BOX_H_

//wb_t@CÇÝÝ//
#include <array>
#include <memory>
#include "Main.h"

//NXé¾//
class SKILLBOX
{
    private:
        D3DXVECTOR2 Position;            //ÊuÀW
        D3DXVECTOR2 Size;                //å«³
        POINT UV;                                       //UVª
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //eNX`ÖÌ|C^
        std::array<VERTEX_2D, 4> Vertex;                //¸_obt@

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        void SetSpriteUV(int);
        void Uninitialize(void);
        void Update(void);
};

#endif