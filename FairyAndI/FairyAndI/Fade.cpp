//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Fade.h"

// 頂点フォーマット
#define FVF_VERTEX_FADE	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//＝＝＝グローバル宣言＝＝＝//
int FADE::Fade;
int FADE::Alpha;
int FADE::Directory;
std::array<VERTEX_2D, 4> FADE::Vertex;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：フェードの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FADE::Draw(void)
{
	//---各種宣言---//
	LPDIRECT3DDEVICE9 pDevice;

	//---初期化処理---//
	pDevice = GetDevice();

	// 2D用レンダリング設定
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	// 頂点書式設定
	pDevice->SetFVF(FVF_VERTEX_FADE);

	// テクスチャ設定
	pDevice->SetTexture(0, NULL);

	// 頂点配列によるポリゴン描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &Vertex, sizeof(VERTEX_2D));

	// 2D用レンダリング設定解除
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：フェードの初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT FADE::Initialize(void)
{
	//---各種宣言---//
	int nCounter;
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//---初期化処理---//
	Alpha = 255;
	Directory = 0;
	Fade = 0;

	Vertex[0].Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
	Vertex[1].Position = D3DXVECTOR3(1.0F, 0.0F, 0.0F);
	Vertex[2].Position = D3DXVECTOR3(1.0F, 1.0F, 0.0F);
	Vertex[3].Position = D3DXVECTOR3(0.0F, 1.0F, 0.0F);

	//値の設定
	for (nCounter = 0; nCounter < 4; ++nCounter)
	{
		Vertex[nCounter].Position.x *= SCREEN_WIDTH;
		Vertex[nCounter].Position.y *= SCREEN_HEIGHT;
		Vertex[nCounter].Position.z = 0.0F;
		Vertex[nCounter].RHW = 1.0F;
		Vertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	return S_OK;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：フェードの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FADE::Uninitialize(void)
{

}

/////////////////////////////////////////////
//関数名：Update
//
//機能：フェードの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void FADE::Update(void)
{
	Fade += Directory;
	if (Fade < 0)
	{
		Fade = 0;
	}
	else if (Fade > 60)
	{
		Fade = 60;
	}
	Alpha = Fade * 255 / 60;
	D3DCOLOR color = D3DCOLOR_ARGB(Alpha, 0, 0, 0);
	for (int i = 0; i < 4; ++i) 
	{
		Vertex[i].Diffuse = color;
	}
}

/////////////////////////////////////////////
//関数名：SetFade
//
//機能：フェードのセット
//
//引数：(FADE)フェードのタイプ
//
//戻り値：なし
/////////////////////////////////////////////
void FADE::SetFade(FADETYPE fadetype)
{
	switch (fadetype)
	{
	case FADE_IN:
		Fade = 60;
		Directory = -1;
		break;

	case FADE_OUT:
		Fade = 0;
		Directory = 1;
		break;

	default:
		break;
	}
}

/////////////////////////////////////////////
//関数名：CheckFadeEnd
//
//機能：フェード完了の判定
//
//引数：なし
//
//戻り値：(int)
/////////////////////////////////////////////
int FADE::CheckFadeEnd(FADETYPE fadetype)
{
	switch (fadetype)
	{
	case FADE_IN:
		if (Directory < 0 && Fade <= 0)
		{
			return true;
		}
		return false;

	case FADE_OUT:
		if (Directory > 0 && Fade >= 60)
		{
			return true;
		}
		return false;

	default:
		break;
	}
}