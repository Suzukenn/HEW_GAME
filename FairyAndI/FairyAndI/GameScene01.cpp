//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "BackGround.h"
#include "Canvas.h"
#include "CharacterFactory.h"
#include "CollisionManager.h"
#include "DirectionalLight.h"
#include "Fade.h"
#include "GameScene01.h"
#include "GimmickFactory.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "SideViewCamera.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "WordManager.h"

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
void GAME01::Draw(void)
{
    Background_Back.Draw();
    Background_Front.Draw();
    Field.Draw();
    ACTORMANAGER::Draw();
    Canvas.Draw();
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
HRESULT GAME01::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

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

    hResult = ANIMATIONMODELMANAGER::Initialize(TEXT("Data/GameScene/Model/AnimationModelList.txt"));
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
    CHARACTERFACTORY::InstantiatePlayer(D3DXVECTOR3(50.0F, 50.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));
    CHARACTERFACTORY::InstantiateFairy(D3DXVECTOR3(50.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 0.0F, 0.0F));

    //敵
    CHARACTERFACTORY::InstantiateSlime(D3DXVECTOR3(700.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 270.0F, 0.0F));

    //エレメント
    OBJECTFACTORY::InstantiateFireElement(D3DXVECTOR3(300.0F, 10.0F, 0.0F));

    //ギミック
    GIMMICKFACTORY::InstantiateWoodGimmick(D3DXVECTOR3(500.0F, 10.0F, 0.0F), D3DXVECTOR3(0.0F, 180.0F, 0.0F));
    OBJECTFACTORY::InstantiateGoal(D3DXVECTOR3(1000.0F, 10.0F, 0.0F));

    //地形
    hResult = Field.Initialize(TEXT("Data/GameScene/Model/Field/Stage01.x"), TEXT("Field"), D3DXVECTOR3(0.0F, 10.0F, 0.0F), D3DXVECTOR3(1.0F, 1.0F, 1.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //背景
    hResult = Background_Back.Initialize(TEXT("BACKGROUND_BACK"), D3DXVECTOR3(0.0F, -12.0F, 80.0F), D3DXVECTOR2(321.0F, 120.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
    hResult = Background_Front.Initialize(TEXT("BACKGROUND_FRONT"), D3DXVECTOR3(0.0F, -12.0F, 80.0F), D3DXVECTOR2(320.0F, 120.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //サイドビューカメラ
    hResult = SIDEVIEWCAMERA::Initialize(D3DXVECTOR3(50.0F, 20.0F, -50.0F), PLAYER::GetPlayerPosition());
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
    SOUNDMANAGER::Play(TEXT("BGM_GAME"));

    return hResult;
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
void GAME01::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    Background_Back.Uninitialize();
    Background_Front.Uninitialize();
    Canvas.Uninitialize();
    Field.Uninitialize();

    //---スタッフ系列の終了処理---//
    ACTORMANAGER::Uninitialize();
    ANIMATIONMODELMANAGER::Uninitialize();
    COLLISIONMANAGER::Uninitialize();
    DIRECTIONALLIGHT::Uninitialize();
    MODELMANAGER::Uninitialize();
    SIDEVIEWCAMERA::Uninitialize();
    SHADERMANAGER::Uninitialize();
    TEXTUREMANAGER::Uninitialize();
    WORDMANAGER::Uninitialize();

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
void GAME01::Update(void)
{
    //---各種宣言---//

    //---オブジェクトの更新処理---//
    SIDEVIEWCAMERA::Update(PLAYER::GetPlayerPosition());
    ACTORMANAGER::Update();
    DIRECTIONALLIGHT::Update();
    COLLISIONMANAGER::Update();

    Background_Back.Update(0.00075F, true);
    Background_Front.Update(0.0015F);
    Canvas.Update();

    //---画面遷移---//
    if(!PLAYER::GetPlayerHP())
    {
        SCENEMANAGER::SetScene(SCENE_GAMEOVER);
    }
}