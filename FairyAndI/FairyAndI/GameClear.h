#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Main.h"

//�������N���X�錾������//
class GAMECLEAR final : public BASE_SCENE
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