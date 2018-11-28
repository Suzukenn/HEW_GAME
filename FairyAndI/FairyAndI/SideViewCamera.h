#ifndef _SIDE_VIEW_CAMERA_H_
#define _SIDE_VIEW_CAMERA_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include "Main.h"

//＝＝＝クラス宣言＝＝＝//
class SIDEVIEWCAMERA
{
	private:
        static D3DXVECTOR3 Position;					//位置
        static D3DXVECTOR3 Rotation;					//向き
        static D3DXVECTOR3 ReversoPoint;				//カメラの注視点
        static D3DXVECTOR3 UpVector;				    //カメラの上方向
        static float Interval;                         //視点と注視点の距離

        static D3DXMATRIX ViewMatrix;				//ビューマトリックス
        static bool PositionPlace;				//左右判定(?)	右true	左false

	public:
        static HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        static void Uninitialize(void);
        static void Update(D3DXVECTOR3);

        static HRESULT SetCamera(void);

        static const D3DXVECTOR3& GetRotation(void);
        static void GetViewMtx(LPD3DXMATRIX);
};

#endif
