//wb_t@CÇÝÝ//
#include "InputManager.h"
#include "SceneManager.h"
#include "TrainingButton.h"

//Öè`//
/////////////////////////////////////////////
//Ö¼FBehavior
//
//@\Fg[jO{^Ì®
//
//øFÈµ
//
//ßèlFÈµ
/////////////////////////////////////////////
void TRAININGBUTTON::Behavior(void)
{
    if (INPUTMANAGER::GetMouseButton(MOUSEBUTTON_LEFT, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TRAINING);
    }
}