#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class COLLISION;

//�������N���X�錾������//
class GAMEOBJECT
{
    protected:
        D3DXVECTOR3 Position;                           //�ʒu���W
        D3DXVECTOR3 Rotation;                           //����
        D3DXVECTOR3 Size;                               //�傫��

        std::shared_ptr<MODEL> Model;
        COLLISION* Collision;

    public:
        GAMEOBJECT() {}
        ~GAMEOBJECT() {}
        virtual void Draw(void) = 0;
        virtual void Uninitialize(void) = 0;
        virtual void Update(void) = 0;

        virtual void OnCollision(COLLISION*) = 0;
};

#endif