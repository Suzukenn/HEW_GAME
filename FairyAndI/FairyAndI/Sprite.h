#ifndef _SPRITE_H_
#define _SPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SPRITE
{
    protected:
        D3DXVECTOR2 Pos;                    //位置座標
        D3DXVECTOR2 Size;                   //大きさ
        LPDIRECT3DTEXTURE9 Graphic;           //テクスチャ
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ

    public:
        virtual void Draw(void) = 0;
        virtual HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR2, LPCWSTR) = 0;
        virtual void Uninitialize(void) = 0;
};

#endif