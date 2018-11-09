#ifndef _BUTTON_H_
#define _BUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class BUTTON
{
	protected:
        D3DXVECTOR2 Position;				    //�{�^���̈ʒu
        D3DXVECTOR2 Size;				        //�{�^���̑傫��
        LPDIRECT3DTEXTURE9 Graphic;				//�e�N�X�`��
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;	//���_�o�b�t�@

        virtual void Behavior(void) = 0;

	public:
        void Draw(void);
		HRESULT Initialize(LPTSTR, D3DXVECTOR2, D3DXVECTOR2);
		void Uninitialize(void);
		void Update(void);
};

#endif