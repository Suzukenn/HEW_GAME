#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class BASE_SCENE
{
    public:
        virtual void Draw(void) PURE;
        virtual void Uninitialize(void) PURE;
        virtual HRESULT Initialize(void) PURE;
        virtual void Update(void) PURE;
};

#endif