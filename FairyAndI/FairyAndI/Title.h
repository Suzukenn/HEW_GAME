#ifndef _TITLE_H_
#define _TITLE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"
#include "StartButton.h"

//�������N���X�錾������//
class TITLE final : public BASE_SCENE
{
    private:
        BACKGROUND Back;
        STARTBUTTON StartButton;

    public:
        void Draw(void) final;
        void Uninitialize(void) final;
        HRESULT Initialize(void) final;
        void Update(void) final;
};

#endif