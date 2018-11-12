#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class DIRECTIONALLIGHT
{
    private:
        static D3DLIGHT9 Light;

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);
};

#endif