#ifndef _GIMMICK_FACTORY_H_
#define _GIMMICK_FACTORY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス定義＝＝＝//
class GIMMICKFACTORY
{
    public:
        static void InstantiateFireGimmick(D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateGimmick(tstring, D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateIceGimmick(D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiateWoodGimmick(D3DXVECTOR3, D3DXVECTOR3);

        friend ACTORMANAGER;
};

#endif