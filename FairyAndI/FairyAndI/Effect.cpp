//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Effect.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "SideViewCamera.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FFAIRY
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR2)�傫��,(bool)���],(POINT)UV�����l
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
EFFECT::EFFECT(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted, POINT uv)
{
    Initialize(texturename, position, scale, inverted, uv);
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�w�i�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void EFFECT::Draw(void)
{
    Billboard.Draw(Transform.Position);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�w�i�̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR2)�傫��,(bool)���],(POINT)UV�����l
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT EFFECT::Initialize(LPCTSTR texturename, D3DXVECTOR3 position, D3DXVECTOR2 scale, bool inverted, POINT uv)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Transform.Position = position;
    Transform.Rotation = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(scale.x, scale.y, 1.0F);
    EffectNumber = 0;
    FrameCounter = 0;
    UV = uv;

    hResult = Billboard.Initialize(texturename, scale, inverted, uv);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�w�i�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
void EFFECT::Uninitialize(void)
{
    Billboard.Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�w�i�̍X�V
//
//�����F(float)�ړ���
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void EFFECT::Update(void)
{
    if (++FrameCounter >= 4)
    {
        FrameCounter = 0;
        if (++EffectNumber >= UV.x * UV.y)
        {
            ACTORMANAGER::Destroy(this);
        }
        else
        {
            Billboard.SetUV(EffectNumber);
        }
    }

    Billboard.Update();
}