//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "SoundManager.h"
#include "TextureManager.h"

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
void SELECTSCENE::Draw(void)
{
    Back.Draw();

	switch (Select)
	{
		case SELECT_STAGE1:
			if (dwTicks & dwMask)
			{
				Button1.Draw();
			}
			Button2.Draw();
			Button3.Draw();
			break;
		case SELECT_STAGE2:
			if (dwTicks & dwMask)
			{
				Button2.Draw();
			}
			Button1.Draw();
			Button3.Draw();
			break;
		case SELECT_STAGE3:
			if (dwTicks & dwMask)
			{
				Button3.Draw();
			}
			Button1.Draw();
			Button2.Draw();
			break;

		default:
			break;
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

	dwTicks = 0;
	dwMask = 8;
	Select = SELECT_STAGE1;

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

	hResult = Button1.Initialize(TEXT("BACKGROUND"),D3DXVECTOR2(200.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
	if (FAILED(hResult))
	{
		return E_FAIL;
	}

	hResult = Button2.Initialize(TEXT("BACKGROUND"),D3DXVECTOR2(500.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
	if (FAILED(hResult))
	{
		return E_FAIL;
	}

	hResult = Button3.Initialize(TEXT("BACKGROUND"), D3DXVECTOR2(800.0F, 500.0F), D3DXVECTOR2(200.0F, 50.0F));
	if (FAILED(hResult))
	{
		return E_FAIL;
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

	Button1.Uninitialize();
	Button2.Uninitialize();
	Button3.Uninitialize();

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
	//---各種宣言---//
	D3DXVECTOR2 vecStickVector;
	static int IntervalCnt;

	vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);
	dwTicks++;

    //---オブジェクトの更新---//
    Back.Update();
	Button1.Update();
	Button2.Update();
	Button3.Update();

	IntervalCnt++;
	if (IntervalCnt > 60 / 3)
	{
		//右にスティックを入力
		if (vecStickVector.x > 0.0F)
		{
			IntervalCnt = 0;
			Select++;
			if (Select > SELECT_MAX - 1)
			{
				Select = SELECT_MAX - 1;
			}
		}
		//左スティックを入力
		else if (vecStickVector.x < 0.0F)
		{
			IntervalCnt = 0;
			Select--;
			if (Select < 0)
			{
				Select = 0;
			}
		}
	}

	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
		dwMask = 2;
		FADE::SetFade(FADE_OUT);
	}
	else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
	{
		SCENEMANAGER::SetScene(SCENE_TITLE);
	}

	//フェードアウトが終わっていたら
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		switch (Select)
		{
			case SELECT_STAGE1:
				SCENEMANAGER::SetScene(SCENE_GAME);
				break;
			case SELECT_STAGE2:
				SCENEMANAGER::SetScene(SCENE_TITLE);
				break;
			case SELECT_STAGE3:
				SCENEMANAGER::SetScene(SCENE_GAMECLEAR);
				break;
			default:
				break;
		}
	}
}