#ifndef _MODEL_H_
#define _MODEL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class MODELMANAGER;
class SHADER;

//＝＝＝クラス宣言＝＝＝//
class MODEL
{
    private:
        DWORD MaterialValue;			                //マテリアル情報の数
        DWORD AttributeValue;		                    //属性数(サブセット数)

        std::vector<D3DMATERIAL9> Material;	            //マテリアル配列
        std::vector<LPDIRECT3DTEXTURE9>	Texture;	    //テクスチャへのポインタ
        std::vector<LPD3DXATTRIBUTERANGE> Attribute;    //属性配列

        LPD3DXMESH Mesh;		                        //メッシュ情報へのポインタ
        LPD3DXBUFFER MaterialBuffer;	                //マテリアル情報へのポインタ

    public:
        void Draw(bool);
        void MODEL::Draw(std::weak_ptr<SHADER>&, LPCTSTR, UINT, D3DXMATRIX&);

        friend MODELMANAGER;
};

#endif