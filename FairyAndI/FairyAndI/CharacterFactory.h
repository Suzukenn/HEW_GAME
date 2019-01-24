#ifndef _CHARACTER_FACTORY_H_
#define _CHARACTER_FACTORY_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス定義＝＝＝//
class CHARACTERFACTORY
{
    public:
        static void InstantiateFairy(D3DXVECTOR3, D3DXVECTOR3);
		static void InstantiatePlant(D3DXVECTOR3, D3DXVECTOR3);
        static void InstantiatePlayer(D3DXVECTOR3, D3DXVECTOR3);
		static void InstantiateSlime(D3DXVECTOR3, D3DXVECTOR3);

    friend ACTORMANAGER;
};

#endif