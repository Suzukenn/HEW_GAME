//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Button.h"
#include "InputManager.h"

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Draw
//
//機能：ボタンの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BUTTON::Draw(void)
{
    //---各種宣言---//
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();

    //---書式設定---//
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_2D)); //頂点書式設定
    pDevice->SetFVF(FVF_VERTEX_2D);                                  //フォーマット設定
    pDevice->SetTexture(0, Graphic);                              //テクスチャ設定

    //---頂点バッファによる背景描画---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ボタンの初期化
//
//引数：(LPTSTR)画像のファイル名
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BUTTON::Initialize(LPTSTR filepath, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
	//---各種宣言---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

    VERTEX_2D* pVertex;

	//---初期化処理---//
	pDevice = GetDevice();
    Position = position;
    Size = size;

	//---テクスチャの読み込み---//
	hResult = D3DXCreateTextureFromFile(pDevice, filepath, &Graphic);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("ボタンの画像の取得に失敗しました"), filepath, MB_OK);
		Graphic = nullptr;
		return hResult;
	}

	//---頂点バッファの生成---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &VertexBuffer, nullptr);
	if (FAILED(hResult))
	{
		return hResult;
	}

	//---頂点バッファへの値の設定---//
	//バッファのポインタを取得
	VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	//値の設定
	for (nCounter = 0; nCounter < 4; nCounter++)
	{
		pVertex[nCounter].U = (float)(nCounter & 1);
		pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
		pVertex[nCounter].Position.x = pVertex[nCounter].U * Size.x + Position.x;
		pVertex[nCounter].Position.y = pVertex[nCounter].V * Size.y + Position.y;
		pVertex[nCounter].Position.z = 0.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//バッファのポインタの解放
	VertexBuffer->Unlock();

	return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ボタンの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BUTTON::Uninitialize(void)
{
    //---開放---//
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(Graphic)
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ボタンの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void BUTTON::Update(void)
{
    //---各種宣言---//
    D3DXVECTOR2 vecCursorPoition;

    //---初期化処理---//
    vecCursorPoition.x = (FLOAT)INPUTMANAGER::GetMousePosition().x;
    vecCursorPoition.y = (FLOAT)INPUTMANAGER::GetMousePosition().y;

    //---判定---//
    if (Position.x < vecCursorPoition.x && vecCursorPoition.x < (Position.x + Size.x))
    {
        if (Position.y < vecCursorPoition.y && vecCursorPoition.y < (Position.y + Size.y))
        {
            Behavior();
        }
    }
}