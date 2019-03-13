#ifndef _ENEMY_H_
#define _ENEMY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class ENEMY : public GAMEOBJECT
{
	protected:
        int AttackCool;
        bool Gray;

		std::shared_ptr<ANIMATIONMODEL> Model;
		SPHERE* Collision;

	public:
		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
        bool SearchTarget(D3DXVECTOR3, float);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);
};

#endif