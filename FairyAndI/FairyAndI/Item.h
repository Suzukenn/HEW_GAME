#ifndef _ITEM_H_
#define _ITEM_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������N���X�錾������//
class ITEM final : private GAMEOBJECT
{
	private:
        LPCTSTR Name;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);
};

#endif