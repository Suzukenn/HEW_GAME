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
    BILLBOARD::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR3)位置,(D3DXVECTOR3)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR3 size)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = BILLBOARD::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
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

