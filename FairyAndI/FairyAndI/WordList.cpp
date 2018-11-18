//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "InputManager.h"
#include "WordList.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ワードリストの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDLIST::Draw(void)
{
    //---各種宣言---//
    int nCounter;

    Back.Draw();
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        WordPlate.at(nCounter).Draw();
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ワードリストの初期化
//
//引数：(LPCTSTR)背景テクスチャ,(LPCTSTR*)文字リスト,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDLIST::Initialize(LPCTSTR texturename, LPCTSTR* list, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    D3DXVECTOR2 vecPanelPosition;

    //---初期化処理---//
    SelectNumber = 1;
    vecPanelPosition = D3DXVECTOR2(position.x + 20.0F, position.y + 30.0F);

    for (nCounter = 0; nCounter < WORD_VALUE; ++nCounter)
    {
        WordList.at(nCounter) = (*(list + nCounter));
    }

    //---オブジェクトの初期化---//
    //背景
    hResult = Back.Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        return hResult;
    }

    //ワードパネル
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        hResult = WordPlate.at(nCounter).Initialize(WordList.at(nCounter), D3DXVECTOR2(vecPanelPosition.x + 160.0F * nCounter, vecPanelPosition.y + 30.0F), D3DXVECTOR2(130.0F, 130.0F));
        if (FAILED(hResult))
        {
            return hResult;
        }
    }

    //ロックチェック
    for (nCounter = 0; nCounter < WORD_VALUE; ++nCounter)
    {
        UnlockCheck.at(nCounter) = false;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：ResetTexture
//
//機能：パネルの表示テクスチャの設定
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDLIST::ResetTexture(void)
{
    WordPlate.at(0).SetTexture(WordList.at((SelectNumber + WORD_VALUE - 1) % WORD_VALUE));
    WordPlate.at(1).SetTexture(WordList.at(SelectNumber % WORD_VALUE));
    WordPlate.at(2).SetTexture(WordList.at((SelectNumber + 1) % WORD_VALUE));
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ワードリストの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDLIST::Uninitialize(void)
{
    Back.Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ワードリストの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDLIST::Update(void)
{
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + WORD_VALUE + 1) % WORD_VALUE;
        ResetTexture();
    }
    else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + 1) % WORD_VALUE;
        ResetTexture();
    }

    //------//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + WORD_VALUE + 1) % WORD_VALUE;
        ResetTexture();
    }
}