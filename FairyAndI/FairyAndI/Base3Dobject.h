#ifndef _BASE_3D_OBJECT_H_
#define _BASE_3D_OBJECT_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <memory>
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
typedef struct
{
    D3DXVECTOR3 Position;                           //位置座標
    D3DXVECTOR3 Rotation;                           //向き
    D3DXVECTOR3 Size;                               //大きさ
} BASE3DOBJECT;

#endif