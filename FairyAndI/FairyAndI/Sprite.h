#ifndef _SPRITE_H_
#define _SPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class TEXTURE;

//＝＝＝クラス宣言＝＝＝//
class SPRITE 
{
    protected:
        D3DXVECTOR2 Position;            //位置座標
        D3DXVECTOR2 Size;                //大きさ

        std::weak_ptr<TEXTURE> Texture;		                    //テクスチャへのポインタ
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//頂点バッファへのポインタ

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        virtual void Uninitialize(void);
};

#endif