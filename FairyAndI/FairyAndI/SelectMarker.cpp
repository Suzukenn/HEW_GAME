//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SelectMarker.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�I���}�[�J�[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTMARKER::Draw(void)
{
    ANIMATIONSPRITE::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�I���}�[�J�[�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SELECTMARKER::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = ANIMATIONSPRITE::Initialize(texturename, position, size);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�̗̓n�[�g�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�I���}�[�J�[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTMARKER::Uninitialize(void)
{
    ANIMATIONSPRITE::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�I���}�[�J�[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTMARKER::Update(void)
{
    //---�e��錾---//
    int nCounter;
    static int nPositionNumber = 0;

    const static D3DXVECTOR2 vecPosition[2] = { D3DXVECTOR2(390.0F, 120.0F), D3DXVECTOR2(740.0F, 120.0F) };

    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER, TRIGGER))
    {
        nPositionNumber = !nPositionNumber;

        for (nCounter = 0; nCounter < 4; ++nCounter)
        {
            Vertex.at(nCounter).Position.x = vecPosition[nPositionNumber].x + (nCounter & 1) * Size.x;
            Vertex.at(nCounter).Position.y = vecPosition[nPositionNumber].y + ((nCounter >> 1) & 1) * Size.y;
        }
    }
}