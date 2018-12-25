#ifndef _BULLET_H_
#define _BULLET_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"

class SPHERE;

//�������N���X�錾������//
class BULLET final : public  GAMEOBJECT
{
    public:
        std::unique_ptr<MODEL> Model;

        D3DXVECTOR3 Move;

        SPHERE* Collision;

        BULLET(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~BULLET(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif