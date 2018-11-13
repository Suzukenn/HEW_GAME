#ifndef _FLEXIBLE_CAMERA_H_
#define _FLEXIBLE_CAMERA_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class FLEXIBLECAMERA
{
    private:
        D3DXVECTOR3 Position;					//位置
        D3DXVECTOR3 Rotation;					//向き
        D3DXVECTOR3	ReversoPoint;				// カメラの注視点
        D3DXVECTOR3 UpVector;				    // カメラの上方向
        float Interval;                         //視点と注視点の距離
        D3DXMATRIX m_mtxWorldField;				//ワールドマトリックス

    public:
        HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        void Uninitialize(void);
        void Update(void);
        HRESULT SetCamera(void);

};

#endif