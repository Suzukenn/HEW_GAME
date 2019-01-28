#ifndef _WORD_MANAGER_H
#define _WORD_MANAGER_H

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <unordered_map>
#include <memory>
#include "FileParameter.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class WORDMANAGER
{
    private:
        static std::unordered_map<tstring, LPDIRECT3DTEXTURE9> NounTexture;
        static std::unordered_map<tstring, LPDIRECT3DTEXTURE9> AdjectiveTexture;
        static std::unordered_map<tstring, bool> NounLock;
        static std::unordered_map<tstring, bool> AdjectiveLock;
        static std::unordered_map<tstring, tstring> NounToAdjective;
        static std::unordered_map<tstring, LPDIRECT3DTEXTURE9> SkillTexture;
        static std::unordered_map<tstring, bool> SkillLock;

        static HRESULT CreatePair(void);
        static HRESULT CreateTexture(std::unordered_map<tstring, LPDIRECT3DTEXTURE9>&, const FILEPARAMETER&);
        static HRESULT LoadTexture(std::vector<FILEPARAMETER>&, LPCTSTR);

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static HRESULT UnLockWord(LPCTSTR);
        static void Update(void);

        static HRESULT GetWordLock(tstring, bool&);
        static HRESULT GetWordTexture(tstring, LPDIRECT3DTEXTURE9&);
};

#endif