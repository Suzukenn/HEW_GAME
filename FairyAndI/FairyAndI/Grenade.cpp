//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "Grenade.h"
#include "InputManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Sphere.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FGRENADE
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
GRENADE::GRENADE(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~GRENADE
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
GRENADE::~GRENADE(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�֒e�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GRENADE::Draw(void)
{
    //---�e��錾---//
    D3DXMATRIX mtxWorld;

    std::shared_ptr<MODEL> pModel;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);
    GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

    //---�`��---//
    //�`��Ώۃ`�F�b�N
    pModel = Model.lock();
    if (!pModel)
    {
        MessageBox(nullptr, TEXT("�֒e�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        return;
    }

    //�`��
    pModel->Draw(Gray);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�֒e�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GRENADE::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---�e��錾---//
	HRESULT hResult;

	//---����������---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	BornTime = 0;
	Move = D3DXVECTOR3(sinf(Transform.Rotation.y) * 1.5F, 3.0F, 0.0F);//-cosf(Transform.Rotation.y) * 1.5F);
	Throw = true;
	Tag = TEXT("Grenade");
    Type = type;

	//---���f���̓ǂݍ���---//
	hResult = MODELMANAGER::GetModel(modelname, Model);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�֒e�̃��f���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
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
void GRENADE::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag().find(TEXT("Player")) != tstring::npos)
	{
		return;
	}

	ACTORMANAGER::Destroy(this);
	COLLISIONMANAGER::Destroy((COLLISION*)Collision);
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�֒e�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GRENADE::Uninitialize(void)
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
//�@�\�F�֒e�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GRENADE::Update(void)
{
	++BornTime;
	if (BornTime > 120)
	{
		ACTORMANAGER::Destroy(this);
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
		Throw = true;
	}
	else if (Throw)
	{
		Move.y += 0.5F;
		Throw = false;
	}
	else
	{
		Move.y -= 0.1F;		//�֒e�ɏd�͂����Z
        Transform.Position += Move;
		Collision->Position = Transform.Position;
	}
}