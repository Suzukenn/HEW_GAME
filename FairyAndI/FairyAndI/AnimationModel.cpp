//＝＝＝ヘッダファイル読み込み＝＝＝//
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "AnimationModel.h"
#include "AnimationModelContainer.h"
#include "AnimationModelFrame.h"
#include "AnimationModelHierarchy.h"
#include "InputManager.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define SKIN_ANIME_SPEED 0.000125F    //アニメーションコントローラーのスピード

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：AllocateBoneMatrix
//
//機能：ボーン行列のアロケート
//
//引数：(LPD3DXFRAME)処理フレーム
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODEL::AllocateAllBoneMatrices(LPD3DXFRAME frame)
{
    //---各種宣言---//
    HRESULT hResult;

    ANIMATIONMODELFREAM* pFrame;

    //---初期化処理---//
    pFrame = (ANIMATIONMODELFREAM*)frame;

    //階層の走査(メモリを確保したメッシュコンテナ領域を探す処理)
    if (frame->pMeshContainer)
    {
        //ボーン行列の初期化処理
        hResult = AllocateBoneMatrix(frame->pMeshContainer);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("ボーン行列の初期化に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            return hResult;
        }
    }

    //再帰判断処理
    if (frame->pFrameSibling)
    {
        hResult = AllocateAllBoneMatrices(frame->pFrameSibling);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("兄弟フレームのボーン行列の初期化に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            return hResult;
        }
    }
    if (frame->pFrameFirstChild)
    {
        hResult = AllocateAllBoneMatrices(frame->pFrameFirstChild);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("子フレームのボーン行列の初期化に失敗しました"), TEXT("初期化エラー"), MB_ICONSTOP | MB_OK);
            return hResult;
        }
    }
    return S_OK;
}

/////////////////////////////////////////////
//関数名：AllocateBoneMatrix
//
//機能：ボーンマトリクスの生成
//
//引数：(LPD3DXMESHCONTAINER)メッシュコンテナ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODEL::AllocateBoneMatrix(LPD3DXMESHCONTAINER meshcontainer)
{
    //---各種宣言---//
    DWORD dwBoneValue;
    DWORD dwCounter;

    ANIMATIONMODELFREAM* pFrame;
    ANIMATIONMODELCONTAINER* pMeshContainer;

    //---初期化処理---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)meshcontainer;

    //スキンメッシュでなければなにもしない
    if (!pMeshContainer->pSkinInfo)
    {
        return S_OK;
    }

    dwBoneValue = pMeshContainer->pSkinInfo->GetNumBones();     //ボーンの数取得
    pMeshContainer->BoneMatrix.resize(dwBoneValue); //各ボーンのワールド行列格納用領域を確保

    //---ボーンのポインタの格納---//
    for (dwCounter = 0; dwCounter < dwBoneValue; ++dwCounter)
    {
        //子フレーム(ボーン)のアドレスを検索して格納
        pFrame = (ANIMATIONMODELFREAM*)D3DXFrameFind(FrameRoot, pMeshContainer->pSkinInfo->GetBoneName(dwCounter));

        if (pFrame)
        {
            //各ボーンのワールド行列格納用変数に最終行列を格納
            pMeshContainer->BoneMatrix.at(dwCounter) = &pFrame->CombinedTransformationMatrix;
        }
        else
        {
            return E_FAIL;
        }
    }
    return S_OK;
}

