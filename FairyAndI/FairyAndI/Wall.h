#ifndef _WALL_H_
#define _WALL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Skill.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class WALL final : public SKILL
{
    private:
        DWORD BornTime;

        SPHERE* Collision;

    public:
        WALL(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~WALL(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif