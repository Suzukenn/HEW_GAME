#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class DIRECTIONALLIGHT
{
    private:
        static D3DLIGHT9 Light;

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);
};

#endif