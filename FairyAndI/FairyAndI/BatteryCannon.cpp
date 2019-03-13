//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "BatteryCannon.h"
#include "CollisionManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Skill.h"
#include "Sphere.h"
#include "SquareGauge.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FBATTERYCANNON
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BATTERYCANNON::BATTERYCANNON(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~BATTERYCANNON
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
BATTERYCANNON::~BATTERYCANNON(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�C�e�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BATTERYCANNON::Draw(void)
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
        MessageBox(nullptr, TEXT("�C�e�M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        return;
    }

    //�`��
    pModel->Draw(Gray);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�C�e�̏�����
//
//�����F(LPCTSTR)���f����,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT BATTERYCANNON::Initialize(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    BornTime = 0;
    Move = D3DXVECTOR3(sinf(Transform.Rotation.y) * 1.5F, 0.0F, 0.0F);
    Tag = TEXT("BatteryCannon");

    //---���f���̓ǂݍ���---//
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�C�e�̃��f���̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.5F, TEXT("BatteryCannon"), this);

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
void BATTERYCANNON::OnCollision(COLLISION* opponent)
{
    //���˕Ԃ�������
    if (opponent->Owner->GetTag() == TEXT("Wall"))
    {
        SKILL* Skill = dynamic_cast<SKILL*>(opponent->Owner);
        if (Skill)
        {
            if (Skill->GetType() == TEXT("SOFT"))
            {
                Move.x = -Move.x;
            }
        }
    }
    else
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�C�e�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BATTERYCANNON::Uninitialize(void)
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
//�@�\�F�C�e�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void BATTERYCANNON::Update(void)
{
	Gray = SQUAREGAUGE::GetFairyTime();

    if (Gray)
    {
        return;
    }

    ++BornTime;
    if (BornTime > 120)
    {
        ACTORMANAGER::Destroy(this);
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
    else
    {
        Transform.Position += Move;
        Collision->Position = Transform.Position;
    }
}