#ifndef _FIELD_H_
#define _FIELD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class FIELD
{
    private:
        D3DXVECTOR3 Position;					                //位置
        D3DXVECTOR3 Rotation;					                //向き
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;		    //テクスチャへのポインタ
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//頂点バッファへのポインタ
        std::unique_ptr<LPDIRECT3DINDEXBUFFER9> IndexBuffer;	//インデックスバッファへのポインタ
        int PolygonValue;
        int VertexValue;

        HRESULT MakeVertex(const LPDIRECT3DDEVICE9&, const int&, const int&, const float&, const float&);

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, const int&, const int&, const float&, const float&);
        void Uninitialize(void);
        void Update(void);
};

#endif