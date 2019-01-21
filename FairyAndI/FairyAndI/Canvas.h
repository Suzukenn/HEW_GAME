#ifndef _CANVAS_H_
#define _CANVAS_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Heart.h"
#include "ItemBox.h"
#include "Main.h"
#include "Player.h"
#include "Sprite.h"
#include "WordMenu.h"

//�������N���X�錾������//
class CANVAS
{
    private:
        ITEMBOX ItemBox;
        WORDPLATE Item;
        WORDMENU Menu;

        bool Mode;

        std::array<HEART, MAX_PLAYER_HP> Heart;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif