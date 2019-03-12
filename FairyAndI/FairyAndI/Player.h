#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//---�萔�E�}�N����`---//
#define MAX_PLAYER_HP 5
#define	VALUE_MOVE_PLAYER 0.5F

//�������O���錾������//
class SPHERE;

//�������N���X��`������//
class PLAYER final : public GAMEOBJECT
{
	private:
        int HP;
        int State;
        int Vibration;
        bool Gray;
        D3DXVECTOR3 Move;
        std::shared_ptr<ANIMATIONMODEL> Model;

        SPHERE* Collision;

	public:
        PLAYER(D3DXVECTOR3, D3DXVECTOR3);

        void Draw(void);
		HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);

		static D3DXVECTOR3 GetPlayerPosition(void);
		static D3DXVECTOR3 GetPlayerRotation(void);
        static int GetPlayerHP(void);
};

#endif