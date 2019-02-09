//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackImage.h"
#include "TextureManager.h"



void BACKIMAGE::Draw(void)
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

HRESULT BACKIMAGE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{	
	//---�e��錾---//
	int nCounter;
	HRESULT hResult;
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVertex;

	//---����������---//
	Position = position;
	Size = size;
	pDevice = GetDevice();
	Texture.reset(new LPDIRECT3DTEXTURE9());
	VertexBuffer.reset(new LPDIRECT3DVERTEXBUFFER9());

	//---�e�N�X�`���̓ǂݍ���---//

	hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
	// ���_���̍쐬

	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�w�i�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}

	// ---���_�o�b�t�@�̐���---//
	hResult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, VertexBuffer.get(), nullptr);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�w�i�̒��_�o�b�t�@�̐����Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}

	//---���_�o�b�t�@�ւ̒l�̐ݒ�---//
	//�o�b�t�@�̃|�C���^���擾
	hResult = (*VertexBuffer)->Lock(0, 0, (void**)&pVertex, 0);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�w�i�̒��_�o�b�t�@�̃|�C���^�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}
	//�l�̐ݒ�
	for (nCounter = 0; nCounter < 4; ++nCounter)
	{
		pVertex[nCounter].U = (float)(nCounter & 1);
		pVertex[nCounter].V = (float)((nCounter >> 1) & 1);
		pVertex[nCounter].Position.x = position.x + pVertex[nCounter].U * Size.x;
		pVertex[nCounter].Position.y = position.y + pVertex[nCounter].V * Size.y;
		pVertex[nCounter].Position.z = 300.0F;
		pVertex[nCounter].RHW = 1.0F;
		pVertex[nCounter].Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	//�o�b�t�@�̃|�C���^�̉��
	hResult = (*VertexBuffer)->Unlock();
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�w�i�̒��_�o�b�t�@�̃|�C���^�̊J���Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}

	return hResult;
}

void BACKIMAGE::Update(void)
{


}

void BACKIMAGE::Uninitialize(void)
{


}