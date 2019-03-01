#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include "Main.h"
#include "Transform.h"

//＝＝＝前方宣言＝＝＝//
class TEXTURE;

//＝＝＝構造体定義＝＝＝//
typedef struct 
{
    D3DVECTOR	Position;	//頂点の位置
    D3DCOLOR	Color;	    //頂点の色
    D3DXVECTOR2 Texture;    //テクスチャ
}CUSTOMVERTEX;

//＝＝＝クラス宣言＝＝＝//
class BILLBOARD
{
    protected:
        bool Gray;
        TRANSFORM Transform;
        POINT UV;

        std::array<CUSTOMVERTEX, 4> Vertex;        //頂点バッファ

        LPD3DXEFFECT Effect;
        std::weak_ptr<TEXTURE> Texture;		    //テクスチャへのポインタ

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3, POINT uv = { 1, 1 });
        void Uninitialize(void);
        void Update(void);
};

#endif