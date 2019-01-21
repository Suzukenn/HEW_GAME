#ifndef _BATTERYGIMMICK_H_
#define _BATTERYGIMMICK_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class SPHERE;
//class OBB;
//�������N���X�錾������//
class BATTERYGIMMICK final : public GAMEOBJECT
{
	private:

		std::weak_ptr<MODEL> Model;
		SPHERE* Collision;
		//OBB* Collision;

	public:

		BATTERYGIMMICK(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		~BATTERYGIMMICK(void);

		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif