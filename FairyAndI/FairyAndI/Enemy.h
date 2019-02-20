#ifndef _ENEMY_H_
#define _ENEMY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
	ENEMYSTATE_NORMAL,
	ENEMYSTATE_BATTLE,
	ENEMYSTATE_RETURN,
	MAX_ENEMYSTATE
} ENEMYSTATE;

//＝＝＝前方宣言＝＝＝//
//class OBB;
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class ENEMY final : public GAMEOBJECT
{
	private:
        bool Gray;

		std::weak_ptr<MODEL> Model;
		//OBB* Collision;
		SPHERE* Collision;

		D3DXVECTOR3 InitialPosition;			//初期位置
		D3DXVECTOR3 Move;
		ENEMYSTATE StateType;

	public:

		ENEMY(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		~ENEMY(void);

		HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};
#endif