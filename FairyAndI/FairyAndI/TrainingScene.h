#ifndef _TRAININGSCENE_H_
#define _TRAININGSCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BaseScene.h"
#include "Canvas.h"
#include "Field.h"
#include "FlexibleCamera.h"
#include "Ground.h"
#include "Main.h"

//�������N���X�錾������//
class TRAINING final : public BASE_SCENE
{
    private:
        CANVAS Canvas;
        FIELD Field;
        GROUND Ground;
        FLEXIBLECAMERA FlexibleCamera;

        bool Mode;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif