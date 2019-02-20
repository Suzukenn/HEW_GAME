//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Main.h"
#include "Model.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���f���̕`��
//
//�����F(bool)�G�t�F�N�g�̗L�����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void MODEL::Draw(bool effect)
{
    //---�e��錾---//
    DWORD nCounter;
    HRESULT hResult;
    D3DMATERIAL9 matDefault;
    D3DMATERIAL9 matEffect;

    const D3DCOLORVALUE GrayScale = { 0.2126F, 0.7152F, 0.0722F , 1.0F };

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMatrix;

    //---����������---//
    pDevice = GetDevice();

    //���݂̃}�e���A�����擾
    hResult = pDevice->GetMaterial(&matDefault);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�W���}�e���A���̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
    }

    //�|�C���^���擾
    pMatrix = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //�}�e���A���̐ݒ�
        if (effect)
        {
            matEffect = pMatrix[nCounter].MatD3D;
            matEffect.Diffuse = { 0.5F, 0.5F, 0.5F, 1.0F };
            hResult = pDevice->SetMaterial(&matEffect);
        }
        else
        {
            hResult = pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);
        }
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�}�e���A���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
        }

        //�e�N�X�`���̐ݒ�
        hResult = pDevice->SetTexture(0, Texture.at(nCounter));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�e�N�X�`���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
        }

        //�`��
        hResult = Mesh->DrawSubset(nCounter);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���b�V���̕`��Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
        }

    }

    //�}�e���A�����f�t�H���g�ɖ߂�
    hResult = pDevice->SetMaterial(&matDefault);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�W���}�e���A���̕����Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
    }
}