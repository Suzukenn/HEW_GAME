#ifndef _WORDPLATE_H_
#define _WORDPLATE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class WORDPLATE
{
    private:
        D3DXVECTOR2 Position;            //位置座標
        D3DXVECTOR2 Size;                //大きさ
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;		    //テクスチャへのポインタ
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//頂点バッファへのポインタ

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2 size = D3DXVECTOR2(130.0F, 130.0F));
        void Update(void);

        HRESULT SetTexture(tstring);
};

#endif