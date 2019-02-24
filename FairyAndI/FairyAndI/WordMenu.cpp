//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include <vector>
#include "Main.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "WordMenu.h"
#include "WordManager.h"

//＝＝＝グローバル宣言＝＝＝//
int WORDMENU::State;
bool WORDMENU::Control;
BACKIMAGE WORDMENU::Back;
SELECTMARKER WORDMENU::SelectMarker;

std::array<WORDPLATE, 2> WORDMENU::SelectWord;
std::array<WORDLIST, 2> WORDMENU::List;

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

    if (!Control)
    {
        return;
    }

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
    const LPCTSTR strWord[2] = { TEXT("ADJECTIVELIST"), TEXT("NOUNLIST") };
    std::vector<std::vector<tstring>> conList;

    //---初期化処理---//
    Control = false;
    State = SETTING_STATE_SELECT;

    //データのロード
    hResult = Load(conList);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードペアの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //---オブジェクトの初期化---//
    //吹き出し
    hResult = Back.Initialize(TEXT("BALLOON"), D3DXVECTOR2(350.0F, 100.0F), D3DXVECTOR2(600.0F, 250.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("吹き出しの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //選択中の言葉の初期化
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = SelectWord.at(nCounter).Initialize(TEXT("EMPTY"), vecPanelPosition[nCounter]);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("掛け合わせパネルの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    //選択部分表示マーカー
    hResult = SelectMarker.Initialize(TEXT("MARKER"), D3DXVECTOR2(390.0F, 120.0F), D3DXVECTOR2(150.0F, 150.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("選択マーカーの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //ワードリスト
    for (nCounter = 0; nCounter < 2; ++nCounter)
    {
        hResult = List.at(nCounter).Initialize(strWord[nCounter], conList.at(nCounter), vecListPosition[nCounter], D3DXVECTOR2(500.0F, 200.0F));
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
//関数名：Load
//
//機能：ペアの作成
//
//引数：(std::vector<std::vector<tstring>>&)格納リスト
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMENU::Load(std::vector<std::vector<tstring>>& list)
{
    //---各種宣言---//
    std::string szAdjective;
    std::string szNoun;
    std::wstring wszAdjective;
    std::wstring wszNoun;
    std::ifstream file;

    //---初期化処理---//
    list.resize(2);

    //---ファイルの読み込み---//
    file.open(TEXT("Data/GameScene/Word/WordPair.txt"));
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("ワードペアリストを開けませんでした"), TEXT("Data/GameScene/Word/WordPair.txt"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---データの抽出---//
    while (!file.eof())
    {
        file >> szNoun >> szAdjective;

#ifdef _UNICODE
        wszNoun = std::wstring(szNoun.begin(), szNoun.end());
        wszNoun.shrink_to_fit();
        wszAdjective = std::wstring(szAdjective.begin(), szAdjective.end());
        wszAdjective.shrink_to_fit();
        list.at(0).emplace_back(wszAdjective);
        list.at(1).emplace_back(wszNoun);
#else
        list.at(0).emplace_back(szNoun);
        list.at(1).emplace_back(szAdjective);
#endif
    }

    return S_OK;
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

    //---開放---//
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
    bool bCheck;
    static int nNextState = SETTING_STATE_ADJECTIVELIST;
    static LPCTSTR strCurrentWord;

    //---モード切替---//
    if (State == SETTING_STATE_SELECT && INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Control = !Control;
    }
    if (Control)
    {
        SelectWord.at(0).SetTexture(List.at(0).GetSelectWord());
        SelectWord.at(1).SetTexture(List.at(1).GetSelectWord());
    }
    else
    {
        return;
    }

    //---各種処理---//
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
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                strCurrentWord = List.at(nNextState).GetSelectWord();
                State = nNextState;
            }

            break;

        //形容詞設定
        case SETTING_STATE_ADJECTIVELIST:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                if (FAILED(WORDMANAGER::GetWordLock(List.at(0).GetSelectWord(), bCheck)))
                {
                    MessageBox(nullptr, TEXT("単語が見つかりませんでした"), TEXT("エラー"), MB_ICONSTOP | MB_OK);
                    Uninitialize();
                    exit(EXIT_FAILURE);
                }

                bCheck ? State = SETTING_STATE_SELECT : SOUNDMANAGER::Play(TEXT("SE_SHOT"));
            }
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
            {
                SelectWord.at(0).SetTexture(strCurrentWord);
                List.at(0).ResetWordNumber(strCurrentWord);
                State = SETTING_STATE_SELECT;
            }
            else
            {
                SelectWord.at(0).SetTexture(List.at(0).GetSelectWord());
                List.at(0).Update();
            }
            break;

        //名詞設定
        case SETTING_STATE_NOUN:
            if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
            {
                if (FAILED(WORDMANAGER::GetWordLock(List.at(1).GetSelectWord(), bCheck)))
                {
                    MessageBox(nullptr, TEXT("単語が見つかりませんでした"), TEXT("エラー"), MB_ICONSTOP | MB_OK);
                    Uninitialize();
                    exit(EXIT_FAILURE);
                }

                bCheck ? State = SETTING_STATE_SELECT : SOUNDMANAGER::Play(TEXT("SE_SHOT"));
            }
            else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
            {
                SelectWord.at(1).SetTexture(strCurrentWord);
                List.at(1).ResetWordNumber(strCurrentWord);
                State = SETTING_STATE_SELECT;
            }
            else
            {
                SelectWord.at(1).SetTexture(List.at(1).GetSelectWord());
                List.at(1).Update();
            }
            break;
    }

    //各リストの更新
    List.at(0).ResetTexture();
    List.at(1).ResetTexture();

    //背景の更新
    Back.Update();
}