//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "EffectFactory.h"
#include "Fade.h"
#include "Field.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "SideViewCamera.h"
#include "SkillFactory.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "WordMenu.h"

//�������萔�E�}�N����`������//
#define GRAVITY 0.18F
#define JUMP 5.0F

//�������񋓌^��`������//
enum
{
    STATE_WAIT,
    STATE_WALK,
    STATE_RUN,
    STATE_JUMP,
    STATE_FALL,
    STATE_ATTACK,
    STATE_DAMAGE
};

//�������O���[�o���錾������//
int hp;
D3DXVECTOR3 pos;
D3DXVECTOR3 rot;

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
    State = STATE_WAIT;
    Gray = false;
    Vibration = 0;
    Move = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
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
	/*if (opponent->Owner->GetTag() == TEXT("Goal"))
	{
		FADE::SetFade(FADE_OUT);
		Goal = true;
	}*/
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
    Model->Uninitialize();

    ACTORMANAGER::Destroy(this);

    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
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
    float fAfterYPosition;
    D3DXVECTOR3 vecInstancePosition;
    D3DXVECTOR2 vecStickVector;
    D3DXVECTOR3 vecCameraRotation;
    static D3DXVECTOR2 vecVibration;

    //---����������---//
    Move.x = 0.0F;

    //---�t���[�Y����---//
    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/

	Gray = SQUAREGAUGE::GetFairyTime();
    if (INPUTMANAGER::GetKey(DIK_H, TRIGGER))
    {

    }
    if (Gray)
    {
        Model->SetSpeed(0.0);
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        return;
    }
    else
    {
        Model->SetSpeed(1.0);
        INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, vecVibration.x, vecVibration.y);
    }

    //---�o�C�u���[�V����---//
    if (--Vibration <= 0)
    {
        INPUTMANAGER::StopGamePadVibration(GAMEPADNUMBER_1P);
        vecVibration = D3DXVECTOR2(0.0F, 0.0F);
        Vibration = 0;
    }

    //---�ړ�����---//
	//�J�����̌����擾
    vecCameraRotation = SIDEVIEWCAMERA::GetRotation();
    vecStickVector = INPUTMANAGER::GetGamePadStick(GAMEPADNUMBER_1P, GAMEPADDIRECTION_LEFT);

	//�d�͉��Z
	Move.y -= GRAVITY;

    //���n����
    if (FIELD::CheckField(&D3DXVECTOR3(Transform.Position.x, Transform.Position.y - 5.0F, Transform.Position.z), &D3DXVECTOR3(0.0F, 1.0F, 0.0F), fAfterYPosition))
    {
        Transform.Position.y = fAfterYPosition + 5.0F;
        Move.y = 0.0F;
    }

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
	Collision->Position = Transform.Position;

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
        vecInstancePosition.x = Transform.Position.x + sinf(D3DXToRadian(Transform.Rotation.y)) + cosf(D3DXToRadian(Transform.Rotation.y));
        vecInstancePosition.y = Transform.Position.y + 10.0F;
        vecInstancePosition.z = 0.0F;

        SKILLFACTORY::InstantiateSkill(WORDMENU::NotificationAdjective(), WORDMENU::NotificationNoun(), vecInstancePosition, Transform.Rotation);
        EFFECTFACTORY::InstantiateSkillEffect(vecInstancePosition, D3DXVECTOR2(10.0F, 10.0F), false);
        vecVibration = D3DXVECTOR2(0.5F, 0.5F);
        INPUTMANAGER::PlayGamePadVibration(GAMEPADNUMBER_1P, vecVibration.x, vecVibration.y);
        Vibration = 100;
    }

    hp = HP;
    pos = Transform.Position;
    rot = Transform.Rotation;

    if (Move.x)
    {
        State = STATE_WALK;
    }
    else
    {
        State = STATE_WAIT;
    }

    if (Move.y != 0.0F)
    {
        State = STATE_WAIT;
    }
    Model->ChangeAnimation(State);

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

// ���f���ʒu�̎擾
D3DXVECTOR3 PLAYER::GetPlayerPosition(void)
{
	return pos;
}

// ���f�������̎擾
D3DXVECTOR3 PLAYER::GetPlayerRotation(void)
{
	return rot;
}