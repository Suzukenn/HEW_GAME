#ifndef _TRAINING_BUTTON_H_
#define _TRAINING_BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Button.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class TRAININGBUTTON final : public BUTTON
{
    virtual void Behavior(void) final;
};

#endif