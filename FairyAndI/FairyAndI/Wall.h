#ifndef _WALL_H_
#define _WALL_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class WALL final : public GAMEOBJECT
{
    public:
        WALL(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif