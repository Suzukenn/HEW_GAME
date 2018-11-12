//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "AnimationSprite.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�X�v���C�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONSPRITE::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX_2D);     //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Texture);    //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex, sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�X�v���C�g�̏�����
//
//�����F(LPTSTR)�摜�̃t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONSPRITE::Initialize(D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv, LPCTSTR filepath)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    Position = position;
    Size = size;
    UV = uv;

    pDevice = GetDevice();

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFile(pDevice, filepath, &Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�X�`���̏������Ɏ��s���܂���"), filepath, MB_OK);
        Texture = nullptr;
        return hResult;
    }

    //---�����l�̐ݒ�---//
    for (nCounter = 0; nCounter < 4; nCounter++)
    {
        SetSpriteUV(1);
        Vertex.at(nCounter).Position.x = Position.x + Size.x * (nCounter & 1);
        Vertex.at(nCounter).Position.y = Position.y + Size.y * ((nCounter >> 1) & 1);
        Vertex.at(nCounter).Position.z = 0.0F;
        Vertex.at(nCounter).RHW = 1.0F;
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FSetSpriteUV
//
//�@�\�F�A�j���[�V�����̍X�V
//
//�����F(int)�t���[���ԍ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONSPRITE::SetSpriteUV(int number)
{
    //---�e��錾---//
    int nCounter;       //�J�E���^�[
    float fU;           //U�l
    float fV;           //V�l

    //---�l�Z�o---//
    fU = (number % UV.x) * (1.0F / UV.x);
    fV = (number / UV.y) * (1.0F / UV.y);

    //---�l�X�V---//
    for (nCounter = 0; nCounter < 4; nCounter++)
    {
        Vertex.at(nCounter).U = fU + (nCounter % 2) * (1.0F / UV.x);
        Vertex.at(nCounter).V = fV + (nCounter >> 1) * (1.0F / UV.y);
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�X�v���C�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONSPRITE::Uninitialize(void)
{
    //---�J��---//
    SAFE_RELEASE(Texture);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONSPRITE::Update(void)
{

}