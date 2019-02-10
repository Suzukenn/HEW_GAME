//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "SquareGauge.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�v���C���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SQUAREGAUGE::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�`��---//
    Back.Draw();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX_2D);         //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, *MemoryTexture); //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &MemoryVertex, sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�v���C���[�̏�����
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SQUAREGAUGE::Initialize(LPCTSTR background, LPCTSTR gauge, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    //---����������---//
    Percent = 0.5F;
    Size = size;
    MemoryTexture.reset(new LPDIRECT3DTEXTURE9);

    //�w�i
    hResult = Back.Initialize(background, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�Q�[�W�w�i�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //�Q�[�W������
    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::GetTexture(gauge, *MemoryTexture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�X�v���C�g�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����l�̐ݒ�---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        MemoryVertex.at(nCounter).U = (float)(nCounter & 1);
        MemoryVertex.at(nCounter).V = (float)((nCounter >> 1) & 1);
        MemoryVertex.at(nCounter).Position.x = position.x + MemoryVertex.at(nCounter).U * Size.x;
        MemoryVertex.at(nCounter).Position.y = position.y + MemoryVertex.at(nCounter).V * Size.y;
        MemoryVertex.at(nCounter).Position.z = 0.0F;
        MemoryVertex.at(nCounter).RHW = 1.0F;
        MemoryVertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�v���C���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SQUAREGAUGE::Uninitialize(void)
{
    Back.Uninitialize();
    MemoryTexture.reset(nullptr);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�v���C���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SQUAREGAUGE::Update(void)
{
    MemoryVertex.at(1).Position.x = MemoryVertex.at(0).Position.x + Size.x * Percent;
    MemoryVertex.at(3).Position.x = MemoryVertex.at(2).Position.x + Size.x * Percent;
}