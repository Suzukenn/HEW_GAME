//=============================================================================
//
// ライト処理 [light.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT LIGHT::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 環境光
	m_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -0.6f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &m_aLight[0]);

	// ライトの設定
	pDevice->LightEnable(0, FALSE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	m_aLight[1].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

	// 環境光
	m_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    // ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(1, &m_aLight[1]);

	// ライトの設定
	pDevice->LightEnable(1, TRUE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	m_aLight[2].Type = D3DLIGHT_POINT;

	// 拡散光
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 環境光
	m_aLight[2].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

    // ライトの位置の設定
    m_aLight[2].Position = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	// ライトの減衰の設定
	m_aLight[2].Attenuation0 = 0.0f;
	m_aLight[2].Attenuation1 = 0.0f;
	m_aLight[2].Attenuation2 = 0.01f;
	m_aLight[2].Falloff = 1.0f;

	// ライトの範囲の設定
	m_aLight[2].Range = 50.0f;

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(2, &m_aLight[2]);

	// ライトの設定
	pDevice->LightEnable(2, FALSE);


	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void LIGHT::Uninit(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void LIGHT::Update(D3DXVECTOR3* Player)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // ライトの位置の設定
	m_aLight[2].Position.x = Player->x;
	m_aLight[2].Position.z = Player->z;

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(2, &m_aLight[2]);
}
