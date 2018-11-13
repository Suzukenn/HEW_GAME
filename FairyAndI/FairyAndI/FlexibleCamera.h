#ifndef _FLEXIBLE_CAMERA_H_
#define _FLEXIBLE_CAMERA_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"

//�������N���X�錾������//
class FLEXIBLECAMERA
{
    private:
        D3DXVECTOR3 Position;					//�ʒu
        D3DXVECTOR3 Rotation;					//����
        D3DXVECTOR3	ReversoPoint;				// �J�����̒����_
        D3DXVECTOR3 UpVector;				    // �J�����̏����
        float Interval;                         //���_�ƒ����_�̋���
        D3DXMATRIX m_mtxWorldField;				//���[���h�}�g���b�N�X

    public:
        HRESULT Initialize(D3DXVECTOR3, D3DXVECTOR3);
        void Uninitialize(void);
        void Update(void);
        HRESULT SetCamera(void);

};

#endif