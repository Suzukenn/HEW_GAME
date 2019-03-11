//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TrainingButton.h"
#include "Title.h"

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
void TITLE::ChooseStage(void)
{
	//---各種宣言---//
	D3DXVECTOR2 vecStickVector;
	static int IntervalCnt;

	vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	++IntervalCnt;
	if (IntervalCnt > 60 / 3)
	{
		IntervalCnt = 60 / 3;
		//上にスティックを入力
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
				CursorPos.y = 450.0F;
			}
		}
		//下にスティックを入力
		else if (vecStickVector.y < 0.0F)
		{
            SOUNDMANAGER::Stop(TEXT("SE_CURSOR"));
            SOUNDMANAGER::Play(TEXT("SE_CURSOR"));
			IntervalCnt = 0;
			++Select;
			CursorPos.y += 100.0F;
			if (Select > TITLE_BUTTON - 1)
			{
				Select = TITLE_BUTTON - 1;
				CursorPos.y = 550.0F;
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
void TITLE::Draw(void)
{
	int nConter;

    //---オブジェクトの描画処理---//
    AnimationBack.Draw();
    Back.Draw();
    Logo.Draw();

	switch (Mode)
	{
		case MODE_FIRST:
			if (dwTicks & dwMask)
			{
				FirstButton.Draw();
			}
			break;

		case MODE_SELECT:
			for (nConter = 0; nConter < TITLE_BUTTON; ++nConter)
			{
				SelectButton.at(nConter).Draw();
			}
			Cursor.Draw();
			break;

		case MODE_MANUAL:
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
HRESULT TITLE::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

	//---各種初期化---//
	dwTicks = 0;
	dwMask = 8;
	Select = 0;
	CursorPos = D3DXVECTOR2(350.0F, 450.0F);
	Mode = MODE_FIRST;
	LogoAlpha = 0;

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

	//最初のボタン
	hResult = FirstButton.Initialize(TEXT("PUSHBUTTON"), D3DXVECTOR2(450.0F, 500.0F), D3DXVECTOR2(400.0F, 200.0F));
	if (FAILED(hResult))
	{
		return hResult;
	}

    //スタート
    hResult = SelectButton.at(0).Initialize(TEXT("GAMESTART"), D3DXVECTOR2(450.0F, 400.0F), D3DXVECTOR2(400.0F, 200.0F));
    if (FAILED(hResult))
    {
        return hResult;
    }
	//マニュアル
	hResult = SelectButton.at(1).Initialize(TEXT("MANUAL"), D3DXVECTOR2(450.0F, 500.0F), D3DXVECTOR2(400.0F, 200.0F));
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
	int nConter;

    //---オブジェクトの終了処理---//
    AnimationBack.Uninitialize();
    Back.Uninitialize();
    Logo.Uninitialize();
	FirstButton.Uninitialize();
	for (nConter = 0; nConter < TITLE_BUTTON; ++nConter)
	{
		SelectButton.at(nConter).Uninitialize();
	}
	Cursor.Uninitialize();

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
	//---オブジェクトの更新処理---//
    AnimationBack.MoveTexture();
    Back.Update();
    Logo.Update();
	FirstButton.Update();
	Logo.SetAlpha((unsigned char)LogoAlpha);

	//フェードインが終わっていたら
	if (FADE::CheckFadeEnd(FADE_IN))
	{
		++LogoAlpha;
		if (LogoAlpha >= 255)
		{
			LogoAlpha = 255;
			++dwTicks;
		}

		switch (Mode)
		{
			case MODE_FIRST:
				if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, 0xFFFF, TRIGGER))
				{
                    SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
                    SOUNDMANAGER::Play(TEXT("SE_ENTER"));

					if (LogoAlpha == 255)
					{
						Mode = MODE_SELECT;
					}
					else
					{
						LogoAlpha = 255;
					}
				}
				break;

			case MODE_SELECT:
				ChooseStage();
				Cursor.SetPosition(CursorPos);
				if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
				{
                    SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
                    SOUNDMANAGER::Play(TEXT("SE_ENTER"));

					if (!Select)
					{
						FADE::SetFade(FADE_OUT);
					}
					else
					{
						Mode = MODE_MANUAL;
					}
				}
				else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
				{
                    SOUNDMANAGER::Stop(TEXT("SE_ENTER"));
                    SOUNDMANAGER::Play(TEXT("SE_ENTER"));

					Mode = MODE_FIRST;
				}
				break;

			case MODE_MANUAL:
                SCENEMANAGER::SetScene(SCENE_TRAINING);
                break;

			default:
				break;
		}
	}
	//フェードアウトが終わっていたら
	if (FADE::CheckFadeEnd(FADE_OUT))
	{
		SCENEMANAGER::SetScene(SCENE_SELECT);
	}
}