#ifndef _WORDPLATE_H_
#define _WORDPLATE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class WORDPLATE final : protected SPRITE
{
    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2 size = D3DXVECTOR2(130.0F, 130.0F));
        void Update(void);

        HRESULT SetTexture(LPCTSTR);
};

#endif