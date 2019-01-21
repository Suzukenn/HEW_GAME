//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "DirectionalLight.h"
#include "Main.h"

//�������O���[�o���錾������//
D3DLIGHT9 DIRECTIONALLIGHT::Light;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���C�g�̏�����
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�����_
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT DIRECTIONALLIGHT::Initialize(void)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXVECTOR3 vecDirection;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();
    memset(&Light, 0, sizeof(D3DLIGHT9));

    //---�f�B���N�V���i�����C�g�̐ݒ�---//
    //���C�g�^�C�v
    Light.Type = D3DLIGHT_DIRECTIONAL;

    //�g�U��
    Light.Diffuse = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);

    //����
    Light.Ambient = D3DXCOLOR(1.0F, 1.0F, 1.0F, 1.0F);

    //����
    vecDirection = D3DXVECTOR3(0.0F, -0.6F, 1.0F);
    D3DXVec3Normalize(&vecDirection, &vecDirection);
    Light.Direction = vecDirection;

    //�����_�����O�p�C�v���C���ɐݒ�
    hResult = pDevice->SetLight(0, &Light);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���C�g�������_�����O�p�C�v���C���ɐݒ�ł��܂���ł���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    // ���C�g�̔��f
    hResult = pDevice->LightEnable(0, TRUE);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���C�g�̔��f�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���C�e�B���O���[�h�̐ݒ�---//
    hResult = pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���C�e�B���O���[�h�̐ݒ�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���C�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DIRECTIONALLIGHT::Uninitialize(void)
{

}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���C�g�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DIRECTIONALLIGHT::Update(void)
{

}