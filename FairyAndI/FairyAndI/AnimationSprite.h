#ifndef _ANIMATIONSPRITE_H_
#define _ANIMATIONSPRITE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Base2DObjeck.h"
#include "Main.h"

//�������N���X�錾������//
class ANIMATIONSPRITE : protected BASE2DOBJECT
{
    protected:
        POINT UV;                                       //UV������
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //�e�N�X�`���ւ̃|�C���^
        std::array<VERTEX_2D, 4> Vertex;                //���_�o�b�t�@

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2, POINT);
        virtual void SetSpriteUV(int);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif