//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Skill.h"
#include "Slime.h"
#include "Sphere.h"

//�������萔�E�}�N����`������//
#define VISIBILITY 50.0F

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FSLIME
//
//�@�\�F�R���X�g���N�^
//
//�����F(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
SLIME::SLIME(tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(tag, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~SLIME
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
SLIME::~SLIME(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�G�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SLIME::Draw(void)
{
    //---�e��錾---//
    D3DXMATRIX mtxWorld;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);

    //---�`��---//
    Model->Draw(mtxWorld, false);

    //ENEMY::Draw();
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�G�̏�����
//
//�����F(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT SLIME::Initialize(tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    //�����ݒ�
    hResult = ENEMY::Initialize(TEXT("SLIME"), tag, position, rotation, D3DXVECTOR3(450.0F, 450.0F, 450.0F));
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�X���C���̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    InitialPosition = Transform.Position;
    Move = D3DXVECTOR3(1.0F, 0.0F, 0.0F);

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
void SLIME::OnCollision(COLLISION* opponent)
{
    SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
    if (Skill)
    {
        if (Skill->GetType() == TEXT("COLD"))
        {
            ACTORMANAGER::Destroy(this);
            COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        }
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�G�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SLIME::Uninitialize(void)
{
    //---�J��---//
    ENEMY::Uninitialize();
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�G�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void SLIME::Update(void)
{
    //---�e��錾---//
    D3DXVECTOR3 PlayerPosition;
    static int nStopCount;	//�[�ŏ����~�܂�p
    static int nAttackCount;

    //---����������---//
    PlayerPosition = PLAYER::GetPlayerPosition();
    Transform.Position += Move;

    switch (State)
    {
        case SLIMESTATE_MOVE:
            //---�p�j---//
            if (fabsf(Transform.Position.x - InitialPosition.x) >= 100.0F)
            {
                //2�b�~�܂�
                if (++nStopCount > 120)
                {
                    Transform.Rotation.y = -Transform.Rotation.y;
                    Move.x = -Move.x;
                    nStopCount = 0;
                }
            }

            //---�G�̍��G---//
            if (ENEMY::SearchTarget(PlayerPosition, VISIBILITY))
            {
                if (AttackCool)
                {
                    --AttackCool;
                }
                else
                {
                    State = SLIMESTATE_ATTACK;
                }
            }
            break;

        case SLIMESTATE_ATTACK:
            //---�������Ȃ�U���A�����łȂ���Μp�j���ĊJ����---//
            Move.x = 0.0F;
            Model->ChangeAnimation(SLIMESTATE_ATTACK);
            if (++nAttackCount > 60)
            {
                //�U��

                Model->ChangeAnimation(SLIMESTATE_MOVE);
                AttackCool = 120;
                State = SLIMESTATE_MOVE;
            }
            break;

            default:
                break;
    }

    ENEMY::Update();
}