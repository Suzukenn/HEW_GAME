//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
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
void SELECTSCENE::ChooseStage(void)
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
		if (vecStickVector.x > 0.0F)
		{
			IntervalCnt = 0;
			++Select;
			if (Select > MAX_SELECTBUTTON - 1)
			{
				Select = MAX_SELECTBUTTON - 1;
			}
		}
		//左にスティックを入力
		else if (vecStickVector.x < 0.0F)
		{
			IntervalCnt = 0;
			--Select;
			if (Select < 0)
			{
				Select = 0;
			}
		}
	}
}

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

	for (int nConter = 0; nConter < 3; ++nConter)
	{
		if (Select == nConter)
		{
			if (dwTicks & dwMask)
			{
				Button.at(nConter).Draw();
			}
			continue;
		}
		Button.at(nConter).Draw();
	}
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
	D3DXVECTOR2 ButtonPos;

	ButtonPos = D3DXVECTOR2(200.0F, 500.0F);
	dwTicks = 0;
	dwMask = 8;
	Select = 0;

	//各ボタンの行き先
	Button.at(0).SetSelectStage(SCENE_TRAINING);
	Button.at(1).SetSelectStage(SCENE_TITLE);
	Button.at(2).SetSelectStage(SCENE_GAMECLEAR);

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

	for (int nConter = 0; nConter < 3; ++nConter)
	{
		hResult = Button.at(nConter).Initialize(TEXT("BACKGROUND"), ButtonPos, D3DXVECTOR2(200.0F, 50.0F));
		if (FAILED(hResult))
		{
			return E_FAIL;
		}

		ButtonPos.x += 300.0F;
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

	for (int nConter = 0; nConter < 3; ++nConter)
	{
		Button.at(nConter).Uninitialize();
	}

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
	++dwTicks;

	//---オブジェクトの更新---//
	Back.Update();
	for (int nConter = 0; nConter < 3; ++nConter)
	{
		if (Select == nConter)
		{
			Button.at(nConter).Update();
		}
	}

	if (FADE::CheckFadeEnd(FADE_IN))
	{
		ChooseStage();

		if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
		{
			SCENEMANAGER::SetScene(SCENE_TITLE);
		}
	}
}
