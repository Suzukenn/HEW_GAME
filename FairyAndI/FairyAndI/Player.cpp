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
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxScale;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�傫����ݒ�
    D3DXMatrixScaling(&mtxScale, 0.1F, 0.1F, 0.1F);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

    //��]�𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRotation, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

    //�ړ��𔽉f
    D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

    //�ݒ�
    GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

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
    Position = D3DXVECTOR3(0.0F, 10.0F, 0.0F);
    Rotation = D3DXVECTOR3(270.0F, 270.0F, 0.0F);
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
    //Collision = COLLISIONMANAGER::InstantiateToOBB(D3DXVECTOR3(Position.x + 5.0F, Position.y + 5.0F, Position.z + 5.0F), D3DXVECTOR3(5.0F, 5.0F, 5.0F), TEXT("Character"), this);

    return S_OK;// hResult;
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
    DWORD dwAnime;
    bool bMove;

    //---����������---//
    Move.x = 0.0F;
    Move.z = 0.0F;
    bMove = false;

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
        Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));

        bMove = true;
    }

	//�W�����v
	if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
	{
        //�W�����v�͂̕t�^
        Move.y += JUMP;
	}

	//---�ʒu���X�V---//
    Position += Move;

	//�ړ�����
	if (Position.y < 0.0F)
	{
        Position.y = 0.0F;
		Move.y = 0.0F;
	}
	if (Position.x > 1500.0F)
	{
        Position.x = 1500.0F;
	}
	else if (Position.x < -1500.0F)
	{
        Position.x = -1500.0F;
	}

    //---�A�C�e������---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        vecInstancePosition.x = Position.x - sinf(Rotation.y) * 10.0F - cosf(Rotation.y) * 8.0F;
        vecInstancePosition.y = Position.y + 21.0F;
        vecInstancePosition.z = 0.0F;

        SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationItem(), vecInstancePosition, Rotation);
    }

    pos = Position;
    rot = Rotation;

    if (Move.y != 0.0F)
    {
        dwAnime = 2;
        Model.ChangeAnimation(dwAnime);

    }
    else
    {
        if (bMove)
        {
            dwAnime = 1;
            Model.ChangeAnimation(dwAnime);

        }
        else
        {
            dwAnime = 0;
            Model.ChangeAnimation(dwAnime);
        }
    }

    if (INPUTMANAGER::GetKey(DIK_0, TRIGGER))
    {
        Model.ChangeAnimation(0);
    }
    else if (INPUTMANAGER::GetKey(DIK_1, TRIGGER))
    {
        Model.ChangeAnimation(1);
    }
    else if (INPUTMANAGER::GetKey(DIK_2, TRIGGER))
    {
        Model.ChangeAnimation(2);
    }
    else if (INPUTMANAGER::GetKey(DIK_3, TRIGGER))
    {
        Model.ChangeAnimation(3);
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