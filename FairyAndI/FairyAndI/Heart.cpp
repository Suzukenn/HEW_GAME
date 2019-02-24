//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Heart.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�̗̓n�[�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void HEART::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�n�[�g�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT HEART::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�̗̓n�[�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
    }
   
    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�n�[�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void HEART::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�n�[�g�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void HEART::Update(void)
{

}