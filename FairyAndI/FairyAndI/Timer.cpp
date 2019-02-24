//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Timer.h"
#include "Texture.h"
#include "TextureManager.h"

//＝＝＝定数・マクロ定義＝＝＝//
//テクスチャ分割数
#define TIME_DIV_U			(10)	//横分割数
#define TIME_DIV_V			(1)		//縦分割数

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：タイマーの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TIMER::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pTexture;

    //---初期化処理---//
    pDevice = GetDevice();
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("描画対象のテクスチャが存在しません"), TEXT("描画エラー"), MB_OK);
    }

    //---書式設定---//
    pDevice->SetFVF(FVF_VERTEX_2D);             //フォーマット設定
    pDevice->SetTexture(0, pTexture->Image);    //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, Length * 4 - 2, &Vertex, sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：タイマーの初期化
//
//引数：(LPCTSTR)テクスチャ名, (D3DXVECTOR2)位置 , (D3DXVECTOR2)サイズ, (int)制限時間
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT TIMER::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, int timer)
{
	//---各種宣言---//
	int nCounter;
	HRESULT hResult;

	//---初期化処理---//
	Position = position;
	Size = size;
	Length = MAX_LENGTH;
	Timer = timer;
	VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9);

	//---テクスチャの読み込み---//
	hResult = TEXTUREMANAGER::GetTexture(texturename, Texture);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("タイマーのテクスチャの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
		Uninitialize();
		return hResult;
	}

	//---頂点バッファの生成---//
	hResult = GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("タイマーの頂点バッファの生成に失敗しました"), texturename, MB_OK);
		Uninitialize();
		return hResult;
	}

	//---頂点バッファへの値の設定---//
	//バッファのポインタを取得
	hResult = (*VertexBuffer)->Lock(0, 0, (void**)&Vertex, 0);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("タイマーの頂点バッファのポインタの取得に失敗しました"), TEXT("初期化エラー"), MB_OK);
		Uninitialize();
		return hResult;
	}
	for (int i = Length - 1; i >= 0; --i)
	{
		//値の設定
		for (nCounter = 0; nCounter < 4; ++nCounter)
		{
			Vertex.at(i * 4 + nCounter).U = (float)(nCounter & 1);
			Vertex.at(i * 4 + nCounter).V = (float)((nCounter >> 1) & 1);
			Vertex.at(i * 4 + nCounter).Position.x = position.x + Vertex[nCounter].U * Size.x;
			Vertex.at(i * 4 + nCounter).Position.y = position.y + Vertex[nCounter].V * Size.y;
			Vertex.at(i * 4 + nCounter).Position.z = 0.0F;
			Vertex.at(i * 4 + nCounter).RHW = 1.0F;
			Vertex.at(i * 4 + nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
	}
	//バッファのポインタの解放
	hResult = (*VertexBuffer)->Unlock();
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("タイマーの頂点バッファのポインタの開放に失敗しました"), TEXT("初期化エラー"), MB_OK);
		Uninitialize();
		return hResult;
	}

	return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：タイマーの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TIMER::Uninitialize(void)
{

}

/////////////////////////////////////////////
//関数名：Update
//
//機能：タイマーの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void TIMER::Update(void)
{
    //---各種宣言---//
	static int nCnt;							//秒をカウントするため
	const float dx[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	const float dy[] = { 1.0f, 0.0f, 1.0f, 0.0f };
	Length = MAX_LENGTH;
	int timer;

	timer = Timer;

	///シーンの切替（タイムオーバー）
	//if (Timer < 1)
	//{
	//	//if (EndFadeIn())
	//	//{
	//	//	StartFadeOut();
	//	//}
	//	//if (EndFadeOut())
	//	//{
	//	//	SetScene(SCENE_GAMEOVER);
	//	//}
	//}

	nCnt++;
	if (nCnt > 60)
	{
		Timer--;
		nCnt = 0;
	}

	//タイマー終了(仮)
	if (Timer < 1)
	{
		Timer = 0;
	}

	if (Length < 1)								//値が1未満のとき
	{
		Length = 1;
	}
	else if (Length > MAX_LENGTH)				//値が最大値より大きかったら
	{
		Length = MAX_LENGTH;
	}
	for (int i = Length - 1; i >= 0; --i)
	{
		int n = timer % 10;
		timer /= 10;
		int u = n % TIME_DIV_U;
		int v = n / TIME_DIV_V;

		for (int j = 0; j < 4; ++j)
		{
			// 位置を更新
			Vertex.at(i * 4 + j).Position.x = Position.x + (dx[j] + i) * Size.x;
			Vertex.at(i * 4 + j).Position.y = Position.y + dy[j] * Size.y;
			// フレーム設定
			Vertex.at(i * 4 + j).U = (u + dx[j]) * (1.0f / TIME_DIV_U);
			Vertex.at(i * 4 + j).V = (v + dy[j]) * (1.0f / TIME_DIV_V);
		}
	}
   
}