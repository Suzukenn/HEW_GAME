//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SquareGauge.h"
#include "Texture.h"
#include "TextureManager.h"

bool SQUAREGAUGE::FairyTime;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�l�p�Q�[�W�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SQUAREGAUGE::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pMemoryTexture;

    //---����������---//
    pDevice = GetDevice();
    pMemoryTexture = MemoryTexture.lock();
    if (!pMemoryTexture)
    {
        MessageBox(nullptr, TEXT("�Q�[�W�������̃e�N�X�`�������݂��܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�`��---//

    //������
    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX_2D);                //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, pMemoryTexture->Image); //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &MemoryVertex, sizeof(VERTEX_2D));

    //�w�i
    Back.Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�l�p�Q�[�W�̏�����
//
//�����F(LPCTSTR)�w�i�e�N�X�`����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
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
    Size.x = 207.0F;
    Size.y = 30.0F;
    Percent = 0.5F;
	FairyTime = false;

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
    hResult = TEXTUREMANAGER::GetTexture(gauge, MemoryTexture);
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
        MemoryVertex.at(nCounter).Position.x = position.x + 25.0F + MemoryVertex.at(nCounter).U * Size.x;
        MemoryVertex.at(nCounter).Position.y = position.y + 73.0F + MemoryVertex.at(nCounter).V * Size.y;
        MemoryVertex.at(nCounter).Position.z = 0.0F;
        MemoryVertex.at(nCounter).RHW = 1.0F;
        MemoryVertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�l�p�Q�[�W�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SQUAREGAUGE::Uninitialize(void)
{
    Back.Uninitialize();
    MemoryTexture.reset();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�l�p�Q�[�W�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SQUAREGAUGE::Update(void)
{
	//---�e��錾---//
	int nCounter;
	static int GaugeCnt;	//�Q�[�W�̑����̕b���J�E���g

	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
	{
		FairyTime = FairyTime ? false : Percent >= 1.0F;
	}

	++GaugeCnt;

	if (FairyTime)
	{
		//�Q�[�W����
		if (GaugeCnt > 60 / 10)
		{
			GaugeCnt = 0;
			Percent -= 0.01F;
		}
		//���E�l�␳
		if (Percent < 0.0F)
		{
			FairyTime = false;
			Percent = 0.0F;
		}

	}
	else
	{
		//�Q�[�W����
		if (GaugeCnt > 60 / 20)
		{
			for (nCounter = 0; nCounter < 4; ++nCounter)
			{
				MemoryVertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 128, 128, 128);
			}
			GaugeCnt = 0;
			Percent += 0.01F;
		}
		//���E�l�␳
		if (Percent > 1.0F)
		{
			Percent = 1.0F;
			for (nCounter = 0; nCounter < 4; ++nCounter)
			{
				MemoryVertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
			}
		}
	}

	//�Q�[�W���f
    MemoryVertex.at(1).Position.x = MemoryVertex.at(0).Position.x + Size.x * Percent;
    MemoryVertex.at(3).Position.x = MemoryVertex.at(2).Position.x + Size.x * Percent;
}