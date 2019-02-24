#ifndef _GROUND_H_
#define _GROUND_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"
#include "Transform.h"

//＝＝＝前方宣言＝＝＝//
class TEXTURE;

//＝＝＝クラス宣言＝＝＝//
class GROUND
{
    private:
        TRANSFORM Transform;
        int PolygonValue;
        int VertexValue;

        std::weak_ptr<TEXTURE> Texture;		                    //テクスチャへのポインタ
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//頂点バッファへのポインタ
        std::unique_ptr<LPDIRECT3DINDEXBUFFER9> IndexBuffer;	//インデックスバッファへのポインタ

        HRESULT MakeVertex(int, int, float, float);

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, const int&, const int&, const float&, const float&);
        void Uninitialize(void);
};

#endif