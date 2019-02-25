#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Billboard.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class BACKGROUND final : protected BILLBOARD 
{
    private:

	public:
		void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);
};

#endif