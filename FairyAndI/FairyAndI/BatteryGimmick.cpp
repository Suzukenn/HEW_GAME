//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "BatteryGimmick.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "GimmickFactory.h"
#include "ModelManager.h"
#include "Player.h"
#include "SkillFactory.h"

//�������萔�E�}�N����`������//

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBATTERYGIMMICK
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BATTERYGIMMICK::BATTERYGIMMICK(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~WOODGIMMICK
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BATTERYGIMMICK::~BATTERYGIMMICK()
{
	Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�C��M�~�b�N�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BATTERYGIMMICK::Draw(void)
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
		MessageBox(nullptr, TEXT("�C��M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
//�@�\�F�C��M�~�b�N�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BATTERYGIMMICK::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
	Position = position;
	Rotation = rotation;
	Tag = tag;

	//Model.reset(new MODEL);

    //X�t�@�C���̓ǂݍ���
	hResult = MODELMANAGER::GetModel(modelfile, Model);
    //hResult = D3DXLoadMeshFromX(TEXT("Data/Common/Model/Character/car001.x"), D3DXMESH_SYSTEMMEM, GetDevice(), nullptr, &MaterialBuffer, nullptr, &MaterialValue, &Mesh);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�C��M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�����蔻��̕t�^---//
	//Collision = COLLISIONMANAGER::InstantiateToOBB(Position, Rotation, TEXT("Object"), this);
	Collision = COLLISIONMANAGER::InstantiateToSphere(Position, 5.0F, TEXT("Object"), this);

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
void BATTERYGIMMICK::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag().find(TEXT("GimmickBullet")) != tstring::npos)
	{
		ACTORMANAGER::Destroy(this);
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�C��M�~�b�N�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BATTERYGIMMICK::Uninitialize(void)
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
//�@�\�F�C��M�~�b�N�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BATTERYGIMMICK::Update(void)
{	
	static int Count;	//�e���o���Ԋu�b��
	D3DXVECTOR3 BulletPosition = D3DXVECTOR3(0.0F, 20.0F, 0.0F);

	//2�b�o������
	if (++Count > 120)
	{
		if (PLAYER::GetPlayerPosition().x < Position.x)
		{
			Rotation.y = D3DX_PI * 0.50F;
			BulletPosition.x = Position.x - 10.0F;
		}
		else if (PLAYER::GetPlayerPosition().x > Position.x)
		{
			Rotation.y = -(D3DX_PI * 0.50f);
			BulletPosition.x = Position.x + 10.0F;
		}

		//�e����
		GIMMICKFACTORY::InstantiateGimmick(TEXT("ICE"), BulletPosition, Rotation);
		//���Z�b�g
		Count = 0;
	}
}

/////////////////////////////////////////////
//�֐����FGetPos
//
//�@�\�F�C��M�~�b�N�̈ʒu���擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
D3DXVECTOR3 BATTERYGIMMICK::GetPos(void)
{
	return Position;
}