//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Ground.h"
#include "TextureManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：地形の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void GROUND::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;

    //---初期化処理---//
    pDevice = GetDevice();

    //ワールドマトリックスの設定---//
    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&mtxWorld);

    //回転を反映
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //移動を反映
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    //頂点バッファをレンダリングパイプラインに設定
    pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_3D));

    //頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_3D);

    //インデックスバッファをレンダリングパイプラインに設定
    pDevice->SetIndices(*IndexBuffer);

    //テクスチャの設定
    pDevice->SetTexture(0, *Texture);

    //ポリゴンの描画
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VertexValue, 0, PolygonValue);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：地形の初期化
//
//引数：(LPCTSTR)テクスチャ名,(const int&)Xポリゴン数,(const int&)Zポリゴン数,(const float&)Xサイズ,(const float&)Zサイズ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT GROUND::Initialize(LPCTSTR texturename, const int& valueX, const int& valueZ, const float& sizeX, const float& sizeZ)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Texture.reset(new LPDIRECT3DTEXTURE9);

    //---テクスチャの読み込み---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形のテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---頂点情報の作成---//
    hResult = MakeVertex(GetDevice(), valueX, valueZ, sizeX, sizeZ);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形の頂点情報の作成に失敗しました"), texturename, MB_OK);
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
void GROUND::Uninitialize(void)
{
    //---開放---//
    SAFE_RELEASE((*VertexBuffer));
    SAFE_RELEASE((*IndexBuffer));
    SAFE_RELEASE((*Texture));
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
void GROUND::Update(void)
{

}

/////////////////////////////////////////////
//関数名：MakeVertex
//
//機能：地形の頂点データの作成
//
//引数：(const LPDIRECT3DDEVICE9&)デバイス,(const int&)Xポリゴン数,(const int&)Zポリゴン数,(const float&)Xサイズ,(const float&)Zサイズ
//
//戻り値：なし
/////////////////////////////////////////////
HRESULT GROUND::MakeVertex(const LPDIRECT3DDEVICE9& device, const int& valueX, const int& valueZ, const float& sizeX, const float& sizeZ)
{
    //---各種宣言---//
    int nCounterX;
    int nCounterZ;
    int nIndexNumber;
    int nIndexValue;
    int nVertexNumber;
    HRESULT hResult;

    VERTEX_3D *pVertex;
    WORD *pIndex;

    //---初期化処理---//
    IndexBuffer.reset(new LPDIRECT3DINDEXBUFFER9());
    VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9());

    //---各種算出---//
    VertexValue = (valueX + 1) * (valueZ + 1);                          //頂点数(インデックス有なら)
    nIndexValue = (valueX + 1) * (valueZ << 1) + ((valueZ - 1) << 1);   //インデックス数(縮退ポリゴンを考慮)
    PolygonValue = valueX * (valueZ << 1) + ((valueZ - 1) << 2);        //ポリゴン数(縮退ポリゴンを考慮)

    //---バッファの生成---//
    //頂点バッファ
    hResult = device->CreateVertexBuffer(sizeof(VERTEX_3D) * VertexValue, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形の頂点バッファの作成に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //インデックスバッファ
    hResult = device->CreateIndexBuffer(sizeof(WORD) * nIndexValue, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, IndexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形のインデックスバッファの作成に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---頂点バッファの中身を埋める---//
    //バッファのポインタを取得
    hResult = (*VertexBuffer)->Lock(0, 0, (void**)&pVertex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形の頂点バッファのポインタの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //値の設定
    for (nCounterZ = 0; nCounterZ < (valueZ + 1); ++nCounterZ)
    {
        for (nCounterX = 0; nCounterX < (valueX + 1); ++nCounterX)
        {
            nVertexNumber = nCounterZ * (valueX + 1) + nCounterX;
            pVertex[nVertexNumber].Vertex.x = -(valueX >> 1) * sizeX + nCounterX * sizeX;
            pVertex[nVertexNumber].Vertex.y = 0.0F;
            pVertex[nVertexNumber].Vertex.z = (valueX >> 1) * sizeZ - nCounterZ * sizeZ;
            pVertex[nVertexNumber].Normal = D3DXVECTOR3(0.0F, 1.0F, 0.0F);
            pVertex[nVertexNumber].Diffuse = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);
            pVertex[nVertexNumber].Texture.x = 1.0F * nCounterX;
            pVertex[nVertexNumber].Texture.y = 1.0F * nCounterZ;
        }
    }

    //バッファのポインタの開放
    hResult = (*VertexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形の頂点バッファのポインタの開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    //---インデックスバッファの中身を埋める---//
    //バッファのポインタを取得
    hResult = (*IndexBuffer)->Lock(0, 0, (void**)&pIndex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形のインデックスバッファのポインタの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    nIndexNumber = 0;
    for (nCounterZ = 0; nCounterZ < valueZ; ++nCounterZ)
    {
        //縮退ポリゴンの重複を設定
        if (nCounterZ > 0)
        {
            pIndex[nIndexNumber] = (nCounterZ + 1) * (valueX + 1);
            nIndexNumber++;
        }
        for (int nCounterX = 0; nCounterX < (valueX + 1); ++nCounterX)
        {
            pIndex[nIndexNumber] = (nCounterZ + 1) * (valueX + 1) + nCounterX;
            nIndexNumber++;
            pIndex[nIndexNumber] = nCounterZ * (valueX + 1) + nCounterX;
            nIndexNumber++;
        }

        //縮退ポリゴンのための重複を設定
        if (nCounterZ < valueZ - 1)
        {
            pIndex[nIndexNumber] = nCounterZ * (valueX + 1) + valueX;
            nIndexNumber++;
        }
    }

    //バッファのポインタの開放
    hResult = (*IndexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("地形のインデックスバッファのポインタの開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

    return hResult;
}