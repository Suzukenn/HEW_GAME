#ifndef _PLAYER_H_
#define _PLAYER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//---�萔�E�}�N����`---//
#define	VALUE_MOVE_PLAYER 5.0F

//�������O���錾������//
class OBB;

//�������N���X��`������//
class PLAYER final : public GAMEOBJECT
{
	private:
        D3DXVECTOR3 Move;

        ANIMATIONMODEL Model;

        OBB* Collision;

	public:
        PLAYER(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);

		static const D3DXVECTOR3 GetPlayerPosition(void);
		static const D3DXVECTOR3 GetPlayerRotation(void);
};

#endif