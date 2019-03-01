#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include "Main.h"
#include "Transform.h"

//�������O���錾������//
class TEXTURE;

//�������\���̒�`������//
typedef struct 
{
    D3DVECTOR	Position;	//���_�̈ʒu
    D3DCOLOR	Color;	    //���_�̐F
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

        LPD3DXEFFECT Effect;
        std::weak_ptr<TEXTURE> Texture;		    //�e�N�X�`���ւ̃|�C���^

    public:
        void Draw(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3, POINT uv = { 1, 1 });
        void Uninitialize(void);
        void Update(void);
};

#endif