//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingButton.h"
#include "Title.h"

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
void TITLE::Draw(void)
{
    //---オブジェクトの描画処理---//
    Back.Draw();
    StartButton.Draw();
    TrainingButton.Draw();
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
HRESULT TITLE::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/Title/TextureList.txt"));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---オブジェクトの初期化処理---//
    //背景
    hResult = Back.Initialize((TEXT("BACKGROUND")));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //スタートボタン
    hResult = StartButton.Initialize(TEXT("START_BUTTON"), D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //トレーニングボタン
    hResult = FAILED(TrainingButton.Initialize(TEXT("TRAINING_BUTTON"), D3DXVECTOR2(800.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F)));
    if (FAILED(hResult))
    {
        return E_FAIL;
    }

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_OPENING"));

    return S_OK;
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
void TITLE::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    Back.Uninitialize();
    StartButton.Uninitialize();
    TrainingButton.Uninitialize();

    //---テクスチャの削除---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    SOUNDMANAGER::Stop(TEXT("BGM_OPENING"));
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
void TITLE::Update(void)
{
    //---オブジェクトの更新処理---//
    Back.Update();
    StartButton.Update();
    TrainingButton.Update();
}