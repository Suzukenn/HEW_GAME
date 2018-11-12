#ifndef _TRAININGSCENE_H_
#define _TRAININGSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Debug.h"
#include "Field.h"
#include "FlexibleCamera.h"
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class TRAINING final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        FLEXIBLECAMERA FlexibleCamera;
        DEBUG Debugger;
        FIELD Field;
        SPRITE Sprite;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif