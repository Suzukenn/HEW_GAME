//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include "WordManager.h"

//＝＝＝グローバル宣言＝＝＝//
std::unordered_map<tstring, LPDIRECT3DTEXTURE9> WORDMANAGER::NounTexture;
std::unordered_map<tstring, LPDIRECT3DTEXTURE9> WORDMANAGER::AdjectiveTexture;
std::unordered_map<tstring, bool> WORDMANAGER::NounLock;
std::unordered_map<tstring, bool> WORDMANAGER::AdjectiveLock;
std::unordered_map<tstring, tstring> WORDMANAGER::NounToAdjective;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CreatePair
//
//機能：ペアの作成
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::CreatePair(void)
{
    //---各種宣言---//
    std::string szAdjective;
    std::string szNoun;
    std::wstring wszAdjective;
    std::wstring wszNoun;
    std::ifstream file(TEXT("Data/Common/Word/WordPair.txt"));

    //---初期化処理---//
    NounToAdjective.clear();

    //---ファイルの読み込み---//
    if (!file.is_open())
    {
        MessageBox(nullptr, TEXT("ワードペアリストを開けませんでした"), TEXT("Data/Common/Word/WordPair.txt"), MB_ICONSTOP | MB_OK);
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
#endif
        NounToAdjective.insert(std::make_pair(wszNoun, wszAdjective));
    }

    return S_OK;
}

/////////////////////////////////////////////
//関数名：CreateTexture
//
//機能：テクスチャの作成
//
//引数：(std::unordered_map<tstring, LPDIRECT3DTEXTURE9>)格納リスト,(FILEPARAMETER)参照データ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::CreateTexture(std::unordered_map<tstring, LPDIRECT3DTEXTURE9>& list, const FILEPARAMETER& data)
{
    //---各種宣言---//
    std::unique_ptr<LPDIRECT3DTEXTURE9> pTexture;

    //---初期化処理---//
    pTexture.reset(new LPDIRECT3DTEXTURE9());

    //---データの展開---//
    //ファイルの指定確認
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("開くテクスチャファイルが見つかりません"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //テクスチャの作成
    if (SUCCEEDED(D3DXCreateTextureFromFile(GetDevice(), data.FileName.data(), pTexture.get())))
    {
        list.insert(std::make_pair(data.CallKey, *pTexture));
    }
    else
    {
        MessageBox(nullptr, TEXT("テクスチャの作成に失敗しました"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ワードマネージャの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---オブジェクト準備---//
    //名詞テクスチャリストの読み込み
    hResult = LoadTexture(conList, TEXT("Data/Common/Word/NounList.txt"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("名詞テクスチャの読み込みに失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //名詞テクスチャの作成
    for (auto& data : conList)
    {
        if (FAILED(CreateTexture(NounTexture, data)))
        {
            MessageBox(nullptr, TEXT("名詞テクスチャデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
        NounLock.insert(std::make_pair(data.CallKey, true));
    }

    //形容詞テクスチャリストの読み込み
    hResult = LoadTexture(conList, TEXT("Data/Common/Word/AdjectiveList.txt"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("形容詞テクスチャの読み込みに失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //形容詞テクスチャの作成
    for (auto& data : conList)
    {
        if (FAILED(CreateTexture(AdjectiveTexture, data)))
        {
            MessageBox(nullptr, TEXT("形容詞テクスチャデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
        AdjectiveLock.insert(std::make_pair(data.CallKey, true));
    }

    //ワードペアの作成
    hResult = CreatePair();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードペアの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }
    return hResult;
}

/////////////////////////////////////////////
//関数名：LoadTexture
//
//機能：ワードテクスチャの読み込み
//
//引数：(FILEPARAMETER)テクスチャリスト,(LPCTSTR)リストファイル
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::LoadTexture(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
{
    //---各種宣言---//
    int nCounter;
    std::string szFileName;
    std::string szKeyName;
    std::ifstream file(filename);

    //---初期化処理---//
    nCounter = 0;
    list.resize(999);

    //---ファイルの読み込み---//
    if (!file.is_open())
    {
        MessageBox(nullptr, TEXT("テクスチャリストを開けませんでした"), filename, MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---データの抽出---//
    while (!file.eof())
    {
        file >> szFileName >> szKeyName;

#ifdef _UNICODE
        list.at(nCounter).FileName.resize(szFileName.size());
        list.at(nCounter).FileName = std::wstring(szFileName.begin(), szFileName.end());
        list.at(nCounter).CallKey.resize(szKeyName.size());
        list.at(nCounter).CallKey = std::wstring(szKeyName.begin(), szKeyName.end());
#else
        list.at(nCounter).FileName = szFileName;
        list.at(nCounter).CallKey = szKeyName;
#endif

        ++nCounter;
    }

    list.resize(nCounter);
    list.shrink_to_fit();

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ワードマネージャの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDMANAGER::Uninitialize(void)
{
    //---開放---//
    //名詞テクスチャの破棄
    for (auto& data : NounTexture)
    {
        SAFE_RELEASE(data.second);
    }
    NounTexture.clear();

    //形容詞テクスチャの破棄
    for (auto& data : AdjectiveTexture)
    {
        SAFE_RELEASE(data.second);
    }
    AdjectiveTexture.clear();

    //名詞ロックの破棄
    NounLock.clear();

    //形容詞ロックの破棄
    AdjectiveLock.clear();

    //ペア辞書の破棄
    NounToAdjective.clear();
}

/////////////////////////////////////////////
//関数名：UnLockWord
//
//機能：ワードロックの解除
//
//引数：(LPCTSTR)言葉
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::UnLockWord(LPCTSTR word)
{
    if (NounToAdjective.find(word) != NounToAdjective.end())
    {
        NounLock.at(word) = true;
        AdjectiveLock.at(NounToAdjective.at(word)) = true;
    }
    else
    {
        MessageBox(nullptr, TEXT("単語が存在しません"), word, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ワードマネージャの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void WORDMANAGER::Update(void)
{

}

/////////////////////////////////////////////
//関数名：GetWordTexture
//
//機能：名詞テクスチャの取得
//
//引数：(LPCTSTR)言葉,(LPDIRECT3DTEXTURE9)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::GetWordTexture(LPCTSTR word, LPDIRECT3DTEXTURE9& address)
{
    try
    {
        address = NounLock.at(word) ? NounTexture.at(word) : NounTexture.at(TEXT("LOCK"));
        if (!address)
        {
            MessageBox(nullptr, TEXT("テクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    catch (const std::out_of_range&)
    {
        try
        {
            address = AdjectiveLock.at(word) ? AdjectiveTexture.at(word) : AdjectiveTexture.at(TEXT("LOCK"));
            if (!address)
            {
                MessageBox(nullptr, TEXT("テクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
                return E_FAIL;
            }
        }
        catch (const std::exception&)
        {
            MessageBox(nullptr, TEXT("テクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    return S_OK;
}