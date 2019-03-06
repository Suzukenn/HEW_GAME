#ifndef _STAGE_BUTTON_H_
#define _STAGE_BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Button.h"
#include "Main.h"
#include "SceneManager.h"

//＝＝＝クラス宣言＝＝＝//
class STAGEBUTTON final : public BUTTON
{
	private:
		SCENE Stage;
	public:
		virtual void Behavior(void) final;
		void SetSelectStage(SCENE);
};

#endif