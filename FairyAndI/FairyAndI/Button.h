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
        virtual void Behavior(void) PURE;

	public:
        void Draw(void) override;
		HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2) override;
		void Uninitialize(void) override;
		void Update(void);
};

#endif