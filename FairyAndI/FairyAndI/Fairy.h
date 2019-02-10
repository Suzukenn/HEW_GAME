#ifndef _FAIRY_H_
#define _FAIRY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "AnimationModel.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝定数・マクロ定義＝＝＝//
#define	VALUE_MOVE_FAIRY 2.0F   // 移動速度

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    STATE_CHASE,
    STATE_SYNTHIESIS,
    STATE_MAX
} STATE;

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class FAIRY final : public GAMEOBJECT
{
	private:
        D3DXVECTOR3	Move;	        //移動量
        D3DXVECTOR3	ElementPosition;//回収エレメントの位置
		bool Collection;	        //回収状態
        STATE State;
		float ToTargetAngle;
        ANIMATIONMODEL Model;

        std::vector<GAMEOBJECT*> Element;
        SPHERE* Collision;

        bool SearchElement(D3DXVECTOR3&);

	public:
        FAIRY(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);

		HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
		void Uninitialize(void);
		void Update(void);
		void Draw(void);

        void OnCollision(COLLISION*);

		D3DXVECTOR3 GetPos(void);
};

#endif