#ifndef _GAME_SCENE_01_H_
#define _GAME_SCENE_01_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Canvas.h"
#include "Field.h"
#include "Main.h"

//�������N���X�錾������//
class GAME01 final : public BASE_SCENE
{
    private:
        BACKGROUND Background_Back;
        BACKGROUND Background_Front;
        CANVAS Canvas;
        FIELD Field;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif