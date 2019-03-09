#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include <memory>
#include "GameObject.h"
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
        D3DXVECTOR2 Scale;
        POINT UV;
        bool Gray;
        bool Inverted;

        std::array<CUSTOMVERTEX, 4> Vertex;        //���_�o�b�t�@

        std::weak_ptr<SHADER> Shader;
        std::weak_ptr<TEXTURE> Texture;

    public:
        void Draw(D3DXVECTOR3);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2, bool inverted = false, POINT uv = { 1, 1 });
        void SetUV(int);
        void Uninitialize(void);
        void Update(void);
};

#endif