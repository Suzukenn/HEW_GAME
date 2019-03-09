#ifndef _SKILL_H_
#define _SKILL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Billboard.h"
#include "GameObject.h"
#include "Main.h"

//�������N���X�錾������//
class SKILL : public GAMEOBJECT
{
    protected:
        bool Gray;
        BILLBOARD BillBoard;
        tstring Type;

    public:
        virtual void Draw(void) PURE;
        virtual void OnCollision(COLLISION*) PURE;
        virtual void Uninitialize(void) PURE;
        virtual void Update(void) PURE;

        tstring GetType(void) { return Type; }
};

#endif