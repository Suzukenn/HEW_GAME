//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <fstream>
#include <string>
#include <vector>
#include "Main.h"
#include "Shader.h"
#include "ShaderManager.h"

//＝＝＝グローバル変数＝＝＝//
std::unordered_map<tstring, std::shared_ptr<SHADER>> SHADERMANAGER::Shader;

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
HRESULT SHADERMANAGER::Create(const FILEPARAMETER& data)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXHANDLE hCurrentHandle;
    D3DXHANDLE hNextHandle;
    D3DXTECHNIQUE_DESC TechnicDiscriptor;
    SHADER sShader;
    std::string strName;
    LPD3DXBUFFER pErrMessage;

    //---初期化処理---//
    hCurrentHandle = nullptr;

    //---データの展開---//
    //ファイルの指定確認
    if (!data.FileName.data())
    {
        MessageBox(nullptr, TEXT("開くシェーダーファイルが見つかりません"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //テクスチャの作成
#ifdef _DEBUG
    hResult = D3DXCreateEffectFromFile(GetDevice(), data.FileName.data(), nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &sShader.Effect, &pErrMessage);
#else
    hResult = D3DXCreateEffectFromFile(GetDevice(), data.FileName.data(), nullptr, nullptr, D3DXSHADER_OPTIMIZATION_LEVEL1, nullptr, &sShader.Effect, &pErrMessage);
#endif // _DEBUG

    if (SUCCEEDED(hResult))
    {
        do
        {
            hResult = sShader.Effect->FindNextValidTechnique(hCurrentHandle, &hNextHandle);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("テクニックのハンドルの取得に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
                return hResult;
            }
            if (hNextHandle)
            {
                hResult = sShader.Effect->GetTechniqueDesc(hNextHandle, &TechnicDiscriptor);
                if (SUCCEEDED(hResult))
                {
                    strName = std::string(TechnicDiscriptor.Name);
                    sShader.Technic.emplace(std::make_pair(tstring(strName.begin(), strName.end()), hNextHandle));
                    sShader.Dectriptor.emplace(std::make_pair(tstring(strName.begin(), strName.end()), TechnicDiscriptor));
                }
                else
                {
                    MessageBox(nullptr, TEXT("テクニックのデータの取得に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
                    return hResult;
                }
            }

        } while (!hNextHandle);
        Shader.emplace(std::make_pair(data.CallKey, std::make_shared<SHADER>(sShader)));
    }
    else
    {
        MessageBox(nullptr, TEXT("シェーダーの作成に失敗しました"), data.FileName.data(), MB_ICONSTOP | MB_OK);
        return hResult;
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
HRESULT SHADERMANAGER::Initialize(LPCTSTR filename)
{
    //---各種宣言---//
    HRESULT hResult;

    std::vector<FILEPARAMETER> conList;

    //---初期化処理---//
    Shader.clear();

    //---オブジェクト準備---//
    //ファイルの設定
    hResult = Load(conList, filename);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("シェーダーリストの読み込みに失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
        Uninitialize();
        return hResult;
    }

    //テクスチャデータの作成
    for (auto& data : conList)
    {
        if (FAILED(Create(data)))
        {
            MessageBox(nullptr, TEXT("シェーダーデータの作成に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
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
HRESULT SHADERMANAGER::Load(std::vector<FILEPARAMETER>& list, LPCTSTR filename)
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
        MessageBox(nullptr, TEXT("シェーダーリストを開けませんでした"), filename, MB_ICONSTOP | MB_OK);
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
void SHADERMANAGER::Uninitialize(void)
{
    //---開放---//
    //テクスチャの破棄
    for (auto& data : Shader)
    {
        SAFE_RELEASE(data.second->Effect);
    }
    Shader.clear();
}

/////////////////////////////////////////////
//関数名：GetTexture
//
//機能：テクスチャの取得
//
//引数：(LPCTSTR)シェーダー名,(LPDIRECT3DTEXTURE9)格納アドレス
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT SHADERMANAGER::GetShader(LPCTSTR shadername, std::weak_ptr<SHADER>& address)
{
    try
    {
        address = Shader.at(shadername);
    }
    catch (const std::out_of_range&)
    {
        MessageBox(nullptr, TEXT("シェーダーが存在しません"), shadername, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }
    return S_OK;
}