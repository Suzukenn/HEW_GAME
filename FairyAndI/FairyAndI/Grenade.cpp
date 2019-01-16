//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "Grenade.h"
#include "InputManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Sphere.h"
#include "Player.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FGRENADE
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
GRENADE::GRENADE(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	Initialize(modelname, tag, position, rotation);
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
GRENADE::~GRENADE()
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
void GRENADE::Draw(void)
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
	D3DXMatrixRotationYawPitchRoll(&mtxRotation, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotation);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//---�`��---//
	//�`��Ώۃ`�F�b�N
	pModel = Model.lock();
	if (!pModel)
	{
		MessageBox(nullptr, TEXT("�e�ۂ̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
//�@�\�F�e�ۂ̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GRENADE::Initialize(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---�e��錾---//
	HRESULT hResult;

	//---����������---//
	Position = position;
	Rotation = rotation;
	BornTime = 0;
	Move = D3DXVECTOR3(-sinf(Rotation.y) * 1.5F, 3.0F, -cosf(Rotation.y) * 1.5F);
	Tag = tag;

	//---���f���̓ǂݍ���---//
	hResult = MODELMANAGER::GetModel(modelname, Model);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("�֒e�̃��f���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		Uninitialize();
		return hResult;
	}

	//---�����蔻��̕t�^---//
	Collision = COLLISIONMANAGER::InstantiateToSphere(Position, 3.5F, TEXT("Skill"), this);

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
//�@�\�F�e�ۂ̍X�V
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
	}
	else
	{
		Move.y += 0.5F;
		Position += Move;
		Collision->Position = Position;
	}
}