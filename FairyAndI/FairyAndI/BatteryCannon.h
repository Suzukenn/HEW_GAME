#ifndef _BATTERY_CANNON_H_
#define _BATTERY_CANNON_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class BATTERYCANNON final : public GAMEOBJECT
{
    public:
        D3DXVECTOR3 Move;
        DWORD BornTime;

        std::weak_ptr<MODEL> Model;
        SPHERE* Collision;

        BATTERYCANNON(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        ~BATTERYCANNON(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif