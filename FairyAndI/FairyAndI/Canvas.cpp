//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Canvas.h"
#include "InputManager.h"
#include "Player.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：キャンバスの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CANVAS::Draw(void)
{
    //---各種宣言---//
    int nCounter;

    //---描画---//
    for (nCounter = 0; nCounter < PLAYER::GetPlayerHP(); ++nCounter)
    {
        Heart.at(nCounter).Draw();
    }

	Timer.Draw();

    SkillBox.Draw();
    Skill.Draw();
    Menu.Draw();
    TimeGauge.Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：キャンバスの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT CANVAS::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //---初期化処理---//
    hResult = WORDMENU::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    //スキルボックス
    hResult = SkillBox.Initialize(TEXT("SKILLBOX"), D3DXVECTOR2(1050.0F, 10.0F), D3DXVECTOR2(150.0F, 150.0F), { 2, 1 });
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アイテムボックスの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //スキル
    hResult = Skill.Initialize(TEXT("EMPTY"), D3DXVECTOR2(1076.0F, 35.0F), D3DXVECTOR2(100.0F, 100.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アイテムの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //ハート
    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        hResult = Heart.at(nCounter).Initialize(TEXT("HEART"), D3DXVECTOR2(10.0F + 60.0F * nCounter, 10.0F), D3DXVECTOR2(90.0F, 70.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("ハートの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
            return hResult;
        }
    }

    //タイムゲージ
    hResult = TimeGauge.Initialize(TEXT("GAUGEBACK"), TEXT("GAUGEMEMORY"), D3DXVECTOR2(720.0F, -10.0F), D3DXVECTOR2(300.0F, 120.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("タイムゲージの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //タイマー
	hResult = Timer.Initialize(TEXT("TIMER"), D3DXVECTOR2(580.0F, 30.0F), D3DXVECTOR2(30.0F, 60.0F), 10);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("アイテムの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
		Uninitialize();
		return hResult;
	}

    Mode = false;

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：キャンバスの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CANVAS::Uninitialize(void)
{
    //---各種宣言---//
    int nCounter;

    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        Heart.at(nCounter).Uninitialize();
    }

	Timer.Uninitialize();

    SkillBox.Uninitialize();
    Skill.Uninitialize();
    Menu.Uninitialize();
    TimeGauge.Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：キャンバスの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CANVAS::Update(void)
{
    //---各種宣言---//
    int nCounter;

    //---表示モード切り替え---//
  /*  if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Mode = !Mode;
    }*/
	Mode = SQUAREGAUGE::GetFairyTime();

    for (nCounter = 0; nCounter < MAX_PLAYER_HP; ++nCounter)
    {
        Heart.at(nCounter).Update();
    }

	Timer.Update();

    Menu.Update();
    SkillBox.Update();
    if (Mode)Skill.SetTexture(tstring(WORDMENU::NotificationAdjective() + WORDMENU::NotificationNoun()).data());
    TimeGauge.Update();
}