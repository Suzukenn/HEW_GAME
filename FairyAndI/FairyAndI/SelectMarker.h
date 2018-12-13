#ifndef _SELECTMARKER_H_
#define _SELECTMARKER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "AnimationSprite.h"

//＝＝＝クラス宣言＝＝＝//
class SELECTMARKER final : protected ANIMATIONSPRITE
{
    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);
};

#endif