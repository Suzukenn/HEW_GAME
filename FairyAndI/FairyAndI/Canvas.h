#ifndef _CANVAS_H_
#define _CANVAS_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Heart.h"
#include "Main.h"
#include "Player.h"
#include "SkillBox.h"
#include "WordMenu.h"

//＝＝＝クラス宣言＝＝＝//
class CANVAS
{
    private:
        SKILLBOX SkillBox;
        WORDPLATE Skill;
        WORDMENU Menu;
        bool Mode;

        std::array<HEART, MAX_PLAYER_HP> Heart;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif