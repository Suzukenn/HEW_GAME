#ifndef _PLAYER_H_
#define _PLAYER_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝定数・マクロ定義＝＝＝//
#define MAX_PLAYER_HP 5
#define	VALUE_MOVE_PLAYER 0.5F

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    PLAYERSTATE_WAIT,
    PLAYERSTATE_WALK,
    PLAYERSTATE_RUN,
    PLAYERSTATE_JUMP,
    PLAYERSTATE_FALL,
    PLAYERSTATE_ATTACK,
    PLAYERSTATE_DAMAGE
}PLAYERSTATE;

//＝＝＝クラス定義＝＝＝//
class PLAYER final : public GAMEOBJECT
{
	private:
        int HP;
        PLAYERSTATE State;
        int Vibration;
        int AnimationTime;
        bool Gray;
        bool Jump;
        bool IsGround;
        D3DXVECTOR3 Move;
        D3DXVECTOR2 VibrationPower;

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
        static PLAYERSTATE GetPlayerState(void);
};

#endif