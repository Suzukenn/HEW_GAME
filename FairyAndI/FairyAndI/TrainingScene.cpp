//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "BackGround.h"
#include "Canvas.h"
#include "CharacterFactory.h"
#include "CollisionManager.h"
#include "DirectionalLight.h"
#include "Fade.h"
#include "FlexibleCamera.h"
#include "GimmickFactory.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
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
    Ground.Draw();
    Back.Draw();
    ACTORMANAGER::Draw();
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
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/GameScene/TextureList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = MODELMANAGER::Initialize(TEXT("Data/GameScene/Model/ModelList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = SHADERMANAGER::Initialize(TEXT("Data/GameScene/ShaderList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = WORDMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = ACTORMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = COLLISIONMANAGER::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---オブジェクトの初期化処理---//

    //キャラクター
    CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3(-20.0F, 50.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));
    CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));

    //エレメント
    OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3(100.0F, 0.0F, 0.0F));
    OBJECTFACTORY::InstantiateIceElement(D3DXVECTOR3(-50.0F, 0.0F, 0.0F));

    //ギミック
    GIMMICKFACTORY::InstantiateBatteryGimmick(D3DXVECTOR3(50.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));
	OBJECTFACTORY::InstantiateGoal(D3DXVECTOR3(150.0F, 10.0F, 0.0F));

    //地形
    //hResult = Field.Initialize(TEXT("Data/Common/Model/Field/Field.x"), TEXT("Field"), D3DXVECTOR3(0.0F, -10.0F, 0.0F), D3DXVECTOR3(20.0F, 20.0F, 20.0F));
    hResult = Field.Initialize(TEXT("Data/GameScene/Model/Field/Field.x"), TEXT("Field"), D3DXVECTOR3(0.0F, -10.0F, 0.0F), D3DXVECTOR3(1.0F, 20.0F, 1.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    hResult = Ground.Initialize(TEXT("FIELD"), 40, 40, 8.0F, 8.0F);
    if (FAILED(hResult))
    {
        return hResult;
    }
    hResult = Back.Initialize(TEXT("SKILL_HOTFIRE"), D3DXVECTOR3(0.0F, 0.0F, 100.0F), D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
    //フレキシブルカメラ
    hResult = FlexibleCamera.Initialize(D3DXVECTOR3(0.0F, 100.0F, -200.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //サイドビューカメラ
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(0.0F, 20.0F, -150.0F), PLAYER::GetPlayerPosition());
    if (FAILED(hResult))
    {
        return hResult;
    }

    //ディレクショナルライト
    hResult = DIRECTIONALLIGHT::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    //UIキャンバス
    hResult = Canvas.Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    FADE::SetFade(FADE_IN);

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_TRAINING"));

    return hResult;
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
    Back.Uninitialize();
    Canvas.Uninitialize();
    FlexibleCamera.Uninitialize();
    Field.Uninitialize();

    DIRECTIONALLIGHT::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();
    ACTORMANAGER::Uninitialize();
    COLLISIONMANAGER::Uninitialize();
    WORDMANAGER::Uninitialize();
    SHADERMANAGER::Uninitialize();

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

    //---オブジェクトの更新処理---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_START, TRIGGER))
    {
        bCameraMode = !bCameraMode;
    }
    bCameraMode ? FlexibleCamera.Update() : SIDEVIEWCAMERA::Update(PLAYER::GetPlayerPosition());

    ACTORMANAGER::Update();

    Field.Update();

    DIRECTIONALLIGHT::Update();

    COLLISIONMANAGER::Update();

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }

    if (INPUTMANAGER::GetKey(DIK_Z, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("FIRE"));
    }
    if (INPUTMANAGER::GetKey(DIK_X, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("ICE"));
    }
    if (INPUTMANAGER::GetKey(DIK_C, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("ROCK"));
    }
    if (INPUTMANAGER::GetKey(DIK_V, TRIGGER))
    {
        WORDMANAGER::UnLockWord(TEXT("RICECAKE"));
    }

    Canvas.Update();
    Back.Update();

    //---画面遷移---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_BACK, TRIGGER))
    {
        SCENEMANAGER::SetScene(SCENE_TITLE);
    }
}