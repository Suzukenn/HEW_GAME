#ifndef _SIDE_VIEW_CAMERA_H_
#define _SIDE_VIEW_CAMERA_H_

//wb_t@CΗέέ//
#include "Main.h"

//NXιΎ//
class SIDEVIEWCAMERA
{
	private:
        static D3DXVECTOR3 Position;			//Κu
        static D3DXVECTOR3 Rotation;			//ό«
        static D3DXVECTOR3 ReversoPoint;		//JΜ_
        static D3DXVECTOR3 UpVector;			//JΜγϋό
        static float Interval;                  //_Ζ_Μ£

        static D3DXMATRIX ViewMatrix;			//r[}gbNX
        static D3DXMATRIX ProjectionMatrix;		//vWFNV}gbNX
        static bool PositionPlace;				//ΆE»θ(?)	Etrue	Άfalse

	public:
        static HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        static void Uninitialize(void);
        static void Update(D3DXVECTOR3);

        static HRESULT SetCamera(void);

        static D3DXVECTOR3 GetRotation(void);
        static void GetViewMatrix(LPD3DXMATRIX);
        static void GetProjectionMatrix(LPD3DXMATRIX);
};

#endif
