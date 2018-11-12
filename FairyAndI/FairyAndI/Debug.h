#ifndef _DEBUG_H_
#define _DEBUG_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <array>
#include "Main.h"


//�������N���X�錾������//
class DEBUG
    {
    private:
        static  std::array<TCHAR, 1024> DebugString;	//�����p�o�b�t�@
        LPDIRECT3DDEVICE9 Device;	                    //�`��f�o�C�X
        LPD3DXFONT Font;		                        //�t�H���g�I�u�W�F�N�g�|�C���^
        D3DXFONT_DESC D3DFD;	                        //�t�H���g����
        POINT Block;
        int Block_x;			                        //�\���ʒu
        int Block_y;
        tstring str;			                        //�f�o�b�O������ێ��o�b�t�@

    public:
        static void Draw(void);
        static HRESULT Initialize(void);
        static void Uninitialize(void);
        static void Update(void);
        static void PrintDebugData(TCHAR *fmt, ...);
};

#endif