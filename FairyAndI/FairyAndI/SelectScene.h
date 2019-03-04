#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"
#include "StageButton.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define MAX_SELECTBUTTON (3)

//＝＝＝クラス宣言＝＝＝//
class SELECTSCENE final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;
		std::array<STAGEBUTTON, MAX_SELECTBUTTON> Button;
		int Select;
		// 点滅制御用
		DWORD dwTicks;
		DWORD dwMask;

		void ChooseStage(void);

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif