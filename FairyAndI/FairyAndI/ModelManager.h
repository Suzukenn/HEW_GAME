#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <unordered_map>
#include "FileParameter.h"
#include "Main.h"
#include "Model.h"

//＝＝＝クラス宣言＝＝＝//
class MODELMANAGER
{
    private:
        static std::unordered_map<tstring, std::shared_ptr<MODEL>> Model;

        static HRESULT Create(const FILEPARAMETER&);
        static HRESULT Load(std::vector<FILEPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(LPCTSTR);
        static void Uninitialize(void);

        static HRESULT GetModel(tstring, std::weak_ptr<MODEL>&);

        friend MODEL;
};

#endif