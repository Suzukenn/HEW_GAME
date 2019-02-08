#ifndef _SELECTMARKER_H_
#define _SELECTMARKER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include "Main.h"

//�������N���X�錾������//
class SELECTMARKER
{
    private:
        D3DXVECTOR2 Position;            //�ʒu���W
        D3DXVECTOR2 Size;                //�傫��
        POINT UV;                                       //UV������
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;    //�e�N�X�`���ւ̃|�C���^
        std::array<VERTEX_2D, 4> Vertex;                //���_�o�b�t�@

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
        void Uninitialize(void);
        void Update(void);
};

#endif