/////////////////////////////////////////////
//関数名：ChangeAnimation
//
//機能：再生アニメーションの変更
//
//引数：(DWORD)再生アニメーション番号
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODEL::ChangeAnimation(DWORD animationnumber)
{
    //指定値の境界チェック
    if (animationnumber >= AnimationData.size())
    {
        return;
    }
    else if (CurrentTrack == animationnumber)
    {
        return;
    }
    else
    {
        CurrentTrack = animationnumber;

        //アニメーションを最初の位置から再生させる
        if (FAILED(AnimationController->SetTrackAnimationSet(0, AnimationData.at(animationnumber))))
        {
            MessageBox(nullptr, TEXT("アニメーションの変更に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            exit(EXIT_FAILURE);
        }

    }
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：モデルの描画
//
//引数：(D3DXMATRIX)ワールドマトリクス,(bool)エフェクトの有効状態
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODEL::Draw(D3DXMATRIX worldmatrix, bool effect)
{
    // アニメーション更新
    if (AnimationController)
    {
        //アニメーション時間データの更新
        if (FAILED(AnimationController->AdvanceTime(SKIN_ANIME_SPEED * PlaySpeed, nullptr)))
        {
            MessageBox(nullptr, TEXT("メッシュアニメーションの再生に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            exit(EXIT_FAILURE);
        }
    }

    //フレームの更新
    if (FrameRoot)
    {
        //アニメーションデータを更新
        UpdateFrameMatrices(FrameRoot, &worldmatrix);

        //アニメーション描画
        DrawFrame(FrameRoot, effect);
    }
}

/////////////////////////////////////////////
//関数名：DrawFrame
//
//機能：フレームのレンダリング
//
//引数：(LPD3DXFRAME)ルートフレーム,(bool)エフェクトの有効状態
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODEL::DrawFrame(LPD3DXFRAME framebase, bool effect)
{
    //---各種宣言---//
    LPD3DXMESHCONTAINER pMeshContainer;

    //---初期化処理---//
    pMeshContainer = framebase->pMeshContainer;

    //---レンダリング---//
    while (pMeshContainer)
    {
        //メッシュのレンダリング
        RenderMeshContainer(pMeshContainer, framebase, effect);

        //次のメッシュコンテナへアクティブを移す
        pMeshContainer = pMeshContainer->pNextMeshContainer;
    }

    //兄弟フレームのレンダリング
    if (framebase->pFrameSibling)
    {
        DrawFrame(framebase->pFrameSibling, effect);
    }

    //子フレームのレンダリング
    if (framebase->pFrameFirstChild)
    {
        DrawFrame(framebase->pFrameFirstChild, effect);
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：モデルの初期化
//
//引数：(LPCTSTR)ファイル名,(float)再生速度
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT ANIMATIONMODEL::Initialize(LPCTSTR filename, float speed)
{
    //---各種宣言---//
    DWORD dwCounter;
    HRESULT hResult;

    TCHAR szDirectory[_MAX_DIR];
    TCHAR szWork[_MAX_DIR];

    //---初期化処理---//
    PlaySpeed = speed;
    CurrentTrack = 0;
    CurrentTrackDescription = { D3DXPRIORITY_LOW, 1.0F, 1.0F, 0.0, TRUE };
    AnimationData.clear();

    //---ディレクトリの抽出---//
    if (filename)
    {
        //フォルダ名を抽出
        _tsplitpath(filename, szDirectory, szWork, nullptr, nullptr);
        lstrcat(szDirectory, szWork);
        Hierarchy.SetDirectory(szDirectory);
    }
    else
    {
        MessageBox(nullptr, TEXT("開くモデルファイルが見つかりません"), filename, MB_ICONSTOP | MB_OK);
        return E_FAIL;
    }

    //---階層構造メッシュの読み込み---//
    hResult = D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, GetDevice(), &Hierarchy, nullptr, &FrameRoot, &AnimationController);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アニメーション付きXファイルの読み込みに失敗しました"), filename, MB_OK);
        return hResult;
    }

    //---ボーン行列初期化---//
    hResult = AllocateAllBoneMatrices(FrameRoot);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ボーン行列の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---アニメーショントラックの取得---//
    if (AnimationController)
    {
        AnimationData.resize(AnimationController->GetNumAnimationSets());
        for (dwCounter = 0; dwCounter < AnimationData.size(); ++dwCounter)
        {
            //アニメーション取得
            hResult = AnimationController->GetAnimationSet(dwCounter, &AnimationData.at(dwCounter));
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("アニメーションの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
                return hResult;
            }
        }
    }

    //---マトリクスの更新---//
    if (FrameRoot)
    {
        SetTime(0.0);
        UpdateFrameMatrices(FrameRoot, &World);
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：RenderMeshContainer
//
//機能：フレーム内のメッシュのレンダリング
//
//引数：(LPD3DXMESHCONTAINER)メッシュコンテナ,(LPD3DXFRAME)レンダリングフレーム,(bool)エフェクトの有効状態
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
void ANIMATIONMODEL::RenderMeshContainer(LPD3DXMESHCONTAINER meshcontainer, LPD3DXFRAME frame, bool effect)
{
    //---各種宣言---//
    HRESULT hResult;
    DWORD dwAttribute;
    DWORD dwBoneCounter;
    DWORD dwWeightCounter;
    DWORD dwBlendMatrixNumber;
    DWORD dwPreviewBoneID;
    DWORD dwMatrixID;
    D3DMATERIAL9 matEffect;

    volatile DWORD dwAttributeCounter;

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXBONECOMBINATION pBoneCombination;
    ANIMATIONMODELCONTAINER* pMeshContainer;
    ANIMATIONMODELFREAM* pFrame;

    //---初期化処理---//
    pMeshContainer = (ANIMATIONMODELCONTAINER*)meshcontainer;
    pFrame = (ANIMATIONMODELFREAM*)frame;
    pDevice = GetDevice();

    //---描画---//
    //スキンメッシュの描画
    if (meshcontainer->pSkinInfo)
    {
        //ボーンテーブルからバッファの先頭アドレスを取得
        pBoneCombination = (LPD3DXBONECOMBINATION)pMeshContainer->BoneBuffer->GetBufferPointer();

        //dwPrevBoneIDを初期化
        dwPreviewBoneID = UINT_MAX;

        //スキニング計算
        for (dwBoneCounter = 0; dwBoneCounter < pMeshContainer->BoneValue; ++dwBoneCounter)
        {
            dwBlendMatrixNumber = 0;
            //影響している行列数取得
            for (dwWeightCounter = 0; dwWeightCounter < pMeshContainer->Weight; ++dwWeightCounter)
            {
                //影響数が初期値か判定
                if (pBoneCombination[dwBoneCounter].BoneId[dwWeightCounter] != UINT_MAX)
                {
                    //現在影響を受けているボーンの数
                    dwBlendMatrixNumber = dwWeightCounter;
                }
            }

            //ジオメトリブレンディングを使用するために行列の個数を指定
            hResult = pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNumber);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("テクスチャの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }

            //影響している行列の検索
            for (dwWeightCounter = 0; dwWeightCounter < pMeshContainer->Weight; ++dwWeightCounter)
            {
                //nMatrixIndexに1度の呼び出しで描画出来る各ボーンを識別する値を格納
                dwMatrixID = pBoneCombination[dwBoneCounter].BoneId[dwWeightCounter];

                //行列の情報があれば
                if (dwMatrixID != UINT_MAX)
                {
                    //行列スタックに格納
                    hResult = pDevice->SetTransform(D3DTS_WORLDMATRIX(dwWeightCounter), &(pMeshContainer->BoneOffsetMatrix[dwMatrixID] * (*pMeshContainer->BoneMatrix[dwMatrixID])));
                    if (FAILED(hResult))
                    {
                        MessageBox(nullptr, TEXT("行列スタックへの格納に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
                    }
                }
            }

            //マテリアルの設定
            if (effect)
            {
                matEffect = pMeshContainer->pMaterials[pBoneCombination[dwBoneCounter].AttribId].MatD3D;
                matEffect.Diffuse = { 0.5F, 0.5F, 0.5F, 1.0F };
                hResult = pDevice->SetMaterial(&matEffect);
            }
            else
            {
                hResult = pDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneCombination[dwBoneCounter].AttribId].MatD3D);
            }

            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("マテリアルの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }

            hResult = pDevice->SetTexture(0, pMeshContainer->Texture.at(pBoneCombination[dwBoneCounter].AttribId));
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("テクスチャの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }

            //属性テーブルの識別子を格納
            dwPreviewBoneID = pBoneCombination[dwBoneCounter].AttribId;

            //メッシュの描画
            hResult = pMeshContainer->MeshData.pMesh->DrawSubset(dwBoneCounter);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("メッシュの描画に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }
        }
    }

    //通常メッシュの描画
    else
    {
        hResult = pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
        for (dwAttributeCounter = 0; dwAttributeCounter < pMeshContainer->NumMaterials; ++dwAttributeCounter)
        {
            //属性テーブルの取得
            dwAttribute = pMeshContainer->AttributeTable.at(dwAttributeCounter).AttribId;

            //マテリアルの設定
            hResult = pDevice->SetMaterial(&pMeshContainer->pMaterials[dwAttribute].MatD3D);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("マテリアルの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }

            //テクスチャの設定
            hResult = pDevice->SetTexture(0, pMeshContainer->Texture.at(dwAttribute));
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("テクスチャの設定に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }

            //メッシュの描画
            hResult = pMeshContainer->MeshData.pMesh->DrawSubset(dwAttribute);
            if (FAILED(hResult))
            {
                MessageBox(nullptr, TEXT("メッシュの描画に失敗しました"), TEXT("描画エラー"), MB_ICONSTOP | MB_OK);
            }
        }
    }
}

/////////////////////////////////////////////
//関数名：SetTime
//
//機能：再生位置の設定
//
//引数：(double)再生位置
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODEL::SetTime(double time)
{
    //---各種宣言---//
    UINT nCounter;

    if (!AnimationController)
    {
        return;
    }
    
    for (nCounter = 0; nCounter < AnimationController->GetMaxNumTracks(); ++nCounter)
    {
        AnimationController->SetTrackPosition(nCounter, 0.0);
    }

    AnimationController->ResetTime();
    AnimationController->AdvanceTime(time, nullptr);
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：モデルの削除
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODEL::Uninitialize(void)
{
    //---各種宣言---//
    int nCounter;
    HRESULT hResult;

    //アニメーションコントローラー解放
    if (AnimationController)
    {
        for (nCounter = 0; nCounter < AnimationData.size(); ++nCounter)
        {
            SAFE_RELEASE(AnimationData.at(nCounter));
        }
    }
    AnimationData.clear();
    SAFE_RELEASE(AnimationController);

    //ボーン開放
    if (FrameRoot)
    {
        hResult = D3DXFrameDestroy(FrameRoot, &Hierarchy);
        if (SUCCEEDED(hResult))
        {
            //ボーンフレーム関係解放
            FrameRoot = nullptr;
        }
    }
}

/////////////////////////////////////////////
//関数名：UpdateFrameMatrices
//
//機能：フレーム内のメッシュごとのワールド変換行列の更新
//
//引数：(LPD3DXFRAME)更新フレーム,(LPD3DXMATRIX)親マトリクス
//
//戻り値：なし
/////////////////////////////////////////////
void ANIMATIONMODEL::UpdateFrameMatrices(LPD3DXFRAME framebase, LPD3DXMATRIX parentmatrix)
{
    //---各種宣言---//
    ANIMATIONMODELFREAM* pFrame;

    //---初期化処理---//
    pFrame = (ANIMATIONMODELFREAM*)framebase;

    //CombinedTransformationMatrixに最終行列を格納
    pFrame->CombinedTransformationMatrix = parentmatrix ? pFrame->TransformationMatrix * *parentmatrix : pFrame->TransformationMatrix;

    // 兄弟フレームがあればマトリックスを更新
    if (pFrame->pFrameSibling)
    {
        UpdateFrameMatrices(pFrame->pFrameSibling, parentmatrix);
    }

    // 子フレームがあればマトリックスを更新
    if (pFrame->pFrameFirstChild)
    {
        UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
    }
}