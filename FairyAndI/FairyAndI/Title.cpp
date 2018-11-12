//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
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
    //---オブジェクトの初期化処理---//
    if (FAILED(Back.Initialize(TEXT("Data/Title/Title.png"))))
    {
        return E_FAIL;
    }

    if (FAILED(StartButton.Initialize(TEXT("Data/Title/UI/GameStartButton.png"), { 500.0F, 500.0F }, { 200.0F, 50.0F })))
    {
        return E_FAIL;
    }

    if (FAILED(TrainingButton.Initialize(TEXT("Data/Title/UI/Training.tga"), { 800.0F, 500.0F }, { 200.0F, 50.0F })))
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