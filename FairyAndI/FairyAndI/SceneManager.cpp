//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Fade.h"
#include "GameClear.h"
#include "GameOver.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Title.h"
#include "TrainingScene.h"

//�������O���[�o���ϐ�������//
std::unique_ptr<BASE_SCENE> SCENEMANAGER::Scene(new TITLE());
SCENE SCENEMANAGER::CurrentScene = SCENE_TITLE;
SCENE SCENEMANAGER::NextScene = CurrentScene;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�V�[���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENEMANAGER::Draw(void)
{
    Scene->Draw();

	FADE::Draw();
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�V�[���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENEMANAGER::Uninitialize(void)
{
    Scene->Uninitialize();

	FADE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�V�[���̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SCENEMANAGER::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;
    
    //---����������---//
    hResult = E_FAIL;

    //---�V�[���ƃt�F�[�h�̐؂�ւ�---//
	hResult = FADE::Initialize();
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�t�F�[�h�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		return hResult;
	}
    hResult = Scene->Initialize();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�V�[���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FSetScene
//
//�@�\�F�V�[���̐ݒ�
//
//�����F(SCENE)�V�[���ԍ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENEMANAGER::SetScene(SCENE scene)
{
    NextScene = scene;
}

/////////////////////////////////////////////
//�֐����FUpdateScene
//
//�@�\�F�V�[���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SCENEMANAGER::Update(void)
{
    //---�V�[���؂�ւ�---//
    if (CurrentScene != NextScene)
    {
        Scene->Uninitialize();
        switch (NextScene)
        {
            case SCENE_TRAINING:
                Scene.reset(new TRAINING());
                break;

            case SCENE_TITLE:
                Scene.reset(new TITLE());
                break;

            case SCENE_SELECT:
                Scene.reset(new SELECTSCENE());
                break;

            case SCENE_GAME:
                Scene.reset(new GAME());
                break;

            case SCENE_GAMEOVER:
                Scene.reset(new GAMEOVER());
                break;
			case SCENE_GAMECLEAR:
				Scene.reset(new GAMECLEAR());
				break;
        }
        if (FAILED(Scene->Initialize()))
        {
            MessageBox(nullptr, TEXT("�V�[���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
            exit(EXIT_FAILURE);
        }
        CurrentScene = NextScene;
    }
    else
    {
        //---�V�[���֐��Ăяo��---//
        Scene->Update();
    }

	FADE::Update();
}