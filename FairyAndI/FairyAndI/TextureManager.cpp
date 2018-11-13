//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Main.h"
#include "TextureManager.h"

//＝＝＝グローバル変数＝＝＝//
std::unordered_map<tstring, LPDIRECT3DTEXTURE9> TEXTUREMANAGER::Texture;           //テクスチャ

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Create
//
//機能：ソースボイスの作成
//
//引数：(TEXTUREPARAMETER)元データ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Create(TEXTUREPARAMETER data)
{
    //---各種宣言---//
    std::unique_ptr<LPDIRECT3DTEXTURE9> pTexture;

    //---初期化処理---//
    pTexture.reset(new LPDIRECT3DTEXTURE9);

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
        Texture.insert(std::make_pair(data.CallKey, *pTexture));
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

    std::vector<TEXTUREPARAMETER> conList;

    //---初期化処理---//

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
            MessageBox(nullptr, TEXT("サウンドデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
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
//引数：(TEXTUREPARAMETER)楽曲リスト,(LPCTSTR)ファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TEXTUREMANAGER::Load(std::vector<TEXTUREPARAMETER>& list, LPCTSTR filename)
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
    if (file.fail())
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
        list.at(nCounter).FileName = szFileName.c_str();;
        list.at(nCounter).CallKey = szKeyName.c_str();
#endif

        ++nCounter;
    }

    list.resize(nCounter);

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
    //---解放---//
    //テクスチャの破棄
    for (auto& data : Texture)
    {
        SAFE_RELEASE(data.second);
    }
}

/////////////////////////////////////////////
//関数名：GetTexture
//
//機能：テクスチャの取得
//
//引数：(LPCTSTR)テクスチャ名
//
//戻り値：(LPDIRECT3DTEXTURE9)テクスチャへのアドレス
/////////////////////////////////////////////
LPDIRECT3DTEXTURE9 TEXTUREMANAGER::GetTexture(LPCTSTR texturename)
{
    return Texture.at(texturename);
}