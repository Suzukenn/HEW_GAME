//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "EffectFactory.h"
#include "Field.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SideViewCamera.h"
#include "SkillFactory.h"
#include "SoundManager.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "WordMenu.h"

//�������萔�E�}�N����`������//
#define GRAVITY 0.018F
#define JUMP 0.75F

//�������O���[�o���錾������//
int hp;
D3DXVECTOR3 pos;
D3DXVECTOR3 rot;
PLAYERSTATE state;

/////////////////////////////////////////////
//�֐����FPLAYER
//
//�@�\�F�R���X�g���N�^
//
//�����F(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
PLAYER::PLAYER(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(position, rotation);
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
    Model->Draw(mtxWorld, Gray);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�v���C���[�̏�����
//
//�����F((D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT PLAYER::Initialize(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(100.0F, 100.0F, 100.0F);
    HP = MAX_PLAYER_HP;
    State = PLAYERSTATE_WAIT;
    Gray = false;
    Jump = false;
    IsGround = false;
    Vibration = 0;
    AnimationTime = 0;
	NotCollision = 0;
    Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
    VibrationPower = D3DXVECTOR2(0.0F, 0.0F);
    Tag = TEXT("Player");

    //---���f���̓ǂݍ���---//
    hResult = ANIMATIONMODELMANAGER::GetModel(TEXT("PLAYER"), Model);
    if(FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�v���C���[�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }
    else
    {
        Model->ChangeAnimation(State);
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Player"), this);

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
	if (opponent->Owner->GetTag() == TEXT("Enemy") || opponent->Owner->GetTag() == TEXT("EnemyBullet") || opponent->Owner->GetTag() == TEXT("FireGimmick"))
	{
		if (!NotCollision)
		{
			Transform.Position.x -= 15.0F;
			Model->ChangeAnimation(PLAYERSTATE_DAMAGE);
			Model->SetSpeed(1.3);
			--HP;
			State = PLAYERSTATE_DAMAGE;
			AnimationTime = 90;
			VibrationPower = D3DXVECTOR2(0.7F, 0.7F);
			Vibration = 45;
			NotCollision = 240;
		}
	}
	else
	{
		Transform.Position.x -= Move.x;
	}
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
    Model->Uninitialize();
    ACTORMANAGER::Destroy(this);
    COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    Collision = nullptr;
	INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
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

    //---�t���[�Y����---//
	Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        Model->SetSpeed(0.0);
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        return;
    }
    else
    {
        Model->SetSpeed(1.0);
        INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, VibrationPower.x, VibrationPower.y);
    }

    //---�o�C�u���[�V����---//
    if (--Vibration <= 0)
    {
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        VibrationPower = D3DXVECTOR2(0.0F, 0.0F);
        Vibration = 0;
    }

    //---�ړ�����---//
	//�J�����̌����擾
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	//�d�͉��Z
    if (!IsGround)
    {
        Move.y -= GRAVITY;
        if (State != PLAYERSTATE_JUMP)
        {
            State = PLAYERSTATE_FALL;
        }
    }

    //���n����
	if (Transform.Position.y <= 11.0F)
	{
		Transform.Position.y = 11.0F;
		Move.y = 0.0F;
		Jump = false;
		IsGround = true;
		if (State != PLAYERSTATE_ATTACK && State != PLAYERSTATE_DAMAGE)
		{
		    State = PLAYERSTATE_WAIT;
		}
	}
    else
    {
        State = PLAYERSTATE_FALL;
        IsGround = false;
    }

    //---���f������---//
    //�ړ�
    if (State != PLAYERSTATE_ATTACK && State != PLAYERSTATE_DAMAGE && vecStickVector != D3DXVECTOR2(0.0F, 0.0F))
    {
        Move.x += VALUE_MOVE_PLAYER * vecStickVector.x;

        //�����ɉ����ĉ�]
        Transform.Rotation.y = 90.0F * ((vecStickVector.x > 0.0F) - (vecStickVector.x < 0.0F));

        if (IsGround)
        {
            State = PLAYERSTATE_WALK;
        }
        if (!SOUNDMANAGER::CheckPlay(TEXT("SE_PLAYER_WALK")))
        {
            SOUNDMANAGER::Play(TEXT("SE_PLAYER_WALK"));
        }
    }
    
    else
    {
        SOUNDMANAGER::Stop(TEXT("SE_PLAYER_WALK"));
    }

	//�W�����v
    if (!Jump && State != PLAYERSTATE_ATTACK && State != PLAYERSTATE_DAMAGE)
    {
        if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_A, TRIGGER))
        {
            Move.y += JUMP;
            Jump = true;
            IsGround = false;
            AnimationTime = 50;
            State = PLAYERSTATE_JUMP;
        }
    }
    if (State == PLAYERSTATE_JUMP)
    {
        if (!--AnimationTime)
        {
            State = PLAYERSTATE_FALL;
        }
    }

	if (State == PLAYERSTATE_DAMAGE)
	{
		if (!--AnimationTime)
		{
			State = PLAYERSTATE_WAIT;
			Model->SetSpeed(1.0);
		}
	}

	//---�ʒu���X�V---//
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
	else if (Transform.Position.x < 50.0F)
	{
        Transform.Position.x = 50.0F;
	}

	//�ړ��𔽉f
	Transform.Position += Move;
	Collision->Position = Transform.Position;

    //---�X�L������---//
    if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_B, TRIGGER))
    {
        if (IsGround)
        {
           State = PLAYERSTATE_ATTACK;
           AnimationTime = 130;
        }
    }

    //�U��
    if (State == PLAYERSTATE_ATTACK)
    {
        Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
        --AnimationTime;

        //���X�g30�t���[���ŃX�L���E�G�t�F�N�g����
        if (AnimationTime == 70)
        {
            vecInstancePosition.x = Transform.Position.x + sinf(D3DXToRadian(Transform.Rotation.y)) * 4.0F + cosf(D3DXToRadian(Transform.Rotation.y));
            vecInstancePosition.y = Transform.Position.y + 5.0F;
            vecInstancePosition.z = 0.0F;

            SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationAdjective(), WORDMENU::NotificationNoun(), vecInstancePosition, Transform.Rotation);
            EFFECTFACTORY::InstantiateSkillEffect(vecInstancePosition, D3DXVECTOR2(5.0F, 5.0F), false);
            VibrationPower = D3DXVECTOR2(0.4F, 0.4F);
            INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, VibrationPower.x, VibrationPower.y);
            Vibration = 30;

            SOUNDMANAGER::Stop(tstring(TEXT("SE_SKILL_TYPE") + WORDMENU::NotificationNoun()).data());
            SOUNDMANAGER::Play(tstring(TEXT("SE_SKILL_TYPE") + WORDMENU::NotificationNoun()).data());
        }

        //0�t���[���őҋ@�Ɉڍs
        else if (!AnimationTime)
        {
            State = PLAYERSTATE_WAIT;
        }
    }

	if (NotCollision)
	{
		--NotCollision;
	}

    Model->ChangeAnimation(State);

    hp = HP;
    pos = Transform.Position;
    rot = Transform.Rotation;
    state = State;
}

/////////////////////////////////////////////
//�֐����FGetPlayerHP
//
//�@�\�F�v���C���[�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
int PLAYER::GetPlayerHP(void)
{
    return hp;
}

/////////////////////////////////////////////
//�֐����FGetPlayerPosition
//
//�@�\�F�v���C���[�̈ʒu�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return pos;
}

/////////////////////////////////////////////
//�֐����FGetPlayerRotation
//
//�@�\�F�v���C���[�̌����̎擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
D3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return rot;
}

/////////////////////////////////////////////
//�֐����FGetPlayerState
//
//�@�\�F�v���C���[�̃X�e�[�g�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
PLAYERSTATE PLAYER::GetPlayerState(void)
{
    return state;
}
