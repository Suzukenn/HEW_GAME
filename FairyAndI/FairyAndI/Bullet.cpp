//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "Texture.h"
#include "TextureManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBULLET
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BULLET::BULLET(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~BULLET
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BULLET::~BULLET(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�e�ۂ̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::Draw(void)
{
    BillBoard.Draw(Transform.Position);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�e�ۂ̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BULLET::Initialize(LPCTSTR texturename, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Move = D3DXVECTOR3(sinf(Transform.Rotation.y) * 1.5F, 0.0F, 0.0F);
	Tag = TEXT("Bullet");
	Type = type;

    //---�r���{�[�h�̍쐬---//
    hResult = BillBoard.Initialize(texturename, D3DXVECTOR2(5.0F, 5.0F), Transform.Rotation.y > 0.0F);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�e�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.5F, TEXT("Skill"), this);

    return hResult;
}

/////////////////////////////////////////////
//�֐����FOnCollision
//
//�@�\�F�����蔻�蔽�����̋���
//
//�����F(COLLISITON)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::OnCollision(COLLISION* opponent)
{
	ACTORMANAGER::Destroy(this);
	COLLISIONMANAGER::Destroy((COLLISION*)Collision);
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�e�ۂ̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::Uninitialize(void)
{
    //---�J��---//
    BillBoard.Uninitialize();
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�e�ۂ̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BULLET::Update(void)
{
    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/

	Gray = SQUAREGAUGE::GetFairyTime();
    BillBoard.Update();

    if (Gray)
    {
        return;
    }

    ++BornTime;
    if (BornTime > 120)
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
    else
    {
        Transform.Position += Move;
        Collision->Position = Transform.Position;
    }
}