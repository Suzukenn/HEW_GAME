//＝＝＝ヘッダファイル読み込み＝＝＝//
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <tchar.h>
#include <vector>
#include "AnimationModelManager.h"
#include "Main.h"

//＝＝＝グローバル変数＝＝＝//
std::unordered_map<tstring, std::shared_ptr<ANIMATIONMODEL>> ANIMATIONMODELMANAGER::Model;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Create
//
//機能：モデルの作成
//
//引数：(FILEPARAMETER)参照データ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELMANAGER::Create(const FILEPARAMETER& data)
{
    //---各種宣言---//
    HRESULT hResult;
    ANIMATIONMODEL mModel;

    //---モデルデータの読み込み---//
    hResult = mModel.Initialize(data.FileName.data(), 1.0F);
    if (SUCCEEDED(hResult))
    {
        Model.emplace(std::make_pair(data.CallKey, std::make_shared<ANIMATIONMODEL>(mModel)));
    }
    else
    {
        MessageBox(nullptr, TEXT("モデルの作成に失敗しました"), data.FileName.data(), MB_ICONSTOP | MB_OK);
    }

    return hResult;
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
HRESULT ANIMATIONMODELMANAGER::Initialize(LPCTSTR filename)
{
    //---各種宣言---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---初期化処理---//
    Model.clear();

    //---オブジェクト準備---//
    //ファイルの設定
    hResult = Load(conList, filename);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("オブジェクトリストの読み込みに失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //モデルデータの作成
    for (auto& data : conList)
    {
        if (FAILED(Create(data)))
        {
            MessageBox(nullptr, TEXT("オブジェクトデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
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
//引数：(TEXTUREPARAMETER)テクスチャリスト,(LPCTSTR)ファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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
        MessageBox(nullptr, TEXT("モデルリストを開けませんでした"), filename, MB_ICONSTOP | MB_OK);
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
    file.close();

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
void ANIMATIONMODELMANAGER::Uninitialize(void)
{
    //---解放---//
    //モデルの破棄
    for (auto& data : Model)
    {
        data.second->Uninitialize();
    }
    Model.clear();
}

/////////////////////////////////////////////
//関数名：GetTexture
//
//機能：テクスチャの取得
//
//引数：(LPCTSTR)テクスチャ名,(std::shared_ptr<ANIMATIONMODEL>)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELMANAGER::GetModel(LPCTSTR modelname, std::shared_ptr<ANIMATIONMODEL>& address)
{
    try
    {
        address = Model.at(modelname);
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("モデルが存在しません"), modelname, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}