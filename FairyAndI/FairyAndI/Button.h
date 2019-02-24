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
        virtual void Behavior(void) PURE;

	public:
        void Draw(void) override;
		HRESULT Initialize(LPCTSTR, D3DXVECTOR2, D3DXVECTOR2) override;
		void Uninitialize(void) override;
		void Update(void);
};

#endif