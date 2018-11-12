#ifndef _MAIN_H_
#define _MAIN_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <Windows.h>

//＝＝＝ライブラリのリンク＝＝＝//
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "imm32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Xinput")

//＝＝＝定数・マクロ定義＝＝＝//
#define FVF_VERTEX_2D D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE              //2Dテクスチャのフォーマット
#define	FVF_VERTEX_3D D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 //3Dテクスチャのフォーマット
#define SCREEN_HEIGHT 720.0F                                                    //ウインドウの高さ
#define SCREEN_WIDTH 1280.0F  		                                            //ウインドウの幅
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)                                      //ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	                                    //ウインドウの中心Ｙ座標

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){x->Release();x = nullptr;}}
#endif

//＝＝＝型宣言＝＝＝//
typedef std::basic_string<TCHAR> tstring;

//＝＝＝構造体定義＝＝＝//
typedef struct
{
    int Frame; //パターン番号
    int Count; //フレーム数
}MOTION;

typedef struct
{
    D3DXVECTOR3 Position;	//スクリーン座標
    float RHW;			    //RHW(常に1.0F)
    D3DCOLOR Diffuse;	    //頂点カラー(拡散反射色=物体本来の色)
    float U;                //テクスチャ座標U
    float V;			    //テクスチャ座標V
} VERTEX_2D;

typedef struct
{
    D3DXVECTOR3 Vertex;		//頂点座標
    D3DXVECTOR3 Normal;		//法線ベクトル
    D3DCOLOR Diffuse;		//反射光
    D3DXVECTOR2 Texture;	//テクスチャ座標
} VERTEX_3D;

//＝＝＝プロトタイプ宣言＝＝＝//
LPDIRECT3DDEVICE9 GetDevice(void);

#endif