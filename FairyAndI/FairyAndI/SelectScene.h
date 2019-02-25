#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "BackImage.h"
#include "BaseScene.h"
#include "Main.h"
#include "StartButton.h"

typedef enum
{
	SELECT_STAGE1 = 0,
	SELECT_STAGE2,
	SELECT_STAGE3,
	SELECT_MAX
}SELECT_STAGE;

//＝＝＝クラス宣言＝＝＝//
class SELECTSCENE final : public BASE_SCENE
{
    private:
		BACKIMAGE Back;
		STARTBUTTON Button1;
		STARTBUTTON Button2;
		STARTBUTTON Button3;

		int Select;

		// 点滅制御用
		DWORD dwTicks;
		DWORD dwMask;

    public:
        virtual void Draw(void) final;
        virtual void Uninitialize(void) final;
        virtual HRESULT Initialize(void) final;
        virtual void Update(void) final;
};

#endif