#ifndef _SPRITE_H_
#define _SPRITE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Base2DObjeck.h"
#include "Main.h"

//�������N���X�錾������//
class SPRITE : protected BASE2DOBJECT 
{
    protected:
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;		    //�e�N�X�`���ւ̃|�C���^
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//���_�o�b�t�@�ւ̃|�C���^

    public:
        virtual void Draw(void);
        virtual HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        virtual void Uninitialize(void);
        virtual void Update(void);
};

#endif