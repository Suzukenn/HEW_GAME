#ifndef _WORDMENU_H_
#define _WORDMENU_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
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
        static int State;
        static bool Control;
        static BACKGROUND Back;
        static SELECTMARKER SelectMarker;
        static std::array<WORDPLATE, 2> SelectWord;
        static std::array<WORDLIST, 2> List;

        static HRESULT Load(std::vector<std::vector<tstring>>&);

    public:
        static void Draw(void);
        static void Uninitialize(void);
        static HRESULT Initialize(void);
        static void Update(void);
        static tstring NotificationAdjective(void) { return List.at(0).GetSelectWord(); }
        static tstring NotificationNoun(void) { return List.at(1).GetSelectWord(); }
};

#endif