//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Fade.h"
#include "GameClear.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームオーバーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Draw(void)
{
    //---オブジェクトの描画処理---//
    Back.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ゲームオーバーの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAMECLEAR::Initialize(void)
{
    if (FAILED(TEXTUREMANAGER::Initialize(TEXT("Data/GameClear/TextureList.txt"))))
    {
        return E_FAIL;
    }

    //---オブジェクトの初期化処理---//
    if (FAILED(Back.Initialize(TEXT("BACKGROUND"))))
    {
        return E_FAIL;
    }

	FADE::SetFade(FADE_IN);

    //---BGM再生---//
    //SOUNDMANAGER::Play(TEXT("BGM_GAMEOVER"));

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゲームオーバーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    Back.Uninitialize();

    //---テクスチャの削除---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    //SOUNDMANAGER::Stop(TEXT("BGM_GAMEOVER"));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ゲームオーバーの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Update(void)
{
    //---オブジェクトの更新処理---//
    Back.Update();

    //---画面遷移---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
    {
		FADE::SetFade(FADE_OUT);        
    }
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		SCENEMANAGER::SetScene(SCENE_TITLE);
	}
}