//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include "TextureManager.h"
#include "WordManager.h"

//＝＝＝グローバル宣言＝＝＝//
std::unordered_map<tstring, bool> WORDMANAGER::NounLock;
std::unordered_map<tstring, bool> WORDMANAGER::AdjectiveLock;
std::unordered_map<tstring, bool> WORDMANAGER::SkillLock;
std::unordered_map<tstring, tstring> WORDMANAGER::NounToAdjective;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CreateWord
//
//機能：言葉の作成
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::CreateWord(void)
{
    //---各種宣言---//
    std::string szAdjective;
    std::string szNoun;
    std::wstring wszAdjective;
    std::wstring wszNoun;
    std::ifstream file;

    //---初期化処理---//
    NounToAdjective.clear();

    //---ファイルの読み込み---//
    file.open("Data/GameScene/Word/WordPair.txt");
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("ワードペアリストを開けませんでした"), TEXT("Data/GameScene/Word/WordPair.txt"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---データの抽出---//
    while (!file.eof())
    {
        //データの読み取り
        file >> szNoun >> szAdjective;

        //データの作成
#ifdef _UNICODE
        wszNoun = std::wstring(szNoun.begin(), szNoun.end());
        wszNoun.shrink_to_fit();
        wszAdjective = std::wstring(szAdjective.begin(), szAdjective.end());
        wszAdjective.shrink_to_fit();

        NounToAdjective.emplace(std::make_pair(wszNoun, wszAdjective));
        NounLock.insert(std::make_pair(wszNoun, false));
        AdjectiveLock.insert(std::make_pair(wszAdjective, false));

#else
        NounToAdjective.emplace(std::make_pair(szNoun, szAdjective));
        NounLock.insert(std::make_pair(szNoun, false));
        AdjectiveLock.insert(std::make_pair(szAdjective, false));
#endif

    }

    file.close();

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
    //ワードの準備
    hResult = CreateWord();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ワードペアの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //合成アイテムテクスチャリストの作成
    for (auto& Noun : NounLock)
    {
        for (auto& Adjective : AdjectiveLock)
        {
            SkillLock.insert(std::make_pair(Adjective.first + Noun.first, false));
        }
    }

    return hResult;
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
    //名詞ロックの破棄
    NounLock.clear();

    //形容詞ロックの破棄
    AdjectiveLock.clear();

    //スキルロックの破棄
    SkillLock.clear();

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
    //---各種宣言---//
    std::vector<tstring> conList;

    //---ロック解除---//
    if (NounToAdjective.find(word) != NounToAdjective.end())
    {
        //名詞と形容詞の解除
        NounLock.at(word) = true;
        AdjectiveLock.at(NounToAdjective.at(word)) = true;

        //合成アイテムの解除
        for (auto& noun : NounLock)
        {
            if (!noun.second || noun.first == TEXT("EMPTY"))
            {
                continue;
            }
            for (auto& adjective : AdjectiveLock)
            {
                if (SkillLock.find(adjective.first + noun.first) == SkillLock.end())
                {
                    continue;
                }
                SkillLock.at(adjective.first + noun.first) = adjective.second ? true : false;
            }
        }
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
//関数名：GetWordLock
//
//機能：言葉のロック状態の取得
//
//引数：(tstring)言葉,(LPDIRECT3DTEXTURE9)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::GetWordLock(LPCTSTR word, bool& lock)
{
    try
    {
        lock = NounLock.at(word);
    }
    catch (const std::out_of_range&)
    {
        try
        {
            lock = AdjectiveLock.at(word);
        }
        catch (const std::out_of_range&)
        {
            MessageBox(nullptr, TEXT("単語が存在しません"), TEXT("取得エラー"), MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    return S_OK;
}

/////////////////////////////////////////////
//関数名：GetWordTexture
//
//機能：テクスチャの取得
//
//引数：(tstring)言葉,(std::weak_ptr<TEXTURE>)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT WORDMANAGER::GetWordTexture(LPCTSTR word, std::weak_ptr<TEXTURE>& address)
{
    try
    {
        if (FAILED(TEXTUREMANAGER::GetTexture(NounLock.at(word) ? word : TEXT("EMPTY"), address)))
        {
            MessageBox(nullptr, TEXT("名詞テクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
            return E_FAIL;
        }
    }
    catch (const std::out_of_range&)
    {
        try
        {
            if (FAILED(TEXTUREMANAGER::GetTexture(AdjectiveLock.at(word) ? word : TEXT("EMPTY"), address)))
            {
                MessageBox(nullptr, TEXT("形容詞テクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
                return E_FAIL;
            }
        }
        catch (const std::out_of_range&)
        {
            try
            {
                if (FAILED(TEXTUREMANAGER::GetTexture(SkillLock.at(word) ? word : TEXT("EMPTY"), address)))
                {
                    MessageBox(nullptr, TEXT("スキルテクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
                    return E_FAIL;
                }
            }
            catch (const std::out_of_range&)
            {
                try
                {
                    if (FAILED(TEXTUREMANAGER::GetTexture(TEXT("EMPTY"), address)))
                    {
                        MessageBox(nullptr, TEXT("エンプティテクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
                        return E_FAIL;
                    }
                }
                catch (const std::out_of_range&)
                {
                    MessageBox(nullptr, TEXT("表示可能な言葉のテクスチャが存在しません"), word, MB_ICONSTOP | MB_OK);
                    return E_FAIL;
                }
            }
        }
    }
    return S_OK;
}