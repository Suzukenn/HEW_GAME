#ifndef _WORDLIST_H_
#define _WORDLIST_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class WORDLIST
{
    private:
        BACKGROUND Back;
        std::vector<SPRITE> WordSprite;
        std::vector<bool> UnlockCheck;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif