#ifndef _WORDLIST_H_
#define _WORDLIST_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include <memory>
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "WordPlate.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define DISPLAY_VALUE 3

//＝＝＝クラス宣言＝＝＝//
class WORDLIST
{
    private:
        BACKGROUND Back;
        int SelectNumber;
        std::array<WORDPLATE, DISPLAY_VALUE> WordPlate;
        std::vector<tstring> WordList;

        void ResetTexture(void);

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, std::vector<tstring>&, D3DXVECTOR2, D3DXVECTOR2);
        void Update(void);

        LPCTSTR GetSelectItem(void) { return WordList.at(SelectNumber).data(); }
};

#endif