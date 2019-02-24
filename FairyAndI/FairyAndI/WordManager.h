#ifndef _WORD_MANAGER_H
#define _WORD_MANAGER_H

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <unordered_map>
#include <memory>
#include "FileParameter.h"
#include "Main.h"

class TEXTURE;

//�������N���X�錾������//
class WORDMANAGER
{
    private:
        static std::unordered_map<tstring, bool> NounLock;
        static std::unordered_map<tstring, bool> AdjectiveLock;
        static std::unordered_map<tstring, bool> SkillLock;
        static std::unordered_map<tstring, tstring> NounToAdjective;

        static HRESULT CreateWord(void);

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static HRESULT UnLockWord(LPCTSTR);
        static void Update(void);

        static HRESULT GetWordLock(LPCTSTR, bool&);
        static HRESULT GetWordTexture(LPCTSTR, std::weak_ptr<TEXTURE>&);
};

#endif