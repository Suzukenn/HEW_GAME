//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "GameOver.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

SCENE GAMEOVER::RetryScene;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：ChooseStage
//
//機能：ステージの選択
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMEOVER::ChooseButton(void)
{
	//---各種宣言---//
	D3DXVECTOR2 vecStickVector;
	static int IntervalCnt;

	vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	++IntervalCnt;
	if (IntervalCnt > 60 / 3)
	{
		IntervalCnt = 60 / 3;
		//右にスティックを入力
		if (vecStickVector.y > 0.0F)
		{
			IntervalCnt = 0;
			--Select;
			CursorPos.y -= 100.0F;
			if (Select < 0)
			{
				Select = 0;
				CursorPos.y = 400.0F;
			}
		}
		//左にスティックを入力
		else if (vecStickVector.y < 0.0F)
		{
			IntervalCnt = 0;
			++Select;
			CursorPos.y += 100.0F;
			if (Select > GAMEOVER_BUTTON - 1)
			{
				Select = GAMEOVER_BUTTON - 1;
				CursorPos.y = 500.0F;
			}
		}
	}
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームオーバーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMEOVER::Draw(void)
{
    //---オブジェクトの描画処理---//
    Back.Draw();
	Logo.Draw();
	if (LogoAlpha == 255 - 1)
	{
		for (int nConter = 0; nConter < GAMEOVER_BUTTON; ++nConter)
		{
			SelectButton.at(nConter).Draw();
		}
		Cursor.Draw();
	}
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
HRESULT GAMEOVER::Initialize(void)
{
	//---各種初期---//
	LogoAlpha = 0;
	CursorPos = D3DXVECTOR2(350.0F, 400.0F);
	Select = 0;
	RetryScene = SCENE_GAMECLEAR;			//今だけ後で消すこと

    if (FAILED(TEXTUREMANAGER::Initialize(TEXT("Data/GameOver/TextureList.txt"))))
    {
        return E_FAIL;
    }

    //---オブジェクトの初期化処理---//
    if (FAILED(Back.Initialize(TEXT("BACKGROUND"))))
    {
        return E_FAIL;
    }

	//ロゴ
	if (FAILED(Logo.Initialize((TEXT("GAMEOVER")), D3DXVECTOR2(300.0F, 100.0F), D3DXVECTOR2(700.0F, 350.0F))))
	{
		return E_FAIL;
	}

	//セレクトシーン行きのボタン
	if (FAILED(SelectButton.at(0).Initialize((TEXT("RETRY")), D3DXVECTOR2(500.0F, 400.0F), D3DXVECTOR2(300.0F, 100.0F))))
	{
		return E_FAIL;
	}

	//タイトル行きのボタン
	if (FAILED(SelectButton.at(1).Initialize((TEXT("RETURN_TITLE")), D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(300.0F, 100.0F))))
	{
		return E_FAIL;
	}

	//カーソル
	if (FAILED(Cursor.Initialize(TEXT("CURSOR"), CursorPos, D3DXVECTOR2(100.0F, 100.0F))))
	{
		return E_FAIL;
	}

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_GAMEOVER"));

	//フェード開始
	FADE::SetFade(FADE_IN);

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
void GAMEOVER::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    Back.Uninitialize();
	Logo.Uninitialize();
	for (int nConter = 0; nConter < GAMEOVER_BUTTON; ++nConter)
	{
		SelectButton.at(nConter).Uninitialize();
	}
	Cursor.Uninitialize();

    //---テクスチャの削除---//
    TEXTUREMANAGER::Uninitialize();

    //---BGM停止---//
    SOUNDMANAGER::Stop(TEXT("BGM_GAMEOVER"));
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
void GAMEOVER::Update(void)
{
    //---オブジェクトの更新処理---//
    Back.Update();
	Logo.Update();
	Logo.SetAlpha((unsigned char)LogoAlpha);

	//フェードインが終わっていたら
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		LogoAlpha += 1;
		if (LogoAlpha >= 255)
		{
			LogoAlpha = 255 - 1;
		}

		ChooseButton();
		Cursor.SetPosition(CursorPos);
		//---画面遷移---//
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, 0xFFFF, TRIGGER))
		{
			if (LogoAlpha == 255 - 1)
			{
				FADE::SetFade(FADE_OUT);
			}
			else
			{
				LogoAlpha = 255 - 1;
			}
		}
	}
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		if (Select == 0)
		{
			SCENEMANAGER::SetScene(RetryScene);
		}
		else
		{
			SCENEMANAGER::SetScene(SCENE_TITLE);
		}
	}
}

/////////////////////////////////////////////
//関数名：SetRetryScene
//
//機能：リトライ先のセット
//
//引数：(SCENE)リトライするシーン
//
//戻り値：なし
/////////////////////////////////////////////
void GAMEOVER::SetRetryScene(SCENE retryScene)
{
	RetryScene = retryScene;
}