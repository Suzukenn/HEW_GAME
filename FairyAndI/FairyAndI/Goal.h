#ifndef _GOAL_H_
#define _GOAL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class GOAL final : public GAMEOBJECT
{
	private:
        bool Gray;

        std::weak_ptr<MODEL> Model;
        SPHERE* Collision;

		int Goal;

	public:
		GOAL(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        ~GOAL(void);

        void Draw(void);
		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);
};

#endif