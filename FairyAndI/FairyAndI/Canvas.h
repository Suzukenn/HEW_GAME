#ifndef _CANVAS_H_
#define _CANVAS_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <list>
#include "ItemBox.h"
#include "Main.h"
#include "Sprite.h"
#include "WordMenu.h"
//＝＝＝クラス宣言＝＝＝//
class CANVAS
{
    private:
        ITEMBOX ItemBox;
        WORDPLATE Item;
        WORDMENU Menu;

        bool Mode;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif