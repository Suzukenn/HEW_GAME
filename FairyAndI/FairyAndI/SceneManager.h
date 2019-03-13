#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "BaseScene.h"
#include "Fade.h"
#include "Main.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    SCENE_TRAINING,
    SCENE_TITLE,
    SCENE_SELECT,
    SCENE_GAME01,
    SCENE_GAME02,
    SCENE_GAME03,
    SCENE_GAMEOVER,
	SCENE_GAMECLEAR,
    MAX_SCENE
}SCENE;

//＝＝＝クラス宣言＝＝＝//
class SCENEMANAGER
{
    private:
        static std::unique_ptr<BASE_SCENE> Scene;
        static SCENE CurrentScene;
        static SCENE NextScene;

    public:
        static void Draw(void);
        static void Uninitialize(void);
        static HRESULT Initialize(void);
        static void Update(void);
    
        static void SetScene(SCENE);
};

#endif