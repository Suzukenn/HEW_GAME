//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "AnimationBackImage.h"
#include "Texture.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONBACKIMAGE::Draw(void)
{
    ANIMATIONSPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F(LPCTSTR)�e�N�X�`��,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��,(POINT)UV�����l
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ANIMATIONBACKIMAGE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = ANIMATIONSPRITE::Initialize(texturename, position, size, uv);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�A�j���[�V�����w�i�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FMoveTexture
//
//�@�\�F�e�N�X�`���̈ړ�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONBACKIMAGE::MoveTexture(void)
{
    //---�e��錾---//
    int nCounter;

    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).U += 0.00075F;
        if (Vertex.at(nCounter).U > 2.0F)
        {
            Vertex.at(nCounter).U = 0.0F;
        }
    }
}

/////////////////////////////////////////////
//�֐����FSetAlpha
//
//�@�\�F�����x�̕ύX
//
//�����F(unsigned char)�����x
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONBACKIMAGE::SetAlpha(unsigned char alpha)
{
    //---�e��錾---//
    int nCounter;

    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(alpha, 255, 255, 255);
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�w�i�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ANIMATIONBACKIMAGE::Uninitialize(void)
{
    ANIMATIONSPRITE::Uninitialize();
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
void ANIMATIONBACKIMAGE::Update(void)
{

}