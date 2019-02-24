#ifndef _GROUND_H_
#define _GROUND_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Transform.h"

//�������O���錾������//
class TEXTURE;

//�������N���X�錾������//
class GROUND
{
    private:
        TRANSFORM Transform;
        int PolygonValue;
        int VertexValue;

        std::weak_ptr<TEXTURE> Texture;		                    //�e�N�X�`���ւ̃|�C���^
        std::unique_ptr<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;	//���_�o�b�t�@�ւ̃|�C���^
        std::unique_ptr<LPDIRECT3DINDEXBUFFER9> IndexBuffer;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

        HRESULT MakeVertex(int, int, float, float);

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, const int&, const int&, const float&, const float&);
        void Uninitialize(void);
};

#endif