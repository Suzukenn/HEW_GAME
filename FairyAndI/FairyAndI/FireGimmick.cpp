//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "FireGimmick.h"
#include "ModelManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FFIREGIMMICK
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
FIREGIMMICK::FIREGIMMICK(LPCTSTR modelname, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, tag, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~FIREGIMMICK
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
FIREGIMMICK::~FIREGIMMICK()
{
	Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F���̕ǃM�~�b�N�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FIREGIMMICK::Draw(void)
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
        MessageBox(nullptr, TEXT("���̕ǃM�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
//�@�\�F���̕ǃM�~�b�N�̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�O,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT FIREGIMMICK::Initialize(LPCTSTR modelfile, tstring tag, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	//�����ݒ�
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	Tag = tag;

	//Model.reset(new MODEL);

    //X�t�@�C���̓ǂݍ���
	hResult = MODELMANAGER::GetModel(modelfile, Model);
    if (FAILED(hResult))
	{
        MessageBox(nullptr, TEXT("���̕ǃM�~�b�N�̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
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
void FIREGIMMICK::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag().find(TEXT("HotIce")) != tstring::npos ||
		opponent->Owner->GetTag().find(TEXT("SoftIce")) != tstring::npos)
	{
		ACTORMANAGER::Destroy(this);
		COLLISIONMANAGER::Destroy((COLLISION*)Collision);
    }
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F���̕ǃM�~�b�N�̏I��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FIREGIMMICK::Uninitialize(void)
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
//�@�\�F���̕ǃM�~�b�N�̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void FIREGIMMICK::Update(void)
{	

}

/////////////////////////////////////////////
//�֐����FGetPos
//
//�@�\�F���̕ǃM�~�b�N�̈ʒu���擾
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
D3DXVECTOR3 FIREGIMMICK::GetPos(void)
{
	return Transform.Position;
}