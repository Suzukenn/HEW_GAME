#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス定義＝＝＝//
class OBJECTFACTORY
{
    public:
        static void InstantiateFireElement(D3DXVECTOR3);
        static void InstantiateIceElement(D3DXVECTOR3);
        static void InstantiateRockElement(D3DXVECTOR3);

        friend ACTORMANAGER;
};

#endif