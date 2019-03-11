#ifndef _EFFECT_FACTORY_H_
#define _EFFECT_FACTORY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス定義＝＝＝//
class EFFECTFACTORY
{
    public:
        static void InstantiateSkillEffect(D3DXVECTOR3, D3DXVECTOR2, bool);

        friend ACTORMANAGER;
};

#endif