//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Billboard.h"
#include "InputManager.h"
#include "SideViewCamera.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "SquareGauge.h"
#include "Texture.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�r���{�[�h�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BILLBOARD::Draw(void)
{
    //---�e��錾---//
    HRESULT hResult;
    D3DXMATRIX mtxProjection;
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxWorld;
    D3DXMATRIX mtxWVP;

    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<SHADER> pShader;
    std::shared_ptr<TEXTURE> pTexture;

    LPDIRECT3DVERTEXDECLARATION9 pVertexDeclaration; //���_�V�F�[�_�̒��_��`

    //�p�C�v���C���ɓn�����_�f�[�^�̍\�����`
    D3DVERTEXELEMENT9 decl[] = {{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, //�ʒu
                                { 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 }, //�e�N�X�`�����W
                                D3DDECL_END() //�Ō�ɕK��D3DDECL_END()������
                               };

    //---����������---//
    pDevice = GetDevice();
    D3DXMatrixIdentity(&mtxWorld);
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("�`��Ώۂ̃e�N�X�`�������݂��܂���"), TEXT("�`��G���["), MB_OK);
    }

    pShader = Shader.lock();
    if (!pShader)
    {
        MessageBox(nullptr, TEXT("�`��Ɏg�p����V�F�[�_�[�����݂��܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�����ݒ�---//
    SIDEVIEWCAMERA::GetViewMatrix(&mtxView);
    D3DXMatrixInverse(&mtxWorld, nullptr, &mtxView);

    //�ړ��𔽉f
    mtxWorld._41 = Transform.Position.x;
    mtxWorld._42 = Transform.Position.y;
    mtxWorld._43 = Transform.Position.z;

    SIDEVIEWCAMERA::GetProjectionMatrix(&mtxProjection);
    mtxWVP = mtxWorld * mtxView * mtxProjection;

    //---�����ݒ�---//
    //���_�̒�`�I�u�W�F�N�g���쐬����
    hResult = pDevice->CreateVertexDeclaration(decl, &pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���_���̒�`�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }
    //���_��`���Z�b�g
    hResult = pDevice->SetVertexDeclaration(pVertexDeclaration);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���_���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�G�t�F�N�g�̓K�p---//
    hResult = pShader->Effect->SetTechnique("Gray");
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->SetMatrix("WorldViewProjection", &mtxWVP);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�}�g���N�X�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->SetTexture("Texture", pTexture->Image);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�X�`���̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->Begin(nullptr, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̓K�p���J�n�ł��܂���ł���"), TEXT("�`��G���["), MB_OK);
    }

    hResult = pShader->Effect->BeginPass(UINT(Gray));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�j�b�N�̓K�p�p�X�̐ݒ�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�`��---//
    hResult = pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, &Vertex, sizeof(CUSTOMVERTEX));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�|���S���̕`��Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
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

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�r���{�[�h�̏�����
//
//�����F(LPCTSTR)�e�N�X�`��,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��,(POINT)UV�����l
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BILLBOARD::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR3 scale, POINT uv)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    //---����������---//
    Transform.Position = position;
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = scale;
    UV = uv;
    Gray = false;

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�r���{�[�h�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�r���{�[�h�̍쐬---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Position.x = Transform.Position.x + Transform.Scale.x * (nCounter >> 1);
        Vertex.at(nCounter).Position.y = Transform.Position.y + Transform.Scale.y * (nCounter & 1);
        Vertex.at(nCounter).Position.z = 0.0F;
        Vertex.at(nCounter).Texture.x = (float)(nCounter >> 1);
        Vertex.at(nCounter).Texture.y = (float)!(nCounter & 1);
    }

    //---�G�t�F�N�g�̍쐬---//
    hResult = SHADERMANAGER::GetShader(TEXT("GRAY"), Shader);
    //hResult = D3DXCreateEffectFromFile(GetDevice(), TEXT("Data/GameScene/Gray.fx"), nullptr, nullptr, 0, nullptr, &Effect, &pErrMessage);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�r���{�[�h�̃V�F�[�_�[�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�r���{�[�h�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BILLBOARD::Uninitialize(void)
{
    Texture.reset();
    Shader.reset();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�r���{�[�h�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BILLBOARD::Update(void)
{
    ////---�e��錾---//
    //int nCounter;       //�J�E���^�[
    //float fU;           //U�l
    //float fV;           //V�l

    ////---�l�Z�o---//
    //fU = (number % UV.x) * (1.0F / UV.x);
    //fV = (number / UV.x) * (1.0F / UV.y);

    ////---�l�X�V---//
    //for (nCounter = 0; nCounter < 4; ++nCounter)
    //{
    //    Vertex.at(nCounter).Texture.x = fU + (nCounter % 2) * (1.0F / UV.x);
    //    Vertex.at(nCounter).Texture.y = fV + (nCounter / 2) * (1.0F / UV.y);
    //}

   /* if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = Gray ? false : true;
    }*/
	Gray = SQUAREGAUGE::GetFairyTime();
}