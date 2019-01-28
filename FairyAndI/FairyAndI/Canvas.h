#ifndef _CANVAS_H_
#define _CANVAS_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Heart.h"
#include "Main.h"
#include "Player.h"
#include "SkillBox.h"
#include "WordMenu.h"

//�������N���X�錾������//
class CANVAS
{
    private:
        SKILLBOX SkillBox;
        WORDPLATE Skill;
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