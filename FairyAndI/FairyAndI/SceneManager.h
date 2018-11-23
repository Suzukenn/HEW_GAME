#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "BaseScene.h"
#include "Main.h"

//�������񋓌^��`������//
typedef enum
{
    SCENE_TRAINING,
    SCENE_TITLE,
    SCENE_SELECT,
    SCENE_GAME,
    SCENE_GAMEOVER,
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