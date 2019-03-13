#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class ENEMYBULLET final : public GAMEOBJECT
{
    private:
        bool Gray;
        D3DXVECTOR3 Move;
        DWORD BornTime;

        std::weak_ptr<MODEL> Model;
        std::weak_ptr<SHADER> Shader;
        SPHERE* Collision;

    public:
        ENEMYBULLET(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        ~ENEMYBULLET(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif