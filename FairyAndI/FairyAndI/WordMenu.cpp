//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "WordMenu.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ワードメニューの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDMENU::Draw(void)
{
    //---各種宣言---//
    int nCounter;

    Back.Draw();
    SelectMarker.Draw();

    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        SelectWord.at(nCounter).Draw();
    }

    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        List.at(nCounter).Draw();
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ワードメニューの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMENU::Initialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    const D3DXVECTOR2 vecListPosition[2] = { D3DXVECTOR2(50.0F, 500.0F), D3DXVECTOR2(750.0F, 500.0F) };
    const D3DXVECTOR2 vecPanelPosition[2] = { D3DXVECTOR2(400.0F, 130.0F), D3DXVECTOR2(750.0F, 130.0F) };
    LPCTSTR strWord[2] = { TEXT("ADJECTIVELIST"), TEXT("NOUNLIST") };
    LPCTSTR strList[2][WORD_VALUE] = {{ TEXT("HOT"), TEXT("COLD"), TEXT("HARD"), TEXT("SOFT") }, { TEXT("FIRE"), TEXT("ICE"), TEXT("ROCK"), TEXT("EARTH") }};

    //---初期化処理---//
    State = SETTING_STATE_SELECT;

    //---オブジェクトの初期化---//
    //吹き出し
    hResult = Back.Initialize(TEXT("BALLON"), D3DXVECTOR2(350.0F, 100.0F), D3DXVECTOR2(600.0F, 250.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードリストの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //吹き出しの中
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = SelectWord.at(nCounter).Initialize(TEXT("LOCK"), vecPanelPosition[nCounter], D3DXVECTOR2(130.0F, 130.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("ワードリストの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    //選択部分表示マーカー
    hResult = SelectMarker.Initialize(TEXT("MARKER"), D3DXVECTOR2(390.0F, 120.0F), D3DXVECTOR2(150.0F, 150.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードリストの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //ワードリスト
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = List.at(nCounter).Initialize(strWord[nCounter], strList[nCounter], vecListPosition[nCounter], D3DXVECTOR2(500.0F, 200.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("ワードリストの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ワードメニューの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDMENU::Uninitialize(void)
{
    //---各種宣言---//
    int nCounter;

    Back.Uninitialize();
    SelectMarker.Uninitialize();
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        SelectWord.at(nCounter).Uninitialize();
    }

    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        List.at(nCounter).Uninitialize();
    }
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ワードメニューの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDMENU::Update(void)
{
    //---各種宣言---//
    static int nNextState = SETTING_STATE_ADJECTIVELIST;

    switch (State)
    {
        //入力選択画面
        case SETTING_STATE_SELECT:

            //設定品詞選択
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
            {
                SelectMarker.Update();
                nNextState = !nNextState;
            }

            //挙動設定
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                State = nNextState;
            }
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
            {
                return;
            }

            break;

        //形容詞設定
        case SETTING_STATE_ADJECTIVELIST:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B, TRIGGER))
            {
                State = SETTING_STATE_SELECT;
            }
            List.at(0).Update();
            SelectWord.at(0).SetTexture(List.at(0).GetSelectItem());
            break;

        //名詞設定
        case SETTING_STATE_NOUN:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B, TRIGGER))
            {
                State = SETTING_STATE_SELECT;
            }
            List.at(1).Update();
            SelectWord.at(1).SetTexture(List.at(1).GetSelectItem());
            break;
    }

    Back.Update();
}