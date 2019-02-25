#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SELECTSCENE final : public BASE_SCENE
{
    private:
        BACKIMAGE Back;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif