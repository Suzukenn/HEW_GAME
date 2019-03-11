//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Fade.h"
#include "GameClear.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

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
void GAMECLEAR::ChooseButton(void)
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
            SOUNDMANAGER::Stop(TEXT("SE_CURSOR"));
            SOUNDMANAGER::Play(TEXT("SE_CURSOR"));

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
            SOUNDMANAGER::Stop(TEXT("SE_CURSOR"));
            SOUNDMANAGER::Play(TEXT("SE_CURSOR"));

			IntervalCnt = 0;
			++Select;
			CursorPos.y += 100.0F;
			if (Select > GAMECLEAR_BUTTON - 1)
			{
				Select = GAMECLEAR_BUTTON - 1;
				CursorPos.y = 500.0F;
			}
		}
	}
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：ゲームクリアの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Draw(void)
{
    //---オブジェクトの描画処理---//
    Back.Draw();
	for (int nConter = 0; nConter < GAMECLEAR_BUTTON; ++nConter)
	{
		SelectButton.at(nConter).Draw();
	}
	Cursor.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ゲームクリアの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GAMECLEAR::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

	//---各種初期---//
	CursorPos = D3DXVECTOR2(350.0F, 400.0F);
	Select = 0;

    hResult = TEXTUREMANAGER::Initialize(TEXT("Data/GameClear/TextureList.txt"));
    if (FAILED(hResult))
    {
        return hResult;
    }

    //---オブジェクトの初期化処理---//
    hResult = Back.Initialize(TEXT("BACKGROUND"));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//セレクトシーン行きのボタン
    hResult = SelectButton.at(0).Initialize((TEXT("SELECT_STAGE")), D3DXVECTOR2(500.0F, 400.0F), D3DXVECTOR2(300.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//タイトル行きのボタン
    hResult = SelectButton.at(1).Initialize((TEXT("RETURN_TITLE")), D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(300.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

	//カーソル
    hResult = Cursor.Initialize(TEXT("CURSOR"), CursorPos, D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }

	FADE::SetFade(FADE_IN);

    //---BGM再生---//
    SOUNDMANAGER::Play(TEXT("BGM_GAMEOVER"));

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ゲームクリアの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Uninitialize(void)
{
    //---オブジェクトの終了処理---//
    Back.Uninitialize();
	for (int nConter = 0; nConter < GAMECLEAR_BUTTON; ++nConter)
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
//機能：ゲームクリアの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GAMECLEAR::Update(void)
{
    //---オブジェクトの更新処理---//
    Back.Update();

	if (FADE::CheckFadeEnd(FADE_IN))
	{
		ChooseButton();
		Cursor.SetPosition(CursorPos);

		//---画面遷移---//
		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
		{
            SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
            SOUNDMANAGER::Play(TEXT("SE_ENTER"));

			FADE::SetFade(FADE_OUT);
		}

	}
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		if (Select == 0)
		{
			SCENEMANAGER::SetScene(SCENE_SELECT);
		}
		else
		{
			SCENEMANAGER::SetScene(SCENE_TITLE);
		}
	}
}