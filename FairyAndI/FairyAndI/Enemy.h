#ifndef _ENEMY_H_
#define _ENEMY_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//�������񋓌^��`������//
//typedef enum
//{
//	ENEMYSTATE_NORMAL,
//	ENEMYSTATE_BATTLE,
//	ENEMYSTATE_RETURN,
//	MAX_ENEMYSTATE
//} ENEMYSTATE;

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class ENEMY : public GAMEOBJECT
{
	protected:
        int AttackCool;
        bool Gray;

		std::shared_ptr<ANIMATIONMODEL> Model;
		SPHERE* Collision;

		//ENEMYSTATE StateType;

	public:
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
        bool SearchTarget(D3DXVECTOR3, float);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);
};

#endif