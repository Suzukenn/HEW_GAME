//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "SoundManager.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：タイトルの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTSCENE::Draw(void)
{
    Back.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：タイトルの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SELECTSCENE::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/SelectScene/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---オブジェクトの初期化---//
    hResult = Back.Initialize(TEXT("BACKGROUND"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

	FADE::SetFade(FADE_IN);

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_SELECT"));

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：タイトルの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTSCENE::Uninitialize(void)
{
    //---解放---//
    Back.Uninitialize();

    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    SOUNDMANAGER::Stop(TEXT("BGM_SELECT"));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：タイトルの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void SELECTSCENE::Update(void)
{
    //---オブジェクトの更新---//
    Back.Update();

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_GAME);
    }
    else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TITLE);
    }
}