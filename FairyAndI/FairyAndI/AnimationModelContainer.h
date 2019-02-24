#ifndef _ANIMATION_MODEL_CONTAINER_H_
#define _ANIMATION_MODEL_CONTAINER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONMODELCONTAINER : public D3DXMESHCONTAINER
{
    public:
        DWORD AttributeGroupValue;                      //属性数
        DWORD Weight;                                   //重みの個数
        DWORD BoneValue;                                //ボーンの数

        std::vector<LPD3DXMATRIX> BoneMatrix;           //全てのボーンのワールド行列の先頭ポインター
        std::vector<LPDIRECT3DTEXTURE9> Texture;        //張り付けるテクスチャ
        std::vector<D3DXATTRIBUTERANGE> AttributeTable; //属性テーブル
        std::vector<D3DXMATRIX> BoneOffsetMatrix;       //フレームとしてのボーンのワールド行列

        LPD3DXBUFFER BoneBuffer;                        //ボーンテーブル
};

#endif