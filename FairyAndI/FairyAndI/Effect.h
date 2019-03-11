#ifndef _EFFECT_H_
#define _EFFECT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Billboard.h"
#include "GameObject.h"
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class EFFECT final : public GAMEOBJECT
{
    private:
        int EffectNumber;
        int FrameCounter;
        POINT UV;
        BILLBOARD Billboard;

    public:
        EFFECT(LPCTSTR, D3DXVECTOR3, D3DXVECTOR2, bool, POINT);

        void Draw(void);
        void Uninitialize(void);
        HRESULT Initialize(LPCTSTR, D3DXVECTOR3, D3DXVECTOR2, bool, POINT);
        void Update(void);

        void OnCollision(COLLISION*) {};
};

#endif