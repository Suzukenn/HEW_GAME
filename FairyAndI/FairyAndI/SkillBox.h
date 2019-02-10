#ifndef _SKILLBOX_BOX_H_
#define _SKILLBOX_BOX_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SKILLBOX
{
    private:
        D3DXVECTOR2 Position;            //位置座標
        D3DXVECTOR2 Size;                //大きさ
        POINT UV;                                       //UV分割数
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //テクスチャへのポインタ
        std::array<VERTEX_2D, 4> Vertex;                //頂点バッファ

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        void SetSpriteUV(int);
        void Uninitialize(void);
        void Update(void);
};

#endif