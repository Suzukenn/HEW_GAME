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
//引数：(LPCTSTR)背景テクスチャ,(std::vector<tstring>&*)文字リスト,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDLIST::Initialize(LPCTSTR texturename, std::vector<tstring>& list, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;
    D3DXVECTOR2 vecPanelPosition;

    //---初期化処理---//
    SelectNumber = 0;
    vecPanelPosition = D3DXVECTOR2(position.x + 20.0F, position.y + 30.0F);
    WordList.clear();

    for (auto& data : list)
    {
        WordList.emplace_back(data);
    }

    //---オブジェクトの初期化---//
    //背景
    hResult = Back.Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードリストの背景の作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //ワードパネル
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        hResult = WordPlate.at(nCounter).Initialize(WordList.at(nCounter).data(), D3DXVECTOR2(vecPanelPosition.x + 160.0F * nCounter, vecPanelPosition.y + 30.0F));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("ワードリスト内のワードパネルの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    //初期テクスチャの設定
    ResetTexture();

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
    //---各種宣言---//
    int nListSize;

    //---初期化処理---//
    nListSize = (int)WordList.size();

    //---テクスチャの設定---//
    WordPlate.at(0).SetTexture(WordList.at((SelectNumber + nListSize - 1) % nListSize).data());
    WordPlate.at(1).SetTexture(WordList.at(SelectNumber % nListSize).data());
    WordPlate.at(2).SetTexture(WordList.at((SelectNumber + 1) % nListSize).data());
}

/////////////////////////////////////////////
//関数名：ResetWordNumber
//
//機能：選択中の言葉の番号の変更
//
//引数：(tstring)言葉
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDLIST::ResetWordNumber(tstring word)
{
    //---各種宣言---//
    int nCounter;

    //---選択中の言葉の探索---//
    for (nCounter = 0; nCounter < WordList.size(); ++nCounter)
    {
        if (WordList.at(nCounter) == word)
        {
            SelectNumber = nCounter;
            return S_OK;
        }
    }
    return E_FAIL;
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
    //---各種宣言---//
    int nCounter;

    //---開放---//
    Back.Uninitialize();
    for (nCounter = 0; nCounter < DISPLAY_VALUE; ++nCounter)
    {
        WordPlate.at(nCounter).Uninitialize();
    }
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
    //---各種宣言---//
    int nListSize;

    //---初期化処理---//
    nListSize = (int)WordList.size();

    //---カーソル移動---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + nListSize - 1) % nListSize;
        ResetTexture();
    }
    else if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
    {
        SelectNumber = (SelectNumber + 1) % nListSize;
        ResetTexture();
    }
}