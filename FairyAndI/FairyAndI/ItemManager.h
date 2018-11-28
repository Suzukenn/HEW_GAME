#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <unordered_map>
#include "FileParameter.h"
#include "Main.h"
#include "Model.h"

//�������N���X�錾������//
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