//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Button.h"
#include "InputManager.h"
#include "TextureManager.h"

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
    SPRITE::Draw();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：ボタンの初期化
//
//引数：(LPCTSTR)画像のファイル名,(D3DXVECTOR2)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BUTTON::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("ボタンの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return hResult;
    }

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
    SPRITE::Uninitialize();
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
    ////---各種宣言---//
    //D3DXVECTOR2 vecCursorPoition;

    ////---初期化処理---//
    //vecCursorPoition.x = (FLOAT)INPUTMANAGER::GetMousePosition().x;
    //vecCursorPoition.y = (FLOAT)INPUTMANAGER::GetMousePosition().y;

    ////---判定---//
    //if (Position.x < vecCursorPoition.x && vecCursorPoition.x < (Position.x + Size.x))
    //{
    //    if (Position.y < vecCursorPoition.y && vecCursorPoition.y < (Position.y + Size.y))
    //    {
            Behavior();
       /* }
    }*/
}