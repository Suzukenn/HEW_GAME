//＝＝＝ヘッダファイル読み込み＝＝＝//
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <memory>
#include <string>
#include <tchar.h>
#include <unordered_map>
#include <vector>
#include "Main.h"
#include "ModelManager.h"

//＝＝＝グローバル変数＝＝＝//
std::unordered_map<tstring, std::shared_ptr<MODEL>> MODELMANAGER::Model;           //テクスチャ

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
HRESULT MODELMANAGER::Create(const FILEPARAMETER& data)
{
    //---各種宣言---//
    HRESULT hResult;
    DWORD nCounter;
    MODEL mModel;

    TCHAR szDirectory[_MAX_DIR];
    TCHAR szCurrentDirectory[_MAX_PATH];

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;
    LPD3DXMESH pTempMesh;

    //---初期化処理---//
    pDevice = GetDevice();

    //---データの展開---//
    //ファイルの指定確認
    if (data.FileName.data())
    {
        //フォルダ名を抽出
        _tsplitpath(data.FileName.data(), nullptr, szDirectory, nullptr, nullptr);
    }
    else
    {
        MessageBox(nullptr, TEXT("開くモデルファイルが見つかりません"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //Xファイルの読み込み
    hResult = D3DXLoadMeshFromX(data.FileName.data(), D3DXMESH_SYSTEMMEM, pDevice, nullptr, &mModel.MaterialBuffer, nullptr, &mModel.MaterialValue, &mModel.Mesh);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("モデルの作成に失敗しました"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //属性テーブル取得
    mModel.Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0);
    mModel.AttributeValue = 0;
    mModel.Mesh->GetAttributeTable(nullptr, &mModel.AttributeValue);
    mModel.Attribute.resize(mModel.AttributeValue);
    mModel.Mesh->GetAttributeTable(mModel.Attribute.at(0), &mModel.AttributeValue);

    //カレントディレクトリを変更
    if (szDirectory[0])
    {
        GetCurrentDirectory(_MAX_PATH, szCurrentDirectory);
        SetCurrentDirectory(szDirectory);
    }

    //マテリアル読み込み
    pMaterial = (LPD3DXMATERIAL)mModel.MaterialBuffer->GetBufferPointer();
    mModel.Material.resize(mModel.MaterialValue);
    mModel.Texture.resize(mModel.MaterialValue);
    for (nCounter = 0; nCounter < mModel.MaterialValue; ++nCounter)
    {
        mModel.Material.at(nCounter) = pMaterial[nCounter].MatD3D;
        mModel.Material.at(nCounter).Ambient = mModel.Material.at(nCounter).Diffuse;
        mModel.Texture.at(nCounter) = nullptr;
        if (pMaterial[nCounter].pTextureFilename && pMaterial[nCounter].pTextureFilename[0])
        {
            // テクスチャファイルを読み込む
            hResult = D3DXCreateTextureFromFile(pDevice, (LPCTSTR)pMaterial[nCounter].pTextureFilename, &mModel.Texture[nCounter]);
            if (FAILED(hResult))
            {
                mModel.Texture.at(nCounter) = nullptr;
                Uninitialize();
                return hResult;
            }
        }
    }

    //法線がなければ追加
    if (!(mModel.Mesh->GetFVF() & D3DFVF_NORMAL))
    {
        mModel.Mesh->CloneMeshFVF(mModel.Mesh->GetOptions(), mModel.Mesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pTempMesh);
        D3DXComputeNormals(pTempMesh, nullptr);
        SAFE_RELEASE(mModel.Mesh);
        mModel.Mesh = pTempMesh;
    }

    //カレントディレクトリを元に戻す
    if (szDirectory[0])
    {
        SetCurrentDirectory(szCurrentDirectory);
    }

    Model.emplace(std::make_pair(data.CallKey, std::make_shared<MODEL>(mModel)));

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
HRESULT MODELMANAGER::Initialize(LPCTSTR filename)
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
HRESULT MODELMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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
void MODELMANAGER::Uninitialize(void)
{
    //---解放---//
    //モデルの破棄
    for (auto& data : Model)
    {
        SAFE_RELEASE((data.second->Mesh));
        SAFE_RELEASE((data.second->MaterialBuffer));
        for (auto& texture : data.second->Texture)
        {
            SAFE_RELEASE((texture));
        }
    }
    Model.clear();
}

/////////////////////////////////////////////
//関数名：GetTexture
//
//機能：テクスチャの取得
//
//引数：(LPCTSTR)テクスチャ名,(MODEL*)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT MODELMANAGER::GetModel(LPCTSTR modelname, std::weak_ptr<MODEL>& address)
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