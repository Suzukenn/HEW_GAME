#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "BaseScene.h"
#include "Fade.h"
#include "Main.h"

//�������񋓌^��`������//
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

//�������N���X�錾������//
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