#ifndef _MAIN_H_
#define _MAIN_H_

//wb_t@CÇÝÝ//
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <windows.h>

//CuÌN//
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "imm32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Xinput")

//èE}Nè`//
#define FVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_TEX1|D3DFVF_DIFFUSE)       //eNX`ÌtH[}bg
#define SCREEN_HEIGHT 480.0F                                        //EChEÌ³
#define SCREEN_WIDTH 854.0F  		                                //EChEÌ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)                          //EChEÌSwÀW
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	                        //EChEÌSxÀW

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){x->Release();x = nullptr;}}
#endif

//^é¾//
typedef std::basic_string<TCHAR> tstring;

//\¢Ìè`//
typedef struct
{
    int Frame; //p^[Ô
    int Count; //t[
}MOTION;

typedef struct
{
    D3DVECTOR Position;	    //¸_ÀW
    float RHW;			    //RHW(íÉ1.0F)
    D3DCOLOR Diffuse;	    //¸_J[(gU½ËF=¨Ì{ÌF)
    float U;                //eNX`ÀWU
    float V;			    //eNX`ÀWV
} VERTEX;

//vg^Cvé¾//
LPDIRECT3DDEVICE9 GetDevice(void);

#endif