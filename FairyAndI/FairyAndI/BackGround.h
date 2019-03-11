#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Billboard.h"
#include "Main.h"

//�������N���X�錾������//
class BACKGROUND
{
    private:
        D3DXVECTOR3 Position;
        BILLBOARD Billboard;

	public:
		void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR2);
        void Update(float value = 0.0F);
};

#endif