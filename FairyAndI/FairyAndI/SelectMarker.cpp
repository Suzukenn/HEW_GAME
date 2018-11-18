//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "InputManager.h"
#include "SelectMarker.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�X�v���C�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTMARKER::Draw(void)
{
    //---�e��錾---//
    LPDIRECT3DDEVICE9 pDevice;

    //---����������---//
    pDevice = GetDevice();

    //---�����ݒ�---//
    pDevice->SetFVF(FVF_VERTEX_2D);     //�t�H�[�}�b�g�ݒ�
    pDevice->SetTexture(0, *Texture);   //�e�N�X�`���ݒ�

    //---���_�o�b�t�@�ɂ��w�i�`��---//
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex, sizeof(VERTEX_2D));
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�X�v���C�g�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR2)�ʒu,(D3DXVECTOR2)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SELECTMARKER::Initialize(LPCTSTR texturename, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
    //---�e��錾---//
    int nCounter;
    HRESULT hResult;

    //---����������---//
    Position = position;
    Size = size;
    Texture.reset(new LPDIRECT3DTEXTURE9());

    //---�e�N�X�`���̓ǂݍ���---//
    hResult = TEXTUREMANAGER::GetTexture(texturename, *Texture);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̃e�N�X�`���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����l�̐ݒ�---//
    for (nCounter = 0; nCounter < 4; ++nCounter)
    {
        Vertex.at(nCounter).U = (float)(nCounter & 1);
        Vertex.at(nCounter).V = (float)((nCounter >> 1) & 1);
        Vertex.at(nCounter).Position.x = position.x + Vertex.at(nCounter).U * Size.x;
        Vertex.at(nCounter).Position.y = position.y + Vertex.at(nCounter).V * Size.y;
        Vertex.at(nCounter).Position.z = 0.0F;
        Vertex.at(nCounter).RHW = 1.0F;
        Vertex.at(nCounter).Diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    return hResult;
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�X�v���C�g�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SELECTMARKER::Uninitialize(void)
{
    //---�J��---//
    SAFE_RELEASE((*Texture));
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
            Vertex.at(nCounter).Position.x = vecPosition[nPositionNumber].x + Vertex.at(nCounter).U * Size.x;
            Vertex.at(nCounter).Position.y = vecPosition[nPositionNumber].y + Vertex.at(nCounter).V * Size.y;
        }
    }
}