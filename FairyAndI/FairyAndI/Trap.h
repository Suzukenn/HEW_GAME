#ifndef _TRAP_H_
#define _TRAP_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//�������O���錾������//
class SPHERE;

//�������N���X�錾������//
class TRAP final : public  GAMEOBJECT
{
public:
	DWORD BornTime;
	std::weak_ptr<MODEL> Model;
	D3DXVECTOR3 Move;

	SPHERE* Collision;

	TRAP(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
	~TRAP();

	void Draw(void);
	void Uninitialize(void);
	HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
	void Update(void);

	void OnCollision(COLLISION*);
};

#endif
