#ifndef _WALL_H_
#define _WALL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"

//�������O���錾������//
class OBB;

//�������N���X�錾������//
class WALL final : public GAMEOBJECT
{
    private:
        std::weak_ptr<MODEL> Model;
        OBB* Collision;

    public:
        WALL(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~WALL();

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif