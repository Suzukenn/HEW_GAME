#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Billboard.h"
#include "Main.h"
#include "Transform.h"

//＝＝＝クラス宣言＝＝＝//
class BACKGROUND
{
    private:
        D3DXVECTOR3 Position;
        BILLBOARD Billboard;

	public:
		void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR2);
        void Update(void);

        virtual void OnCollision(COLLISION*) = delete;
};

#endif