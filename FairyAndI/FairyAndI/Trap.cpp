//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Player.h"
#include "Sphere.h"
#include "SquareGauge.h"
#include "Trap.h"

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
TRAP::~TRAP(void)
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
		MessageBox(nullptr, TEXT("㩂̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
		return;
	}

    //�`��
    pModel->Draw(Gray);
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
    Gray = false;
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
    /*if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/

	Gray = SQUAREGAUGE::GetFairyTime();
}