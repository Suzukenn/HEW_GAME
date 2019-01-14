#ifndef _ELEMENT_H_
#define _ELEMENT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class OBB;

//�������N���X�錾������//
class ELEMENT final : private GAMEOBJECT
{
	private:
        tstring Type;

        std::weak_ptr<MODEL> Model;
        OBB* Collision;
        LPCTSTR Name;

	public:
        ELEMENT(LPCTSTR, tstring, D3DXVECTOR3);
        ~ELEMENT(void);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);
};

#endif