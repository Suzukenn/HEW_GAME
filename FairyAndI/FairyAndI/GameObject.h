#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class COLLISION;

//＝＝＝クラス宣言＝＝＝//
class GAMEOBJECT
{
    protected:
        D3DXVECTOR3 Position;                           //位置座標
        D3DXVECTOR3 Rotation;                           //向き
        D3DXVECTOR3 Size;                               //大きさ

        std::shared_ptr<MODEL> Model;
        COLLISION* Collision;

    public:
        GAMEOBJECT() {}
        ~GAMEOBJECT() {}
        virtual void Draw(void) = 0;
        virtual void Uninitialize(void) = 0;
        virtual void Update(void) = 0;

        virtual void OnCollision(COLLISION*) = 0;
};

#endif