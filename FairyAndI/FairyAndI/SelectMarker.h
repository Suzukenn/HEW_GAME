#ifndef _SELECTMARKER_H_
#define _SELECTMARKER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "AnimationSprite.h"

//�������N���X�錾������//
class SELECTMARKER final : protected ANIMATIONSPRITE
{
    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);
};

#endif