//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Skill.h"
#include "SquareGauge.h"
#include "WoodGimmick.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FWOODGIMMICK
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
WOODGIMMICK::WOODGIMMICK(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
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
WOODGIMMICK::~WOODGIMMICK(void)
{
	Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F����M�~�b�N�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WOODGIMMICK::Draw(void)
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
        MessageBox(nullptr, TEXT("����M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        return;
    }

    //�`��
    pModel->Draw(Shader, TEXT("NonTextureModel"), (UINT)Gray, mtxWorld);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F����M�~�b�N�̏�����
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WOODGIMMICK::Initialize(LPCTSTR modelfile, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(500.0F, 500.0F, 500.0F);
    Gray = false;
    Small = false;
	Tag = TEXT("WoodGimmick");

    //---���f���̓ǂݍ���---//
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("����M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�V�F�[�_�[�̎擾---//
    hResult = SHADERMANAGER::GetShader(TEXT("MODEL"), Shader);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("����M�~�b�N�`��p�̃V�F�[�_�[�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 5.0F, TEXT("Gimmick"), this);

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
void WOODGIMMICK::OnCollision(COLLISION* opponent)
{
    if (opponent->Owner->GetTag() == TEXT("Grenade"))
    {
        Small = true;
    }
    else
    {
        SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
        if (Skill)
        {
            if (Skill->GetType() == TEXT("HOT"))
            {
                Small = true;
            }
        }
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F����M�~�b�N�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WOODGIMMICK::Uninitialize(void)
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
//�@�\�F����M�~�b�N�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WOODGIMMICK::Update(void)
{	
    Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }

    if (Small)
    {
        Transform.Scale.x -= 5.0F;
        Transform.Scale.y -= 5.0F;
        Transform.Scale.z -= 5.0F;
        if (Transform.Scale.x < 0.0F)
        {
            ACTORMANAGER::Destroy(this);
            COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        }
    }
}