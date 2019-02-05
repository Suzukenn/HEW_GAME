//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "TextureManager.h"
#include "SideViewCamera.h"

#define MAX_BILLBOARD 1

#define FLD_X_MIN			(-150.0f)
#define FLD_X_MAX			(150.0f)
#define FLD_Z_MIN			(-150.0f)
#define FLD_Z_MAX			(150.0f)

// 構造体定義
typedef struct _TBillboard {
	int				stat;	// 状態
	D3DXVECTOR3		pos;	// 位置
	D3DXVECTOR3		vel;	// 速度
} TBillboard;

// ---プロトタイプ宣言---
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//---グローバル変数---
D3DXMATRIX          g_matrix;   //  ワールド行列     
LPD3DXSPRITE        pSprite;    //  スプライト管理変数      
LPDIRECT3DTEXTURE9  tex;        //  テクスチャロード変数  
static LPDIRECT3DTEXTURE9 g_pD3DTextureBillboard;		// テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBillboard;	// 頂点バッファへのポインタ

static D3DXMATRIX g_mtxWorldBillboard;			// ワールドマトリックス
static TBillboard g_billboard[MAX_BILLBOARD];	// ビルボード情報

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：背景の描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKGROUND::Draw(void)
{
	//---各種宣言---//
	LPDIRECT3DDEVICE9 pDevice;

	//---初期化処理---//
	pDevice = GetDevice();

	// 回転を反映
	D3DXMATRIX mtxView;
	SIDEVIEWCAMERA::GetViewMtx(&mtxView);
	g_mtxWorldBillboard._11 = mtxView._11;
	g_mtxWorldBillboard._12 = mtxView._21;
	g_mtxWorldBillboard._13 = mtxView._31;
	g_mtxWorldBillboard._21 = mtxView._12;
	g_mtxWorldBillboard._22 = mtxView._22;
	g_mtxWorldBillboard._23 = mtxView._32;
	g_mtxWorldBillboard._31 = mtxView._13;
	g_mtxWorldBillboard._32 = mtxView._23;
	g_mtxWorldBillboard._33 = mtxView._33;

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, g_pD3DVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//---書式設定---//
    pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_2D)); //頂点書式設定
	pDevice->SetFVF(FVF_VERTEX_2D);                                   //フォーマット設定
	pDevice->SetTexture(0, *Texture);                                 //テクスチャ設定			
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);  // ライティング無効化

	for (int i = 0; i < MAX_BILLBOARD; ++i) {
		if (!g_billboard[i].stat) continue;

		// 移動を反映
		g_mtxWorldBillboard._41 = g_billboard[i].pos.x;
		g_mtxWorldBillboard._42 = g_billboard[i].pos.y;
		g_mtxWorldBillboard._43 = g_billboard[i].pos.z;

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);
	}

	//---頂点バッファによる背景描画---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
	//---各種宣言---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVertex;

	//---初期化処理---//
    Position = position;
    Size = size;
	pDevice = GetDevice();
    Texture.reset(new LPDIRECT3DTEXTURE9());
    VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9());
	//---テクスチャの読み込み---//

	hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);

	// 頂点情報の作成
	hResult = MakeVertexBillboard(pDevice);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景のテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

   // ---頂点バッファの生成---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
	if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("背景の頂点バッファの生成に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
		return hResult;
	}

	//---頂点バッファへの値の設定---//
	//バッファのポインタを取得
    hResult = (*VertexBuffer)->Lock(0, 0, (void**)&pVertex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景の頂点バッファのポインタの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //値の設定
	for (nCounter = 0; nCounter < 4; ++nCounter)
	{
		pVertex[nCounter].U = (float)(nCounter & 1);
		pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
		pVertex[nCounter].Position.x = position.x + pVertex[nCounter].U * Size.x;
		pVertex[nCounter].Position.y = position.y + pVertex[nCounter].V * Size.y;
		pVertex[nCounter].Position.z = 300.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	// ビルボードの初期設定
	for (int i = 0; i < MAX_BILLBOARD; ++i) {
		g_billboard[i].stat = 0;
		g_billboard[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billboard[i].vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//バッファのポインタの解放
    hResult = (*VertexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景の頂点バッファのポインタの開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

	return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：背景の終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKGROUND::Uninitialize(void)
{
\

	if (g_pD3DTextureBillboard)
	{// テクスチャの開放
		g_pD3DTextureBillboard->Release();
		g_pD3DTextureBillboard = NULL;
	}
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：背景の更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BACKGROUND::Update(void)
{

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	int g_nNumBlockX, g_nNumBlockZ, g_nNumVertex, g_nNumPolygon;
	float g_fSizeBlockX, g_fSizeBlockZ;
	// ブロック数
	g_nNumBlockX = 1;
	g_nNumBlockZ = 1;

	// 頂点数
	g_nNumVertex = 4;

	// ポリゴン数
	g_nNumPolygon = 2;

	// ブロックサイズ
	g_fSizeBlockX = 200.0f;
	g_fSizeBlockZ = 200.0f;

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffBillboard,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < g_nNumBlockZ; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < (g_nNumBlockX + 1); nCntVtxX++, pVtx += 2)
			{
				// 頂点座標の設定
				pVtx[0].Vertex.x = -(g_nNumBlockX / 2.0f) * g_fSizeBlockX + nCntVtxX * g_fSizeBlockX;
				pVtx[0].Vertex.y = (g_nNumBlockZ / 2.0f) * g_fSizeBlockZ - (nCntVtxY + 1) * g_fSizeBlockZ;
				pVtx[0].Vertex.z = 0.0f;
				pVtx[1].Vertex.x = -(g_nNumBlockX / 2.0f) * g_fSizeBlockX + nCntVtxX * g_fSizeBlockX;
				pVtx[1].Vertex.y = (g_nNumBlockZ / 2.0f) * g_fSizeBlockZ - nCntVtxY * g_fSizeBlockZ;
				pVtx[1].Vertex.z = 0.0f;

				// 法線の設定
				pVtx[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// 反射光の設定
				pVtx[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[0].Texture.x = fSizeTexX * nCntVtxX;
				pVtx[0].Texture.y = fSizeTexZ * (nCntVtxY + 1);
				pVtx[1].Texture.x = fSizeTexX * nCntVtxX;
				pVtx[1].Texture.y = fSizeTexZ * nCntVtxY;
			}
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffBillboard->Unlock();
	}

	return S_OK;
}

// ビルボード生成
int  BACKGROUND::CreateBillboard(LPD3DXVECTOR3 pos, LPD3DXVECTOR3 vel)
{
	int nBillboard = -1;

	for (int i = 0; i < MAX_BILLBOARD; ++i) {
		if (g_billboard[i].stat) continue;
		g_billboard[i].pos = *pos;
		g_billboard[i].vel = *vel;
		g_billboard[i].stat = 1;
		return i;
	}
	return nBillboard;
}

// ビルボード破棄
void  BACKGROUND::ReleaseBillboard(int nBillboard)
{
	if (nBillboard < 0 || nBillboard >= MAX_BILLBOARD)
		return;
	g_billboard[nBillboard].stat = 0;
}

