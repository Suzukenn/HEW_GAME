#ifndef _MAIN_H_
#define _MAIN_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <Windows.h>

//���������C�u�����̃����N������//
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "imm32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Xinput")

//�������萔�E�}�N����`������//
#define FVF_VERTEX_2D D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE              //2D�e�N�X�`���̃t�H�[�}�b�g
#define	FVF_VERTEX_3D D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 //3D�e�N�X�`���̃t�H�[�}�b�g
#define SCREEN_HEIGHT 720.0F                                                    //�E�C���h�E�̍���
#define SCREEN_WIDTH 1280.0F  		                                            //�E�C���h�E�̕�
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)                                      //�E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	                                    //�E�C���h�E�̒��S�x���W

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){x->Release();x = nullptr;}}
#endif

//�������^�錾������//
typedef std::basic_string<TCHAR> tstring;

//�������\���̒�`������//
typedef struct
{
    int Frame; //�p�^�[���ԍ�
    int Count; //�t���[����
}MOTION;

typedef struct
{
    D3DXVECTOR3 Position;	//�X�N���[�����W
    float RHW;			    //RHW(���1.0F)
    D3DCOLOR Diffuse;	    //���_�J���[(�g�U���ːF=���̖{���̐F)
    float U;                //�e�N�X�`�����WU
    float V;			    //�e�N�X�`�����WV
} VERTEX_2D;

typedef struct
{
    D3DXVECTOR3 Vertex;		//���_���W
    D3DXVECTOR3 Normal;		//�@���x�N�g��
    D3DCOLOR Diffuse;		//���ˌ�
    D3DXVECTOR2 Texture;	//�e�N�X�`�����W
} VERTEX_3D;

//�������v���g�^�C�v�錾������//
LPDIRECT3DDEVICE9 GetDevice(void);

#endif