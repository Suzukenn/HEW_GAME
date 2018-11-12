#ifndef _SPRITE_H_
#define _SPRITE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Main.h"

//�������N���X�錾������//
class SPRITE
{
    private:
        LPDIRECT3DVERTEXBUFFER9 VertexBuffer; //���_�o�b�t�@

    protected:
        D3DXVECTOR2 Position;            //�ʒu���W
        D3DXVECTOR2 Size;                //�傫��
        LPDIRECT3DTEXTURE9 Texture;      //�e�N�X�`��
        std::array<VERTEX_2D, 4> Vertex; //���_���

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(D3DXVECTOR2, D3DXVECTOR2, LPCTSTR);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif