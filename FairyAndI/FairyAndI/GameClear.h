#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class GAMECLEAR final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif