#ifndef _POSITION_H_
#define _POSITION_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class POSITION
{
    private:
        D3DXVECTOR2 Position;

    public:
        void Draw(void);
        HRESULT Initialize(void);
        void Update(void);
        void Uninitialize(void);
};

#endif