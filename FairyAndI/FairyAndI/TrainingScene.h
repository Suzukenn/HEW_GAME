#ifndef _TRAININGSCENE_H_
#define _TRAININGSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BaseScene.h"
#include "BackGround.h"
#include "Canvas.h"
#include "Field.h"
#include "FlexibleCamera.h"
#include "Ground.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class TRAINING final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        CANVAS Canvas;
        FIELD Field;
        GROUND Ground;
        FLEXIBLECAMERA FlexibleCamera;

        bool Mode;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif