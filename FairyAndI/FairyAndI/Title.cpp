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
    AnimationBack.Draw();
    Back.Draw();
    Logo.Draw();
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
        return hResult;
    }

    //---オブジェクトの初期化処理---//
    //雲
    hResult = AnimationBack.Initialize((TEXT("TITLE_BACK")));
    if (FAILED(hResult))
    {
        return hResult;
    }
    
    //ビル群
    hResult = Back.Initialize((TEXT("TITLE_FRONT")));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //タイトルロゴ
    hResult = Logo.Initialize((TEXT("TITLE_LOGO")), D3DXVECTOR2(300.0F, 100.0F), D3DXVECTOR2(700.0F, 350.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //スタートボタン
    hResult = StartButton.Initialize(TEXT("START_BUTTON"), D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //トレーニングボタン
    hResult = FAILED(TrainingButton.Initialize(TEXT("TRAINING_BUTTON"), D3DXVECTOR2(800.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F)));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_TITLE"));

	//フェード開始
	FADE::SetFade(FADE_IN);

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
void TITLE::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    AnimationBack.Uninitialize();
    Back.Uninitialize();
    Logo.Uninitialize();
    StartButton.Uninitialize();
    TrainingButton.Uninitialize();

    //---テクスチャの削除---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    SOUNDMANAGER::Stop(TEXT("BGM_TITLE"));
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
	static int Mood;
    static unsigned char LogoAlpha = 0;

    //---オブジェクトの更新処理---//
    AnimationBack.MoveTexture();
    Back.Update();
    Logo.Update();
    if (++LogoAlpha > 255)
    {
        Logo.SetAlpha(LogoAlpha);
    }
    StartButton.Update();
    TrainingButton.Update();

	//フェードインが終わっていたら
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
		{
			FADE::SetFade(FADE_OUT);
			//SCENEMANAGER::SetScene(SCENE_SELECT);
			Mood = 1;
		}
		else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_START, TRIGGER))
		{
			FADE::SetFade(FADE_OUT);
			//SCENEMANAGER::SetScene(SCENE_TRAINING);
			Mood = 2;
		}
	}
	//フェードアウトが終わっていたら
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		if (Mood == 1)
		{
			SCENEMANAGER::SetScene(SCENE_SELECT);
		}
		else if(Mood == 2)
		{
			SCENEMANAGER::SetScene(SCENE_TRAINING);
		}
	}
}