#ifndef _MODEL_H_
#define _MODEL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
typedef struct
{
    LPD3DXMESH Mesh;		        //メッシュ情報へのポインタ
    D3DMATERIAL9* Material;	        //マテリアル配列
    LPD3DXBUFFER MaterialBuffer;	//マテリアル情報へのポインタ
    DWORD MaterialValue;			//マテリアル情報の数
    LPDIRECT3DTEXTURE9*	Texture;	//テクスチャへのポインタ
    LPD3DXATTRIBUTERANGE Attribute;	//属性配列
    DWORD AttributeValue;		    //属性数(サブセット数)

    void Release(void)
    {
        //SAFE_RELEASE(Mesh);
        //SAFE_RELEASE(MaterialBuffer);
        //SAFE_RELEASE((*Texture));
    }

} MODEL;

#endif