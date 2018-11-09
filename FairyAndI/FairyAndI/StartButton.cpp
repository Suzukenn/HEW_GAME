//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "StartButton.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Behavior
//
//機能：スタートボタンの挙動
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void STARTBUTTON::Behavior(void)
{
    if (INPUTMANAGER::GetMouseButton(MOUSEBUTTON_LEFT, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAME);
    }
}