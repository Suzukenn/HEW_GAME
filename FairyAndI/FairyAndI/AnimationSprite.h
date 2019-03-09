#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include "Main.h"

//�������O���錾������//
class TEXTURE;

//�������N���X�錾������//
class ANIMATIONSPRITE
{
    protected:
        D3DXVECTOR2 Position;            //�ʒu���W
        D3DXVECTOR2 Size;                //�傫��
        POINT UV;                                       //UV������
        
        std::array<VERTEX_2D, 4> Vertex;                //���_�o�b�t�@

        std::weak_ptr<TEXTURE> Texture;    //�e�N�X�`���ւ̃|�C���^

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT uv = { 1, 1 });
		void SetPosition(D3DXVECTOR2);
        void SetSpriteUV(int);
        virtual void Uninitialize(void);
};

#endif