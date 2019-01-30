//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Fade.h"

// ���_�t�H�[�}�b�g
#define FVF_VERTEX_FADE	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//�������O���[�o���錾������//
int FADE::Fade;
int FADE::Alpha;
int FADE::Directory;
std::array<VERTEX_2D, 4> FADE::Vertex;

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�t�F�[�h�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FADE::Draw(void)
{
	//---�e��錾---//
	LPDIRECT3DDEVICE9 pDevice;

	//---����������---//
	pDevice = GetDevice();

	// ���_�����ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, NULL);

	// ���_�z��ɂ��|���S���`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &Vertex, sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�t�F�[�h�̏�����
//
//�����F�Ȃ�
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FADE::Initialize(void)
{
	//---�e��錾---//
	int nCounter;
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//---����������---//
	Alpha = 255;
	Directory = 0;
	Fade = 0;

	Vertex.at(0).Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
	Vertex.at(1).Position = D3DXVECTOR3(1.0F, 0.0F, 0.0F);
	Vertex.at(2).Position = D3DXVECTOR3(1.0F, 1.0F, 0.0F);
	Vertex.at(3).Position = D3DXVECTOR3(0.0F, 1.0F, 0.0F);

	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; ++nCounter)
	{
		Vertex.at(nCounter).Position.x *= SCREEN_WIDTH;
		Vertex.at(nCounter).Position.y *= SCREEN_HEIGHT;
		Vertex.at(nCounter).Position.z = 0.0F;
		Vertex.at(nCounter).RHW = 1.0F;
		Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	return S_OK;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�t�F�[�h�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FADE::Uninitialize(void)
{

}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�t�F�[�h�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FADE::Update(void)
{
    //---�e��錾---//
    int nCounter;
    D3DCOLOR dwColor;

	Fade += Directory;
	if (Fade < 0)
	{
		Fade = 0;
	}
	else if (Fade > 60)
	{
		Fade = 60;
	}
	Alpha = Fade * 255 / 60;
	dwColor = D3DCOLOR_ARGB(Alpha, 0, 0, 0);
	for (nCounter = 0; nCounter < 4; ++nCounter)
	{
		Vertex.at(nCounter).Diffuse = dwColor;
	}
}

/////////////////////////////////////////////
//�֐����FSetFade
//
//�@�\�F�t�F�[�h�̃Z�b�g
//
//�����F(FADE)�t�F�[�h�̃^�C�v
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FADE::SetFade(FADETYPE fadetype)
{
	switch (fadetype)
	{
	    case FADE_IN:
		    Fade = 60;
		    Directory = -1;
		    break;

	    case FADE_OUT:
		    Fade = 0;
		    Directory = 1;
		    break;

	    default:
		    break;
	}
}

/////////////////////////////////////////////
//�֐����FCheckFadeEnd
//
//�@�\�F�t�F�[�h�����̔���
//
//�����F�Ȃ�
//
//�߂�l�F(int)
/////////////////////////////////////////////
bool FADE::CheckFadeEnd(FADETYPE fadetype)
{
	switch (fadetype)
	{
	    case FADE_IN:
            return Directory < 0 && Fade <= 0 ? true : false;

	    case FADE_OUT:
            return Directory > 0 && Fade >= 60 ? true : false;

	    default:
            return false;
	}
}