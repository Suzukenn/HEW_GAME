//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackImage.h"
#include "TextureManager.h"



void BACKIMAGE::Draw(void)
{
	//---各種宣言---//
	LPDIRECT3DDEVICE9 pDevice;

	//---初期化処理---//
	pDevice = GetDevice();

	//---書式設定---//
	pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_2D)); //頂点書式設定
	pDevice->SetFVF(FVF_VERTEX_2D);                                   //フォーマット設定
	pDevice->SetTexture(0, *Texture);                                 //テクスチャ設定
	 //---頂点バッファによる背景描画---//																 
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

HRESULT BACKIMAGE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
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

void BACKIMAGE::Update(void)
{


}

void BACKIMAGE::Uninitialize(void)
{


}
