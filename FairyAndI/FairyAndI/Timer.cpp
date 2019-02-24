//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Timer.h"
#include "Texture.h"
#include "TextureManager.h"

//�������萔�E�}�N����`������//
//�e�N�X�`��������
#define TIME_DIV_U			(10)	//��������
#define TIME_DIV_V			(1)		//�c������

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�^�C�}�[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TIMER::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;
    std::shared_ptr<TEXTURE> pTexture;

    //---����������---//
    pDevice = GetDevice();
    pTexture = Texture.lock();
    if (!pTexture)
    {
        MessageBox(nullptr, TEXT("�`��Ώۂ̃e�N�X�`�������݂��܂���"), TEXT("�`��G���["), MB_OK);
    }

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX_2D);             //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, pTexture->Image);    //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, Length * 4 - 2, &Vertex, sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�^�C�}�[�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����, (D3DXVECTOR2)�ʒu , (D3DXVECTOR2)�T�C�Y, (int)��������
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TIMER::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, int timer)
{
	//---�e��錾---//
	int nCounter;
	HRESULT hResult;

	//---����������---//
	Position = position;
	Size = size;
	Length = MAX_LENGTH;
	Timer = timer;
	VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9);

	//---�e�N�X�`���̓ǂݍ���---//
	hResult = TEXTUREMANAGER::GetTexture(texturename, Texture);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�^�C�}�[�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}

	//---���_�o�b�t�@�̐���---//
	hResult = GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�^�C�}�[�̒��_�o�b�t�@�̐����Ɏ��s���܂���"), texturename, MB_OK);
		Uninitialize();
		return hResult;
	}

	//---���_�o�b�t�@�ւ̒l�̐ݒ�---//
	//�o�b�t�@�̃|�C���^���擾
	hResult = (*VertexBuffer)->Lock(0, 0, (void**)&Vertex, 0);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�^�C�}�[�̒��_�o�b�t�@�̃|�C���^�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}
	for (int i = Length - 1; i >= 0; --i)
	{
		//�l�̐ݒ�
		for (nCounter = 0; nCounter < 4; ++nCounter)
		{
			Vertex.at(i * 4 + nCounter).U = (float)(nCounter & 1);
			Vertex.at(i * 4 + nCounter).V = (float)((nCounter >> 1) & 1);
			Vertex.at(i * 4 + nCounter).Position.x = position.x + Vertex[nCounter].U * Size.x;
			Vertex.at(i * 4 + nCounter).Position.y = position.y + Vertex[nCounter].V * Size.y;
			Vertex.at(i * 4 + nCounter).Position.z = 0.0F;
			Vertex.at(i * 4 + nCounter).RHW = 1.0F;
			Vertex.at(i * 4 + nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
	}
	//�o�b�t�@�̃|�C���^�̉��
	hResult = (*VertexBuffer)->Unlock();
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�^�C�}�[�̒��_�o�b�t�@�̃|�C���^�̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}

	return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�^�C�}�[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TIMER::Uninitialize(void)
{

}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�^�C�}�[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TIMER::Update(void)
{
    //---�e��錾---//
	static int nCnt;							//�b���J�E���g���邽��
	const float dx[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	const float dy[] = { 1.0f, 0.0f, 1.0f, 0.0f };
	Length = MAX_LENGTH;
	int timer;

	timer = Timer;

	///�V�[���̐ؑցi�^�C���I�[�o�[�j
	//if (Timer < 1)
	//{
	//	//if (EndFadeIn())
	//	//{
	//	//	StartFadeOut();
	//	//}
	//	//if (EndFadeOut())
	//	//{
	//	//	SetScene(SCENE_GAMEOVER);
	//	//}
	//}

	nCnt++;
	if (nCnt > 60)
	{
		Timer--;
		nCnt = 0;
	}

	//�^�C�}�[�I��(��)
	if (Timer < 1)
	{
		Timer = 0;
	}

	if (Length < 1)								//�l��1�����̂Ƃ�
	{
		Length = 1;
	}
	else if (Length > MAX_LENGTH)				//�l���ő�l���傫��������
	{
		Length = MAX_LENGTH;
	}
	for (int i = Length - 1; i >= 0; --i)
	{
		int n = timer % 10;
		timer /= 10;
		int u = n % TIME_DIV_U;
		int v = n / TIME_DIV_V;

		for (int j = 0; j < 4; ++j)
		{
			// �ʒu���X�V
			Vertex.at(i * 4 + j).Position.x = Position.x + (dx[j] + i) * Size.x;
			Vertex.at(i * 4 + j).Position.y = Position.y + dy[j] * Size.y;
			// �t���[���ݒ�
			Vertex.at(i * 4 + j).U = (u + dx[j]) * (1.0f / TIME_DIV_U);
			Vertex.at(i * 4 + j).V = (v + dy[j]) * (1.0f / TIME_DIV_V);
		}
	}
   
}