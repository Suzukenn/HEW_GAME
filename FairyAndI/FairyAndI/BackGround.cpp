//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackGround.h"

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
void BACKGROUND::Draw(void)
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
//�@�\�F�w�i�̏�����
//
//�����F(LPTSTR)�摜�̃t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BACKGROUND::Initialize(LPCTSTR filepath)
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
		MessageBox(nullptr, TEXT("�w�i�̓ǂݍ��݂Ɏ��s���܂���"), filepath, MB_OK);
        Texture = nullptr;
		return hResult;
	}

	//---���_�o�b�t�@�̐���---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &VertexBuffer, nullptr);
	if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�w�i�̒��_�o�b�t�@�̐����Ɏ��s���܂���"), filepath, MB_OK);
		return hResult;
	}

	//---���_�o�b�t�@�ւ̒l�̐ݒ�---//
	//�o�b�t�@�̃|�C���^���擾
    hResult = VertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̒��_�o�b�t�@�̃|�C���^�̎擾�Ɏ��s���܂���"), filepath, MB_OK);
        return hResult;
    }
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
    hResult = VertexBuffer->Unlock();
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̒��_�o�b�t�@�̃|�C���^�̊J���Ɏ��s���܂���"), filepath, MB_OK);
        return hResult;
    }

	return hResult;
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
void BACKGROUND::Uninitialize(void)
{
	//---�J��---//
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(Texture)
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
void BACKGROUND::Update(void)
{

}