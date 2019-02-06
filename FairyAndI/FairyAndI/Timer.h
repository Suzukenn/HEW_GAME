#ifndef _TIMER_H_
#define _TIMER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"
#include "Sprite.h"

#define MAX_LENGTH (3)		//最大桁数

//＝＝＝クラス宣言＝＝＝//
class TIMER : protected SPRITE
{
    private:
		int Timer;
		int Length;
		std::array<VERTEX_2D, 4 * MAX_LENGTH> Vertex;                //頂点バッファ

    public:
		void Draw(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, int);
		void Uninitialize(void);
		void Update(void);
};

#endif