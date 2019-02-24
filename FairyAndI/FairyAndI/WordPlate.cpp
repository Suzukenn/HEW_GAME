//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "TextureManager.h"
#include "WordPlate.h"
#include "WordManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���[�h�v���[�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDPLATE::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F���[�h�v���[�g�̏�����
//
//�����F(LPCTSTR)�摜�̃t�@�C����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDPLATE::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h�v���[�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }
    hResult = SetTexture(TEXT("EMPTY"));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("���[�h�v���[�g�����̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���[�h�v���[�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDPLATE::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F���[�h�v���[�g�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WORDPLATE::Update(void)
{
}

/////////////////////////////////////////////
//�֐����FSetTexture
//
//�@�\�F���[�h�v���[�g�̓K�p�e�N�X�`���̐ݒ�
//
//�����F(tstring)�e�N�X�`����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WORDPLATE::SetTexture(LPCTSTR texturename)
{
    if (FAILED(WORDMANAGER::GetWordTexture(texturename, Texture)))
    {
        MessageBox(nullptr, TEXT("���[�h�v���[�g�̓K�p�e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�ݒ�G���["), MB_OK);
        Uninitialize();
        return E_FAIL;
    }
    return S_OK;
}