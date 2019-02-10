//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Sphere.h"
#include "Trap.h"
#include "Player.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FTRAP
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
TRAP::TRAP(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~TRAP
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
TRAP::~TRAP()
{
	Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F㩂̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TRAP::Draw(void)
{
	//---�e��錾---//
	DWORD nCounter;
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxWorld;
	LPD3DXMATERIAL pMatrix;
	D3DMATERIAL9 matDef;

	std::shared_ptr<MODEL> pModel;

	//---����������---//
	pDevice = GetDevice();

	//---���[���h�}�g���N�X�̐ݒ�---//
	//������
	D3DXMatrixIdentity(&mtxWorld);

	//�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);

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
//�@�\�F㩂̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT TRAP::Initialize(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	//---�e��錾---//
	HRESULT hResult;

	//---����������---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Tag = TEXT("Trap");
    Type = type;

	//---���f���̓ǂݍ���---//
	hResult = MODELMANAGER::GetModel(modelname, Model);
	if (FAILED(hResult))
	{
		MessageBox(nullptr, TEXT("㩂̃��f���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
void TRAP::OnCollision(COLLISION* opponent)
{
	//ACTORMANAGER::Destroy(this);
	//COLLISIONMANAGER::Destroy((COLLISION*)Collision);
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F㩂̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TRAP::Uninitialize(void)
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
//�@�\�F㩂̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void TRAP::Update(void)
{

}