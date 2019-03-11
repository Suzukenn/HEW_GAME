#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "AnimationbackImage.h"
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"

#define GAMECLEAR_BUTTON (2)

//＝＝＝クラス宣言＝＝＝//
class GAMECLEAR final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;
		std::array<SPRITE, GAMECLEAR_BUTTON> SelectButton;
		ANIMATIONSPRITE Cursor;

		int Select;
		D3DXVECTOR2 CursorPos;

		void ChooseButton(void);

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif