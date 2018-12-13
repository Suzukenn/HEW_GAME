#ifndef _BULLET_H_
#define _BULLET_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "GameObject.h"
#include "Main.h"

class SPHERE;

//＝＝＝クラス宣言＝＝＝//
class BULLET final : public  GAMEOBJECT
{
    public:
        SPHERE* Collision;
        bool data;
        BULLET(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        ~BULLET();

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, tstring, D3DXVECTOR3, D3DXVECTOR3);
        void Update(void);

        void OnCollision(COLLISION*);
        float a;
};

#endif