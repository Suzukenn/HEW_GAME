//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Debug.h"
#include "DirectionalLight.h"
#include "FlexibleCamera.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingScene.h"
#include "WordMenu.h"

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
void TRAINING::Draw(void)
{
    //---カメラのセット---//

    //---オブジェクトの描画処理---//
    //Debugger.Draw();
    Field.Draw();
    if (!Mode)
    {
        Menu.Draw();
    }
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
HRESULT TRAINING::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    Mode = true;

    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Training/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---オブジェクトの初期化処理---//

    //カメラ
    hResult = FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //デバッガー
    //if (FAILED(Debugger.Initialize()))
    //{
    //    return E_FAIL;
    //}

    //地形
    hResult = Field.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //ディレクショナルライト
    hResult = DIRECTIONALLIGHT::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //フェアリータイムメニュー
    hResult = Menu.Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_TRAINING"));

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
void TRAINING::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    FlexibleCamera.Uninitialize();
    //Debugger.Uninitialize();
    DIRECTIONALLIGHT::Uninitialize();
    Field.Uninitialize();
    Menu.Uninitialize();

    //---テクスチャの削除---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    SOUNDMANAGER::Stop(TEXT("BGM_TRAINING"));
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
void TRAINING::Update(void)
{
    //---各種宣言---//

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }

    //---オブジェクトの更新処理---//
    if (Mode)
    {
        FlexibleCamera.Update();
        //Debugger.Update();
        DIRECTIONALLIGHT::Update();
        Field.Update();

        //---画面遷移---//
        if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
        {
            SCENEMANAGER::SetScene(SCENE_TITLE);
        }
    }
    else
    {
        Menu.Update();
    }
}