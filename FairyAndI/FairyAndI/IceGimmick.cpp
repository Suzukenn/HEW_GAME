//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "IceGimmick.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "SquareGauge.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FICEGIMMICK
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ICEGIMMICK::ICEGIMMICK(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~ICEGIMMICK
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
ICEGIMMICK::~ICEGIMMICK(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�X�̕ǃM�~�b�N�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ICEGIMMICK::Draw(void)
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
        MessageBox(nullptr, TEXT("�X�̕ǂ̃M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return;
    }

    //�`��
    pModel->Draw(Gray);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�X�̕ǃM�~�b�N�̏�����
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT ICEGIMMICK::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Gray = false;
    Tag = TEXT("Gimmick");

    //---���f���̓ǂݍ���---//
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�X�ǃM�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToOBB(Transform.Position, D3DXVECTOR3(3.0F, 3.0F, 3.0F), TEXT("Object"), this);

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
void ICEGIMMICK::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag().find(TEXT("Hot")) != tstring::npos)
	{
		ACTORMANAGER::Destroy(this);
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�X�̕ǃM�~�b�N�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ICEGIMMICK::Uninitialize(void)
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
//�@�\�F�X�̕ǃM�~�b�N�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void ICEGIMMICK::Update(void)
{	
   /* if (INPUTMANAGER::GetGamePadButton(GAMEPADNUMBER_1P, XINPUT_GAMEPAD_Y, TRIGGER))
    {
        Gray = !Gray;
    }*/
	Gray = SQUAREGAUGE::GetFairyTime();
}