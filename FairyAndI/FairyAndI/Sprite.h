#ifndef _SPRITE_H_
#define _SPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Base2DObjeck.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SPRITE : protected BASE2DOBJECT 
{
    protected:
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;		    //テクスチャへのポインタ
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//頂点バッファへのポインタ

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif