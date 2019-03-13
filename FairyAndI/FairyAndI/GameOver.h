#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "AnimationbackImage.h"
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"
#include "SceneManager.h"

#define GAMEOVER_BUTTON	(2)

//＝＝＝クラス宣言＝＝＝//
class GAMEOVER final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;
		ANIMATIONBACKIMAGE Logo;
		std::array<SPRITE, GAMEOVER_BUTTON> SelectButton;
		ANIMATIONSPRITE Cursor;

		unsigned int LogoAlpha;
		int Select;
		D3DXVECTOR2 CursorPos;
		static SCENE RetryScene;

		void ChooseButton(void);

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);

		static void SetRetryScene(SCENE);
};

#endif