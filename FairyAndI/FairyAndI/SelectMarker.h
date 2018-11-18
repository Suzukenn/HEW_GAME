#ifndef _SELECTMARKER_H_
#define _SELECTMARKER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "AnimationSprite.h"

//＝＝＝クラス宣言＝＝＝//
class SELECTMARKER final : protected BASE2DOBJECT
{
    private:
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //テクスチャへのポインタ
        std::array<VERTEX_2D, 4> Vertex;                //頂点バッファ

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);
};

#endif