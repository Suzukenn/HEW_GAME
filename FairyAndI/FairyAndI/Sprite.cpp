//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Sprite.h"

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
    pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_2D)); //���_�����ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);                                  //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, Texture);                              //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
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
HRESULT SPRITE::Initialize(D3DXVECTOR2 position, D3DXVECTOR2 size, LPCTSTR filepath)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;
    LPDIRECT3DDEVICE9 pDevice;

    VERTEX_2D* pVertex;

    //---����������---//
    pDevice = GetDevice();

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = D3DXCreateTextureFromFile(pDevice, filepath, &Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�X�`���̏������Ɏ��s���܂���"), filepath, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�̐���---//
    hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &VertexBuffer, nullptr);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�N�X�`���̏������Ɏ��s���܂���"), filepath, MB_OK);
        Uninitialize();
        return hResult;
    }

    //---���_�o�b�t�@�ւ̒l�̐ݒ�---//
    //�o�b�t�@�̃|�C���^���擾
    VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

    //�l�̐ݒ�
    for (nCounter = 0; nCounter < 4; nCounter++)
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
    VertexBuffer->Unlock();

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
    SAFE_RELEASE(Texture);
    SAFE_RELEASE(VertexBuffer);
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