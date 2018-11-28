#ifndef _WORDLIST_H_
#define _WORDLIST_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "WordPlate.h"

//�������萔�E�}�N����`������//
#define DISPLAY_VALUE 3

//�������N���X�錾������//
class WORDLIST
{
    private:
        BACKGROUND Back;
        int SelectNumber;
        std::array<WORDPLATE, DISPLAY_VALUE> WordPlate;
        std::vector<tstring> WordList;


    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, std::vector<tstring>&, D3DXVECTOR2, D3DXVECTOR2);
        void ResetTexture(void);
        void Update(void);

        tstring GetSelectWord(void) { return WordList.at(SelectNumber); }
        HRESULT ResetWordNumber(tstring);
};

#endif