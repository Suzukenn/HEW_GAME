#ifndef _WORDLIST_H_
#define _WORDLIST_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class WORDLIST
{
    private:
        BACKGROUND Back;
        std::vector<SPRITE> WordSprite;
        std::vector<bool> UnlockCheck;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif