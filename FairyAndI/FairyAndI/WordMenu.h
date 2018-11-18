#ifndef _WORDMENU_H_
#define _WORDMENU_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "SelectMarker.h"
#include "WordList.h"
#include "WordPlate.h"

//＝＝＝列挙型定義＝＝＝//
enum
{
    SETTING_STATE_ADJECTIVELIST,
    SETTING_STATE_NOUN,
    SETTING_STATE_SELECT,
    SETTING_STATE_MAX
};

//＝＝＝クラス宣言＝＝＝//
class WORDMENU
{
    private:
        int State;
        BACKGROUND Back;
        SELECTMARKER SelectMarker;
        std::array<WORDPLATE, 2> SelectWord;
        std::array<WORDLIST, 2> List;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif