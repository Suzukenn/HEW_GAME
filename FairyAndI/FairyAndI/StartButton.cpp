//wb_t@CÇÝÝ//
#include "InputManager.h"
#include "SceneManager.h"
#include "StartButton.h"

//Öè`//
/////////////////////////////////////////////
//Ö¼FBehavior
//
//@\FX^[g{^Ì®
//
//øFÈµ
//
//ßèlFÈµ
/////////////////////////////////////////////
void STARTBUTTON::Behavior(void)
{
    if (INPUTMANAGER::GetMouseButton(MOUSEBUTTON_LEFT, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_SELECT);
    }
}