//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameOver.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Title.h"
#include "TrainingScene.h"

//＝＝＝グローバル変数＝＝＝//
std::unique_ptr<BASE_SCENE> SCENEMANAGER::Scene(new TITLE());
SCENE SCENEMANAGER::CurrentScene = SCENE_TITLE;
SCENE SCENEMANAGER::NextScene = CurrentScene;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：シーンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SCENEMANAGER::Draw(void)
{
    Scene->Draw();
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：シーンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SCENEMANAGER::Uninitialize(void)
{
    Scene->Uninitialize();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：シーンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SCENEMANAGER::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;
    
    //---初期化処理---//
    hResult = E_FAIL;

    //---シーンの切り替え---//
    hResult = Scene->Initialize();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("シーンの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：SetScene
//
//機能：シーンの設定
//
//引数：(SCENE)シーン番号
//
//戻り値：なし
/////////////////////////////////////////////
void SCENEMANAGER::SetScene(SCENE scene)
{
    NextScene = scene;
}

/////////////////////////////////////////////
//関数名：UpdateScene
//
//機能：シーンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SCENEMANAGER::Update(void)
{
    //---シーン切り替え---//
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
        }
        if (FAILED(Scene->Initialize()))
        {
            MessageBox(nullptr, TEXT("シーンの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
            exit(EXIT_FAILURE);
        }
        CurrentScene = NextScene;
    }
    else
    {
        //---シーン関数呼び出し---//
        Scene->Update();
    }
}