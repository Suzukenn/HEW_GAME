#ifndef _MODEL_H_
#define _MODEL_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
typedef struct
{
    LPD3DXMESH Mesh;		        //���b�V�����ւ̃|�C���^
    D3DMATERIAL9* Material;	        //�}�e���A���z��
    LPD3DXBUFFER MaterialBuffer;	//�}�e���A�����ւ̃|�C���^
    DWORD MaterialValue;			//�}�e���A�����̐�
    LPDIRECT3DTEXTURE9*	Texture;	//�e�N�X�`���ւ̃|�C���^
    LPD3DXATTRIBUTERANGE Attribute;	//�����z��
    DWORD AttributeValue;		    //������(�T�u�Z�b�g��)

    void Release(void)
    {
        //SAFE_RELEASE(Mesh);
        //SAFE_RELEASE(MaterialBuffer);
        //SAFE_RELEASE((*Texture));
    }

} MODEL;

#endif