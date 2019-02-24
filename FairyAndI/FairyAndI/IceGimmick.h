#ifndef _ICEGIMMICK_H_
#define _ICEGIMMICK_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class OBB;

//�������N���X�錾������//
class ICEGIMMICK final : public GAMEOBJECT
{
	private:
        bool Gray;

		std::weak_ptr<MODEL> Model;
        OBB* Collision;

	public:

		ICEGIMMICK(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		~ICEGIMMICK(void);

		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);
};

#endif