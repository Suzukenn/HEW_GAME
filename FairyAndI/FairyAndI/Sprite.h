#ifndef _SPRITE_H_
#define _SPRITE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class SPRITE
{
    protected:
        D3DXVECTOR2 Pos;                    //�ʒu���W
        D3DXVECTOR2 Size;                   //�傫��
        LPDIRECT3DTEXTURE9 Graphic;           //�e�N�X�`��
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@

    public:
        virtual void Draw(void) = 0;
        virtual HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR2, LPCWSTR) = 0;
        virtual void Uninitialize(void) = 0;
};

#endif