#ifndef _TITLE_H_
#define _TITLE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "StartButton.h"

//＝＝＝クラス宣言＝＝＝//
class TITLE final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        STARTBUTTON StartButton;

    public:
        void Draw(void) final;
        void Uninitialize(void) final;
        HRESULT Initialize(void) final;
        void Update(void) final;
};

#endif