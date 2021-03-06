//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackGround.h"
#include "InputManager.h"
#include "Player.h"
#include "TextureManager.h"
#include "SideViewCamera.h"
#include "SquareGauge.h"

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
    Billboard.Draw(Position);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：背景の初期化
//
//引数：(LPCTSTR)テクスチャ名,(D3DXVECTOR3)位置,(D3DXVECTOR2)大きさ
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
    //---各種宣言---//
    HRESULT hResult;

    //---初期化処理---//
    Position = position;

    hResult = Billboard.Initialize(texturename, scale);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("背景の初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
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
    Billboard.Uninitialize();
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：背景の更新
//
//引数：(float)移動量
//
//戻り値：なし
/////////////////////////////////////////////
void BACKGROUND::Update(float value, bool nonstickmove)
{
    //---各種宣言---//
    float Stick;

    if (PLAYER::GetPlayerState() == PLAYERSTATE_ATTACK || PLAYER::GetPlayerState() == PLAYERSTATE_DAMAGE)
    {
        return;
    }
	else if (SQUAREGAUGE::GetFairyTime())
	{
		return;
	}

	Position.x = PLAYER::GetPlayerPosition().x;

    Stick = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT).x;

    if (Stick)
    {
        if (Position.x < 0.0F)
        {
            Position.x = 0.0F;
            if (nonstickmove)
            {
                Billboard.MoveTexture(value);
            }
        }
        else if (Position.x > 1500.0F)
        {
            if (nonstickmove)
            {
                Billboard.MoveTexture(value);
            }
        }
        else
        {
            Billboard.MoveTexture(value * Stick);
        }
    }
    else
    {
        if (nonstickmove)
        {
            Billboard.MoveTexture(value);
        }
    }
    Billboard.Update();
}