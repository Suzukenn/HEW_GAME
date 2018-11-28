#ifndef _BULLET_H_
#define _BULLET_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"

//�������N���X�錾������//
class BULLET final : private GAMEOBJECT
{
    public:
        BULLET(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3 size = D3DXVECTOR3(1.0F, 1.0F, 1.0F));

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3 size = D3DXVECTOR3(1.0F, 1.0F, 1.0F));
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif