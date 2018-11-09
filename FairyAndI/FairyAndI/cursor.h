#ifndef _CURSOR_H_
#define _CURSOR_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "main.h"
#include "title.h"
//＝＝＝クラス定義＝＝＝//
class CURSOR
{
	private:
		float Pos_X;		//X座標
		float Pos_Y;		//Y座標
		float Width;		//幅
		float Height;		//高さ
		UI_TEX Texture;		//テクスチャ
		KPADStatus* Input;	//コントローラ情報
		
		bool CheckPush(BUTTON*);
		
	public:
		void Draw(void);
        void Initialize(float, float, float, float, UI_TEX);
		void Update(BUTTON*);
};

#endif