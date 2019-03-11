//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Skill.h"
#include "Sphere.h"
#include "Wood.h"

//�������萔�E�}�N����`������//
#define VISIBILITY 50.0F

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FWOOD
//
//�@�\�F�R���X�g���N�^
//
//�����F(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
WOOD::WOOD(tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(tag, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~WOOD
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
WOOD::~WOOD(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�؂̃I�o�P�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WOOD::Draw(void)
{
    ENEMY::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�؂̃I�o�P�̏�����
//
//�����F(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WOOD::Initialize(tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    hResult = ENEMY::Initialize(TEXT("WOOD"), tag, position, rotation, D3DXVECTOR3(300.0F, 300.0F, 300.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�؂̃I�o�P�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    State = WOODSTATE_WAIT;

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Character"), this);

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
void WOOD::OnCollision(COLLISION* opponent)
{
    SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
    if (Skill)
    {
        if (Skill->GetType() == TEXT("HOT") || Skill->GetType() == TEXT("COLD"))
        {
            ACTORMANAGER::Destroy(this);
            COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        }
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�؂̃I�o�P�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WOOD::Uninitialize(void)
{
    //---�J��---//
    ENEMY::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�؂̃I�o�P�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WOOD::Update(void)
{
    //---�e��錾---//
    D3DXVECTOR3 PlayerPosition;
    static int nAttackCount;

    //---����������---//
    PlayerPosition = PLAYER::GetPlayerPosition();

    switch (State)
    {
        case WOODSTATE_WAIT:

            if (AttackCool)
            {
                --AttackCool;
            }

            //---�G�̍��G---//
            if (ENEMY::SearchTarget(PlayerPosition, VISIBILITY))
            {
                if (!AttackCool)
                {
                    State = WOODSTATE_ATTACK;
                }
            }
            break;

        case WOODSTATE_ATTACK:
            Model->ChangeAnimation(WOODSTATE_ATTACK);
            if (++nAttackCount > 60)
            {
                //�U��
            
                Model->ChangeAnimation(WOODSTATE_WAIT);
                AttackCool = 120;
                State = WOODSTATE_WAIT;
            }
            break;

        default:
            break;
    }

    ENEMY::Update();
}