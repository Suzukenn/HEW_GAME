#ifndef _FIELD_H_
#define _FIELD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"

//�������N���X�錾������//
class FIELD
{
    private:
        D3DXVECTOR3 Position;					                //�ʒu
        D3DXVECTOR3 Rotation;					                //����
        std::unique_ptr<LPDIRECT3DTEXTURE9> Texture;		    //�e�N�X�`���ւ̃|�C���^
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//���_�o�b�t�@�ւ̃|�C���^
        std::unique_ptr<LPDIRECT3DINDEXBUFFER9> IndexBuffer;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
        int PolygonValue;
        int VertexValue;

        HRESULT MakeVertex(const LPDIRECT3DDEVICE9&, const int&, const int&, const float&, const float&);

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, const int&, const int&, const float&, const float&);
        void Uninitialize(void);
        void Update(void);
};

#endif