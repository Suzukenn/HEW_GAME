#ifndef _TRAP_H_
#define _TRAP_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
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
