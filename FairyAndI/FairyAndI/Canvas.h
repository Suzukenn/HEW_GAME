#ifndef _CANVAS_H_
#define _CANVAS_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <list>
#include "ItemBox.h"
#include "Main.h"
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

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif