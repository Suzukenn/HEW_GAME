#ifndef _BATTERY_CANNON_H_
#define _BATTERY_CANNON_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"
#include "Model.h"

//＝＝＝前方宣言＝＝＝//
class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class BATTERYCANNON final : public GAMEOBJECT
{
    public:
        D3DXVECTOR3 Move;
        DWORD BornTime;

        std::weak_ptr<MODEL> Model;
        SPHERE* Collision;

        BATTERYCANNON(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        ~BATTERYCANNON(void);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
};

#endif