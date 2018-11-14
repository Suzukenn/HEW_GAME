#ifndef _WORDMENU_H_
#define _WORDMENU_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <vector>
#include "BackGround.h"
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class WORDMENU
{
    private:
        SPRITE Back;
        std::vector<SPRITE> Item;
        std::vector<bool> Unlockcheck;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif