//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Main.h"
#include "Model.h"
#include "SideViewCamera.h"
#include "Shader.h"
#include "Texture.h"

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

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;

    //---����������---//
    pDevice = GetDevice();

    //���݂̃}�e���A�����擾
    hResult = pDevice->GetMaterial(&matDefault);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�W���}�e���A���̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
    }

    //�|�C���^���擾
    pMaterial = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        //�}�e���A���̐ݒ�
        if (effect)
        {
            matEffect = pMaterial[nCounter].MatD3D;
            matEffect.Diffuse = { 0.5F, 0.5F, 0.5F, 1.0F };
            hResult = pDevice->SetMaterial(&matEffect);
        }
        else
        {
            hResult = pDevice->SetMaterial(&pMaterial[nCounter].MatD3D);
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

void MODEL::Draw(std::weak_ptr<SHADER>& shader, LPCTSTR technique, UINT passnumber, D3DXMATRIX& worldmatrix)
{
    //---�e��錾---//
    DWORD nCounter;
    HRESULT hResult;
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxProjection;
    D3DXMATRIX mtxWorldViewProjection;

    LPDIRECT3DDEVICE9 pDevice;
    LPD3DXMATERIAL pMaterial;
    LPDIRECT3DVERTEXDECLARATION9 pVertexDeclaration; //���_�V�F�[�_�̒��_��`
    std::shared_ptr<SHADER> pShader;

    //�p�C�v���C���ɓn�����_�f�[�^�̍\�����`
    D3DVERTEXELEMENT9 decl[] = {{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, //�ʒu
                                { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },  //�@��
                                { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //�e�N�X�`�����W
                                D3DDECL_END() //�Ō�ɕK��D3DDECL_END()������
                               };

    //---����������---//
    pDevice = GetDevice();
    pMaterial = (LPD3DXMATERIAL)MaterialBuffer->GetBufferPointer();

    pShader = shader.lock();
    if (!pShader)
    {
        MessageBox(nullptr, TEXT("�`��Ɏg�p����V�F�[�_�[�����݂��܂���"), TEXT("�`��G���["), MB_OK);
    }


    //---���_��`�̐ݒ�---//
    hResult = pDevice->CreateVertexDeclaration(decl, &pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���_���̒�`�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }
    hResult = pDevice->SetVertexDeclaration(pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���_��`�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�����ݒ�---//
    hResult = pShader->Effect->SetTechnique(pShader->Technic.at(technique));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    SIDEVIEWCAMERA::GetViewMatrix(&mtxView);
    SIDEVIEWCAMERA::GetProjectionMatrix(&mtxProjection);
    mtxWorldViewProjection = worldmatrix * mtxView * mtxProjection;

    hResult = pShader->Effect->SetMatrix("WorldViewProjection", &mtxWorldViewProjection);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�}�g���N�X�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->Begin(nullptr, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̓K�p���J�n�ł��܂���ł���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->BeginPass(passnumber);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̓K�p�p�X�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    for (nCounter = 0; nCounter < MaterialValue; ++nCounter)
    {
        hResult = pDevice->SetMaterial(&pMaterial[nCounter].MatD3D);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�}�e���A���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
        }

        D3DXVECTOR4 Diffuse = D3DXVECTOR4(pMaterial[nCounter].MatD3D.Diffuse.r, pMaterial[nCounter].MatD3D.Diffuse.g, pMaterial[nCounter].MatD3D.Diffuse.b, pMaterial[nCounter].MatD3D.Diffuse.a);
        hResult = pShader->Effect->SetVector("Diffuse", &Diffuse);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�f�B�t���[�Y�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        }

        //�e�N�X�`���̐ݒ�
        hResult = pShader->Effect->SetTexture("Texture", Texture.at(nCounter));
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�e�N�X�`���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        }

        hResult = pShader->Effect->CommitChanges();
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("�ݒ�̕ύX�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        }

        //�`��
        hResult = Mesh->DrawSubset(nCounter);
        if (FAILED(hResult))
        {
            MessageBox(nullptr, TEXT("���b�V���̕`��Ɏ��s���܂���"), TEXT("�`��G���["), MB_ICONSTOP | MB_OK);
        }
    }

    hResult = pShader->Effect->EndPass();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̓K�p�p�X�̏I���Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->End();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̓K�p�̏I���Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }
}