#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <unordered_map>
#include "FileParameter.h"
#include "Main.h"
#include "Model.h"

//＝＝＝クラス宣言＝＝＝//
class ITEMMANAGER
{
    private:
        static std::unordered_map<int, MODEL*> Item;

        static HRESULT Create(const FILEPARAMETER&);
        static HRESULT Load(std::vector<FILEPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(LPCTSTR);
        static void Uninitialize(void);

        static HRESULT Instantiate(LPCTSTR, MODEL*);
};

#endif