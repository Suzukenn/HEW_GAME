#ifndef _GAME_SCENE_03_H_
#define _GAME_SCENE_03_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"

//�������N���X�錾������//
class GAME03 final : public BASE_SCENE
{
    private:
        BACKGROUND Back;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif