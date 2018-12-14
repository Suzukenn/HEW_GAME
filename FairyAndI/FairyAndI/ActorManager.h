#ifndef _ACTOR_MANAGER_H_
#define _ACTOR_MANAGER_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include <list>
#include <vector>
#include "FileParameter.h"
#include "GameObject.h"
#include "Main.h"

//�������N���X�錾������//
class ACTORMANAGER
{
    private:
        static std::list<GAMEOBJECT*> GameObject;
        static std::list<GAMEOBJECT*> DestroyObject;

    public:
        static void Destroy(GAMEOBJECT*);
        static void Draw(void);
        static void FindObject(std::vector<GAMEOBJECT*>&, tstring);
        static HRESULT Initialize(void);
        static void Instantiate(tstring, D3DXVECTOR3, D3DXVECTOR3);
        static void Uninitialize(void);
        static void Update(void);
};

#endif