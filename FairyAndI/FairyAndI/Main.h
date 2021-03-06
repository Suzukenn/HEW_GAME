#ifndef _MAIN_H_
#define _MAIN_H_

//wb_t@CÇÝÝ//
#include <d3d9.h>
#include <d3dx9.h>
#include <iosfwd>
#include <string>
#include <Windows.h>

//CuÌN//
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "imm32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Xinput")

//èE}Nè`//
#define FVF_VERTEX_2D D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1              //2DeNX`ÌtH[}bg
#define	FVF_VERTEX_3D D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 //3DeNX`ÌtH[}bg
#define SCREEN_HEIGHT 720.0F                                                    //EChEÌ³
#define SCREEN_WIDTH 1280.0F  		                                            //EChEÌ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)                                      //EChEÌSwÀW
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	                                    //EChEÌSxÀW

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){x->Release();x = nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)       { if(x) { delete (x); (x)=nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if(x) { delete[] (x); (x)=nullptr; } }
#endif

//^é¾//
typedef std::basic_string<TCHAR> tstring;

//\¢Ìè`//
typedef struct
{
    D3DXVECTOR3 Position;	//XN[ÀW
    float RHW;			    //RHW(íÉ1.0F)
    D3DCOLOR Diffuse;	    //¸_J[(gU½ËF=¨Ì{ÌF)
    float U;                //eNX`ÀWU
    float V;			    //eNX`ÀWV
} VERTEX_2D;

typedef struct
{
    D3DXVECTOR3 Vertex;		//¸_ÀW
    D3DXVECTOR3 Normal;		//@üxNg
    D3DCOLOR Diffuse;		//½Ëõ
    D3DXVECTOR2 Texture;	//eNX`ÀW
} VERTEX_3D;

//vg^Cvé¾//
LPDIRECT3DDEVICE9 GetDevice(void);

#endif