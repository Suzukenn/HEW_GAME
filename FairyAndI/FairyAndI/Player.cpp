//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "SkillFactory.h"
#include "WordMenu.h"

//�������萔�E�}�N����`������//
#define GRAVITY 0.18F
#define JUMP 5.0F

static D3DXVECTOR3 pos;
static D3DXVECTOR3 rot;

/////////////////////////////////////////////
//�֐����FPLAYER
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
PLAYER::PLAYER(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
}

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�v���C���[�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Draw(void)
{
    //---�e��錾---//
    D3DXMATRIX mtxWorld;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);

    //---�`��---//
    Model.Draw(mtxWorld);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�v���C���[�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT PLAYER::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    //�ʒu�E�����̏����ݒ�
    Transform.Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Transform.Rotation = D3DXVECTOR3(270.0F, 270.0F, 0.0F);
    Transform.Scale = D3DXVECTOR3(0.1F, 0.1F, 0.1F);
    Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    Tag = tag;

    //---���f���̓ǂݍ���---//
    hResult = Model.Initialize(TEXT("Data/Common/Model/Character/tiny_4anim.x"));
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�v���C���[�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }
    else
    {
        Model.ChangeAnimation(0);
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Transform.Position.x + 5.0F, Transform.Position.y + 5.0F, Transform.Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Character"), this);

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
void PLAYER::OnCollision(COLLISION* opponent)
{
    //Position = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�v���C���[�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Uninitialize(void)
{
    SAFE_RELEASE(Texture);
    SAFE_RELEASE(Mesh);
    SAFE_RELEASE(MaterialBuffer);

    Model.Uninitialize();

    ACTORMANAGER::Destroy(this);
    COLLISIONMANAGER::Destroy((COLLISION*)Collision);
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�v���C���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void PLAYER::Update(void)
{
    //---�e��錾---//
    D3DXVECTOR3 vecInstancePosition;
    D3DXVECTOR2 vecStickVector;
    D3DXVECTOR3 vecCameraRotation;

    //---����������---//
    Move.x = 0.0F;

    //---�ړ�����---//
	//�J�����̌����擾
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	//�d�͉��Z
	Move.y -= GRAVITY;

    //���f������
    if (vecStickVector != D3DXVECTOR2(0.0F, 0.0F))
    {
        //�ړ�
        Move.x += VALUE_MOVE_PLAYER * vecStickVector.x;

        //��]
        Transform.Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));
    }

	//�W�����v
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
        //�W�����v�͂̕t�^
        Move.y += JUMP;
	}

	//---�ʒu���X�V---//
    Transform.Position += Move;

	//�ړ�����
	if (Transform.Position.y < 0.0F)
	{
        Transform.Position.y = 0.0F;
		Move.y = 0.0F;
	}
	if (Transform.Position.x > 1500.0F)
	{
        Transform.Position.x = 1500.0F;
	}
	else if (Transform.Position.x < -1500.0F)
	{
        Transform.Position.x = -1500.0F;
	}

    //---�A�C�e������---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        vecInstancePosition.x = Transform.Position.x + sinf(D3DXToRadian(Transform.Rotation.y)) * 10.0F + cosf(D3DXToRadian(Transform.Rotation.y)) * 8.0F;
        vecInstancePosition.y = Transform.Position.y + 21.0F;
        vecInstancePosition.z = 0.0F;

        SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationItem(), vecInstancePosition, Transform.Rotation);
    }

    pos = Transform.Position;
    rot = Transform.Rotation;

    if (Move.x)
    {
        Model.ChangeAnimation(1);
    }
    else
    {
        Model.ChangeAnimation(0);
    }

    if (Move.y != 0.0F)
    {
        Model.ChangeAnimation(2);
    }

}

// ���f���ʒu�̎擾
const D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return pos;
}

// ���f�������̎擾
const D3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return rot;
}