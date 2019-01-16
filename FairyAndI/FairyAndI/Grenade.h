#ifndef _GRENADE_H_
#define _GRENADE_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class GRENADE final : public GAMEOBJECT
{
	public:
		DWORD BornTime;
		D3DXVECTOR3 Move;

		std::weak_ptr<MODEL> Model;
		SPHERE* Collision;

		GRENADE(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		~GRENADE(void);

		void Draw(void);
		void Uninitialize(void);
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Update(void);

		void OnCollision(COLLISION*);
};

#endif
