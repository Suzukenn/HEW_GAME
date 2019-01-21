#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//---�萔�E�}�N����`---//
#define MAX_PLAYER_HP 5
#define	VALUE_MOVE_PLAYER 5.0F

//�������O���錾������//
class OBB;

//�������N���X��`������//
class PLAYER final : public GAMEOBJECT
{
	private:
        int HP;
        D3DXVECTOR3 Move;
        ANIMATIONMODEL Model;

        OBB* Collision;

	public:
        PLAYER(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);

		static D3DXVECTOR3 GetPlayerPosition(void);
		static D3DXVECTOR3 GetPlayerRotation(void);
        static int GetPlayerHP(void);
};

#endif