#ifndef _ITEMMENU_H_
#define _ITEMMENU_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class ITEMMENU
{
    private:
        SPRITE Back;
        std::vector<SPRITE> Item;
        std::vector<bool> Unlockcheck;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif