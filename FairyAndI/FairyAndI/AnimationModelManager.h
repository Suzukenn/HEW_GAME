#ifndef _ANIMATION_MODEL_MANAGER_H_
#define _ANIMATION_MODEL_MANAGER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include <unordered_map>
#include "AnimationModel.h"
#include "FileParameter.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class ANIMATIONMODELMANAGER
{
    private:
        static std::unordered_map<tstring, std::shared_ptr<ANIMATIONMODEL>> Model;

        static HRESULT Create(const FILEPARAMETER&);
        static HRESULT Load(std::vector<FILEPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(LPCTSTR);
        static void Uninitialize(void);

        static HRESULT GetModel(LPCTSTR, std::shared_ptr<ANIMATIONMODEL>&);

};

#endif