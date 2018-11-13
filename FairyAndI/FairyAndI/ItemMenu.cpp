//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "ItemMenu.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TrainingScene.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：トレーニングシーンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ITEMMENU::Draw(void)
{
    //---カメラのセット---//

    //---オブジェクトの描画処理---//
    //Back.Draw();
    //Debugger.Draw();
    //Field.Draw();
    //Sprite.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：トレーニングシーンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ITEMMENU::Initialize(void)
{
    //---オブジェクトの初期化処理---//
    //背景
    //if (FAILED(Back.Initialize(D3DXVECTOR2(100.0F, 500.0F), D3DXVECTOR2(0.0F, 0.0F), TEXT("Data/GameScene/BackGround.tga"))))
    //{
    //    return E_FAIL;
    //}

    ////カメラ
    //if (FAILED(FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F))))
    //{
    //    return E_FAIL;
    //}

    //デバッガー
    //if (FAILED(Debugger.Initialize()))
    //{
    //    return E_FAIL;
    //}

    //地形
    //if (FAILED(Field.Initialize(TEXT("Data/Training/Texture/Field.jpg"), 40, 40, 8.0F, 8.0F)))
    //{
    //    return E_FAIL;
    //}

    ////ディレクショナルライト
    //if (FAILED(DIRECTIONALLIGHT::Initialize()))
    //{
    //    return E_FAIL;
    //}

    ////スプライト
    //if (FAILED(Sprite.Initialize({ 0.0F,0.0F }, { SCREEN_WIDTH,SCREEN_HEIGHT }, TEXT("Data/GameScene/BackGround.tga"))))
    //{
    //    return E_FAIL;
    //}

    //---BGM再生---//
    //SOUNDMANAGER::Play(TEXT("BGM_TRAINING"));

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：トレーニングシーンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ITEMMENU::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    //Back.Uninitialize();
    //FlexibleCamera.Uninitialize();
    //Debugger.Uninitialize();
    //DIRECTIONALLIGHT::Uninitialize();
    //Field.Uninitialize();
    //Sprite.Uninitialize();

    //---BGM停止---//
    //SOUNDMANAGER::Stop(TEXT("BGM_TRAINING"));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：トレーニングシーンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ITEMMENU::Update(void)
{
    //---オブジェクトの更新処理---//
    //Back.Update();
    //FlexibleCamera.Update();
    //Debugger.Update();
    //DIRECTIONALLIGHT::Update();
    //Field.Update();
    //Sprite.Update();

    ////---画面遷移---//
    //if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
    //{
    //    SCENEMANAGER::SetScene(SCENE_TITLE);
    //}
}