//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Canvas.h"
#include "DirectionalLight.h"
#include "FlexibleCamera.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "SideViewCamera.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingScene.h"
#include "WordManager.h"

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
    //---オブジェクトの描画処理---//
    Field.Draw();
    
    //for (int i = 0; i < MAX_ITEM; i++)
    //{
    //    Item[i].Draw();
    //}

    Fairy.Draw();

    Player.Draw();

    Canvas.Draw();
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

    //---データの読み込み---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Training/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //hResult = MODELMANAGER::Initialize(TEXT("Data/Model/ModelList.txt"));
    //if (FAILED(hResult))
    //{
    //    return E_FAIL;
    //}

    hResult = WORDMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return E_FAIL;
    }


    //---オブジェクトの初期化処理---//
    //地形
    hResult = Field.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //フェアリー
    if (FAILED(Fairy.Initialize()))
    {
        return E_FAIL;
    }

    //アイテム
    //for (int i = 0; i < MAX_ITEM; i++)
    //{
    //    if (FAILED(Item[i].Initialize()))
    //    {
    //        return E_FAIL;
    //    }
    //}
    //Item[0].CreateItem(D3DXVECTOR3(0.0f, 10.0f, 0.0f), ITEM_ICE);
    //Item[1].CreateItem(D3DXVECTOR3(100.0f, 10.0f, 0.0f), ITEM_FIRE);

    //プレイヤー
    hResult = Player.Initialize(TEXT("Data/Model/car000.x"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //フレキシブルカメラ
    hResult = FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //サイドビューカメラ
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(0.0F, 20.0F, -150.0F), Player.GetPlayerPosition());
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

    //UIキャンバス
    hResult = Canvas.Initialize();
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
    Canvas.Uninitialize();
    FlexibleCamera.Uninitialize();
    Field.Uninitialize();
    Fairy.Uninitialize();
    Player.Uninitialize();

    DIRECTIONALLIGHT::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();

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
    static bool bCameraMode = false;

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }

    //---オブジェクトの更新処理---//
    if (Mode)
    {
        if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_START, TRIGGER)) bCameraMode = !bCameraMode;
        bCameraMode ? FlexibleCamera.Update() : SIDEVIEWCAMERA::Update(Player.GetPlayerPosition());

        Field.Update();

        Player.Update();
        Fairy.Update(SIDEVIEWCAMERA::GetRotation(), Player.GetPlayerPosition(), *Player.GetPlayerRotation(), Item);

        //for (int i = 0; i < MAX_ITEM; i++)
        //{
        //    Item[i].Update(Item);
        //}


        DIRECTIONALLIGHT::Update();

        //---画面遷移---//
        if (INPUTMANAGER::GetKey(DIK_SPACE, TRIGGER))
        {
            SCENEMANAGER::SetScene(SCENE_TITLE);
        }
    }
    Canvas.Update();
}