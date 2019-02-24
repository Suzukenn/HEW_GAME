//＝＝＝ヘッダファイル読み込み＝＝＝//
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "AnimationModelContainer.h"
#include "AnimationModelFrame.h"
#include "AnimationModelHierarchy.h"
#include "Main.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CreateFrame
//
//機能：フレームの作成
//
//引数：(LPCTSTR)フレーム名,(LPD3DXFRAME)新フレーム名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
    //---各種宣言---//
    ANIMATIONMODELFREAM* pFrame;

    //---初期化処理---//
    *ppNewFrame = nullptr;            //新しいフレームアドレス格納用変数を初期化
    pFrame = new ANIMATIONMODELFREAM; //フレームの領域確保
    memset(pFrame, 0, sizeof(ANIMATIONMODELFREAM));

    //---フレーム名格納---//
    if (Name)
    {
        //フレーム名格納
        pFrame->Name = new char[lstrlenA(Name) + 1];
        lstrcpyA(pFrame->Name, Name);
    }
    else
    {
        pFrame->Name = nullptr;
    }

    //行列の初期化
    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
    
    //外部の新規フレームアドレス格納用変数に、作成したフレームのアドレスを格納
    *ppNewFrame = pFrame;

    return S_OK;
}

/////////////////////////////////////////////
//関数名：CreateMeshContainer
//
//機能：メッシュコンテナーの作成
//
//引数：(LPCSTR)メッシュ名,(D3DXMESHDATA*)メッシュデータ,(D3DXMATERIAL*)マテリアル,(D3DXEFFECTINSTANCE*)エフェクト,(DWORD)マテリアル量,(DWORD*)隣接要素,(LPD3DXSKININFO)スキン情報,(LPD3DXMESHCONTAINER*)格納コンテナ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::CreateMeshContainer(THIS_ LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials, CONST DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppMeshContainer)
{
    //---各種宣言---//
    HRESULT hResult;
    DWORD dwFacesAmount;
    DWORD dwCounter;
    DWORD dwMaterial;
    DWORD dwBoneValue;
    std::string strTexturePath;
    std::wstring strTexturePathW;

    TCHAR szCurrentDirectory[_MAX_PATH];
    char szTexturePath[_MAX_DIR];

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMESH pMesh;                           //一時的なメッシュデータ格納用
    ANIMATIONMODELCONTAINER* pMeshContainer;    //一時格納メッシュコンテナ

    //---初期化処理---//
    pMesh = pMeshData->pMesh;      //pMeshに外部引数のメッシュアドレスを格納
    *ppMeshContainer = nullptr;    //メッシュコンテナ格納用変数初期化
    pDevice = GetDevice();
    pMeshContainer = new ANIMATIONMODELCONTAINER;    //メッシュコンテナ領域の動的確保

    //正常なメッシュ以外はエラーで戻す
    if (pMeshData->Type != D3DXMESHTYPE_MESH || !pMeshData->pMesh->GetFVF())
    {
        return E_FAIL;
    }

    //メッシュコンテナを初期化
    memset(pMeshContainer, 0, sizeof(ANIMATIONMODELCONTAINER));

    //---メッシュ名のコピー---//
    if (Name)
    {
        //メッシュコンテナの名前格納
        pMeshContainer->Name = new char[lstrlenA(Name) + 1];
        lstrcpyA(pMeshContainer->Name, Name);
    }
    else
    {
        pMeshContainer->Name = nullptr;
    }

    //---モデルデータの格納---//
    pMesh->GetDevice(&pDevice);                                //DirectXデバイス取得
    dwFacesAmount = pMesh->GetNumFaces();                      //メッシュの面の数を取得

    if (pMesh->GetFVF() & D3DFVF_NORMAL)
    {
        pMeshContainer->MeshData.pMesh = pMesh;
        pMesh->AddRef();
    }
    else
    {
        // 法線を持たない場合は追加
        hResult = pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pMeshContainer->MeshData.pMesh);
        if (FAILED(hResult)) 
        {
            MessageBox(nullptr, TEXT("メッシュの頂点情報形式の複製に失敗しました"), TEXT("初期化エラー"), MB_OK);
            DestroyMeshContainer(pMeshContainer);
            return hResult;
        }
        pMesh = pMeshContainer->MeshData.pMesh;
        hResult = D3DXComputeNormals(pMesh, nullptr);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("メッシュの法線の計算に失敗しました"), TEXT("初期化エラー"), MB_OK);
            DestroyMeshContainer(pMeshContainer);
            return hResult;
        }
    }

    //---メッシュのマテリアル設定----//
    pMeshContainer->NumMaterials = max(1, NumMaterials);                                //メッシュのマテリアル数を格納(最大で1つ)
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];        //メッシュコンテナの、マテリアルデータ格納領域を動的確保
    pMeshContainer->Texture.resize(pMeshContainer->NumMaterials);                       //メッシュコンテナの、テクスチャデータ格納領域を動的確保
    pMeshContainer->pAdjacency = new DWORD[dwFacesAmount * 3];                          //メッシュコンテナの、面ごとに持つ3つの隣接性情報が格納されたDWORD型のアドレス格納用(ポインタ)変数
    if (!pMeshContainer->pAdjacency || pMeshContainer->Texture.empty() || !pMeshContainer->pMaterials)
    {
        MessageBox(nullptr, TEXT("メッシュのマテリアル情報が足りません"), TEXT("初期化エラー"), MB_OK);
        DestroyMeshContainer(pMeshContainer);
        return E_OUTOFMEMORY;
    }

    //外部引数の隣接性情報をメッシュコンテナに格納
    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwFacesAmount * 3);

    //---マテリアルの格納---//
    //マテリアルあり
    if (NumMaterials)
    {
        if (lstrlenA((LPCSTR)FileDirectory.begin()._Ptr))
        {
            GetCurrentDirectory(_MAX_PATH, szCurrentDirectory);
            SetCurrentDirectory(FileDirectory.begin()._Ptr);
        }

        //外部引数のマテリアルデータアドレスをメッシュコンテナに格納
        memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

        //マテリアル数分ループさせる
        for (dwMaterial = 0; dwMaterial < NumMaterials; ++dwMaterial)
        {
            pMeshContainer->pMaterials[dwMaterial].MatD3D.Ambient = pMeshContainer->pMaterials[dwMaterial].MatD3D.Diffuse;

            //テクスチャデータがあれば
            if (pMeshContainer->pMaterials[dwMaterial].pTextureFilename)
            {
                //テクスチャのファイルパスを保存(再読み込み時に必要)
                _splitpath(pMeshContainer->pMaterials[dwMaterial].pTextureFilename, nullptr, szTexturePath, nullptr, nullptr);
                strTexturePath = pMeshContainer->pMaterials[dwMaterial].pTextureFilename;
                strTexturePathW = std::wstring(strTexturePath.begin(), strTexturePath.end());

                //テクスチャ情報の読み込み
                hResult = D3DXCreateTextureFromFile(pDevice, strTexturePathW.data(), &pMeshContainer->Texture.at(dwMaterial));
                if (FAILED(hResult))
                {
                    MessageBox(nullptr, TEXT("メッシュのテクスチャの読み込みに失敗しました"), TEXT("初期化エラー"), MB_OK);
                    pMeshContainer->Texture.at(dwMaterial) = nullptr;
                    return hResult;
                }
            }
        }

        //カレントディレクトリを元に戻す
        if (lstrlenA((LPCSTR)FileDirectory.begin()._Ptr))
        {
            SetCurrentDirectory(szCurrentDirectory);
        }
    }
    else
    {
        //マテリアルなし
        memset(&pMeshContainer->pMaterials, 0, sizeof(D3DXMATERIAL));   //マテリアルデータ初期化
        pMeshContainer->pMaterials->pTextureFilename = nullptr;         //テクスチャファイル名をnullptrに

        //マテリアルカラーを0.5に設定
        pMeshContainer->pMaterials->MatD3D.Diffuse.r = 0.5F;
        pMeshContainer->pMaterials->MatD3D.Diffuse.g = 0.5F;
        pMeshContainer->pMaterials->MatD3D.Diffuse.b = 0.5F;

        //環境光を拡散光と同値に設定(上で設定したマテリアルカラーの0.5の設定をコピー)
        pMeshContainer->pMaterials->MatD3D.Ambient = pMeshContainer->pMaterials->MatD3D.Diffuse;
    }

    //---属性テーブルの取得---//
    hResult = pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshContainer->MeshData.pMesh->GetFVF(), pDevice, &pMesh);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("メッシュの頂点情報形式の読み込みに失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
    pMeshContainer->MeshData.pMesh = pMesh;

    hResult = pMesh->GetAttributeTable(nullptr, &pMeshContainer->AttributeGroupValue);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("メッシュの属性テーブルのエントリ数の読み込みに失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }
    pMeshContainer->AttributeTable.resize(pMeshContainer->AttributeGroupValue);
    hResult = pMesh->GetAttributeTable(pMeshContainer->AttributeTable.begin()._Ptr, &pMeshContainer->AttributeGroupValue);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("メッシュの属性テーブルの読み込みに失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---スキン情報の取得---//
    if (pSkinInfo)
    {
        pMeshContainer->pSkinInfo = pSkinInfo;                  //メッシュ情報を格納(今回は通常メッシュと完全に分けているためすべてスキンメッシュ情報となる)
        pSkinInfo->AddRef();                                    //参照カウンタ
        dwBoneValue = pSkinInfo->GetNumBones();                 //ボーンの数を取得
        pMeshContainer->BoneOffsetMatrix.resize(dwBoneValue);   //フレーム(ボーン)単位でのワールド行列格納用領域の動的確保

        //ボーンの数だけループさせる
        for (dwCounter = 0; dwCounter < dwBoneValue; ++dwCounter)
        {
            //角フレーム(ボーン)のオフセット行列を取得して格納
            pMeshContainer->BoneOffsetMatrix.at(dwCounter) = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(dwCounter);
        }

        //---固定パイプライン描画用に変換---//
        hResult = pMeshContainer->pSkinInfo->ConvertToBlendedMesh(pMesh, 0, pMeshContainer->pAdjacency, nullptr, nullptr, nullptr, &pMeshContainer->Weight, &pMeshContainer->BoneValue, &pMeshContainer->BoneBuffer, &pMeshContainer->MeshData.pMesh);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("メッシュを固定パイプライン用に変換できませんでした"), TEXT("初期化エラー"), MB_OK);
            return hResult;
        }
    }

    //ローカルに生成したメッシュコンテナーを呼び出し側にコピーする
    *ppMeshContainer = pMeshContainer;
    
    return hResult;
}

/////////////////////////////////////////////
//関数名：DestroyFrame
//
//機能：フレームの破棄
//
//引数：(LPD3DXFRAME)廃棄フレーム
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
    //---各種宣言---//
    ANIMATIONMODELFREAM* pFrame;

    //---初期化処理---//
    pFrame = (ANIMATIONMODELFREAM*)pFrameToFree;

    //---開放処理---//
    SAFE_DELETE_ARRAY(pFrame->Name);
    SAFE_DELETE(pFrame);

    return S_OK;
}

/////////////////////////////////////////////
//関数名：DestroyFrame
//
//機能：メッシュコンテナーの破棄
//
//引数：(LPD3DXMESHCONTAINER)廃棄コンテナ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODELHIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
    //---各種宣言---//
    ANIMATIONMODELCONTAINER* pMeshContainer;

    //---初期化処理---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)pMeshContainerBase;

    //---開放処理---//
    SAFE_DELETE_ARRAY(pMeshContainer->Name);
    SAFE_RELEASE(pMeshContainer->pSkinInfo);
    SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
    SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
    for (auto& data : pMeshContainer->BoneMatrix)
    {
        SAFE_DELETE(data);
    }
    pMeshContainer->BoneMatrix.clear();

    //テクスチャ解放
    if (!pMeshContainer->Texture.empty())
    {
        for (auto& data : pMeshContainer->Texture)
        {
            SAFE_RELEASE(data);
        }
    }
    pMeshContainer->Texture.clear();
    SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

    //ボーン開放
    if (pMeshContainer->BoneBuffer)
    {
        SAFE_RELEASE(pMeshContainer->BoneBuffer);
        pMeshContainer->BoneOffsetMatrix.clear();
    }

    SAFE_DELETE(pMeshContainer);
    pMeshContainerBase = nullptr;
    return S_OK;
}

/////////////////////////////////////////////
//関数名：SetDirectory
//
//機能：Xファイルのあるディレクトリの設定
//
//引数：(LPCTSTR)ディレクトリパス
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODELHIERARCHY::SetDirectory(LPCTSTR directory)
{
    directory? lstrcpy(FileDirectory.data(), directory): FileDirectory.assign(0);
}