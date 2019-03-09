#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Transform.h"

//＝＝＝前方宣言＝＝＝//
class SHADER;
class TEXTURE;

//＝＝＝構造体定義＝＝＝//
typedef struct 
{
    D3DVECTOR	Position;	//頂点の位置
    D3DXVECTOR2 Texture;    //テクスチャ
}CUSTOMVERTEX;

//＝＝＝クラス宣言＝＝＝//
class BILLBOARD
{
    protected:
        D3DXVECTOR2 Scale;
        POINT UV;
        bool Gray;
        bool Inverted;

        std::array<CUSTOMVERTEX, 4> Vertex;        //頂点バッファ

        std::weak_ptr<SHADER> Shader;
        std::weak_ptr<TEXTURE> Texture;

    public:
        void Draw(D3DXVECTOR3);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, bool inverted = false, POINT uv = { 1, 1 });
        void SetUV(int);
        void Uninitialize(void);
        void Update(void);
};

#endif