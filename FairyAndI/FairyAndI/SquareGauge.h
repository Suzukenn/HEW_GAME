#ifndef _SQUARE_GAUGE_H_
#define _SQUARE_GAUGE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class SQUAREGAUGE
{
    private:
        float Percent;
        D3DXVECTOR2 Size;
        std::array<VERTEX_2D, 4> MemoryVertex;                //頂点バッファ
        std::unique_ptr<LPDIRECT3DTEXTURE9> MemoryTexture;    //テクスチャへのポインタ
        SPRITE Back;

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);

        float GetPercent(void) { return Percent; }
        void SetPercent(float percent) { Percent = percent; }
};

#endif