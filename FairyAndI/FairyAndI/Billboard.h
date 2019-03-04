#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include "Main.h"
#include "Transform.h"

//�������O���錾������//
class SHADER;
class TEXTURE;

//�������\���̒�`������//
typedef struct 
{
    D3DVECTOR	Position;	//���_�̈ʒu
    D3DXVECTOR2 Texture;    //�e�N�X�`��
}CUSTOMVERTEX;

//�������N���X�錾������//
class BILLBOARD
{
    protected:
        bool Gray;
        TRANSFORM Transform;
        POINT UV;

        std::array<CUSTOMVERTEX, 4> Vertex;        //���_�o�b�t�@

        std::weak_ptr<SHADER> Shader;
        std::weak_ptr<TEXTURE> Texture;

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3, POINT uv = { 1, 1 });
        void Uninitialize(void);
        void Update(void);
};

#endif