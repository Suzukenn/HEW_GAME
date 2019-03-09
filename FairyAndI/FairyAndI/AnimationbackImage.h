#ifndef _ANIMATION_BACKIMAGE_H_
#define _ANIMATION_BACKIMAGE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "AnimationSprite.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONBACKIMAGE final : private ANIMATIONSPRITE
{
    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2 position = D3DXVECTOR2(0.0F, 0.0F), D3DXVECTOR2 size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), POINT uv = {1, 1});
        void MoveTexture(void);
        void SetAlpha(unsigned char);
        void Uninitialize(void);
        void Update(void);
};

#endif 