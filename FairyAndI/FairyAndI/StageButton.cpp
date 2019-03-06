//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Fade.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "StageButton.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Behavior
//
//機能：ステージボタンの挙動
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void STAGEBUTTON::Behavior(void)
{
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
		{
			FADE::SetFade(FADE_OUT);
		}
	}
	//フェードアウトが終わっていたら
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		SCENEMANAGER::SetScene(Stage);
	}
}

/////////////////////////////////////////////
//関数名：SetSelectStage
//
//機能：ステージの行き先セット
//
//引数：(SCENE)ステージの行き先
//
//戻り値：なし
/////////////////////////////////////////////
void STAGEBUTTON::SetSelectStage(SCENE stage)
{
	Stage = stage;
}
