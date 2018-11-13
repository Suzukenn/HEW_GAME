#ifndef _BUTTON_H_
#define _BUTTON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"
#include "Sprite.h"

//＝＝＝クラス宣言＝＝＝//
class BUTTON : protected SPRITE
{
	protected:
        virtual void Behavior(void) = 0;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
		void Uninitialize(void);
		void Update(void);
};

#endif