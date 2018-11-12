#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class GAMEOVER final : public BASE_SCENE
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