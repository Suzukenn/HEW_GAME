#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class BILLBOARD
{
    protected:
        POINT UV;

        LPDIRECT3DTEXTURE9 Texture;		        //テクスチャへのポインタ
        std::array<VERTEX_3D, 4> Vertex;        //頂点バッファ

    public:
        void Draw(D3DXVECTOR3);
        HRESULT Initialize(LPCTSTR, POINT);
        void Uninitialize(void);
        void Update(DWORD);
};

#endif