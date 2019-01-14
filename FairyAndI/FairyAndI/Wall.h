#ifndef _WALL_H_
#define _WALL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"

//＝＝＝前方宣言＝＝＝//
class OBB;

//＝＝＝クラス宣言＝＝＝//
class WALL final : public GAMEOBJECT
{
    private:
        std::weak_ptr<MODEL> Model;
        OBB* Collision;

    public:
        WALL(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~WALL();

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif