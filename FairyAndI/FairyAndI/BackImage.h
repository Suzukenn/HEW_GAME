#ifndef _BACKIMAGE_H_
#define _BACKIMAGE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class BACKIMAGE final : private SPRITE
{
	public:
		void Draw(void);
		void Uninitialize(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR2 position = D3DXVECTOR2(0.0F, 0.0F), D3DXVECTOR2 size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		void Update(void);
};

#endif 
