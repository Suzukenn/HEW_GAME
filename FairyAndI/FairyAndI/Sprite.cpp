//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Sprite.h"
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
void SPRITE::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetStreamSource(0, *VertexBuffer, 0, sizeof(VERTEX_2D)); //���_�����ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);                                   //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, *Texture);                                 //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�X�v���C�g�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SPRITE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    VERTEX_2D* pVertex;

    //---����������---//
    Position = position;
    Size = size;
    Texture.reset(new LPDIRECT3DTEXTURE9());
    VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9());

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�X�v���C�g�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�̐���---//
    hResult = GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�X�v���C�g�̒��_�o�b�t�@�̐����Ɏ��s���܂���"), texturename, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�ւ̒l�̐ݒ�---//
    //�o�b�t�@�̃|�C���^���擾
    hResult = (*VertexBuffer)->Lock(0, 0, (void**)&pVertex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�X�v���C�g�̒��_�o�b�t�@�̃|�C���^�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //�l�̐ݒ�
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        pVertex[nCounter].U = (float)(nCounter & 1);
        pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
        pVertex[nCounter].Position.x = pVertex[nCounter].U * SCREEN_WIDTH;
        pVertex[nCounter].Position.y = pVertex[nCounter].V * SCREEN_HEIGHT;
        pVertex[nCounter].Position.z = 0.0F;
        pVertex[nCounter].RHW = 1.0F;
        pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //�o�b�t�@�̃|�C���^�̉��
    hResult = (*VertexBuffer)->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�X�v���C�g�̒��_�o�b�t�@�̃|�C���^�̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    return hResult;
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
void SPRITE::Uninitialize(void)
{
    //---�J��---//
    SAFE_RELEASE((*VertexBuffer));
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
void SPRITE::Update(void)
{

}