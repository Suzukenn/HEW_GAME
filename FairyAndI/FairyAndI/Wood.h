#ifndef _WOOD_H_
#define _WOOD_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Enemy.h"

//＝＝＝列挙型定義＝＝＝//
typedef enum
{
    WOODSTATE_WAIT,
    WOODSTATE_ATTACK,
    MAX_WOODSTATE
} WOODSTATE;

//＝＝＝クラス宣言＝＝＝//
class WOOD final : public ENEMY
{
    private:
        WOODSTATE State;

    public:
        WOOD(D3DXVECTOR3, D3DXVECTOR3);
        ~WOOD(void);

        HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        void Uninitialize(void);
        void Update(void);
        void Draw(void);

        void OnCollision(COLLISION*);
};

#endif