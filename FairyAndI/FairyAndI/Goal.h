#ifndef _GOAL_H_
#define _GOAL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"

//�������O���錾������//
class MODEL;
class SHADER;
class SPHERE;

//�������N���X�錾������//
class GOAL final : public GAMEOBJECT
{
	private:
        bool Gray;

        std::weak_ptr<MODEL> Model;
        std::weak_ptr<SHADER> Shader;
        SPHERE* Collision;

		int Goal;

	public:
		GOAL(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        ~GOAL(void);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);
};

#endif