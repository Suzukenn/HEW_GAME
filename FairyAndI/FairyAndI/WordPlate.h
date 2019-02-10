#ifndef _WORDPLATE_H_
#define _WORDPLATE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"

//�������N���X�錾������//
class WORDPLATE
{
    private:
        D3DXVECTOR2 Position;            //�ʒu���W
        D3DXVECTOR2 Size;                //�傫��
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;		    //�e�N�X�`���ւ̃|�C���^
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//���_�o�b�t�@�ւ̃|�C���^

    public:
        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2 size = D3DXVECTOR2(130.0F, 130.0F));
        void Update(void);

        HRESULT SetTexture(tstring);
};

#endif