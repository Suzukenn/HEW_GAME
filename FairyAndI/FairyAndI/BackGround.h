#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Sprite.h"

//�������N���X�錾������//
class BACKGROUND final : private SPRITE
{

	public:
		void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR2 position = D3DXVECTOR2(0.0F, 0.0F), D3DXVECTOR2 size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
        void Update(void);
		int CreateBillboard(LPD3DXVECTOR3 pos, LPD3DXVECTOR3 vel);
		void ReleaseBillboard(int nBillboard);
};

#endif