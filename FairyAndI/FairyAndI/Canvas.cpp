//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Canvas.h"
#include "InputManager.h"

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
void CANVAS::Draw(void)
{
    ItemBox.Draw();
    Item.Draw();
    if (Mode)
    {
        Menu.Draw();
    }
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：なし
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT CANVAS::Initialize(void)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = WORDMENU::Initialize();
    if (FAILED(hResult))
    {
        return hResult;
    }

    //アイテムボックス
    hResult = ItemBox.Initialize(TEXT("ITEMBOX"), D3DXVECTOR2(1050.0F, 10.0F), D3DXVECTOR2(150.0F, 150.0F), { 2, 1 });
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アイテムボックスの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }
    //アイテム
    hResult = Item.Initialize(TEXT("UNKNOWN"), D3DXVECTOR2(1060.0F, 15.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("アイテムの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        Uninitialize();
        return hResult;
    }


    Mode = false;

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
void CANVAS::Uninitialize(void)
{
    ItemBox.Uninitialize();
    Item.Uninitialize();
    Menu.Uninitialize();
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
void CANVAS::Update(void)
{
    //---表示モード切り替え---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER) || INPUTMANAGER::GetKey(DIK_A, TRIGGER))
    {
        Mode = !Mode;
    }


    if (Mode)
    {
        Menu.Update();
        Item.Update();
        Item.SetTexture(WORDMENU::NotificationItem());
    }
    else
    {
        ItemBox.Update();
    }
}