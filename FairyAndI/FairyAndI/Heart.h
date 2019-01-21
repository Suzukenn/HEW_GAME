#ifndef _HEART_H_
#define _HEART_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <list>
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class HEART final : protected SPRITE
{
    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);
};

#endif