#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"

//�������N���X�錾������//
class GAME final : public BASE_SCENE
{
    private:
        BACKGROUND Back;

    public:
        void Draw(void) final;
        void Uninitialize(void) final;
        HRESULT Initialize(void) final;
        void Update(void) final;
};

#endif