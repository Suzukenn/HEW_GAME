#ifndef _DEBUG_H_
#define _DEBUG_H_

//＝＝＝ヘッダファイル読み込み＝＝＝//
#include <array>
#include "Main.h"


//＝＝＝クラス宣言＝＝＝//
class DEBUG
    {
    private:
        static  std::array<TCHAR, 1024> DebugString;	//処理用バッファ
        LPDIRECT3DDEVICE9 Device;	                    //描画デバイス
        LPD3DXFONT Font;		                        //フォントオブジェクトポインタ
        D3DXFONT_DESC D3DFD;	                        //フォント属性
        POINT Block;
        int Block_x;			                        //表示位置
        int Block_y;
        tstring str;			                        //デバッグ文字列保持バッファ

    public:
        static void Draw(void);
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);
        static void PrintDebugData(TCHAR *fmt, ...);
};

#endif