//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ModelManager.h"
#include "SquareGauge.h"
#include "Wall.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FWALL
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
WALL::WALL(LPCTSTR modelname, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, type, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~WALL
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
WALL::~WALL(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�ǂ̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WALL::Draw(void)
{
    BillBoard.Draw(Transform.Position);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�ǂ̏�����
//
//�����F(LPCTSTR)�e�N�X�`����,(tstirng)��������,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT WALL::Initialize(LPCTSTR texturename, tstring type, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
    Transform.Position = position;
    Transform.Rotation = rotation;
    BornTime = 0;
    //---�r���{�[�h�̍쐬---//
    hResult = BillBoard.Initialize(texturename, D3DXVECTOR2(50.0F, 50.0F), Transform.Rotation.y > 0.0F);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�ǂ̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return hResult;
    }


    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 3.5F, TEXT("Wall"), this);

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
void WALL::OnCollision(COLLISION* opponent)
{

}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�ǂ̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WALL::Uninitialize(void)
{
    //---�J��---//
    BillBoard.Uninitialize();
    if (Collision)
    {
        COLLISIONMANAGER::Destroy((COLLISION*)Collision);
        Collision = nullptr;
    }
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�ǂ̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void WALL::Update(void)
{
	Gray = SQUAREGAUGE::GetFairyTime();
    if (Gray)
    {
        return;
    }

    if (++BornTime > 60)
    {
        ACTORMANAGER::Destroy(this);
    }
    BillBoard.Update();
}