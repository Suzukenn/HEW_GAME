//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "BatteryGimmick.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "GimmickFactory.h"
#include "ModelManager.h"
#include "Player.h"
#include "ShaderManager.h"
#include "SquareGauge.h"

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
    D3DXMATRIX mtxWorld;

    std::shared_ptr<MODEL> pModel;

    //---���[���h�}�g���N�X�̐ݒ�---//
    //������
    D3DXMatrixIdentity(&mtxWorld);

    //�ݒ�
    Transform.MakeWorldMatrix(mtxWorld);
    //GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);

    //---�`��---//
    //�`��Ώۃ`�F�b�N
    pModel = Model.lock();
    if (!pModel)
    {
        MessageBox(nullptr, TEXT("�C��M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�`��G���["), MB_OK);
        return;
    }

    //�`��
    pModel->Draw(Shader, TEXT("NonTextureModel"), (UINT)Gray, mtxWorld);

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
    Transform.Scale = D3DXVECTOR3(5.0F, 5.0F, 5.0F);
    Gray = false;
	Tag = TEXT("Battery");

    //---���f���̓ǂݍ���---//
    hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("�C��M�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
		return hResult;
	}

    //---�V�F�[�_�[�̎擾---//
    hResult = SHADERMANAGER::GetShader(TEXT("MODEL"), Shader);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�C��`��p�̃V�F�[�_�[�̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }


    //---�����蔻��̕t�^---//
	//Collision = COLLISIONMANAGER::InstantiateToOBB(Position, Rotation, TEXT("Object"), this);
	//Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Object"), this);

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
    if (opponent->Owner->GetTag() == TEXT("BatteryCannon"))
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
	D3DXVECTOR3 BulletPosition;

    Gray = SQUAREGAUGE::GetFairyTime();

    if (Gray)
    {
        return;
    }

    BulletPosition = Transform.Position;

	if (PLAYER::GetPlayerPosition().x < Transform.Position.x)
	{
        Transform.Rotation.y = -180.0F;
		BulletPosition.x = Transform.Position.x - 10.0F;
	}
	else if (PLAYER::GetPlayerPosition().x > Transform.Position.x)
	{
        Transform.Rotation.y += 180.0F;
		BulletPosition.x = Transform.Position.x + 10.0F;
	}

    //2�b�o������
    if (++Count > 120)
    {
		//�e����
		//GIMMICKFACTORY::InstantiateBatteryCannon(BulletPosition, Transform.Rotation);

		//���Z�b�g
		Count = 0;
	}
}