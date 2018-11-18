#ifndef _WORDLIST_H_
#define _WORDLIST_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include "BackGround.h"
#include "Main.h"
#include "WordPlate.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define DISPLAY_VALUE 3
#define WORD_VALUE 4

//＝＝＝クラス宣言＝＝＝//
class WORDLIST
{
    private:
        BACKGROUND Back;
        int SelectNumber;
        std::array<WORDPLATE, DISPLAY_VALUE> WordPlate;
        std::array<LPCTSTR, WORD_VALUE> WordList;
        std::array<bool, WORD_VALUE> UnlockCheck;

        void ResetTexture(void);

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, LPCTSTR*, D3DXVECTOR2, D3DXVECTOR2);
        void Update(void);

        LPCTSTR& GetSelectItem(void) { return WordList.at(SelectNumber); }
};

#endif