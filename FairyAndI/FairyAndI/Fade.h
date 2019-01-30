#ifndef _FADE_H_
#define _FADE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADETYPE;

//＝＝＝クラス宣言＝＝＝//
class FADE
{
    private:
		static int Fade;
		static int Alpha;
		static int Directory;
		static std::array<VERTEX_2D, 4> Vertex;                //頂点バッファ

    public:
		static void Draw(void);
		static HRESULT Initialize(void);
		static void Uninitialize(void);
		static void Update(void);

		static void SetFade(FADETYPE);
		static int CheckFadeEnd(FADETYPE);
};

#endif