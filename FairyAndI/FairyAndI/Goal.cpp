//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include "ActorManager.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Fade.h"
#include "Goal.h"
#include "ModelManager.h"
#include "SceneManager.h"

//�������֐���`������//
/////////////////////////////////////////////
//�֐����FGOAL
//
//�@�\�F�R���X�g���N�^
//
//�����F(LPCTSTR)���f����,(tstirng)�^�C�v,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
GOAL::GOAL(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    Initialize(modelname, position, rotation);
}

/////////////////////////////////////////////
//�֐����F~GOAL
//
//�@�\�F�f�X�g���N�^
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
GOAL::~GOAL(void)
{
    Uninitialize();
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�S�[���̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GOAL::Draw(void)
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
//�@�\�F�S�[���̏�����
//
//�����F(LPCTSTR)���f����,(tstirng)�^�C�v,(D3DXVECTOR3)�ʒu,(D3DXVECTOR3)�傫��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT GOAL::Initialize(LPCTSTR modelname, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
    //---�e��錾---//
    HRESULT hResult;

    //---����������---//
	Goal = 0;
    // �ʒu�E�����̏����ݒ�
    Transform.Position = position;
    Transform.Rotation = rotation;
    Transform.Scale = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
    Tag = TEXT("Goal");

    // X�t�@�C���̓ǂݍ���
    hResult = MODELMANAGER::GetModel(modelname, Model);
    if (FAILED(hResult))
    {
        MessageBox(nullptr, TEXT("�S�[���̃��f�����̎擾�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        Uninitialize();
        return hResult;
    }

    //---�����蔻��̕t�^---//
    Collision = COLLISIONMANAGER::InstantiateToSphere(Transform.Position, 10.0F, TEXT("Object"), this);
    return hResult;
}

/////////////////////////////////////////////
//�֐����FOnCollision
//
//�@�\�F�����蔻�莞�̋���
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
void GOAL::OnCollision(COLLISION* opponent)
{
	if (opponent->Owner->GetTag() == TEXT("Player"))
	{
		Goal++;
	}
}

/////////////////////////////////////////////
//�֐����FUninitialize
//
//�@�\�F�S�[���̏I��
//
//�����F(LPCTSTR)���f���t�@�C����
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
void GOAL::Uninitialize(void)
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
//�@�\�F�S�[���̍X�V
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void GOAL::Update(void)
{
	if (Goal == 1)
	{
		FADE::SetFade(FADE_OUT);
	}
		if (FADE::CheckFadeEnd(FADE_OUT))
		{
			SCENEMANAGER::SetScene(SCENE_GAMECLEAR);
		}
}