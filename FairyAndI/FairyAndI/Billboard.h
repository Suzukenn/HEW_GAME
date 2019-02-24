#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include "Main.h"
#include "Transform.h"

//＝＝＝前方宣言＝＝＝//
class TEXTURE;

//＝＝＝クラス宣言＝＝＝//
class BILLBOARD
{
    protected:
        TRANSFORM Transform;
        POINT UV;

        std::array<VERTEX_3D, 4> Vertex;        //頂点バッファ

        std::weak_ptr<TEXTURE> Texture;		    //テクスチャへのポインタ

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3, POINT uv = { 1, 1 });
        void Uninitialize(void);
        void Update(DWORD);
};

#endif