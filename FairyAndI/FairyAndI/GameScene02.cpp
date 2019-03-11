//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameScene02.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームシーンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME02::Draw(void)
{
    //---オブジェクトの描画処理---//
    //Back.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ゲームシーンの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAME02::Initialize(void)
{
    if (FAILED(TEXTUREMANAGER::Initialize(TEXT("Data/GameScene/TextureList.txt"))))
    {
        return E_FAIL;
    }

    //---オブジェクトの初期化処理---//
    //if (FAILED(Back.Initialize(TEXT("BACKGROUND"))))
    //{
    //    return E_FAIL;
    //}

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_GAME"));

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゲームシーンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME02::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    Back.Uninitialize();

    //---テクスチャの削除---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    SOUNDMANAGER::Stop(TEXT("BGM_GAME"));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ゲームシーンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAME02::Update(void)
{
    //---オブジェクトの更新処理---//
    Back.Update();

    //---画面遷移---//
    if (INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }
}