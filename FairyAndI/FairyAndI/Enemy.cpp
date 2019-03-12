//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "AnimationModelManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Skill.h"
#include "Sphere.h"
#include "SquareGauge.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�G�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ENEMY::Draw(void)
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
//�@�\�F�G�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����,(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ENEMY::Initialize(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
	Transform.Position = position;
	Transform.Rotation = rotation;
    Transform.Scale = scale;
    AttackCool = 0;
    Gray = false;
	Tag = tag;
	//StateType = ENEMYSTATE_NORMAL;

    //X�t�@�C���̓ǂݍ���
    hResult = ANIMATIONMODELMANAGER::GetModel(modelname, Model);
    if (SUCCEEDED(hResult))
    {
        Model->ChangeAnimation(0);
    }
    else
	{
        MessageBox(nullptr, TEXT("�G�̃��f�����̎擾�Ɏ��s���܂���"), modelname, MB_OK);
        Uninitialize();
		return hResult;
	}

	return hResult;
}

/////////////////////////////////////////////
//�֐����FSearchTarget
//
//�@�\�F���G
//
//�����F(D3DXVECTOR3)�ڕW�ʒu,(float)����
//
//�߂�l�F(bool)���茋��
/////////////////////////////////////////////
bool ENEMY::SearchTarget(D3DXVECTOR3 target, float visibility)
{
    if (target.x < Transform.Position.x + visibility && target > Transform.Position)
    {
        if (Transform.Rotation.y == 90.0F)
        {
            return true;
        }
    }
    else if (target.x > Transform.Position.x - visibility && target < Transform.Position)
    {
        if (Transform.Rotation.y == 270.0F)
        {
            return true;
        }
    }

    return false;
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
void ENEMY::OnCollision(COLLISION* opponent)
{

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
void ENEMY::Uninitialize(void)
{
	//---�J��---//
    Model->Uninitialize();
    Model.reset();
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
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
void ENEMY::Update(void)
{	
	//static int Count;	//�[�ŏ����~�܂�p

	//Transform.Position += Move;

	//switch (StateType)
	//{
	//    //===�G�̒ʏ펞�̍s��===//
	//    case ENEMYSTATE_NORMAL:
	//	    //===�G�̒ʏ�ړ�===//
	//	    if (Transform.Position.x > InitialPosition.x + 50.0F ||
	//		    Transform.Position.x < InitialPosition.x - 50.0F)
	//	    {
	//		    if (Transform.Position.x > InitialPosition.x + 50.0F)
	//		    {
	//			    Transform.Position.x = InitialPosition.x + 50.0F;
	//		    }
	//		    else if (Transform.Position.x < InitialPosition.x - 50.0F)
	//		    {
	//			    Transform.Position.x = InitialPosition.x - 50.0F;
	//		    }

	//		    //2�b�~�܂�
	//		    if (++Count > 120)
	//		    {
	//			    Transform.Rotation.y *= -1;
	//			    Move.x *= -1;
	//			    Count = 0;
	//		    }
	//	    }
	//	    //===�G�̍��G===//
	//	    //�͈͓������E�ɓ�������i�H�j�퓬�Ԑ���
	//	    if (PLAYER::GetPlayerPosition().x > Transform.Position.x - 50.0F &&
	//		    PLAYER::GetPlayerPosition().x < Transform.Position.x + 50.0F)
	//	    {
	//		    if (PLAYER::GetPlayerPosition().x > Transform.Position.x && Transform.Rotation.y > 0.0F ||
	//			    PLAYER::GetPlayerPosition().x < Transform.Position.x &&Transform.Rotation.y < 0.0F)
	//		    {
	//			    StateType = ENEMYSTATE_BATTLE;
	//		    }
	//	    }
	//	    break;
	//
	//	    //===�G�̐퓬�Ԑ����̍s��===//
	//    case ENEMYSTATE_BATTLE:
	//	    //===�G�̐퓬���̈ړ�===//
	//	    if (PLAYER::GetPlayerPosition().x - 10.0F <Transform.Position.x &&
	//		    PLAYER::GetPlayerPosition().x + 10.0F > Transform.Position.x)
	//	    {
	//		    Move.x = 0.0F;
	//		    //�ߋ����U���Ȃ炱���Ő錾����
	//	    }
	//	    else if (PLAYER::GetPlayerPosition().x < Transform.Position.x)
	//	    {
	//		    Move.x = -1.0F;
	//		    Transform.Rotation.y = -180.0F;
	//	    }
	//	    else if (PLAYER::GetPlayerPosition().x > Transform.Position.x)
	//	    {
	//		    Move.x = 1.0F;
	//		    Transform.Rotation.y = 180.0F;
	//	    }

	//	    //===���G�͈͊O�Ȃ�==//
	//	    if (PLAYER::GetPlayerPosition().x < Transform.Position.x - 50.0F ||
	//		    PLAYER::GetPlayerPosition().x > Transform.Position.x + 50.0F)
	//	    {
	//		    if (InitialPosition.x + 50.0F < Transform.Position.x ||
	//			    InitialPosition.x - 50.0F > Transform.Position.x)
	//		    {
	//			    StateType = ENEMYSTATE_RETURN;
	//		    }
	//		    else
	//		    {
	//			    StateType = ENEMYSTATE_NORMAL;
	//		    }
	//	    }
	//	    break;

	//    //===���̈ʒu�ɖ߂�܂�===//
	//    case ENEMYSTATE_RETURN:

	//	    if (InitialPosition.x < Transform.Position.x)
	//	    {
	//		    Move.x = -1.0F;
	//		    Transform.Rotation.y = -180.0F;
	//	    }
	//	    else if (InitialPosition.x > Transform.Position.x)
	//	    {
	//		    Move.x = 1.0F;
	//		    Transform.Rotation.y = 180.0F;
	//	    }

	//	    //�߂��Ă�Œ��Ƀv���C���[����������
	//	    if (PLAYER::GetPlayerPosition().x > Transform.Position.x && Transform.Rotation.y > 0.0F ||
	//		    PLAYER::GetPlayerPosition().x < Transform.Position.x && Transform.Rotation.y < 0.0F)
	//	    {
	//		    StateType = ENEMYSTATE_BATTLE;
	//	    }
	//	    //�v���C���[�������������ʒu�܂ŗ�����
	//	    else if (InitialPosition.x + 50.0F > Transform.Position.x &&
	//		    InitialPosition.x - 50.0F < Transform.Position.x)
	//	    {
	//		    StateType = ENEMYSTATE_NORMAL;
	//	    }
	//	    break;

	//    default:
	//	    break;
	//}

    Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }
}