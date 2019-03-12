#ifndef _PLAYER_H_
#define _PLAYER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//---定数・マクロ定義---//
#define MAX_PLAYER_HP 5
#define	VALUE_MOVE_PLAYER 0.5F

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス定義＝＝＝//
class PLAYER final : public GAMEOBJECT
{
	private:
        int HP;
        int State;
        int Vibration;
        bool Gray;
        D3DXVECTOR3 Move;
        std::shared_ptr<ANIMATIONMODEL> Model;

        SPHERE* Collision;

	public:
        PLAYER(D3DXVECTOR3, D3DXVECTOR3);

        void Draw(void);
		HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);

        void OnCollision(COLLISION*);

		static D3DXVECTOR3 GetPlayerPosition(void);
		static D3DXVECTOR3 GetPlayerRotation(void);
        static int GetPlayerHP(void);
};

#endif