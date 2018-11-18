#ifndef _WORDLIST_H_
#define _WORDLIST_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include "BackGround.h"
#include "Main.h"
#include "WordPlate.h"

//�������萔�E�}�N����`������//
#define DISPLAY_VALUE 3
#define WORD_VALUE 4

//�������N���X�錾������//
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