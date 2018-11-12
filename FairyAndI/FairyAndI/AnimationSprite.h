#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class ANIMATIONSPRITE : private SPRITE
{
    private:
        POINT UV;                        //UV������

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(D3DXVECTOR2, D3DXVECTOR2, POINT, LPCTSTR);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif