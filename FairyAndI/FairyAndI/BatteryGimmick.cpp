//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "BatteryGimmick.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "ModelManager.h"
#include "Player.h"
#include "Skill.h"
#include "SkillFactory.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBATTERYGIMMICK
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BATTERYGIMMICK::BATTERYGIMMICK(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
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
BATTERYGIMMICK::~BATTERYGIMMICK(void)
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
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BATTERYGIMMICK::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Tag = TEXT("Battery");

    //X�t�@�C���̓ǂݍ���
	hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�C��M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�����蔻��̕t�^---//
	//Collision = COLLISIONMANAGER::InstantiateToOBB(Position, Rotation, TEXT("Object"), this);
	Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Object"), this);

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
    if (opponent->Owner->GetTag() == TEXT("Bullet"))
    {
        SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
        if (Skill)
        {
            if (Skill->GetType() == TEXT("RETURN"))
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
	D3DXVECTOR3 BulletPosition = D3DXVECTOR3(0.0F, 10.0F, 0.0F);

	//2�b�o������
	if (++Count > 120)
	{
		if (PLAYER::GetPlayerPosition().x < Transform.Position.x)
		{
            Transform.Rotation.y = -(D3DX_PI * 0.50F);
			BulletPosition.x = Transform.Position.x - 10.0F;
		}
		else if (PLAYER::GetPlayerPosition().x > Transform.Position.x)
		{
            Transform.Rotation.y = D3DX_PI * 0.50F;
			BulletPosition.x = Transform.Position.x + 10.0F;
		}

		//�e����
		SKILLFACTORY::InstantiateSkill(TEXT("BATTERY"), TEXT("ICE"), BulletPosition, Transform.Rotation);
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
	return Transform.Position;
}