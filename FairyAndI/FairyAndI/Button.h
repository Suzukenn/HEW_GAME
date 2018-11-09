#ifndef _BUTTON_H_
#define _BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class BUTTON
{
	protected:
        D3DXVECTOR2 Position;				    //ボタンの位置
        D3DXVECTOR2 Size;				        //ボタンの大きさ
        LPDIRECT3DTEXTURE9 Graphic;				//テクスチャ
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//頂点バッファ

        virtual void Behavior(void) = 0;

	public:
        void Draw(void);
		HRESULT Initialize(LPTSTR, D3DXVECTOR2, D3DXVECTOR2);
		void Uninitialize(void);
		void Update(void);
};

#endif