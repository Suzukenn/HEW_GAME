//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <d3dx9mesh.h>
#include "Field.h"
#include "TextureManager.h"

//＝＝＝グローバル宣言＝＝＝//
LPD3DXMESH FIELD::Mesh;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：CheckField
//
//機能：地形の当たり判定
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)距離
//
//戻り値：(bool)判定結果
/////////////////////////////////////////////
bool FIELD::CheckField(LPD3DXVECTOR3 rayposition, LPD3DXVECTOR3 raydirection, float& afterposition)
{
    //---各種宣言---//
    int nCounter;
    BOOL bResult;
    float fHitU;
    float fHitV;
    HRESULT hResult;
    DWORD dwHitIndex;

    WORD dwHitVertexNo[3];

    LPWORD pIndex;
    VERTEX_3D* pVertex;

    //---初期化処理---//
    dwHitIndex = -1;

    //レイピッキング
    hResult = D3DXIntersect(Mesh, rayposition, raydirection, &bResult, &dwHitIndex, &fHitU, &fHitV, nullptr, nullptr, nullptr);
    if (SUCCEEDED(hResult) && bResult)
    {
        hResult = Mesh->LockIndexBuffer(0, (void**)&pIndex);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("地形のモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
            return false;
        }
        for (nCounter = 0; nCounter < 3; ++nCounter)
        {
            dwHitVertexNo[nCounter] = pIndex[dwHitIndex * 3 + nCounter];
        }

        hResult = Mesh->UnlockIndexBuffer();
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("地形のモデル情報の開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
            return false;
        }

        //当たったポリゴン取得
        hResult = Mesh->LockVertexBuffer(0, (void**)&pVertex);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("地形のモデルポリゴンの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
            return false;
        }


        //地面の高さに合わせる
        afterposition = pVertex[dwHitVertexNo[0]].Vertex.y + fHitU * (pVertex[dwHitVertexNo[1]].Vertex.y - pVertex[dwHitVertexNo[0]].Vertex.y) + fHitV * (pVertex[dwHitVertexNo[2]].Vertex.y - pVertex[dwHitVertexNo[0]].Vertex.y);

        hResult = Mesh->UnlockVertexBuffer();
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("地形のモデルポリゴンの開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
            return false;
        }

        return bResult ? true : false;
    }
    else
    {
        return false;
    }
}

/////////////////////////////////////////////
//関数名：Draw
//
//機能：地形の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FIELD::Draw(void)
{
    //---各種宣言---//
    DWORD nCounter;
    D3DXMATRIX mtxWorld;
    D3DMATERIAL9 matDef;

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMatrix;

    //---初期化処理---//
    pDevice = GetDevice();

    D3DXMatrixIdentity(&mtxWorld);

    //ワールドマトリックスの設定---//
    Transform.MakeWorldMatrix(mtxWorld);

    //---描画---//
    // 現在のマテリアルを取得
    pDevice->GetMaterial(&matDef);

    //ポインタを取得
    pMatrix = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //テクスチャの設定
        pDevice->SetTexture(0, Texture);

        //描画
        Mesh->DrawSubset(nCounter);
    }

    //マテリアルをデフォルトに戻す
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：地形の初期化
//
//引数：(LPCTSTR)モデル名,(tstirng)タグ,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FIELD::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 scale)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    //初期設定
    Transform.Position = position;
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = scale;

    //Xファイルの読み込み
    hResult = D3DXLoadMeshFromX(modelfile, D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形のモデル情報の取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：地形の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FIELD::Uninitialize(void)
{
    //---開放---//
    SAFE_RELEASE(MaterialBuffer);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(Texture);
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：地形の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FIELD::Update(void)
{

}