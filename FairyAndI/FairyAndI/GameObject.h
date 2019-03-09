#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Transform.h"

//�������O���錾������//
class COLLISION;

//�������N���X�錾������//
class GAMEOBJECT
{
    protected:
        TRANSFORM Transform;
        tstring Tag;

    public:
        GAMEOBJECT(void) {}
        ~GAMEOBJECT(void) {}
        virtual void Draw(void) PURE;
        virtual void OnCollision(COLLISION*) PURE;
        virtual void Uninitialize(void) PURE;
        virtual void Update(void) PURE;

        D3DXVECTOR3 GetPosition(void) { return Transform.Position; }
        tstring GetTag(void) { return Tag; }
};

#endif