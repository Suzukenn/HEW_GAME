#ifndef _SIDE_VIEW_CAMERA_H_
#define _SIDE_VIEW_CAMERA_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class SIDEVIEWCAMERA
{
	private:
        static D3DXVECTOR3 Position;					//�ʒu
        static D3DXVECTOR3 Rotation;					//����
        static D3DXVECTOR3 ReversoPoint;				//�J�����̒����_
        static D3DXVECTOR3 UpVector;				    //�J�����̏����
        static float Interval;                         //���_�ƒ����_�̋���

        static D3DXMATRIX ViewMatrix;				//�r���[�}�g���b�N�X
        static bool PositionPlace;				//���E����(?)	�Etrue	��false

	public:
        static HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        static void Uninitialize(void);
        static void Update(D3DXVECTOR3);

        static HRESULT SetCamera(void);

        static const D3DXVECTOR3& GetRotation(void);
        static void GetViewMtx(LPD3DXMATRIX);
};

#endif
