#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class BASE_SCENE
{
    public:
        virtual void Draw(void) PURE;
        virtual void Uninitialize(void) PURE;
        virtual HRESULT Initialize(void) PURE;
        virtual void Update(void) PURE;
};

#endif