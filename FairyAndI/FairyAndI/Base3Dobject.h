#ifndef _BASE_3D_OBJECT_H_
#define _BASE_3D_OBJECT_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"

//�������N���X�錾������//
typedef struct
{
    D3DXVECTOR3 Position;                           //�ʒu���W
    D3DXVECTOR3 Rotation;                           //����
    D3DXVECTOR3 Size;                               //�傫��
} BASE3DOBJECT;

#endif