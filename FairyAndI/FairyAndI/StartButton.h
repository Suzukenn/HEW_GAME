#ifndef _START_BUTTON_H_
#define _START_BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Button.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class STARTBUTTON final : public BUTTON
{
    virtual void Behavior(void) final;
};

#endif