//#define _CRT_SECURE_NO_WARNINGS
//
////＝＝＝ヘッダファイル読み込み＝＝＝//
//#include <stdio.h>
//#include <iostream>
//#include <tchar.h>
//#include "Debug.h"
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//LPD3DXFONT DEBUG::Font;			            //フォントへのポインタ
//TCHAR		g_aStrDebug[1024];	// デバッグ情報
//
////=============================================================================
//// デバッグ表示処理の初期化
////=============================================================================
//HRESULT DEBUG::Initialize(void)
//{
//    //---各種宣言---//
//    LPDIRECT3DDEVICE9 pDevice;
//	HRESULT hResult;
//
//    //---初期化処理---//
//    pDevice = GetDevice();
//
//	//情報表示用フォントを設定
//    hResult = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Terminal"), &Font);
//
//	//情報クリア
//	memset(&g_aStrDebug, 0, sizeof g_aStrDebug);
//
//	return hResult;
//}
//
////=============================================================================
//// デバッグ表示処理の終了処理
////=============================================================================
//void DEBUG::Uninitialize(void)
//{
//    SAFE_RELEASE(Font);
//}
//
////=============================================================================
//// デバッグ表示処理の更新処理
////=============================================================================
//void DEBUG::Update(void)
//{
//
//}
//
////=============================================================================
//// デバッグ表示処理の描画処理
////=============================================================================
//void DEBUG::Draw(void)
//{
//    //---各種宣言---//
//    RECT rect;
//    
//    //---初期化処理---//
//    rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
//
//	//情報表示
//	Font->DrawText(nullptr, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
//
//	//情報クリア
//	memset(g_aStrDebug, 0, sizeof(g_aStrDebug));
//}
//
////=============================================================================
//// デバッグ表示の登録
////=============================================================================
//void DEBUG::PrintDebugData(TCHAR *format,...)
//{
//    //---各種宣言---//
//	TCHAR* list;			// 可変引数を処理する為に使用する変数
//    TCHAR* pCur;
//    TCHAR aBuf[256];
//    TCHAR aWk[256];
//
//	// 可変引数にアクセスする前の初期処理
//	va_start(list, format);
//
//	pCur = format;
//
//    while(*pCur)
//	{
//		if(*pCur != '%')
//		{
//            _stprintf_s(aWk, TEXT("%c"), *pCur);
//		}
//		else
//		{
//			pCur++;
//
//            // 可変引数にアクセスしてその変数を取り出す処理
//			switch(*pCur)
//			{
//			    case 'd':
//                    _stprintf_s(aWk, sizeof(aWk),TEXT("%d"), va_arg(list, int));
//				    break;
//
//			    case 'f':
//                    _stprintf_s(aWk, sizeof(aWk), TEXT("%.2f"), va_arg(list, double));		// double型で指定
//				    break;
//
//			    case 's':
//                    _stprintf_s(aWk, sizeof(aWk), TEXT("%s"), va_arg(list, LPTCH));
//				    break;
//
//			    case 'c':
//                    _stprintf_s(aWk, sizeof(aWk), TEXT("%c"), va_arg(list, char));
//				    break;
//
//			    default:
//                    _stprintf_s(aWk, sizeof(aWk),TEXT("%c"), *pCur);
//				    break;
//			}
//		}
//        lstrcat(aBuf, aWk);
//
//        pCur++;
//	}
//
//	// 可変引数にアクセスした後の終了処理
//	va_end(list);
//
//	// 連結
//	if((lstrlen(g_aStrDebug) + lstrlen(aBuf)) < ((sizeof(g_aStrDebug)) - 1))
//	{
//		lstrcat(g_aStrDebug, aBuf);
//	}
//}