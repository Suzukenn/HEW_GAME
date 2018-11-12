#ifndef _SPRITE_H_
#define _SPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SPRITE
{
    private:
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //頂点バッファ

    protected:
        D3DXVECTOR2 Position;            //位置座標
        D3DXVECTOR2 Size;                //大きさ
        LPDIRECT3DTEXTURE9 Texture;      //テクスチャ
        std::array<VERTEX_2D, 4> Vertex; //頂点情報

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(D3DXVECTOR2, D3DXVECTOR2, LPCTSTR);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif