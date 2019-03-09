#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class TEXTURE
{
    public:
        LPDIRECT3DTEXTURE9 Image;
        D3DSURFACE_DESC Descriptor;
};

#endif