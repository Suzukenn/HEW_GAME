#ifndef _BUTTON_H_
#define _BUTTON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class BUTTON : protected SPRITE
{
	protected:
        virtual void Behavior(void) = 0;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2);
		void Uninitialize(void);
		void Update(void);
};

#endif