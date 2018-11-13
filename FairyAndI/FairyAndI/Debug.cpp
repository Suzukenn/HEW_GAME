//#define _CRT_SECURE_NO_WARNINGS
//
////�������w�b�_�t�@�C���ǂݍ��݁�����//
//#include <stdio.h>
//#include <iostream>
//#include <tchar.h>
//#include "Debug.h"
//
////*****************************************************************************
//// �}�N����`
////*****************************************************************************
//
////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//
////*****************************************************************************
//// �O���[�o���ϐ�
////*****************************************************************************
//LPD3DXFONT DEBUG::Font;			            //�t�H���g�ւ̃|�C���^
//TCHAR		g_aStrDebug[1024];	// �f�o�b�O���
//
////=============================================================================
//// �f�o�b�O�\�������̏�����
////=============================================================================
//HRESULT DEBUG::Initialize(void)
//{
//    //---�e��錾---//
//    LPDIRECT3DDEVICE9 pDevice;
//	HRESULT hResult;
//
//    //---����������---//
//    pDevice = GetDevice();
//
//	//���\���p�t�H���g��ݒ�
//    hResult = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Terminal"), &Font);
//
//	//���N���A
//	memset(&g_aStrDebug, 0, sizeof g_aStrDebug);
//
//	return hResult;
//}
//
////=============================================================================
//// �f�o�b�O�\�������̏I������
////=============================================================================
//void DEBUG::Uninitialize(void)
//{
//    SAFE_RELEASE(Font);
//}
//
////=============================================================================
//// �f�o�b�O�\�������̍X�V����
////=============================================================================
//void DEBUG::Update(void)
//{
//
//}
//
////=============================================================================
//// �f�o�b�O�\�������̕`�揈��
////=============================================================================
//void DEBUG::Draw(void)
//{
//    //---�e��錾---//
//    RECT rect;
//    
//    //---����������---//
//    rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
//
//	//���\��
//	Font->DrawText(nullptr, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
//
//	//���N���A
//	memset(g_aStrDebug, 0, sizeof(g_aStrDebug));
//}
//
////=============================================================================
//// �f�o�b�O�\���̓o�^
////=============================================================================
//void DEBUG::PrintDebugData(TCHAR *format,...)
//{
//    //---�e��錾---//
//	TCHAR* list;			// �ψ�������������ׂɎg�p����ϐ�
//    TCHAR* pCur;
//    TCHAR aBuf[256];
//    TCHAR aWk[256];
//
//	// �ψ����ɃA�N�Z�X����O�̏�������
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
//            // �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
//			switch(*pCur)
//			{
//			    case 'd':
//                    _stprintf_s(aWk, sizeof(aWk),TEXT("%d"), va_arg(list, int));
//				    break;
//
//			    case 'f':
//                    _stprintf_s(aWk, sizeof(aWk), TEXT("%.2f"), va_arg(list, double));		// double�^�Ŏw��
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
//	// �ψ����ɃA�N�Z�X������̏I������
//	va_end(list);
//
//	// �A��
//	if((lstrlen(g_aStrDebug) + lstrlen(aBuf)) < ((sizeof(g_aStrDebug)) - 1))
//	{
//		lstrcat(g_aStrDebug, aBuf);
//	}
//}