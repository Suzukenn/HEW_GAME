//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <revolution.h>
#include <demo.h>
#include <math.h>
#include "button.h"
#include "cursor.h"
#include "sound.h"
#include "soundwii5.h"

//＝＝＝関数定義＝＝＝//
///////////////////////////////////
//関数名：Checkhit
//
//機能：選択判定
//
//引数：(BUTTON*)ボタン情報
//
//戻り値：(bool)判定結果
///////////////////////////////////
bool CURSOR::CheckPush(BUTTON* button)
{
	//---各種宣言---//
	int nCounter;
	
    for (nCounter = 0; nCounter < 2; nCounter++)
    {		
	    if (Pos_X + Width > button[nCounter].D_Pos_X && Pos_X < button[nCounter].D_Pos_X + button[nCounter].D_Width)
	    {
	        if (Pos_Y + Height > button[nCounter].D_Pos_Y && Pos_Y < button[nCounter].D_Pos_Y + button[nCounter].D_Height)
	        {
	       		button[nCounter].Push = true;
	            return true;
	        }
	    }
    }
    return false;
}

///////////////////////////////////
//関数名：Draw
//
//機能：カーソルの描画処理
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
void CURSOR::Draw(void)
{	
    //---テクスチャの設定---//

    //テクスチャの取得
    GXLoadTexObj(GetUITex(TEXTURE_UI_CURSOR), GX_TEXMAP0);

    //---描画---//

    //正方形の生成
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    //頂点1
    GXPosition2f32(Pos_X, Pos_Y);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(0.0F, 0.0F);

    //頂点2
    GXPosition2f32(Pos_X + Width, Pos_Y);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(1.0F, 0.0F);

    //頂点3
    GXPosition2f32(Pos_X + Width, Pos_Y + Height);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(1.0F, 1.0F);

    //頂点4
    GXPosition2f32(Pos_X, Pos_Y + Height);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(0.0F, 1.0F);

    GXEnd();
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：カーソルの初期化
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void CURSOR::Initialize(float x, float y, float width, float height, UI_TEX texture)
{
    Pos_X = x;
    Pos_Y = y;
    Width = width;
    Height = height;
    Texture = texture;
    Input = GetKPAD();
}

///////////////////////////////////
//関数名：Update
//
//機能：カーソルの更新
//
//引数：なし
//
//戻り値：なし
///////////////////////////////////
void CURSOR::Update(BUTTON* button)
{	
    //---照準操作---//
    Pos_X = Input->pos.x * SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2;
    Pos_Y = Input->pos.y * SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2;

    //---ボタン入力判定---//
    if (Input->trig & KPAD_BUTTON_B)
    {
    	if(CheckPush(button))
    	{
    		PlaySound(SE_SHOT, FALSE);	
    	}
    }
}