//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include <string>
#include <vector>
#include "Main.h"
#include "Texture.h"
#include "TextureManager.h"

//＝＝＝グローバル変数＝＝＝//
std::unordered_map<tstring, std::shared_ptr<TEXTURE>> TEXTUREMANAGER::Texture;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Create
//
//機能：テクスチャの作成
//
//引数：(FILEPARAMETER)参照データ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Create(const FILEPARAMETER& data)
{
    //---各種宣言---//
    TEXTURE tTexture;

    //---データの展開---//
    //ファイルの指定確認
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("開くテクスチャファイルが見つかりません"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //テクスチャの作成
    if (SUCCEEDED(D3DXCreateTextureFromFile(GetDevice(), data.FileName.data(), &tTexture.Image)))
    {
        tTexture.Image->GetLevelDesc(0, &tTexture.Descriptor);
        Texture.emplace(std::make_pair(data.CallKey, std::make_shared<TEXTURE>(tTexture)));
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
//機能：マネージャーの初期化
//
//引数：(LPCTSTR)ファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Initialize(LPCTSTR filename)
{
    //---各種宣言---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---初期化処理---//
    Texture.clear();

    //---オブジェクト準備---//
    //ファイルの設定
    hResult = Load(conList, filename);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("テクスチャリストの読み込みに失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //テクスチャデータの作成
    for (auto& data : conList)
    {
        if (FAILED(Create(data)))
        {
            MessageBox(nullptr, TEXT("テクスチャデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            Uninitialize();
            return hResult;
        }
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Load
//
//機能：読み込みデータの格納
//
//引数：(std::vector<FILEPARAMETER>&)テクスチャリスト,(LPCTSTR)ファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
{
    //---各種宣言---//
    int nCounter;
    std::string strFileName;
    std::string strKeyName;
    std::ifstream file;

    //---初期化処理---//
    nCounter = 0;
    list.resize(999);

    //---ファイルの読み込み---//
    file.open(filename);
    if (file.fail())
    {
        MessageBox(nullptr, TEXT("テクスチャリストを開けませんでした"), filename, MB_ICONSTOP | MB_OK);
        Uninitialize();
        return E_FAIL;
    }

    //---データの抽出---//
    while (!file.eof())
    {
        //データ読み取り
        file >> strFileName >> strKeyName;

        //格納
        list.at(nCounter).FileName = tstring(strFileName.begin(), strFileName.end());
        list.at(nCounter).CallKey = tstring(strKeyName.begin(), strKeyName.end());

        ++nCounter;
    }

    list.resize(nCounter);
    list.shrink_to_fit();

    return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：マネージャーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TEXTUREMANAGER::Uninitialize(void)
{
    //---開放---//
    //テクスチャの破棄
    for (auto& data : Texture)
    {
        SAFE_RELEASE(data.second->Image);
    }
    Texture.clear();
}

/////////////////////////////////////////////
//関数名：GetTexture
//
//機能：テクスチャの取得
//
//引数：(LPCTSTR)テクスチャ名,(LPDIRECT3DTEXTURE9)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::GetTexture(LPCTSTR texturename, std::weak_ptr<TEXTURE>& address)
{
    try
    {
        address = Texture.at(texturename);
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("テクスチャが存在しません"), texturename, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}