#ifndef _TITLE_H_
#define _TITLE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackImage.h"
#include "BaseScene.h"
#include "Fade.h"
#include "Main.h"
#include "StartButton.h"
#include "TrainingButton.h"

//＝＝＝クラス宣言＝＝＝//
class TITLE final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;
        STARTBUTTON StartButton;
        TRAININGBUTTON TrainingButton;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif