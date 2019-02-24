#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Billboard.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class BACKGROUND final : protected BILLBOARD 
{
	public:
		void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3 position = D3DXVECTOR3(0.0F, 0.0F, 0.0F), D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0F));
        void Update(void);
		int CreateBillboard(LPD3DXVECTOR3 pos, LPD3DXVECTOR3 vel);
		void ReleaseBillboard(int nBillboard);
};

#endif