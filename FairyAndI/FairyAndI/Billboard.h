#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Main.h"

//�������N���X�錾������//
class BILLBOARD
{
    protected:
        POINT UV;

        LPDIRECT3DTEXTURE9 Texture;		        //�e�N�X�`���ւ̃|�C���^
        std::array<VERTEX_3D, 4> Vertex;        //���_�o�b�t�@

    public:
        void Draw(D3DXVECTOR3);
        HRESULT Initialize(LPCTSTR, POINT);
        void Uninitialize(void);
        void Update(DWORD);
};

#endif