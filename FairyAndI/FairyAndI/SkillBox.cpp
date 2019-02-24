//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SkillBox.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�X�L���{�b�N�X�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLBOX::Draw(void)
{
    ANIMATIONSPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�X�L���{�b�N�X�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SKILLBOX::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size, POINT uv)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = ANIMATIONSPRITE::Initialize(texturename, position, size, uv);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�̗̓n�[�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�X�L���{�b�N�X�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLBOX::Uninitialize(void)
{
    //---�J��---//
    ANIMATIONSPRITE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�X�L���{�b�N�X�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SKILLBOX::Update(void)
{
    //---�e��錾---//
    static int nFrameTime = 0;

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        nFrameTime = 30;
        SetSpriteUV(1);
    }

    if (nFrameTime)
    {
        --nFrameTime;
        if (nFrameTime <= 0)
        {
            nFrameTime = 0;
            SetSpriteUV(0);
        }
    }
}