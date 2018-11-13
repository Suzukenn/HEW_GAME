#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Base2DObjeck.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONSPRITE : protected BASE2DOBJECT
{
    protected:
        POINT UV;                                       //UV分割数
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //テクスチャへのポインタ
        std::array<VERTEX_2D, 4> Vertex;                //頂点バッファ

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        virtual void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif