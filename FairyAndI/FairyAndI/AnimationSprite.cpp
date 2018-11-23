//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "AnimationSprite.h"
#include "TextureManager.h"

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
    pDevice->SetTexture(0, *Texture);    //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex.begin(), sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�X�v���C�g�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��,(POINT)UV�����l
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONSPRITE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    //---����������---//
    Position = position;
    Size = size;
    UV = uv;
    Texture.reset(new LPDIRECT3DTEXTURE9());

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����l�̐ݒ�---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        SetSpriteUV(1);
        Vertex.at(nCounter).Position.x = position.x + Vertex.at(nCounter).U * Size.x;
        Vertex.at(nCounter).Position.y = position.y + Vertex.at(nCounter).V * Size.y;
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
    for (nCounter = 0; nCounter < 4; ++nCounter)
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
    SAFE_RELEASE((*Texture));
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