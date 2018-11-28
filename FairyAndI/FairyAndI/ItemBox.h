#ifndef _ITEM_BOX_H_
#define _ITEM_BOX_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "AnimationSprite.h"

//＝＝＝クラス宣言＝＝＝//
class ITEMBOX final : private ANIMATIONSPRITE
{
    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        void Uninitialize(void);
        void Update(void);
};

#endif