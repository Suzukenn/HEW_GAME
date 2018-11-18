#ifndef _TRAININGSCENE_H_
#define _TRAININGSCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"
#include "BaseScene.h"
#include "Debug.h"
#include "Field.h"
#include "FlexibleCamera.h"
#include "Main.h"
#include "WordMenu.h"

//�������N���X�錾������//
class TRAINING final : public BASE_SCENE
{
    private:
        FLEXIBLECAMERA FlexibleCamera;
        DEBUG Debugger;
        FIELD Field;
        WORDMENU Menu;

        bool Mode;

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(void);
        void Update(void);
};

#endif