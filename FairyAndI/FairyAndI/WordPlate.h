#ifndef _WORDPLATE_H_
#define _WORDPLATE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class WORDPLATE final : protected SPRITE
{
    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Update(void);

        HRESULT SetTexture(LPCTSTR&);
};

#endif