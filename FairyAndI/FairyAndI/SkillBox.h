#ifndef _SKILLBOX_BOX_H_
#define _SKILLBOX_BOX_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "AnimationSprite.h"

//�������N���X�錾������//
class SKILLBOX final : private ANIMATIONSPRITE
{
    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        void Uninitialize(void);
        void Update(void);
};

#endif