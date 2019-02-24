#ifndef _TRAP_H_
#define _TRAP_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"
#include "Skill.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class TRAP final : public SKILL
{
    public:
        bool Gray;

	    std::weak_ptr<MODEL> Model;
	    SPHERE* Collision;

	    TRAP(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
	    ~TRAP(void);

	    void Draw(void);
	    void Uninitialize(void);
	    HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
	    void Update(void);

	    void OnCollision(COLLISION*);
};

#endif
