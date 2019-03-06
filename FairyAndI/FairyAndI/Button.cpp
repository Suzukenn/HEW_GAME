//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "Button.h"
#include "InputManager.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�{�^���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Draw(void)
{
    SPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�{�^���̏�����
//
//�����F(LPCTSTR)�摜�̃t�@�C����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BUTTON::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = SPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�{�^���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�{�^���̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Uninitialize(void)
{
    SPRITE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�{�^���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BUTTON::Update(void)
{
    ////---�e��錾---//
    //D3DXVECTOR2 vecCursorPoition;

    ////---����������---//
    //vecCursorPoition.x = (FLOAT)INPUTMANAGER::GetMousePosition().x;
    //vecCursorPoition.y = (FLOAT)INPUTMANAGER::GetMousePosition().y;

    ////---����---//
    //if (Position.x < vecCursorPoition.x && vecCursorPoition.x < (Position.x + Size.x))
    //{
    //    if (Position.y < vecCursorPoition.y && vecCursorPoition.y < (Position.y + Size.y))
    //    {
            Behavior();
       /* }
    }*/
}