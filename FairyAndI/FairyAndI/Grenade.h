#ifndef _GRENADE_H_
#define _GRENADE_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class GRENADE final : public GAMEOBJECT
{
	public:
		DWORD BornTime;
		D3DXVECTOR3 Move;

		std::weak_ptr<MODEL> Model;
		SPHERE* Collision;

		GRENADE(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		~GRENADE(void);

		void Draw(void);
		void Uninitialize(void);
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Update(void);

		void OnCollision(COLLISION*);
};

#endif
