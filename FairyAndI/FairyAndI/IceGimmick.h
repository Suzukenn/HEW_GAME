#ifndef _ICEGIMMICK_H_
#define _ICEGIMMICK_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������萔�E�}�N����`������//

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class ICEGIMMICK final : public GAMEOBJECT
{
	private:

		std::unique_ptr<MODEL> Model;
		SPHERE* Collision;

	public:

		ICEGIMMICK(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		~ICEGIMMICK();

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif