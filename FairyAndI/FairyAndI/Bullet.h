#ifndef _BULLET_H_
#define _BULLET_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Model.h"
#include "Skill.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class BULLET final : public SKILL
{
    public:
        D3DXVECTOR3 Move;
        DWORD BornTime;
        tstring Type;

        std::weak_ptr<MODEL> Model;
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