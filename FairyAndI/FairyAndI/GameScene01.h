#ifndef _GAME_SCENE_01_H_
#define _GAME_SCENE_01_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Canvas.h"
#include "Field.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class GAME01 final : public BASE_SCENE
{
    private:
        BACKGROUND Background_Back;
        BACKGROUND Background_Front;
        CANVAS Canvas;
        FIELD Field;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif