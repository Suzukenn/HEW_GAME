//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "BackImage.h"
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
void BACKIMAGE::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F(LPCTSTR)�e�N�X�`��,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BACKIMAGE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{	
	//---�e��錾---//
	HRESULT hResult;

    //---����������---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
    }

	return hResult;
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BACKIMAGE::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BACKIMAGE::Update(void)
{

}
