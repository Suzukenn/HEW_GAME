#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class TEXTURE;

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONSPRITE
{
    protected:
        D3DXVECTOR2 Position;            //位置座標
        D3DXVECTOR2 Size;                //大きさ
        POINT UV;                                       //UV分割数
        
        std::array<VERTEX_2D, 4> Vertex;                //頂点バッファ

        std::weak_ptr<TEXTURE> Texture;    //テクスチャへのポインタ

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT uv = { 1, 1 });
		void SetPosition(D3DXVECTOR2);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
};

#endif