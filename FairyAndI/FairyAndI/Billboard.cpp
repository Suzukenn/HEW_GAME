//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Billboard.h"
#include "SideViewCamera.h"
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
    D3DXMATRIX mtxView;
    D3DXMATRIX mtxWorld;

    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pTexture;

    //---����������---//
    pDevice = GetDevice();
    D3DXMatrixIdentity(&mtxWorld);
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("�`��Ώۂ̃e�N�X�`�������݂��܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�����ݒ�---//
    SIDEVIEWCAMERA::GetViewMtx(&mtxView);
    mtxWorld._11 = mtxView._11;
    mtxWorld._12 = mtxView._21;
    mtxWorld._13 = mtxView._31;
    mtxWorld._21 = mtxView._12;
    mtxWorld._22 = mtxView._22;
    mtxWorld._23 = mtxView._32;
    mtxWorld._31 = mtxView._13;
    mtxWorld._32 = mtxView._23;
    mtxWorld._33 = mtxView._33;

    //---�����ݒ�---//
    // ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);            //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, pTexture->Image);   //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��`��---//
    // �ړ��𔽉f
    mtxWorld._41 = Transform.Position.x;
    mtxWorld._42 = Transform.Position.y;
    mtxWorld._43 = Transform.Position.z;

    // ���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // �|���S���̕`��
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex, sizeof(VERTEX_3D));
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
        Vertex.at(nCounter).Vertex.x = Transform.Position.x + Transform.Scale.x * (nCounter >> 1);
        Vertex.at(nCounter).Vertex.y = Transform.Position.y + Transform.Scale.y * (nCounter & 1);
        Vertex.at(nCounter).Vertex.z = 0.0F;
        Vertex.at(nCounter).Normal = D3DXVECTOR3(0.0F, 0.0F, -1.0F);
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
        Vertex.at(nCounter).Texture.x = (float)(nCounter & 1);
        Vertex.at(nCounter).Texture.y = (float)((nCounter >> 1) & 1);
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
void BILLBOARD::Update(DWORD number)
{
    //---�e��錾---//
    int nCounter;       //�J�E���^�[
    float fU;           //U�l
    float fV;           //V�l

    //---�l�Z�o---//
    fU = (number % UV.x) * (1.0F / UV.x);
    fV = (number / UV.x) * (1.0F / UV.y);

    //---�l�X�V---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Texture.x = fU + (nCounter % 2) * (1.0F / UV.x);
        Vertex.at(nCounter).Texture.y = fV + (nCounter / 2) * (1.0F / UV.y);
    }
}