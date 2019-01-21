//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "DirectionalLight.h"
#include "Main.h"

//＝＝＝グローバル宣言＝＝＝//
D3DLIGHT9 DIRECTIONALLIGHT::Light;

//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ライトの初期化
//
//引数：(D3DXVECTOR3)位置,(D3DXVECTOR3)注視点
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT DIRECTIONALLIGHT::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;
    D3DXVECTOR3 vecDirection;
    LPDIRECT3DDEVICE9 pDevice;

    //---初期化処理---//
    pDevice = GetDevice();
    memset(&Light, 0, sizeof(D3DLIGHT9));

    //---ディレクショナルライトの設定---//
    //ライトタイプ
    Light.Type = D3DLIGHT_DIRECTIONAL;

    //拡散光
    Light.Diffuse = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);

    //環境光
    Light.Ambient = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);

    //方向
    vecDirection = D3DXVECTOR3(0.0F, -0.6F, 1.0F);
    D3DXVec3Normalize(&vecDirection, &vecDirection);
    Light.Direction = vecDirection;

    //レンダリングパイプラインに設定
    hResult = pDevice->SetLight(0, &Light);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ライトをレンダリングパイプラインに設定できませんでした"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    // ライトの反映
    hResult = pDevice->LightEnable(0, TRUE);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ライトの反映に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---ライティングモードの設定---//
    hResult = pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ライティングモードの設定に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//関数名：Uninitialize
//
//機能：ライトの終了
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DIRECTIONALLIGHT::Uninitialize(void)
{

}

/////////////////////////////////////////////
//関数名：Update
//
//機能：ライトの更新
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DIRECTIONALLIGHT::Update(void)
{

}