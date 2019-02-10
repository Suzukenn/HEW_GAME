#ifndef _ANIMATION_MODEL_CONTAINER_H_
#define _ANIMATION_MODEL_CONTAINER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONMODELCONTAINER : public D3DXMESHCONTAINER
{
    public:
        LPDIRECT3DTEXTURE9* Textures;     //張り付けるテクスチャ
        LPD3DXATTRIBUTERANGE AttributeTable;//属性テーブル
        DWORD AttributeGroupValue;          //属性数

        DWORD Weight;                     //重みの個数（重みとは頂点への影響。）
        DWORD BoneValue;                  //ボーンの数
        LPD3DXBUFFER BoneBuffer;          //ボーン・テーブル
        LPD3DXMATRIX* BoneMatrix;         //全てのボーンのワールド行列の先頭ポインター
        LPD3DXMATRIX BoneOffsetMatrix;    //フレームとしてのボーンのワールド行列のポインター
};

#endif