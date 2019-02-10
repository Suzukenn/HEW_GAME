#ifndef _FIREGIMMICK_H_
#define _FIREGIMMICK_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class OBB;

//�������N���X�錾������//
class FIREGIMMICK final : public GAMEOBJECT
{
	private:
		std::weak_ptr<MODEL> Model;
        OBB* Collision;

	public:

		FIREGIMMICK(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		~FIREGIMMICK(void);

		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif