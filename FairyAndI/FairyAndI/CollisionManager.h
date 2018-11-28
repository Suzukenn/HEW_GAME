#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <list>
#include <vector>
#include "Collision.h"
#include "FileParameter.h"
#include "GameObject.h"
#include "Main.h"

//�������N���X�錾������//
class COLLISIONMANAGER
{
    private:
        static std::list<COLLISION*> Collision;

    public:
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);

        static void Instantiate(tstring);
};

#endif