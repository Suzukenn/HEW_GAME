//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "TrainingButton.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Behavior
//
//機能：トレーニングボタンの挙動
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TRAININGBUTTON::Behavior(void)
{
    if (INPUTMANAGER::GetMouseButton(MOUSEBUTTON_LEFT, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TRAINING);
    }
}