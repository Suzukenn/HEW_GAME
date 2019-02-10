//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "ModelManager.h"
#include "Player.h"
#include "Skill.h"
#include "Sphere.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FENEMY
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ENEMY::ENEMY(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~ENEMY
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ENEMY::~ENEMY()
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
void ENEMY::Draw(void)
{
    //---�e��錾---//
    DWORD nCounter;
    LPDIRECT3DDEVICE9 pDevice;
    D3DXMATRIX mtxRotation;
    D3DXMATRIX mtxTranslate;
    D3DXMATRIX mtxWorld;
    LPD3DXMATERIAL pMatrix;
    D3DMATERIAL9 matDef;

    std::shared_ptr<MODEL> pModel;

    //---����������---//
    pDevice = GetDevice();

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //��]�𔽉f
    Transform.MakeWorldMatrix(mtxWorld);

    //---�`��---//
    //�`��Ώۃ`�F�b�N
    pModel = Model.lock();
    if (!pModel)
    {
        MessageBox(nullptr, TEXT("�G�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return;
    }

    // ���݂̃}�e���A�����擾
    pDevice->GetMaterial(&matDef);

    //�|�C���^���擾
    pMatrix = (LPD3DXMATERIAL)pModel->MaterialBuffer->GetBufferPointer();

    for (nCounter = 0; nCounter < pModel->MaterialValue; ++nCounter)
    {
        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMatrix[nCounter].MatD3D);

        //�e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, *pModel->Texture);

        //�`��
        pModel->Mesh->DrawSubset(nCounter);
    }

    //�}�e���A�����f�t�H���g�ɖ߂�
    pDevice->SetMaterial(&matDef);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�G�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ENEMY::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
	Transform.Position = InitialPosition = position;
	Transform.Rotation = rotation;
	Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Tag = tag;
	Move = D3DXVECTOR3(1.0F, 0.0F, 0.0F);
	StateType = ENEMYSTATE_NORMAL;

    //X�t�@�C���̓ǂݍ���
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�G�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�����蔻��̕t�^---//
	//Collision = COLLISIONMANAGER::InstantiateToOBB(Position, Rotation, TEXT("Character"), this);
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
void ENEMY::OnCollision(COLLISION* opponent)
{
	if (Tag == TEXT("Plant"))
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
	else if (Tag == TEXT("Slime"))
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
    if (Model._Get())
    {
        Model.reset();
    }
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
	static int Count;	//�[�ŏ����~�܂�p

	Transform.Position += Move;

	switch (StateType)
	{
	//===�G�̒ʏ펞�̍s��===//
	case ENEMYSTATE_NORMAL:
		//===�G�̒ʏ�ړ�===//
		if (Transform.Position.x > InitialPosition.x + 50.0F ||
			Transform.Position.x < InitialPosition.x - 50.0F)
		{
			if (Transform.Position.x > InitialPosition.x + 50.0F)
			{
				Transform.Position.x = InitialPosition.x + 50.0F;
			}
			else if (Transform.Position.x < InitialPosition.x - 50.0F)
			{
				Transform.Position.x = InitialPosition.x - 50.0F;
			}

			//�Q�b�~�܂�
			if (++Count > 120)
			{
				Transform.Rotation.y *= -1;
				Move.x *= -1;
				Count = 0;
			}
		}
		//===�G�̍��G===//
		//�͈͓������E�ɓ�������i�H�j�퓬�Ԑ���
		if (PLAYER::GetPlayerPosition().x > Transform.Position.x - 50.0F &&
			PLAYER::GetPlayerPosition().x < Transform.Position.x + 50.0F)
		{
			if (PLAYER::GetPlayerPosition().x > Transform.Position.x && Transform.Rotation.y > 0.0F ||
				PLAYER::GetPlayerPosition().x < Transform.Position.x &&Transform.Rotation.y < 0.0F)
			{
				StateType = ENEMYSTATE_BATTLE;
			}
		}
		break;
	
		//===�G�̐퓬�Ԑ����̍s��===//
	case ENEMYSTATE_BATTLE:
		//===�G�̐퓬���̈ړ�===//
		if (PLAYER::GetPlayerPosition().x - 10.0F <Transform.Position.x &&
			PLAYER::GetPlayerPosition().x + 10.0F > Transform.Position.x)
		{
			Move.x = 0.0F;
			//�ߋ����U���Ȃ炱���Ő錾����
		}
		else if (PLAYER::GetPlayerPosition().x < Transform.Position.x)
		{
			Move.x = -1.0F;
			Transform.Rotation.y = -180.0F;
		}
		else if (PLAYER::GetPlayerPosition().x > Transform.Position.x)
		{
			Move.x = 1.0F;
			Transform.Rotation.y = 180.0F;
		}

		//===���G�͈͊O�Ȃ�==//
		if (PLAYER::GetPlayerPosition().x < Transform.Position.x - 50.0F ||
			PLAYER::GetPlayerPosition().x > Transform.Position.x + 50.0F)
		{
			if (InitialPosition.x + 50.0F < Transform.Position.x ||
				InitialPosition.x - 50.0F > Transform.Position.x)
			{
				StateType = ENEMYSTATE_RETURN;
			}
			else
			{
				StateType = ENEMYSTATE_NORMAL;
			}
		}
		break;

	//===���̈ʒu�ɖ߂�܂�===//
	case ENEMYSTATE_RETURN:

		if (InitialPosition.x < Transform.Position.x)
		{
			Move.x = -1.0F;
			Transform.Rotation.y = -180.0F;
		}
		else if (InitialPosition.x > Transform.Position.x)
		{
			Move.x = 1.0F;
			Transform.Rotation.y = 180.0F;
		}

		//�߂��Ă�Œ��Ƀv���C���[����������
		if (PLAYER::GetPlayerPosition().x > Transform.Position.x && Transform.Rotation.y > 0.0F ||
			PLAYER::GetPlayerPosition().x < Transform.Position.x && Transform.Rotation.y < 0.0F)
		{
			StateType = ENEMYSTATE_BATTLE;
		}
		//�v���C���[�������������ʒu�܂ŗ�����
		else if (InitialPosition.x + 50.0F > Transform.Position.x &&
			InitialPosition.x - 50.0F < Transform.Position.x)
		{
			StateType = ENEMYSTATE_NORMAL;
		}
		break;

	default:
		break;
	}

	Collision->Position = Transform.Position;
}

/////////////////////////////////////////////
//�֐����FGetPos
//
//�@�\�F�G�̈ʒu���擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
D3DXVECTOR3 ENEMY::GetPos(void)
{
	return Transform.Position;
}