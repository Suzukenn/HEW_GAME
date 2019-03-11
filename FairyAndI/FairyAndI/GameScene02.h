#ifndef _GAME_SCENE_02_H_
#define _GAME_SCENE_02_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class GAME02 final : public BASE_SCENE
{
    private:
        BACKGROUND Back;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif